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

#ifndef MCH_KEYMAP_H
#define MCH_KEYMAP_H

#include "mch_types.h"

extern bool read_input_uint8m(chord_t chord, uint8m_t *out_data);
extern bool read_input_uint9(chord_t chord, uint9_t *out_data);
extern bool read_input_chord(chord_t chord, chord_t *out_data);

extern bool reset_option_values(options_state_t *options);
extern bool reset_option_value(chord_t chord, options_state_t *options);
extern bool set_option_value(chord_t chord, uint9_t value, options_state_t *options);

extern bool is_chord_noop(chord_t chord);
extern bool is_chord_cancel(chord_t chord);
extern bool is_chord_zero(chord_t chord);

extern keycode_t get_mapped_chord_key(chord_t chord, layer_t layer);

extern direct_key_index_t get_direct_key_index(chord_t chord);
extern keycode_t          get_mapped_direct_key(direct_key_index_t dk_index, chord_bit_index_t bit_index);

#endif
