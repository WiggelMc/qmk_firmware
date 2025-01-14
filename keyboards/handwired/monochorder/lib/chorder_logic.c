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
#include "function_logic.h"
#include "key_set.h"
#include "quantum.h"

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

void process_code(uint16_t code) {
    state.chord_state.repeat_state.last_code = code;

    if (code == noop_code) {
        // Do Nothing
    } else if (code == cancel_code) {
        cancel();
    } else if (state.chord_state.function_state.running == NULL) {
        process_chord(code, state.chord_state.flags.normal.layer);
    } else {
        process_function(code, state.chord_state.function_state.running);
    }
}

void handle_chord_mode(uint16_t code, bool pressed) {
    if (pressed) {
        state.chord_state.current_phase = PHASE_PRESS;
    } else {
        if (state.chord_state.current_phase == PHASE_PRESS) {
            process_code(state.active_codes);
        }
        state.chord_state.current_phase = PHASE_IDLE;
    }
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

void hold_release_all(void) {
    size_t hold_size = keyset_size(ARR(state.chord_state.hold_state.hold_keys));
    for (uint16_t i = 0; i < hold_size; i++) {
        uint16_t key = state.chord_state.hold_state.hold_keys[i];
        if (key != 0) {
            unregister_code16(key);
        }
    }
    keyset_clear(ARR(state.chord_state.hold_state.hold_keys));

    size_t hold_once_size = keyset_size(ARR(state.chord_state.hold_state.hold_once_keys));
    for (uint16_t i = 0; i < hold_once_size; i++) {
        uint16_t key = state.chord_state.hold_state.hold_once_keys[i];
        if (key != 0) {
            unregister_code16(key);
        }
    }
    keyset_clear(ARR(state.chord_state.hold_state.hold_once_keys));
}

void handle_reset(void) {
    hold_release_all();

    if (state.current_mode == MODE_DIRECT_INPUT) {
        for (uint16_t i = 0; i < 16; i++) {
            if (TEST_BITS(state.active_codes, 1 << i)) {
                handle_direct_key_mode(i, false);
            }
        }
    }

    reset_state(&state);
}

void enter_direct_key_mode(uint16_t index) {
    handle_reset();
    state.direct_key_state.active_index = index;
    state.current_mode                  = MODE_DIRECT_INPUT;
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

    if (pressed) {
        state.active_codes |= ((uint16_t)1 << code);
    } else {
        state.active_codes &= ~((uint16_t)1 << code);
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
        uint16_t code_modifiers = ((modifiers | state.chord_state.flags.normal.modifiers) << 8);
        uint16_t modified_code  = code_modifiers | keycode;

        size_t hold_once_size;
        bool   removed_from_hold;
        bool   removed_from_hold_once;

        switch (state.chord_state.flags.normal.hold_mode) {
            case HOLD_OFF:
                // tap CODE and release all CODES from HOLD_ONCE list, clear HOLD_ONCE list

                hold_once_size = keyset_size(ARR(state.chord_state.hold_state.hold_once_keys));

                tap_code16(modified_code);
                for (size_t i = 0; i < hold_once_size; i++) {
                    unregister_code16(state.chord_state.hold_state.hold_once_keys[i]);
                }
                keyset_clear(ARR(state.chord_state.hold_state.hold_once_keys));

                state.chord_state.repeat_state.last_keycode = modified_code;
                break;
            case HOLD_PRESS:
                // ADD CODE to HOLD list and register (+ remove from hold once list)

                removed_from_hold_once = keyset_remove(ARR(state.chord_state.hold_state.hold_once_keys), modified_code);
                if (keyset_add(ARR(state.chord_state.hold_state.hold_keys), modified_code)) {
                    if (!removed_from_hold_once) {
                        register_code16(modified_code);
                    }
                } else if (removed_from_hold_once) {
                    unregister_code16(modified_code);
                }
                break;
            case HOLD_RELEASE:
                // REMOVE CODE from HOLD and HOLD_ONCE list and unregister

                removed_from_hold      = keyset_remove(ARR(state.chord_state.hold_state.hold_keys), modified_code);
                removed_from_hold_once = keyset_remove(ARR(state.chord_state.hold_state.hold_once_keys), modified_code);

                if (removed_from_hold || removed_from_hold_once) {
                    unregister_code16(modified_code);
                }
                break;
            case HOLD_ONCE:
                // ADD CODE to HOLD_ONCE list and register (+ remove from hold list)

                removed_from_hold = keyset_remove(ARR(state.chord_state.hold_state.hold_keys), modified_code);
                if (keyset_add(ARR(state.chord_state.hold_state.hold_once_keys), modified_code)) {
                    if (!removed_from_hold) {
                        register_code16(modified_code);
                    }
                } else if (removed_from_hold) {
                    unregister_code16(modified_code);
                }
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
