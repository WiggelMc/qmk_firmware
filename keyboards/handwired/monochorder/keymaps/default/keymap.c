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

#include <stdlib.h>
#include "print.h"
#include "action.h"
#include QMK_KEYBOARD_H
#include "../../lib/chorder_logic.h"
#include "../../lib/keymap_logic.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐       ┌───┬───┬───┬───┐
     * │ 0 │ 1 │ 2 │ 3 │       │ 6 │ 7 │ 8 │ 9 │
     * └───┴───┴───┴───┘       └───┴───┴───┴───┘
     *
     *         ┌───┬───┐       ┌───┬───┐
     *         │ R │ 4 │       │ 5 │ R |
     *         └───┴───┘       └───┴───┘
     */
    [0] = LAYOUT(MCH_0, MCH_1, MCH_2, MCH_3,    MCH_6, MCH_7, MCH_8, MCH_9,
		   	                   MCH_R, MCH_4,    MCH_5, MCH_R
    )};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_chorder_logic(keycode, record)) {
        return false;
    }

    return true;
}

void keyboard_post_init_user(void) {
    init_chorder_logic();
}

// clang-format off
const uint16_t PROGMEM keys_a[][64] = {
    // mmm^^ ^^^^-

    [0] = {
        [CODE(00,0000)] = KC_RESERVED,
        [CODE(00,0001)] = 0,
        [CODE(00,0010)] = 0,
        [CODE(00,0011)] = 0,
        [CODE(00,0100)] = 0,
        [CODE(00,0101)] = 0,
        [CODE(00,0110)] = 0,
        [CODE(00,0111)] = 0,
        [CODE(00,1000)] = 0,
        [CODE(00,1001)] = 0,
        [CODE(00,1010)] = 0,
        [CODE(00,1011)] = 0,
        [CODE(00,1100)] = 0,
        [CODE(00,1101)] = 0,
        [CODE(00,1110)] = 0,
        [CODE(00,1111)] = 0,

        [CODE(01,0000)] = 0,
        [CODE(01,0001)] = 0,
        [CODE(01,0010)] = 0,
        [CODE(01,0011)] = 0,
        [CODE(01,0100)] = 0,
        [CODE(01,0101)] = 0,
        [CODE(01,0110)] = 0,
        [CODE(01,0111)] = 0,
        [CODE(01,1000)] = 0,
        [CODE(01,1001)] = 0,
        [CODE(01,1010)] = 0,
        [CODE(01,1011)] = 0,
        [CODE(01,1100)] = KC_I,
        [CODE(01,1101)] = 0,
        [CODE(01,1110)] = 0,
        [CODE(01,1111)] = 0,

        [CODE(10,0000)] = 0,
        [CODE(10,0001)] = 0,
        [CODE(10,0010)] = 0,
        [CODE(10,0011)] = 0,
        [CODE(10,0100)] = 0,
        [CODE(10,0101)] = 0,
        [CODE(10,0110)] = 0,
        [CODE(10,0111)] = 0,
        [CODE(10,1000)] = 0,
        [CODE(10,1001)] = 0,
        [CODE(10,1010)] = 0,
        [CODE(10,1011)] = 0,
        [CODE(10,1100)] = KC_O,
        [CODE(10,1101)] = 0,
        [CODE(10,1110)] = 0,
        [CODE(10,1111)] = 0,

        [CODE(11,0000)] = 0,
        [CODE(11,0001)] = 0,
        [CODE(11,0010)] = KC_U,
        [CODE(11,0011)] = 0,
        [CODE(11,0100)] = KC_E,
        [CODE(11,0101)] = 0,
        [CODE(11,0110)] = 0,
        [CODE(11,0111)] = 0,
        [CODE(11,1000)] = KC_A,
        [CODE(11,1001)] = 0,
        [CODE(11,1010)] = 0,
        [CODE(11,1011)] = 0,
        [CODE(11,1100)] = KC_S,
        [CODE(11,1101)] = 0,
        [CODE(11,1110)] = 0,
        [CODE(11,1111)] = 0,
    },
    [1] = {
        [CODE(00,0000)] = KC_RESERVED,
        [CODE(00,0001)] = 0,
        [CODE(00,0010)] = 0,
        [CODE(00,0011)] = 0,
        [CODE(00,0100)] = 0,
        [CODE(00,0101)] = 0,
        [CODE(00,0110)] = 0,
        [CODE(00,0111)] = 0,
        [CODE(00,1000)] = 0,
        [CODE(00,1001)] = 0,
        [CODE(00,1010)] = 0,
        [CODE(00,1011)] = 0,
        [CODE(00,1100)] = 0,
        [CODE(00,1101)] = 0,
        [CODE(00,1110)] = 0,
        [CODE(00,1111)] = 0,

        [CODE(01,0000)] = 0,
        [CODE(01,0001)] = 0,
        [CODE(01,0010)] = 0,
        [CODE(01,0011)] = 0,
        [CODE(01,0100)] = 0,
        [CODE(01,0101)] = 0,
        [CODE(01,0110)] = 0,
        [CODE(01,0111)] = 0,
        [CODE(01,1000)] = 0,
        [CODE(01,1001)] = 0,
        [CODE(01,1010)] = 0,
        [CODE(01,1011)] = 0,
        [CODE(01,1100)] = 0,
        [CODE(01,1101)] = 0,
        [CODE(01,1110)] = 0,
        [CODE(01,1111)] = 0,

        [CODE(10,0000)] = 0,
        [CODE(10,0001)] = 0,
        [CODE(10,0010)] = 0,
        [CODE(10,0011)] = 0,
        [CODE(10,0100)] = 0,
        [CODE(10,0101)] = 0,
        [CODE(10,0110)] = 0,
        [CODE(10,0111)] = 0,
        [CODE(10,1000)] = 0,
        [CODE(10,1001)] = 0,
        [CODE(10,1010)] = 0,
        [CODE(10,1011)] = 0,
        [CODE(10,1100)] = 0,
        [CODE(10,1101)] = 0,
        [CODE(10,1110)] = 0,
        [CODE(10,1111)] = 0,

        [CODE(11,0000)] = 0,
        [CODE(11,0001)] = 0,
        [CODE(11,0010)] = 0,
        [CODE(11,0011)] = 0,
        [CODE(11,0100)] = 0,
        [CODE(11,0101)] = 0,
        [CODE(11,0110)] = 0,
        [CODE(11,0111)] = 0,
        [CODE(11,1000)] = 0,
        [CODE(11,1001)] = 0,
        [CODE(11,1010)] = 0,
        [CODE(11,1011)] = 0,
        [CODE(11,1100)] = 0,
        [CODE(11,1101)] = 0,
        [CODE(11,1110)] = 0,
        [CODE(11,1111)] = 0,
    },
};

