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
#include "quantum.h"
#include QMK_KEYBOARD_H

const uint16_t MCH_SAFE_RANGE = MCH_R + 1;


void reset_flags_flag(flags_flag_t *flags) {
    flags->flag_lock = false;
}

void try_reset_flags_flag(flags_flag_t *flags) {
    flags->flag_lock = false;
}

void reset_flags_normal(flags_normal_t *flags) {
    flags->hold_mode = HOLD_OFF;
    flags->locked_hold_mode = false;

    flags->layer = 0;
    flags->locked_layer = false;

    flags->modifiers = 0;
    flags->locked_modifiers = 0;

    flags->function_lock = false;
}

void try_reset_flags_normal(flags_normal_t *flags) {
    if (!flags->locked_hold_mode) {
        flags->hold_mode = HOLD_OFF;
    }

    if (!flags->locked_layer) {
        flags->layer = 0;
    }

    flags->modifiers = flags->modifiers & flags->locked_modifiers;

    flags->function_lock = false;
}

void reset_flags_all(flags_t *flags) {
    reset_flags_normal(&flags->normal);
    reset_flags_flag(&flags->flag);
}

void try_reset_flags_all(flags_t *flags) {
    try_reset_flags_normal(&flags->normal);
    try_reset_flags_flag(&flags->flag);
}

void reset_function_state(function_state_t *function_state_ptr) {
    function_state_ptr->running = NULL;
    memset(function_state_ptr->data, 0, sizeof(function_state_ptr->data));
}

void reset_state(state_t *state_ptr) {
    reset_flags_all(&state_ptr->flags);
    reset_function_state(&state_ptr->function_state);
}

state_t state = {
    .flags = {
        .normal = {
            .hold_mode = HOLD_OFF,
            .locked_hold_mode = false,

            .layer = 0,
            .locked_layer = false,

            .modifiers = 0,
            .locked_modifiers = 0,

            .function_lock = false
        },
        .flag = {
            .flag_lock = false
        }
    },
    .function_state = {
        .running = NULL,
        .data = { 0 }
    }
};

input_state_t input_state = {
    .current_mode = MODE_CHORD,
    .current_phase = PHASE_IDLE,
    .active_codes = 0
};

void process_function_initial(bool (*function)(uint16_t code, state_t *state)) {
    bool done = function(0, &state);

    if (done) {
        reset_function_state(&state.function_state);
        try_reset_flags_all(&state.flags);
    } else {
        state.function_state.running = function;
    }
}

void process_function(uint16_t code, bool (*function)(uint16_t code, state_t *state)) {
    if (input_state.active_codes == CODE(00000,00001)) {
        reset_state(&state);

    } else {
        bool done = state.function_state.running(input_state.active_codes, &state);

        if (done) {
            bool (*f)(uint16_t code, state_t *state) = state.function_state.running;
            reset_function_state(&state.function_state);

            if (state.flags.normal.function_lock) {
                process_function_initial(f);
            } else {
                try_reset_flags_all(&state.flags);
            }
        }
    }
}

void handle_chord_mode(uint16_t code, bool pressed) {
    if (pressed) {
        input_state.current_phase = PHASE_PRESS;
        input_state.active_codes |= ((uint16_t)1 << code);
    } else {
        if (input_state.current_phase == PHASE_PRESS) {
            if (state.function_state.running == NULL) {
                process_chord(input_state.active_codes, state.flags.normal.layer);
            } else {
                process_function(input_state.active_codes, state.function_state.running);
            }
        }
        input_state.current_phase = PHASE_IDLE;
        input_state.active_codes &= ~((uint16_t)1 << code);
    }
}

void release_all_keys(void) {
    for (uint16_t keycode = 0; keycode <= 0xFF; keycode++) {
        if (keycode != KC_NO) {
            unregister_code16(keycode);
        }
    }
    // TODO: Test if Modifiers need to be removed seperately
}

void handle_reset(void) {
    reset_state(&state);
    release_all_keys();
    input_state.current_mode = MODE_CHORD;
}

