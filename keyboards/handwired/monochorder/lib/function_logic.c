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

#include "function_logic.h"
#include "keymap_logic.h"

bool fn_cancel(uint16_t code, state_t *state) {
    cancel();
    return true;
}

bool fn_set_option(uint16_t code, state_t *state) {
    switch (PHASE(state)) {
        case 0:
            PHASE(state) = 1;
            return false;
        case 1:
            uint16_t *option_ptr = read_9bit_data(code);
            if (option_ptr == NULL) {
                return true;
            }

            state->chord_state.function_state.data[1] = *option_ptr;
            free(option_ptr);
            PHASE(state) = 2;
            return false;
        case 2:
            uint16_t *value_ptr = read_9bit_data(code);
            if (value_ptr == NULL) {
                return true;
            }

            uint16_t option = state->chord_state.function_state.data[1];
            uint16_t value  = *value_ptr;
            free(value_ptr);

            // TODO: Set [option] to [value]
            uprintf("Set Option: %03u to %03u", option, value);

            return true;
    }
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

bool fn_enter_direct_key_mode(uint16_t code, state_t *state) {
    switch (PHASE(state)) {
        case 0:
            PHASE(state) = 1;
            return false;
        case 1:
            uint16_t *index_ptr = read_9bit_data(code);
            if (index_ptr == NULL) {
                return true;
            }

            uint16_t index = *index_ptr;
            free(index_ptr);
            if (index >= direct_key_keymap_count) {
                return true;
            }

            // TODO: Enter mode with [index]
            uprintf("Enter Direct Key Mode with Index %u", index);

            return true;
    }
    return true;
}

bool fn_enter_special_mode(uint16_t code, state_t *state) {
    // TODO: Implement
    return true;
}

bool fn_hold_release_all(uint16_t code, state_t *state) {
    // TODO: unregister all CODES from HOLD list, clear HOLD and HOLD_ONCE list
    return true;
}

bool fn_type_byte_hex(uint16_t code, state_t *state) {
    switch (PHASE(state)) {
        case 0:
            PHASE(state) = 1;
            return false;
        case 1:
            read_byte_data_t *byte_data_ptr = read_byte_data(code);
            if (byte_data_ptr == NULL) {
                return true;
            }

            char hex_string[3];
            sprintf(hex_string, byte_data_ptr->mod ? "%02X" : "%02x", byte_data_ptr->byte);

            free(byte_data_ptr);
            send_string(hex_string);
            return true;
    }
    return true;
}

bool fn_type_byte_bin(uint16_t code, state_t *state) {
    switch (PHASE(state)) {
        case 0:
            PHASE(state) = 1;
            return false;
        case 1:
            read_byte_data_t *byte_data_ptr = read_byte_data(code);
            if (byte_data_ptr == NULL) {
                return true;
            }

            uint8_t byte = byte_data_ptr->byte;
            char    bin_string[9];
            sprintf(bin_string, "%c%c%c%c%c%c%c%c", byte & MASK(1000, 0000) ? '1' : '0', byte & MASK(0100, 0000) ? '1' : '0', byte & MASK(0010, 0000) ? '1' : '0', byte & MASK(0001, 0000) ? '1' : '0', byte & MASK(0000, 1000) ? '1' : '0', byte & MASK(0000, 0100) ? '1' : '0', byte & MASK(0000, 0010) ? '1' : '0', byte & MASK(0000, 0001) ? '1' : '0');

            free(byte_data_ptr);
            send_string(bin_string);
            return true;
    }
    return true;
}

bool fn_type_byte_oct(uint16_t code, state_t *state) {
    switch (PHASE(state)) {
        case 0:
            PHASE(state) = 1;
            return false;
        case 1:
            read_byte_data_t *byte_data_ptr = read_byte_data(code);
            if (byte_data_ptr == NULL) {
                return true;
            }

            char oct_string[4];
            sprintf(oct_string, "%03o", byte_data_ptr->byte);

            free(byte_data_ptr);
            send_string(oct_string);
            return true;
    }
    return true;
}

bool fn_type_byte_dec(uint16_t code, state_t *state) {
    switch (PHASE(state)) {
        case 0:
            PHASE(state) = 1;
            return false;
        case 1:
            read_byte_data_t *byte_data_ptr = read_byte_data(code);
            if (byte_data_ptr == NULL) {
                return true;
            }

            char dec_string[4];
            sprintf(dec_string, byte_data_ptr->mod ? "%03u" : "%u", byte_data_ptr->byte);

            free(byte_data_ptr);
            send_string(dec_string);
            return true;
    }
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
        case CC_ENTER_DIRECT_KEY_MODE:
            return &fn_enter_direct_key_mode;
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