const uint16_t PROGMEM keys_b[][16] = {
    // mmm^^ ^^7-9

    [0] = {
        [CODE(00,00)] = 0,
        [CODE(00,01)] = 0,
        [CODE(00,10)] = 0,
        [CODE(00,11)] = 0,

        [CODE(01,00)] = 0,
        [CODE(01,01)] = 0,
        [CODE(01,10)] = 0,
        [CODE(01,11)] = 0,

        [CODE(10,00)] = 0,
        [CODE(10,01)] = 0,
        [CODE(10,10)] = 0,
        [CODE(10,11)] = 0,

        [CODE(11,00)] = 0,
        [CODE(11,01)] = 0,
        [CODE(11,10)] = 0,
        [CODE(11,11)] = 0,
    },
    [1] = {
        [CODE(00,00)] = 0,
        [CODE(00,01)] = 0,
        [CODE(00,10)] = 0,
        [CODE(00,11)] = 0,

        [CODE(01,00)] = 0,
        [CODE(01,01)] = 0,
        [CODE(01,10)] = 0,
        [CODE(01,11)] = 0,

        [CODE(10,00)] = 0,
        [CODE(10,01)] = 0,
        [CODE(10,10)] = 0,
        [CODE(10,11)] = 0,

        [CODE(11,00)] = 0,
        [CODE(11,01)] = 0,
        [CODE(11,10)] = 0,
        [CODE(11,11)] = 0,
    },
};

