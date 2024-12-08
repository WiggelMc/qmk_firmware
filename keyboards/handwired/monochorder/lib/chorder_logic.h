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


#ifndef CHORDER_LOGIC_H
#define CHORDER_LOGIC_H

#include QMK_KEYBOARD_H
#include "action.h"

#define MATCH(value, pattern, mask) ((value & mask) == (pattern & mask))
#define CODE(v1, v2) 0b ## v1 ## v2
#define MASK(v1, v2) CODE(v1,v2)

#define ARR_LEN(arr) (sizeof(arr) / sizeof(*arr))

#define KC_RESERVED 0


extern void process_chord(uint16_t keycode, uint8_t layer);
extern const uint16_t PROGMEM direct_key_keymap[10];

enum custom_keycodes {
    MCH_0 = SAFE_RANGE,
    MCH_1,
    MCH_2,
    MCH_3,
    MCH_4,
    MCH_5,
    MCH_6,
    MCH_7,
    MCH_8,
    MCH_9,
    MCH_R
};
const uint16_t MCH_SAFE_RANGE;

typedef enum {
    M_L_CTRL = 1 << 0,
    M_L_SHIFT = 1 << 1,
    M_L_ALT = 1 << 2,
    M_L_META = 1 << 3,
    M_R_CTRL = 1 << 4,
    M_R_SHIFT = 1 << 5,
    M_R_ALT = 1 << 6,
    M_R_META = 1 << 7,
} modifiers_t;

bool process_chorder_logic(uint16_t keycode, keyrecord_t *record);

void send_key(uint16_t keycode, modifiers_t modifiers);
void send_control_code(uint16_t control_code);

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

    CC_ENTER_SPECIAL_MODE,
    CC_HOLD_RELEASE_ALL,

    CC_TYPE_BYTE_HEX,
    CC_TYPE_BYTE_BIN,
    CC_TYPE_BYTE_OCT,
    CC_TYPE_BYTE_DEC,
};

typedef enum {
    HOLD_OFF,
    HOLD_PRESS,
    HOLD_RELEASE,
    HOLD_ONCE
} hold_mode_t;

typedef struct {
    hold_mode_t hold_mode;
    bool locked_hold_mode;

    uint8_t layer;
    bool locked_layer;

    modifiers_t modifiers;
    modifiers_t locked_modifiers;

    bool function_lock;
} flags_normal_t;

typedef struct {
    bool flag_lock;
} flags_flag_t;

typedef struct {
    flags_normal_t normal;
    flags_flag_t flag;
} flags_t;

typedef struct state_struct state_t;

typedef struct {
    bool (*running)(uint16_t code, state_t *state);
    uint16_t data[16];
} function_state_t;

typedef struct state_struct {
    flags_t flags;
    function_state_t function_state;
} state_t;

typedef enum {
    PHASE_IDLE,
    PHASE_PRESS,
} chorder_phase_t;

typedef enum {
    MODE_CHORD,
    MODE_DIRECT_INPUT,
} chorder_mode_t;

typedef struct {
    uint16_t active_codes;
    chorder_phase_t current_phase;
    chorder_mode_t current_mode;
} input_state_t;



#endif
