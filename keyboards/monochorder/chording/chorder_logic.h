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

#ifndef SAFE_RANGE
#error "MATRIX_ROWS undeclared. Must be set when building."
#define SAFE_RANGE 1
#endif

#ifndef CHORDER_KEYMAP
#define CHORDER_KEYMAP


#include "action.h"

extern const uint16_t PROGMEM chorder_keymap[];
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
const uint16_t MCH_SAFE_RANGE = MCH_R + 1;

bool process_chorder_logic(uint16_t keycode, keyrecord_t *record);

#endif
