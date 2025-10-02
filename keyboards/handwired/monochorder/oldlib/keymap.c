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
#include "keymap_german.h"
#include "keymap_us_international.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐       ┌───┬───┬───┬───┐
     * │ 9 │ 8 │ 7 │ 6 │       │ 3 │ 2 │ 1 │ 0 │
     * └───┴───┴───┴───┘       └───┴───┴───┴───┘
     *
     *         ┌───┬───┐       ┌───┬───┐
     *         │ R │ 5 │       │ 4 │ R |
     *         └───┴───┘       └───┴───┘
     */
    [0] = LAYOUT(MCH_9, MCH_8, MCH_7, MCH_6,    MCH_3, MCH_2, MCH_1, MCH_0,
		   	                   MCH_R, MCH_5,    MCH_4, MCH_R
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

// ########################################################
// #                                                      #
// #                    KEYMAP                            #
// #                                                      #
// ########################################################

#define KEY(key) DE_##key

// clang-format off
const uint16_t PROGMEM keys_a[][64] = {
    // mmm^^ ^^^^-

    [0] = {
        [CODE(00,0000)] = KC_RESERVED,
        [CODE(00,0001)] = KC_MEDIA_NEXT_TRACK,
        [CODE(00,0010)] = KC_AUDIO_VOL_UP,
        [CODE(00,0011)] = KC_BRIGHTNESS_UP,
        [CODE(00,0100)] = KC_AUDIO_VOL_DOWN,
        [CODE(00,0101)] = KC_MEDIA_PREV_TRACK,
        [CODE(00,0110)] = KC_AUDIO_MUTE,
        [CODE(00,0111)] = KEY(V),
        [CODE(00,1000)] = KC_MEDIA_PLAY_PAUSE,
        [CODE(00,1001)] = KC_PRINT_SCREEN,
        [CODE(00,1010)] = KEY(M),
        [CODE(00,1011)] = KEY(N),
        [CODE(00,1100)] = KC_BRIGHTNESS_DOWN,
        [CODE(00,1101)] = KEY(P),
        [CODE(00,1110)] = KEY(Y),
        [CODE(00,1111)] = KC_MEDIA_STOP,

        [CODE(01,0000)] = KEY(0),
        [CODE(01,0001)] = KEY(1),
        [CODE(01,0010)] = KEY(2),
        [CODE(01,0011)] = KEY(3),
        [CODE(01,0100)] = KEY(4),
        [CODE(01,0101)] = KEY(5),
        [CODE(01,0110)] = KEY(6),
        [CODE(01,0111)] = KEY(7),
        [CODE(01,1000)] = KEY(8),
        [CODE(01,1001)] = KEY(9),
        [CODE(01,1010)] = KEY(K),
        [CODE(01,1011)] = DE_ODIA,
        [CODE(01,1100)] = KEY(I),
        [CODE(01,1101)] = KEY(J),
        [CODE(01,1110)] = DE_UDIA,
        [CODE(01,1111)] = KC_SPACE,

        [CODE(10,0000)] = 0,
        [CODE(10,0001)] = 0,
        [CODE(10,0010)] = KEY(B),
        [CODE(10,0011)] = DE_ADIA,
        [CODE(10,0100)] = 0,
        [CODE(10,0101)] = KEY(L),
        [CODE(10,0110)] = KEY(T),
        [CODE(10,0111)] = KEY(H),
        [CODE(10,1000)] = 0,
        [CODE(10,1001)] = KEY(R),
        [CODE(10,1010)] = KEY(C),
        [CODE(10,1011)] = DE_SS,
        [CODE(10,1100)] = KEY(O),
        [CODE(10,1101)] = KEY(W),
        [CODE(10,1110)] = KEY(D),
        [CODE(10,1111)] = KC_PAUSE,

        [CODE(11,0000)] = 0,
        [CODE(11,0001)] = KEY(G),
        [CODE(11,0010)] = KEY(U),
        [CODE(11,0011)] = KEY(Z),
        [CODE(11,0100)] = KEY(E),
        [CODE(11,0101)] = KC_SCROLL_LOCK,
        [CODE(11,0110)] = KEY(X),
        [CODE(11,0111)] = KEY(Q),
        [CODE(11,1000)] = KEY(A),
        [CODE(11,1001)] = KC_DOWN,
        [CODE(11,1010)] = KEY(F),
        [CODE(11,1011)] = KC_LEFT,
        [CODE(11,1100)] = KEY(S),
        [CODE(11,1101)] = KC_UP,
        [CODE(11,1110)] = KC_RIGHT,
        [CODE(11,1111)] = 0,
    },
    [1] = {
        [CODE(00,0000)] = KC_RESERVED,
        [CODE(00,0001)] = 0,
        [CODE(00,0010)] = 0,
        [CODE(00,0011)] = KC_APPLICATION,
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

        [CODE(01,0000)] = KC_KP_0,
        [CODE(01,0001)] = KC_KP_1,
        [CODE(01,0010)] = KC_KP_2,
        [CODE(01,0011)] = KC_KP_3,
        [CODE(01,0100)] = KC_KP_4,
        [CODE(01,0101)] = KC_KP_5,
        [CODE(01,0110)] = KC_KP_6,
        [CODE(01,0111)] = KC_KP_7,
        [CODE(01,1000)] = KC_KP_8,
        [CODE(01,1001)] = KC_KP_9,
        [CODE(01,1010)] = 0,
        [CODE(01,1011)] = 0,
        [CODE(01,1100)] = 0,
        [CODE(01,1101)] = 0,
        [CODE(01,1110)] = 0,
        [CODE(01,1111)] = KC_NUM_LOCK,

        [CODE(10,0000)] = 0,
        [CODE(10,0001)] = KC_F1,
        [CODE(10,0010)] = KC_F2,
        [CODE(10,0011)] = KC_F3,
        [CODE(10,0100)] = KC_F4,
        [CODE(10,0101)] = KC_F5,
        [CODE(10,0110)] = KC_F6,
        [CODE(10,0111)] = KC_F7,
        [CODE(10,1000)] = KC_F8,
        [CODE(10,1001)] = KC_F9,
        [CODE(10,1010)] = KC_F10,
        [CODE(10,1011)] = KC_F11,
        [CODE(10,1100)] = KC_F12,
        [CODE(10,1101)] = KC_F13,
        [CODE(10,1110)] = KC_F14,
        [CODE(10,1111)] = KC_F15,

        [CODE(11,0000)] = KC_F16,
        [CODE(11,0001)] = KC_F17,
        [CODE(11,0010)] = KC_F18,
        [CODE(11,0011)] = KC_F19,
        [CODE(11,0100)] = KC_F20,
        [CODE(11,0101)] = KC_F21,
        [CODE(11,0110)] = KC_F22,
        [CODE(11,0111)] = KC_F23,
        [CODE(11,1000)] = KC_F24,
        [CODE(11,1001)] = 0,
        [CODE(11,1010)] = 0,
        [CODE(11,1011)] = 0,
        [CODE(11,1100)] = 0,
        [CODE(11,1101)] = 0,
        [CODE(11,1110)] = 0,
        [CODE(11,1111)] = 0,
    },
};

const uint16_t PROGMEM keys_b[][32] = {
    // mmm^^ ^^^89

    [0] = {
        [CODE(00,000)] = 0,
        [CODE(00,001)] = KC_RIGHT_ALT,
        [CODE(00,010)] = KC_LEFT_GUI,
        [CODE(00,011)] = KEY(DOT),
        [CODE(00,100)] = KC_LEFT_ALT,
        [CODE(00,101)] = KEY(MINS),
        [CODE(00,110)] = KEY(COMM),
        [CODE(00,111)] = 0,

        [CODE(01,000)] = KC_LEFT_CTRL,
        [CODE(01,001)] = DE_CIRC,
        [CODE(01,010)] = 0,
        [CODE(01,011)] = KC_PAGE_DOWN,
        [CODE(01,100)] = DE_ACUT,
        [CODE(01,101)] = KC_RIGHT_SHIFT,
        [CODE(01,110)] = KC_RIGHT_CTRL,
        [CODE(01,111)] = KC_PAGE_UP,

        [CODE(10,000)] = KC_LEFT_SHIFT,
        [CODE(10,001)] = KEY(PLUS),
        [CODE(10,010)] = KEY(HASH),
        [CODE(10,011)] = KC_RIGHT_GUI,
        [CODE(10,100)] = KEY(LABK),
        [CODE(10,101)] = 0,
        [CODE(10,110)] = 0,
        [CODE(10,111)] = KC_INSERT,

        [CODE(11,000)] = KC_ENTER,
        [CODE(11,001)] = KC_TAB,
        [CODE(11,010)] = KC_ESCAPE,
        [CODE(11,011)] = KC_END,
        [CODE(11,100)] = KC_BACKSPACE,
        [CODE(11,101)] = KC_HOME,
        [CODE(11,110)] = KC_DELETE,
        [CODE(11,111)] = KC_RESERVED,
    },
    [1] = {
        [CODE(00,000)] = 0,
        [CODE(00,001)] = 0,
        [CODE(00,010)] = 0,
        [CODE(00,011)] = KC_KP_DOT,
        [CODE(00,100)] = 0,
        [CODE(00,101)] = KC_KP_MINUS,
        [CODE(00,110)] = KC_KP_DOT,
        [CODE(00,111)] = 0,

        [CODE(01,000)] = 0,
        [CODE(01,001)] = KC_KP_SLASH,
        [CODE(01,010)] = 0,
        [CODE(01,011)] = 0,
        [CODE(01,100)] = KC_KP_ASTERISK,
        [CODE(01,101)] = 0,
        [CODE(01,110)] = 0,
        [CODE(01,111)] = 0,

        [CODE(10,000)] = 0,
        [CODE(10,001)] = KC_KP_PLUS,
        [CODE(10,010)] = 0,
        [CODE(10,011)] = 0,
        [CODE(10,100)] = 0,
        [CODE(10,101)] = 0,
        [CODE(10,110)] = 0,
        [CODE(10,111)] = 0,

        [CODE(11,000)] = KC_KP_ENTER,
        [CODE(11,001)] = 0,
        [CODE(11,010)] = 0,
        [CODE(11,011)] = 0,
        [CODE(11,100)] = 0,
        [CODE(11,101)] = 0,
        [CODE(11,110)] = 0,
        [CODE(11,111)] = KC_RESERVED,
    },
};

const uint16_t PROGMEM control_codes_a[128] = {
    // ^^^^^ ^^--9

    [CODE(00101,11)] = CC_REPEAT_LAST_PRESS,
    [CODE(00011,11)] = CC_REPEAT_LAST_RESULT,

    [CODE(10000,10)] = CC_FLAG_MOD_SHIFT,
    [CODE(01000,10)] = CC_FLAG_MOD_CTRL,
    [CODE(00100,10)] = CC_FLAG_MOD_ALT,
    [CODE(00010,10)] = CC_FLAG_MOD_META,
    [CODE(10000,01)] = CC_FLAG_MOD_R_SHIFT,
    [CODE(01000,01)] = CC_FLAG_MOD_R_CTRL,
    [CODE(00100,01)] = CC_FLAG_MOD_R_ALT,
    [CODE(00010,01)] = CC_FLAG_MOD_R_META,

    [CODE(00011,10)] = CC_FLAG_LAYER_1,

    [CODE(00100,11)] = CC_FLAG_HOLD_PRESS,
    [CODE(00110,11)] = CC_FLAG_HOLD_RELEASE,
    [CODE(00001,11)] = CC_FLAG_HOLD_ONCE,
    [CODE(00111,11)] = CC_HOLD_RELEASE_ALL,

    [CODE(11100,10)] = CC_FLAG_LOCK_FLAG,
    [CODE(11100,01)] = CC_FLAG_LOCK_FUNCTION,

    [CODE(00111,00)] = CC_TYPE_BYTE_HEX,
    [CODE(00011,00)] = CC_TYPE_BYTE_BIN,
    [CODE(00101,00)] = CC_TYPE_BYTE_OCT,
    [CODE(00110,00)] = CC_TYPE_BYTE_DEC,
};

const uint16_t PROGMEM control_codes_b[128] = {
    // ^^^^^ ^^7-9

    [CODE(11100,01)] = CC_SET_OPTION,
    [CODE(00111,01)] = CC_ENTER_DIRECT_KEY_MODE,
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

            const uint16_t (*keymap)[64] = &keys_a[layer];
            const uint16_t value         = pgm_read_word(keymap[index]);

            uprintf("Keys A: %u | %02X", value, modifiers);
            send_key(value, modifiers);
        }

    } else if (MATCH(code, CODE(00000, 00011), MASK(00000, 00011))) {
        // mmm^^ ^^^89
        // Keys B (32 + shift, ctrl, alt)

        if (layer < ARRAY_SIZE(keys_b)) {
            const uint16_t index = (code & MASK(00011, 11100)) >> 2;

            const uint16_t (*keymap)[32] = &keys_b[layer];
            const uint16_t value         = pgm_read_word(keymap[index]);

            uprintf("Keys B: %u | %02X", value, modifiers);
            send_key(value, modifiers);
        }

    } else if (MATCH(code, CODE(00000, 00001), MASK(00000, 00111))) {
        // ^^^^^ ^^--9
        // Control Codes A (128)
        const uint16_t index = (code & MASK(11111, 11000)) >> 3;

        const uint16_t (*keymap)[128] = &control_codes_a;
        const uint16_t value          = pgm_read_word(keymap[index]);

        uprintf("Control Codes A: %u", value);
        send_control_code(value);

    } else if (MATCH(code, CODE(00000, 00101), MASK(00000, 00111))) {
        // ^^^^^ ^^7-9
        // Control Codes B (128)
        const uint16_t index = (code & MASK(11111, 11000)) >> 3;

        const uint16_t (*keymap)[128] = &control_codes_b;
        const uint16_t value          = pgm_read_word(keymap[index]);

        uprintf("Control Codes B: %u", value);
        send_control_code(value);
    }
}

