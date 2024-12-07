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

#include "action.h"
#include "chorder_logic.h"
#include QMK_KEYBOARD_H

enum chorder_phase {
    IDLE_PHASE,
    PRESS_PHASE,
};

enum chorder_mode {
    CHORD_MODE,
    DIRECT_KEY_MODE,
};

uint16_t active_codes = 0;
enum chorder_phase current_phase = IDLE_PHASE;
enum chorder_mode current_mode = CHORD_MODE;

void submit_chord(uint16_t codes) {
    //TODO
}

void handle_chord_mode(uint16_t code, bool pressed) {
    if (pressed) {
        current_phase = PRESS_PHASE;
        active_codes |= ((uint16_t)1 << code);
    } else {
        if (current_phase == PRESS_PHASE) {
            submit_chord(active_codes);
        }
        current_phase = IDLE_PHASE;
        active_codes &= ~((uint16_t)1 << code);
    }
}

void handle_reset() {
    current_mode = CHORD_MODE;
}

void handle_direct_key_mode(uint16_t code, bool pressed) {
    uint16_t key = pgm_read_word(&direct_key_keymap[code]);
    if (pressed) {
        register_code(key);
    } else {
        unregister_code(key);
    }
}

void handle_input(uint16_t code, bool pressed) {
    switch (current_mode) {
        case CHORD_MODE:
            handle_chord_mode(code, pressed);
            break;
        case DIRECT_KEY_MODE:
            handle_direct_key_mode(code, pressed);
            break;
    }
}

bool process_chorder_logic(uint16_t keycode, keyrecord_t *record) {

    if (keycode >= MCH_0 && keycode <= MCH_9) {

        handle_input(keycode - MCH_0, record->event.pressed);
        return false;

    } else if (keycode == MCH_R) {

        if (record->event.pressed) {
            handle_reset();
            pgm_read_word(&chorder_keymap[0]);
        }
        return false;
    }

    return true;
}
