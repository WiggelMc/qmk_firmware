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

#include "mch_keymap.h"
#include "chordmap.h"

__attribute__((weak)) bool read_input_uint8m(chord_t chord, uint8m_t *out_data) {
    return read_input_uint8m_gen(chord, out_data);
}
__attribute__((weak)) bool read_input_uint9(chord_t chord, uint9_t *out_data) {
    return read_input_uint9_gen(chord, out_data);
}
__attribute__((weak)) bool read_input_chord(chord_t chord, chord_t *out_data) {
    return read_input_chord_gen(chord, out_data);
}

__attribute__((weak)) bool reset_option_values(options_state_t *options) {
    return reset_option_values_gen(options);
}
__attribute__((weak)) bool reset_option_value(chord_t chord, options_state_t *options) {
    return reset_option_value_gen(chord, options);
}
__attribute__((weak)) bool set_option_value(chord_t chord, uint9_t value, options_state_t *options) {
    return set_option_value_gen(chord, value, options);
}

__attribute__((weak)) bool is_chord_noop(chord_t chord) {
    return is_chord_noop_gen(chord);
}
__attribute__((weak)) bool is_chord_cancel(chord_t chord) {
    return is_chord_cancel_gen(chord);
}

__attribute__((weak)) keycode_t get_mapped_chord_key(chord_t chord, layer_t layer) {
    return get_mapped_chord_key_gen(chord, layer);
}

__attribute__((weak)) direct_key_index_t get_direct_key_index(chord_t chord) {
    return get_direct_key_index_gen(chord);
}
__attribute__((weak)) keycode_t get_mapped_direct_key(direct_key_index_t dk_index, chord_bit_index_t bit_index) {
    return get_mapped_direct_key_gen(dk_index, bit_index);
}
