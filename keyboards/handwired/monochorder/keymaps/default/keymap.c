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

#include "print.h"
#include "action.h"
#include QMK_KEYBOARD_H
#include "../../lib/chorder_logic.h"

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
    [0] = LAYOUT(MCH_0, MCH_1, MCH_2, MCH_3, MCH_4, MCH_5, MCH_6, MCH_7, MCH_8, MCH_9, MCH_R, MCH_R)};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_chorder_logic(keycode, record)) {
        return false;
    }

    return true;
}

const uint16_t PROGMEM keys_a[64] = {
    [0] = 0
};

const uint16_t PROGMEM keys_b[16] = {
    [0] = 0
};

const uint16_t PROGMEM control_codes_a[256] = {
    [0] = 0
};

const uint16_t PROGMEM control_codes_b[128] = {
    [0] = 0
};

bool process_chord(uint16_t keycode) {
    bool shift = (keycode & MASK(10000, 00000)) != 0;
    bool ctrl = (keycode & MASK(01000, 00000)) != 0;
    bool alt = (keycode & MASK(00100, 00000)) != 0;
    modifiers modifiers = (ctrl ? M_L_CTRL : 0) | (shift ? M_L_SHIFT : 0) | (alt ? M_L_ALT : 0);

    if (keycode == CODE(00000,00001)) {
        // ----- ----9
        // CANCEL

        print("Cancel");
        //TODO: Send Cancel Code

    } else if (keycode == CODE(11111,11111)) {
        // 01234 56789
        // NOOP OVERRIDE

        print("Noop Override");

    } else if (MATCH(keycode, CODE(00000,00000), MASK(00000,00001))) {
        // mmm?? ????-
        // Keys A (64 + shift, ctrl, alt)
        uint16_t index = (keycode & MASK(00011,11110)) >> 1;
        uint16_t value = pgm_read_word(&keys_a[index]);

        uprintf("Keys A: %d | %d", value, modifiers);
        send_key(value, modifiers);

    } else if (MATCH(keycode, CODE(00000,00101), MASK(00000,00111))) {
        // mmm?? ??7-9
        // Keys B (16 + shift, ctrl, alt)
        uint16_t index = (keycode & MASK(00011,11000)) >> 3;
        uint16_t value = pgm_read_word(&keys_b[index]);

        uprintf("Keys B: %d | %d", value, modifiers);
        send_key(value, modifiers);

    } else if (MATCH(keycode, CODE(00000,00011), MASK(00000,00011))) {
        // ????? ???89
        // Control Codes A (256)
        uint16_t index = (keycode & MASK(11111,11100)) >> 2;
        uint16_t value = pgm_read_word(&control_codes_a[index]);

        uprintf("Control Codes A: %d", value);
        send_control_code(value);

    } else if (MATCH(keycode, CODE(00000,00001), MASK(00000,00111))) {
        // ????? ??--9
        // Control Codes B (128)
        uint16_t index = (keycode & MASK(11111,11100)) >> 2;
        uint16_t value = pgm_read_word(&control_codes_b[index]);

        uprintf("Control Codes B: %d", value);
        send_control_code(value);

    }

    return false;
}

const uint16_t PROGMEM direct_key_keymap[10] = {
    KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,
};