// clang-format off
const uint16_t PROGMEM direct_key_keymap[][16][10] = {
    // Codes
    [0] = {
        [0] = {KC_0, KC_1, KC_2, KC_3, KC_4,                KC_5, KC_6, KC_7, KC_8, KC_9}
    },

    // QWERTY Rows
    [1] = {
        [0] = {KC_1, KC_2, KC_3, KC_4, KC_5,                KC_6, KC_7, KC_8, KC_9, KC_0}
    },
    [2] = {
        [0] = {KC_Q, KC_W, KC_E, KC_R, KC_T,                KC_Y, KC_U, KC_I, KC_O, KC_P}
    },
    [3] = {
        [0] = {KC_A, KC_S, KC_D, KC_F, KC_G,                KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON}
    },
    [4] = {
        [0] = {KC_Z, KC_X, KC_C, KC_V, KC_B,                KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH}
    },

    // Sokoban Controls
    [8] = {
        [0] = {KC_A, KC_S, KC_W, KC_D, KC_SPACE,            KC_ENTER, KC_Z, KC_ESCAPE, KC_R, KC_Y}
    },
    [9] = {
        [0] = {KC_A, KC_S, KC_W, KC_D, KC_SPACE,            KC_ENTER, KC_Z, KC_ESCAPE, KC_R, KC_X}
    },

    // WASD + Arrow Keys
    [12] = {
        [0] = {KC_A, KC_S, KC_W, KC_D, KC_SPACE,           KC_LEFT_SHIFT, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT}
    },
    // WASD + Mouse
    [13] = {
        [0] = {KC_A, KC_S, KC_W, KC_D, QK_MOUSE_BUTTON_1,  QK_MOUSE_BUTTON_2, QK_MOUSE_CURSOR_LEFT, QK_MOUSE_CURSOR_DOWN, QK_MOUSE_CURSOR_UP, QK_MOUSE_CURSOR_RIGHT}
    },
    // Modifiers + Mouse
    [14] = {
        [0] = {KC_LEFT_SHIFT, KC_LEFT_CTRL, KC_LEFT_ALT, KC_LEFT_GUI, QK_MOUSE_BUTTON_1,
                        QK_MOUSE_BUTTON_2, QK_MOUSE_CURSOR_LEFT, QK_MOUSE_CURSOR_DOWN, QK_MOUSE_CURSOR_UP, QK_MOUSE_CURSOR_RIGHT}
    },

    // Hollow Knight Controls
    [16] = {
        [0] = {KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_Z,     KC_A, KC_X, KC_C, KC_F, MCH_DK_LAYER_1},
        [1] = {_______, _______, _______, _______, _______, KC_TAB, KC_D, KC_S, MCH_DK_LAYER_2, _______},
        [2] = {_______, _______, _______, _______, _______, KC_I, KC_ESCAPE, 0, _______, _______},
    },

    // Generic Layered Game Controls
    [18] = {
        [0] = {KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_SPACE,
                    KC_A, KC_B, KC_C, KC_D, MCH_DK_LAYER_1},

        [1] = {_______, _______, _______, _______, _______,
                    MCH_DK_LAYER_5, MCH_DK_LAYER_4, MCH_DK_LAYER_3, MCH_DK_LAYER_2, _______},

        [2] = {_______, _______, _______, _______, _______,
                    KC_E, KC_F, KC_G, _______, _______},

        [3] = {_______, _______, _______, _______, _______,
                    KC_H, KC_I, _______, KC_J, _______},

        [4] = {_______, _______, _______, _______, _______,
                    KC_K, _______, KC_L, KC_M, _______},

        [5] = {KC_0, KC_1, KC_2, KC_3, KC_4,
                    _______, KC_6, KC_7, KC_8, _______},
    }
};
// clang-format on

const size_t direct_key_keymap_count = ARRAY_SIZE(direct_key_keymap);

const uint16_t cancel_code = CODE(00000, 00001);
const uint16_t noop_code   = CODE(11111, 11111);

// ########################################################
// #                                                      #
// #                    OPTIONS                           #
// #                                                      #
// ########################################################

void default_options_init(options_state_t* options_state) {
    options_state->tap_code_delay = 0;
}

// clang-format off
const option_mapping_t option_mapping = {
    .tap_code_delay = CODE(10001,0000)
};
// clang-format on

// ########################################################
// #                                                      #
// #                    PARSING                           #
// #                                                      #
// ########################################################

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
