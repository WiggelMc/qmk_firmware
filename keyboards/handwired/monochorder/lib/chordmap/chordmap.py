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

from validate import PrefixedDict, get_dict, get_ranged_int, get_str


@dataclass
class MapProperties:
    name: str
    author: str
    key_amount: int
    key_prefix: str
    generation: Generation

    @classmethod
    def from_dict(cls, data: PrefixedDict) -> MapProperties:
        return cls(
            name = get_str(data, 'name'),
            author = get_str(data, 'author'),
            key_amount = get_ranged_int(data, 'keyAmount', (2, 16)),
            key_prefix = get_str(data, 'keyPrefix'),
            generation = Generation.from_dict(get_dict(data, 'generation')),
        )

@dataclass
class Generation:
    header_lines: list[str]

    @classmethod
    def from_dict(cls, data: PrefixedDict) -> Generation:
        return cls(
            header_lines = ["TODO"],
        )

@dataclass
class ChordMap:
    properties: MapProperties
    inputs: Input
    options: Options
    special_chords: SpecialChords
    chords: Chords
    direct_keys: DirectKeys

    @classmethod
    def from_dict(cls, data: PrefixedDict) -> ChordMap:
        properties = MapProperties.from_dict(data)
        return cls(
            properties = properties,
            inputs = Input.from_dict(get_dict(data, 'input'), properties),
            options = Options.from_dict(get_dict(data, 'options'), properties),
            special_chords = SpecialChords.from_dict(get_dict(data, 'specialChords'), properties),
            chords = Chords.from_dict(get_dict(data, 'chords'), properties),
            direct_keys = DirectKeys.from_dict(get_dict(data, 'directKeys'), properties),
        )

@dataclass
class Input:
    uint8m: str
    uint9: str

    @classmethod
    def from_dict(cls, data: PrefixedDict, properties: MapProperties) -> Input:
        ...

@dataclass
class Options:
    tap_code_delay: Option
    tap_code_gap: Option

    @classmethod
    def from_dict(cls, data: PrefixedDict, properties: MapProperties) -> Options:
        return cls(
            tap_code_delay = Option.from_dict(get_dict(data, 'tapCodeDelay'), properties),
            tap_code_gap = Option.from_dict(get_dict(data, 'tapCodeGap'), properties),
        )

@dataclass
class Option:
    default: int
    chords: list[str]

    @classmethod
    def from_dict(cls, data: PrefixedDict, properties: MapProperties) -> Option:
        ...

@dataclass
class SpecialChords:
    noop: list[str]
    cancel: list[str]
    zero: list[str]

    @classmethod
    def from_dict(cls, data: PrefixedDict, properties: MapProperties) -> SpecialChords:
        ...

@dataclass
class Chords:
    pass # TODO

    @classmethod
    def from_dict(cls, data: PrefixedDict, properties: MapProperties) -> Chords:
        ...

@dataclass
class DirectKeys:
    pass # TODO

    @classmethod
    def from_dict(cls, data: PrefixedDict, properties: MapProperties) -> DirectKeys:
        ...
