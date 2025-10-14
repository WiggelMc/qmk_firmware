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

from __future__ import annotations
from dataclasses import dataclass


@dataclass(frozen=True)
class PrefixedDict:
    prefix: str
    dict: dict

    @classmethod
    def from_dict(cls, data: dict):
        return cls(
            prefix="",
            dict=data
        )

@dataclass(frozen=True)
class Comment:
    text: str


@dataclass(frozen=True)
class SimpleChord:
    chord: str
    raw: str


SimpleChordList = list[SimpleChord | Comment]
