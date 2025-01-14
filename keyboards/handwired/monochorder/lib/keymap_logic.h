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

#ifndef KEYMAP_LOGIC_H
#define KEYMAP_LOGIC_H

#include <stdbool.h>
#include <stdint.h>
#include "quantum.h"

extern void                   process_chord(uint16_t code, uint8_t layer);
extern const uint16_t PROGMEM direct_key_keymap[][10];
extern const size_t           direct_key_keymap_count;

extern const uint16_t cancel_code;
extern const uint16_t noop_code;

typedef struct {
    uint8_t byte;
    bool    mod;
} read_byte_data_t;

extern bool read_byte_data(uint16_t code, read_byte_data_t *out_data);
extern bool read_9bit_data(uint16_t code, uint16_t *out_data);

typedef struct {
    uint16_t tap_code_delay;
} option_mapping_t;

extern const option_mapping_t option_mapping;

#define MATCH(value, pattern, mask) (((value) & (mask)) == ((pattern) & (mask)))
#define CODE(v1, v2) 0b##v1##v2
#define MASK(v1, v2) CODE(v1, v2)
#define TEST_BITS(value, mask) (((value) & (mask)) != 0)

#define KC_RESERVED 0

enum custom_keycodes { MCH_0 = SAFE_RANGE, MCH_1, MCH_2, MCH_3, MCH_4, MCH_5, MCH_6, MCH_7, MCH_8, MCH_9, MCH_R };
const uint16_t MCH_SAFE_RANGE;

enum control_codes {
    CC_CANCEL = (uint16_t)1,
    CC_SET_OPTION,
    CC_REPEAT_LAST_PRESS,
    CC_REPEAT_LAST_RESULT,

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
    CC_FLAG_HOLD_ONCE,

    CC_FLAG_LOCK_FLAG,
    CC_FLAG_LOCK_FUNCTION,

    CC_ENTER_DIRECT_KEY_MODE,
    CC_HOLD_RELEASE_ALL,

    CC_TYPE_BYTE_HEX,
    CC_TYPE_BYTE_BIN,
    CC_TYPE_BYTE_OCT,
    CC_TYPE_BYTE_DEC,
};

#endif
