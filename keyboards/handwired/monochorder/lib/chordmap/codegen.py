''' Copyright 2025 Kim Hollstein (WiggelMc)
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
'''

from dataclasses import dataclass
from pathlib import Path
from string import Template
import textwrap


@dataclass
class GenerationOutput:
    chordmap_c: str
    chordmap_data_h: str


def generate_code():
    dir_path = Path(__file__).parent.resolve()

    chordmap_c_template = dir_path.joinpath(
        'chordmap.c.template'
    ).read_text()
    chordmap_data_h_template = dir_path.joinpath(
        'chordmap_data.h.template'
    ).read_text()

    return GenerationOutput(
        chordmap_c=Template(chordmap_c_template).substitute(
            key_prefix='',
            key_amount='',
            chord_definitions='',
            dk_mapping='',
            input_uint8m_code='',
            input_uint8m_mod='',
            input_uint8m_bits='',
            input_uint9_code='',
            input_uint9_bits='',
            reset_options='',
            reset_option_switch='',
            set_option_switch='',
            special_noop_check='',
            special_cancel_check='',
            special_zero_check='',
            trainer_dk_index='',
        ),
        chordmap_data_h=Template(chordmap_data_h_template).substitute(
            layer_size='',
            layer_index='',
            chord_mapping='',
            chord_mods='',
            dk_index_mapping='',
            option_index_mapping='',
        ),
    )
