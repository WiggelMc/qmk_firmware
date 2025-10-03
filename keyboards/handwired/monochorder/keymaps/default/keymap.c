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

#include QMK_KEYBOARD_H

#include <stdint.h>
#include "../../lib/mch_types.h"

// #include "../../lib/chordmap.h"
// #include "../../lib/mch_keymap.h"

// clang-format off
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐       ┌───┬───┬───┬───┐
     * │ 9 │ 8 │ 7 │ 6 │       │ 3 │ 2 │ 1 │ 0 │
     * └───┴───┴───┴───┘       └───┴───┴───┴───┘
     *
     *         ┌───┬───┐       ┌───┬───┐
     *         │ R │ 5 │       │ 4 │ R |
     *         └───┴───┘       └───┴───┘
     */
    // [0] = {}};
    [0] = LAYOUT(MCH_9, MCH_8, MCH_7, MCH_6,    MCH_3, MCH_2, MCH_1, MCH_0,
		   	                   MCH_R, MCH_5,    MCH_4, MCH_R
    )};
// clang-format on
