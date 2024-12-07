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

#ifndef MATRIX_ROWS
#error "MATRIX_ROWS undeclared. Must be set when building."
#define MATRIX_ROWS 1
#endif
#ifndef MATRIX_COLS
#error "MATRIX_COLS undeclared. Must be set when building."
#define MATRIX_COLS 1
#endif
#ifndef LAYOUT_monochorder
#error "LAYOUT_monochorder undeclared. Must be set when building."
#define LAYOUT_monochorder(...) 0
#endif


#include "action.h"
#include QMK_KEYBOARD_H
#include "../chording/chorder_logic.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
      * │ 0 │ 1 │ 2 │ 3 │ 4 │       │ 5 │ 6 │ 7 │ 8 │ 9 │
      * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
      *
      *                   ┌───┐   ┌───┐
      *                   │ R │   │ R │
      *                   └───┘   └───┘
      */
    [0] = LAYOUT_monochorder(
        MCH_0,  MCH_1,  MCH_2,  MCH_3,  MCH_4,    MCH_5,  MCH_6,  MCH_7,  MCH_8,  MCH_9,
                                        MCH_R,    MCH_R
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_chorder_logic(keycode, record)) {
        return false;
    }

    return true;
}

const uint16_t PROGMEM chorder_keymap[] = {
    1,
    2,
    3,
};

const uint16_t PROGMEM direct_key_keymap[10] = {
    KC_0,KC_1,KC_2,KC_3,KC_4,    KC_5,KC_6,KC_7,KC_8,KC_9,
};
