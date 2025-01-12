/* Copyright 2024 Kim Hollstein (WiggelMc)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "action.h"
#include "chorder_logic.h"
#include "state_logic.h"
#include "keymap_logic.h"
#include "quantum.h"
#include QMK_KEYBOARD_H

state_t state;

void process_function_initial(bool (*function)(uint16_t code, state_t *state)) {
    bool done = function(0, &state);

    if (done) {
        init_function_state(&state.chord_state.function_state);
        reset_unlocked_flags(&state.chord_state.flags);
    } else {
        state.chord_state.function_state.running = function;
    }
}

void cancel(void) {
    init_flags(&state.chord_state.flags);
    init_function_state(&state.chord_state.function_state);
}

void process_function(uint16_t code, bool (*function)(uint16_t code, state_t *state)) {
    bool done = state.chord_state.function_state.running(state.active_codes, &state);

    if (done) {
        bool (*f)(uint16_t code, state_t *state) = state.chord_state.function_state.running;
        init_function_state(&state.chord_state.function_state);

        if (state.chord_state.flags.normal.function_lock) {
            process_function_initial(f);
        } else {
            reset_unlocked_flags(&state.chord_state.flags);
        }
    }
}

void handle_chord_mode(uint16_t code, bool pressed) {
    if (pressed) {
        state.chord_state.current_phase = PHASE_PRESS;
        state.active_codes |= ((uint16_t)1 << code);
    } else {
        if (state.chord_state.current_phase == PHASE_PRESS) {
            if (state.active_codes == noop_code) {
                // Do Nothing
            } else if (state.active_codes == cancel_code) {
                cancel();
            } else if (state.chord_state.function_state.running == NULL) {
                process_chord(state.active_codes, state.chord_state.flags.normal.layer);
            } else {
                process_function(state.active_codes, state.chord_state.function_state.running);
            }
        }
        state.chord_state.current_phase = PHASE_IDLE;
        state.active_codes &= ~((uint16_t)1 << code);
    }
}

void handle_reset(void) {
    // TODO: Release all HOLD keys
    init_state(&state);
}

void handle_direct_key_mode(uint16_t code, bool pressed) {
    uint8_t direct_key_index = state.direct_key_state.active_index;

    if (direct_key_index < direct_key_keymap_count) {
        uint16_t key = pgm_read_word(&direct_key_keymap[direct_key_index][code]);
        if (pressed) {
            register_code16(key);
        } else {
            unregister_code16(key);
        }
    }
}

void handle_input(uint16_t code, bool pressed) {
    switch (state.current_mode) {
        case MODE_CHORD:
            handle_chord_mode(code, pressed);
            break;
        case MODE_DIRECT_INPUT:
            handle_direct_key_mode(code, pressed);
            break;
    }
}

bool process_chorder_logic(uint16_t keycode, keyrecord_t *record) {
    if (keycode >= MCH_0 && keycode <= MCH_9) {
        handle_input(keycode - MCH_0, record->event.pressed);
        return false;

    } else if (keycode == MCH_R) {
        if (record->event.pressed) {
            handle_reset();
        }
        return false;
    }

    return true;
}

void send_key(uint16_t keycode, modifiers_t modifiers) {
    if (keycode != 0) {
        uint16_t modified_code = ((modifiers | state.chord_state.flags.normal.modifiers) << 8) | keycode;
        switch (state.chord_state.flags.normal.hold_mode) {
            case HOLD_OFF:
                // tap CODE and all CODES from HOLD_ONCE list, clear HOLD_ONCE list
                tap_code16(modified_code);
                break;
            case HOLD_PRESS:
                // ADD CODE to HOLD list and register
                register_code16(modified_code);
                break;
            case HOLD_RELEASE:
                // REMOVE CODE from HOLD and HOLD_ONCE list and unregister
                unregister_code16(modified_code);
                break;
            case HOLD_ONCE:
                // ADD CODE to HOLD_ONCE list

                // TODO: Handle Hold
                //  Store held keys in arrays: HOLD, HOLD_ONCE of type uint16_t with length 32 each
                break;
        }
    }

    reset_unlocked_flags(&state.chord_state.flags);
}

void handle_flag_modifier(modifiers_t modifier) {
    if (state.chord_state.flags.flag.flag_lock) {
        state.chord_state.flags.normal.locked_modifiers |= modifier;
    }
    state.chord_state.flags.normal.modifiers |= modifier;
}

void handle_flag_layer(uint8_t layer) {
    if (state.chord_state.flags.flag.flag_lock) {
        state.chord_state.flags.normal.locked_layer = true;
    }
    state.chord_state.flags.normal.layer = layer;
}

void handle_flag_hold(hold_mode_t hold_mode) {
    if (state.chord_state.flags.flag.flag_lock) {
        state.chord_state.flags.normal.locked_hold_mode = true;
    }
    state.chord_state.flags.normal.hold_mode = hold_mode;
}

bool handle_flag(uint16_t control_code) {
    switch (control_code) {
        case CC_FLAG_MOD_META:
            handle_flag_modifier(M_L_META);
            break;
        case CC_FLAG_MOD_CTRL:
            handle_flag_modifier(M_L_CTRL);
            break;
        case CC_FLAG_MOD_SHIFT:
            handle_flag_modifier(M_L_SHIFT);
            break;
        case CC_FLAG_MOD_ALT:
            handle_flag_modifier(M_L_ALT);
            break;
        case CC_FLAG_MOD_R_META:
            handle_flag_modifier(M_R_META);
            break;
        case CC_FLAG_MOD_R_CTRL:
            handle_flag_modifier(M_R_CTRL);
            break;
        case CC_FLAG_MOD_R_SHIFT:
            handle_flag_modifier(M_R_SHIFT);
            break;
        case CC_FLAG_MOD_R_ALT:
            handle_flag_modifier(M_R_ALT);
            break;
        case CC_FLAG_LAYER_1:
            handle_flag_layer(1);
            break;
        case CC_FLAG_LAYER_2:
            handle_flag_layer(2);
            break;
        case CC_FLAG_LAYER_3:
            handle_flag_layer(3);
            break;
        case CC_FLAG_LAYER_4:
            handle_flag_layer(4);
            break;
        case CC_FLAG_HOLD_PRESS:
            handle_flag_hold(HOLD_PRESS);
            break;
        case CC_FLAG_HOLD_RELEASE:
            handle_flag_hold(HOLD_RELEASE);
            break;
        case CC_FLAG_HOLD_ONCE:
            handle_flag_hold(HOLD_ONCE);
            break;
        case CC_FLAG_LOCK_FLAG:
            state.chord_state.flags.flag.flag_lock = true;
            return true; // RETURN EARLY (dont reset flags)
        case CC_FLAG_LOCK_FUNCTION:
            state.chord_state.flags.normal.function_lock = true;
            break;
        default:
            return false;
    }

    reset_unlocked_flags_flag(&state.chord_state.flags.flag);
    return true;
}

void send_control_code(uint16_t control_code) {
    bool is_flag = handle_flag(control_code);

    if (!is_flag) {
        bool (*f)(uint16_t code, state_t *state) = get_function(control_code);

        if (f != NULL) {
            process_function_initial(f);
        } else {
            reset_unlocked_flags(&state.chord_state.flags);
        }
    }
}
