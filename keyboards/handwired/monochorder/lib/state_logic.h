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

#ifndef STATE_LOGIC_H
#define STATE_LOGIC_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    M_L_CTRL  = 1 << 0,
    M_L_SHIFT = 1 << 1,
    M_L_ALT   = 1 << 2,
    M_L_META  = 1 << 3,
    M_R_CTRL  = 1 << 4,
    M_R_SHIFT = 1 << 5,
    M_R_ALT   = 1 << 6,
    M_R_META  = 1 << 7,
} modifiers_t;

typedef enum { HOLD_OFF, HOLD_PRESS, HOLD_RELEASE, HOLD_ONCE } hold_mode_t;

typedef struct {
    hold_mode_t hold_mode;
    bool        locked_hold_mode;

    uint8_t layer;
    bool    locked_layer;

    modifiers_t modifiers;
    modifiers_t locked_modifiers;

    bool function_lock;
} flags_normal_t;

typedef struct {
    bool flag_lock;
} flags_flag_t;

typedef struct {
    flags_normal_t normal;
    flags_flag_t   flag;
} flags_t;

typedef struct state_struct state_t;

typedef struct {
    bool (*running)(uint16_t code, state_t *state);
    uint16_t data[16];
} function_state_t;

typedef enum {
    PHASE_IDLE,
    PHASE_PRESS,
} chorder_phase_t;

typedef struct {
    uint16_t last_code;
    uint16_t last_keycode;
} repeat_state_t;

typedef struct {
    uint16_t hold_keys[32];
    uint16_t hold_once_keys[32];
} hold_state_t;

typedef struct {
    chorder_phase_t  current_phase;
    flags_t          flags;
    function_state_t function_state;
    repeat_state_t   repeat_state;
    hold_state_t     hold_state;
} chord_state_t;

typedef struct {
    uint16_t active_index;
} direct_key_state_t;

typedef enum {
    MODE_CHORD,
    MODE_DIRECT_INPUT,
} chorder_mode_t;

typedef struct state_struct {
    chorder_mode_t     current_mode;
    uint16_t           active_codes;
    chord_state_t      chord_state;
    direct_key_state_t direct_key_state;
} state_t;

void init_flags_normal(flags_normal_t *flags);
void reset_unlocked_flags_normal(flags_normal_t *flags);
void init_flags_flag(flags_flag_t *flags);
void reset_unlocked_flags_flag(flags_flag_t *flags);
void init_flags(flags_t *flags);
void reset_unlocked_flags(flags_t *flags);

void init_function_state(function_state_t *function_state);
void init_repeat_state(repeat_state_t *repeat_state);
void init_hold_state(hold_state_t *hold_state);
void init_chord_state(chord_state_t *chord_state);
void init_direct_key_state(direct_key_state_t *direct_key_state);

void init_state(state_t *state);
void reset_state(state_t *state);

#endif
