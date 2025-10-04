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

#include "../mch_types.h"

bool is_any_mch_code(keycode_t code) {
    return code >= SECTION_MCH_KEYBOARD && code < MCH_SAFE_RANGE;
}
bool is_mch_keyboard_code(keycode_t code) {
    return code >= SECTION_MCH_KEYBOARD && code < SECTION_MCH_DK;
}
bool is_mch_direct_key_code(keycode_t code) {
    return code >= SECTION_MCH_DK && code < SECTION_MCH_CC;
}
bool is_mch_control_code(keycode_t code) {
    return code >= SECTION_MCH_CC && code < MCH_SAFE_RANGE;
}
