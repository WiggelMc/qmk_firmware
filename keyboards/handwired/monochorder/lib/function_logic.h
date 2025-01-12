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

#ifndef FUNCTION_LOGIC_H
#define FUNCTION_LOGIC_H

#include <stdbool.h>
#include <stdint.h>
#include "state_logic.h"

bool (*get_function(uint16_t control_code))(uint16_t code, state_t *state);

#define PHASE(state) state->chord_state.function_state.data[0]

#endif
