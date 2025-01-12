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

#include "state_logic.h"
#include <string.h>

void init_flags_normal(flags_normal_t *flags) {
    flags->hold_mode        = HOLD_OFF;
    flags->locked_hold_mode = false;

    flags->layer        = 0;
    flags->locked_layer = false;

    flags->modifiers        = 0;
    flags->locked_modifiers = 0;

    flags->function_lock = false;
}

void reset_unlocked_flags_normal(flags_normal_t *flags) {
    if (!flags->locked_hold_mode) {
        flags->hold_mode = HOLD_OFF;
    }

    if (!flags->locked_layer) {
        flags->layer = 0;
    }

    flags->modifiers = flags->modifiers & flags->locked_modifiers;

    flags->function_lock = false;
}

void init_flags_flag(flags_flag_t *flags) {
    flags->flag_lock = false;
}

void reset_unlocked_flags_flag(flags_flag_t *flags) {
    init_flags_flag(flags);
}

void init_flags(flags_t *flags) {
    init_flags_normal(&flags->normal);
    init_flags_flag(&flags->flag);
}

void reset_unlocked_flags(flags_t *flags) {
    reset_unlocked_flags_normal(&flags->normal);
    reset_unlocked_flags_flag(&flags->flag);
}

void init_function_state(function_state_t *function_state) {
    function_state->running = NULL;
    memset(function_state->data, 0, sizeof(function_state->data));
}

void init_repeat_state(repeat_state_t *repeat_state) {
    repeat_state->last_code    = 0;
    repeat_state->last_keycode = 0;
}

void init_hold_state(hold_state_t *hold_state) {
    memset(hold_state->hold_keys, 0, sizeof(hold_state->hold_keys));
    memset(hold_state->hold_once_keys, 0, sizeof(hold_state->hold_once_keys));
}

void init_chord_state(chord_state_t *chord_state) {
    chord_state->current_phase = PHASE_IDLE;
    init_flags(&chord_state->flags);
    init_function_state(&chord_state->function_state);
    init_repeat_state(&chord_state->repeat_state);
    init_hold_state(&chord_state->hold_state);
}

void init_direct_key_state(direct_key_state_t *direct_key_state) {
    direct_key_state->active_index = 0;
}

void reset_state(state_t *state) {
    state->current_mode = MODE_CHORD;
    init_chord_state(&state->chord_state);
    init_direct_key_state(&state->direct_key_state);
}

void init_state(state_t *state) {
    state->active_codes = 0;
    reset_state(state);
}
