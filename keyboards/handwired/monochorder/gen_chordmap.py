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

import json
from pathlib import Path
import sys

from lib.chordmap.codegen import generate_code

def main():
    input_file = Path(sys.argv[1])
    output_c_file = Path(sys.argv[2])
    output_h_file = Path(sys.argv[3])

    with open(input_file) as f:
        input_map = json.load(f)

    output = generate_code()

    output_c_file.write_text(output.chordmap_c)
    output_h_file.write_text(output.chordmap_data_h)


if __name__ == '__main__':
    main()