const uint16_t PROGMEM control_codes_a[256] = {
    // ^^^^^ ^^^89

    [CODE(00000,000)] = 0
};

const uint16_t PROGMEM control_codes_b[128] = {
    // ^^^^^ ^^--9

    [CODE(00000,00)] = 0
};
// clang-format on

void process_chord(uint16_t code, uint8_t layer) {
    const bool        shift     = TEST_BITS(code, MASK(10000, 00000));
    const bool        ctrl      = TEST_BITS(code, MASK(01000, 00000));
    const bool        alt       = TEST_BITS(code, MASK(00100, 00000));
    const modifiers_t modifiers = (ctrl ? M_L_CTRL : 0) | (shift ? M_L_SHIFT : 0) | (alt ? M_L_ALT : 0);

    if (MATCH(code, CODE(00000, 00000), MASK(00000, 00001))) {
        // mmm^^ ^^^^-
        // Keys A (64 + shift, ctrl, alt)

        if (layer < ARRAY_SIZE(keys_a)) {
            const uint16_t index = (code & MASK(00011, 11110)) >> 1;

            const uint16_t(*keymap)[64] = &keys_a[layer];
            const uint16_t value        = pgm_read_word(keymap[index]);

            uprintf("Keys A: %u | %02X", value, modifiers);
            send_key(value, modifiers);
        }

    } else if (MATCH(code, CODE(00000, 00101), MASK(00000, 00111))) {
        // mmm^^ ^^7-9
        // Keys B (16 + shift, ctrl, alt)

        if (layer < ARRAY_SIZE(keys_b)) {
            const uint16_t index = (code & MASK(00011, 11000)) >> 3;

            const uint16_t(*keymap)[16] = &keys_b[layer];
            const uint16_t value        = pgm_read_word(keymap[index]);

            uprintf("Keys B: %u | %02X", value, modifiers);
            send_key(value, modifiers);
        }

    } else if (MATCH(code, CODE(00000, 00011), MASK(00000, 00011))) {
        // ^^^^^ ^^^89
        // Control Codes A (256)
        const uint16_t index = (code & MASK(11111, 11100)) >> 2;
        const uint16_t value = pgm_read_word(&control_codes_a[index]);

        uprintf("Control Codes A: %u", value);
        send_control_code(value);

    } else if (MATCH(code, CODE(00000, 00001), MASK(00000, 00111))) {
        // ^^^^^ ^^--9
        // Control Codes B (128)
        const uint16_t index = (code & MASK(11111, 11100)) >> 2;
        const uint16_t value = pgm_read_word(&control_codes_b[index]);

        uprintf("Control Codes B: %u", value);
        send_control_code(value);
    }
}

// clang-format off
const uint16_t PROGMEM direct_key_keymap[][10] = {
    [0] = {KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9}
};
// clang-format on

const size_t direct_key_keymap_count = ARRAY_SIZE(direct_key_keymap);

const uint16_t cancel_code = CODE(00000, 00001);
const uint16_t noop_code   = CODE(11111, 11111);

void default_options_init(options_state_t* options_state) {
    options_state->tap_code_delay = 0;
}

// clang-format off
const option_mapping_t option_mapping = {
    .tap_code_delay = CODE(10001,0000)
};
// clang-format on

const uint16_t zero_code = CODE(00000, 10001);

bool read_byte_data(uint16_t code, read_byte_data_t* out_data) {
    const uint16_t mod_mask = MASK(10000, 00000);
    const bool     mod      = TEST_BITS(code, mod_mask);

    if ((code & ~mod_mask) == zero_code) {
        out_data->byte = 0;
        out_data->mod  = mod;
        return true;

    } else if (TEST_BITS(code, MASK(00000, 00001))) {
        return false;

    } else {
        out_data->byte = (code & MASK(01111, 11110)) >> 1;
        out_data->mod  = mod;
        return true;
    }
}

bool read_9bit_data(uint16_t code, uint16_t* out_data) {
    if (code == zero_code) {
        *out_data = 0;
        return true;

    } else if (TEST_BITS(code, MASK(00000, 00001))) {
        return false;

    } else {
        *out_data = (code & MASK(11111, 11110)) >> 1;
        return true;
    }
}