void handle_direct_key_mode(uint16_t code, bool pressed) {
    uint16_t key = pgm_read_word(&direct_key_keymap[code]);
    if (pressed) {
        register_code16(key);
    } else {
        unregister_code16(key);
    }
}

void handle_input(uint16_t code, bool pressed) {
    switch (input_state.current_mode) {
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
        uint16_t modified_code = ((modifiers | state.flags.normal.modifiers) << 8) | keycode;
        switch (state.flags.normal.hold_mode) {
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

                //TODO: Handle Hold
                // Store held keys in arrays: HOLD, HOLD_ONCE of type uint16_t with length 32 each
                break;
        }
    }

    try_reset_flags_all(&state.flags);
}

bool fn_cancel(uint16_t code, state_t *state) {
    reset_state(state);
    return true;
}

bool fn_set_option(uint16_t code, state_t *state) {
    // TODO: Implement
    return true;
}

bool fn_repeat_last_press(uint16_t code, state_t *state) {
    // TODO: Implement
    return true;
}

bool fn_repeat_last_result(uint16_t code, state_t *state) {
    // TODO: Implement
    return true;
}

bool fn_enter_special_mode(uint16_t code, state_t *state) {
    // TODO: Implement
    return true;
}

bool fn_hold_release_all(uint16_t code, state_t *state) {
    release_all_keys();
    //TODO: unregister all CODES from HOLD list, clear HOLD and HOLD_ONCE list (remove release_all_keys)
    return true;
}

bool fn_type_byte_hex(uint16_t code, state_t *state) {
    // TODO: Implement
    return true;
}

bool fn_type_byte_bin(uint16_t code, state_t *state) {
    // TODO: Implement
    return true;
}

bool fn_type_byte_oct(uint16_t code, state_t *state) {
    // TODO: Implement
    return true;
}

bool fn_type_byte_dec(uint16_t code, state_t *state) {
    // TODO: Implement
    return true;
}


bool (*get_function(uint16_t control_code))(uint16_t code, state_t *state) {
    switch (control_code) {
        case CC_CANCEL:
            return &fn_cancel;
        case CC_SET_OPTION:
            return &fn_set_option;
        case CC_REPEAT_LAST_PRESS:
            return &fn_repeat_last_press;
        case CC_REPEAT_LAST_RESULT:
            return &fn_repeat_last_result;
        case CC_ENTER_SPECIAL_MODE:
            return &fn_enter_special_mode;
        case CC_HOLD_RELEASE_ALL:
            return &fn_hold_release_all;
        case CC_TYPE_BYTE_HEX:
            return &fn_type_byte_hex;
        case CC_TYPE_BYTE_BIN:
            return &fn_type_byte_bin;
        case CC_TYPE_BYTE_OCT:
            return &fn_type_byte_oct;
        case CC_TYPE_BYTE_DEC:
            return &fn_type_byte_dec;
        default:
            return NULL;
    }
}

void handle_flag_modifier(modifiers_t modifier) {
    if (state.flags.flag.flag_lock) {
        state.flags.normal.locked_modifiers |= modifier;
    }
    state.flags.normal.modifiers |= modifier;
}

void handle_flag_layer(uint8_t layer) {
    if (state.flags.flag.flag_lock) {
        state.flags.normal.locked_layer = true;
    }
    state.flags.normal.layer = layer;
}

void handle_flag_hold(hold_mode_t hold_mode) {
    if (state.flags.flag.flag_lock) {
        state.flags.normal.locked_hold_mode = true;
    }
    state.flags.normal.hold_mode = hold_mode;
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
            state.flags.flag.flag_lock = true;
            return true; // RETURN EARLY (dont reset flags)
        case CC_FLAG_LOCK_FUNCTION:
            state.flags.normal.function_lock = true;
            break;
        default:
            return false;
    }

    try_reset_flags_flag(&state.flags.flag);
    return true;
}

void send_control_code(uint16_t control_code) {
    bool is_flag = handle_flag(control_code);

    if (!is_flag) {

        bool (*f)(uint16_t code, state_t *state) = get_function(control_code);

        if (f != NULL) {
            process_function_initial(f);
        } else {
            try_reset_flags_all(&state.flags);
        }
    }
}

