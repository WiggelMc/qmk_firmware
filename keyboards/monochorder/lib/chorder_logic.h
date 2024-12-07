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

#define MATCH(value, pattern, mask) (value & mask) == (pattern & mask)
#define CODE(v1, v2) 0b ## v1 ## v2
#define MASK(v1, v2) CODE(v1,v2)

extern bool process_chord(uint16_t keycode);
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
// const uint16_t EEEEEMCH_SAFE_RANGE = MCH_R + 1;

bool process_chorder_logic(uint16_t keycode, keyrecord_t *record);

void send_key(uint16_t keycode, uint8_t modifiers);
void send_control_code(uint16_t control_code);



#endif
