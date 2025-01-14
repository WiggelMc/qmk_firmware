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

#include "action.h"
#include "state_logic.h"

bool process_chorder_logic(uint16_t keycode, keyrecord_t *record);

void send_key(uint16_t keycode, modifiers_t modifiers);
void send_control_code(uint16_t control_code);

void hold_release_all(void);
void cancel(void);
void process_code(uint16_t code);
void enter_direct_key_mode(uint16_t index);

#endif
