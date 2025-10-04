# Copyright 2025 Kim Hollstein (WiggelMc)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.



#######################################################################
#                                                                     #
#                                                                     #
#                           chordmap                                  #
#                                                                     #
#                                                                     #
#######################################################################

PYTHON ?= python3
KEYBOARD_DIR = keyboards/$(KEYBOARD)

$(KEYBOARD_DIR)/keymaps/%/chordmap.c: $(KEYBOARD_DIR)/keymaps/%/chordmap.json $(KEYBOARD_DIR)/gen_chordmap.py
	@echo "generate chordmap for $(KEYBOARD):$*..."
	$(PYTHON) $(KEYBOARD_DIR)/gen_chordmap.py $(KEYBOARD_DIR)/keymaps/$*/chordmap.json $(KEYBOARD_DIR)/keymaps/$*/chordmap.c

SRC += $(KEYBOARD_DIR)/keymaps/$(KEYMAP)/chordmap.c



#######################################################################
#                                                                     #
#                                                                     #
#                           libs                                      #
#                                                                     #
#                                                                     #
#######################################################################

## chording
SRC += lib/chording/chording.c

## direct_key
SRC += lib/direct_key/direct_key.c

## function
SRC += lib/function/function.c

## keypress
SRC += lib/keypress/keypress.c

## mch_keyboard
SRC += lib/mch_keyboard/mch_keyboard.c

## mch_keymap
SRC += lib/mch_keymap/mch_keymap.c

## mch_types
SRC += lib/mch_types/mch_types.c

## options
SRC += lib/options/options.c



#######################################################################
#                                                                     #
#                                                                     #
#                           QMK Flags                                 #
#                                                                     #
#                                                                     #
#######################################################################

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = vendor
