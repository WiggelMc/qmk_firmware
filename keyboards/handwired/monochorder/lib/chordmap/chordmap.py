from __future__ import annotations
from dataclasses import dataclass


@dataclass
class ChordMap:
    schema: str
    name: str
    author: str
    keyAmount: int
    keyPrefix: str
    generation: Generation
    input: Input
    options: Options
    specialChords: SpecialChords
    chords: Chords
    directKeys: DirectKeys

@dataclass
class Generation:
    headerLines: list[str]

@dataclass
class Input:
    uint8m: str
    uint9: str
    chord: str

@dataclass
class Options:
    tapCodeDelay: Option
    tapCodeGap: Option

@dataclass
class Option:
    default: int
    chords: list[str]

@dataclass
class SpecialChords:
    noop: list[str]
    cancel: list[str]
    zero: list[str]

@dataclass
class Chords:
    pass # TODO

@dataclass
class DirectKeys:
    pass # TODO
