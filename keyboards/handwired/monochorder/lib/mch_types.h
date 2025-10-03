/* Copyright 2025 Kim Hollstein (WiggelMc)
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

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "quantum_keycodes.h"

typedef uint16_t keycode_t;
typedef uint8_t  layer_t;
typedef uint8_t  chord_bit_index_t;
typedef uint16_t direct_key_index_t;

typedef struct {
    uint8_t byte;
    bool    mod;
} uint8m_t;
typedef uint16_t uint9_t;
typedef uint16_t chord_t;

typedef struct {
    uint9_t tap_code_delay;
    uint9_t tap_code_gap;
} options_state_t;

#define KC_RESERVED 0

enum custom_keycodes {
    MCH_0 = SAFE_RANGE + 3,
    MCH_1,
    MCH_2,
    MCH_3,
    MCH_4,
    MCH_5,
    MCH_6,
    MCH_7,
    MCH_8,
    MCH_9,
    MCH_A,
    MCH_B,
    MCH_C,
    MCH_D,
    MCH_E,
    MCH_F,

    MCH_R,

    MCH_DK_LAYER_1,
    MCH_DK_LAYER_2,
    MCH_DK_LAYER_3,
    MCH_DK_LAYER_4,
    MCH_DK_LAYER_5,
    MCH_DK_LAYER_6,
    MCH_DK_LAYER_7,
    MCH_DK_LAYER_8,
    MCH_DK_LAYER_9,
    MCH_DK_LAYER_10,
    MCH_DK_LAYER_11,
    MCH_DK_LAYER_12,
    MCH_DK_LAYER_13,
    MCH_DK_LAYER_14,
    MCH_DK_LAYER_15,

    CC_CANCEL,
    CC_RESET,

    CC_SET_OPTION,
    CC_RESET_OPTION,

    CC_REPEAT_LAST_PRESS,
    CC_REPEAT_LAST_RESULT,

    CC_ENTER_DIRECT_KEY_MODE,
    CC_ENTER_TRAINER_MODE,
    CC_HOLD_RELEASE_ALL,
    CC_DETACH_ALL,

    CC_TYPE_BYTE_HEX,
    CC_TYPE_BYTE_BIN,
    CC_TYPE_BYTE_OCT,
    CC_TYPE_BYTE_DEC,

    CC_FLAG_MOD_META,
    CC_FLAG_MOD_CTRL,
    CC_FLAG_MOD_SHIFT,
    CC_FLAG_MOD_ALT,
    CC_FLAG_MOD_R_META,
    CC_FLAG_MOD_R_CTRL,
    CC_FLAG_MOD_R_SHIFT,
    CC_FLAG_MOD_R_ALT,

    CC_FLAG_LAYER_1,
    CC_FLAG_LAYER_2,
    CC_FLAG_LAYER_3,
    CC_FLAG_LAYER_4,

    CC_FLAG_HOLD_PRESS,
    CC_FLAG_HOLD_RELEASE,
    CC_FLAG_ATTACH,
    CC_FLAG_DETACH,

    CC_FLAG_LOCK_FLAG,
    CC_FLAG_LOCK_FUNCTION,

    MCH_SAFE_RANGE,
};
