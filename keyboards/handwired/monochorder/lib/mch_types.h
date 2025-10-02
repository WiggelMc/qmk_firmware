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
} options_state_t;
