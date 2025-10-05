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

MCH_PYTHON_SRC += $(wildcard $(KEYBOARD_DIR)/lib/*.py )
MCH_PYTHON_SRC += $(wildcard $(KEYBOARD_DIR)/lib/*/*.py )
MCH_PYTHON_SRC += $(wildcard $(KEYBOARD_DIR)/lib/*/*/*.py )
MCH_PYTHON_SRC += $(wildcard $(KEYBOARD_DIR)/lib/*/*/*/*.py )
MCH_PYTHON_SRC += $(wildcard $(KEYBOARD_DIR)/lib/*/*/*/*/*.py )
MCH_PYTHON_SRC += $(wildcard $(KEYBOARD_DIR)/lib/*/*/*/*/*/*.py )


$(KEYBOARD_DIR)/keymaps/%/chordmap.c: $(KEYBOARD_DIR)/keymaps/%/chordmap.json $(KEYBOARD_DIR)/gen_chordmap.py $(MCH_PYTHON_SRC)
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

SRC += $(wildcard $(KEYBOARD_DIR)/lib/*.c )
SRC += $(wildcard $(KEYBOARD_DIR)/lib/*/*.c )
SRC += $(wildcard $(KEYBOARD_DIR)/lib/*/*/*.c )
SRC += $(wildcard $(KEYBOARD_DIR)/lib/*/*/*/*.c )
SRC += $(wildcard $(KEYBOARD_DIR)/lib/*/*/*/*/*.c )
SRC += $(wildcard $(KEYBOARD_DIR)/lib/*/*/*/*/*/*.c )



#######################################################################
#                                                                     #
#                                                                     #
#                           QMK Flags                                 #
#                                                                     #
#                                                                     #
#######################################################################

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = vendor
