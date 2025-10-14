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
from typing import Union
import re

from .types import PrefixedDict, SimpleChordList, Comment, SimpleChord
from .chordmap import MapProperties


def validate_none(data, field_name: str):
    if data is None:
        raise TypeError(f"Field '{field_name}' does not exist.")


def validate_dict(data, field_name: str) -> dict:
    validate_none(data, field_name)

    if not isinstance(data, dict):
        raise TypeError(f"Field '{field_name}' must be an object.")

    return data


def get_dict(data: PrefixedDict, field_name: str) -> PrefixedDict:
    return PrefixedDict(
        prefix=f"{data.prefix}{field_name}.",
        dict=validate_dict(data.dict.get(field_name),
                           f"{data.prefix}{field_name}")
    )



def validate_str(data, field_name: str) -> str:
    validate_none(data, field_name)

    if not isinstance(data, str):
        raise TypeError(f"Field '{field_name}' must be a string.")

    return data


def get_str(data: PrefixedDict, field_name: str) -> str:
    return validate_str(data.dict.get(field_name), data.prefix + field_name)


def validate_int(data, field_name: str) -> int:
    validate_none(data, field_name)

    if not isinstance(data, int):
        raise TypeError(f"Field '{field_name}' must be an integer.")

    return data


def get_int(data: PrefixedDict, field_name: str) -> int:
    return validate_int(data.dict.get(field_name), data.prefix + field_name)


def get_ranged_int(data: PrefixedDict, field_name: str, bounds: tuple[int, int]) -> int:
    amount = validate_int(data.dict.get(field_name), data.prefix + field_name)

    min_bound, max_bound = bounds

    if not (min_bound <= amount <= max_bound):
        raise TypeError(
            f"Field '{field_name}' must be in the range [{min_bound},{max_bound}].")

    return amount


chord_regex = "^[ 01-]+$"

def validate_simple_chord_list(data, field_name: str, properties: MapProperties) -> SimpleChordList:
    validate_none(data, field_name)

    if not isinstance(data, list):
        raise TypeError(f"Field '{field_name}' must be an array.")

    items: SimpleChordList = []

    for i, item in enumerate(data):
        inner_field_name = field_name + f"[{i}]"
        item = validate_str(item, inner_field_name)

        if item.startswith("/"):
            items.append(Comment(item.removeprefix("/")))
        else:
            if re.search(chord_regex, item) is None:
                raise TypeError(
                    f"Field '{inner_field_name}' has an invalid structure."
                )

            stripped_item = item.replace(" ", "")
            if len(stripped_item) != properties.key_amount:
                raise TypeError(
                    f"Field '{inner_field_name}' has the wrong number of keys."
                )

            items.append(SimpleChord(chord=stripped_item, raw=item))

    return items


def get_simple_chord_list(data: PrefixedDict, field_name: str, properties: MapProperties) -> SimpleChordList:
    return validate_simple_chord_list(data.dict.get(field_name), data.prefix + field_name, properties)



