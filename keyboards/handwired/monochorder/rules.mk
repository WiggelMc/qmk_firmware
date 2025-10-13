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

KEYBOARD_DIR = keyboards/$(KEYBOARD)
LIB_INCLUDE = \
	$(wildcard $(KEYBOARD_DIR)/lib/$(1) ) \
	$(wildcard $(KEYBOARD_DIR)/lib/*/$(1) ) \
	$(wildcard $(KEYBOARD_DIR)/lib/*/*/$(1) ) \
	$(wildcard $(KEYBOARD_DIR)/lib/*/*/*/$(1) ) \
	$(wildcard $(KEYBOARD_DIR)/lib/*/*/*/*/$(1) ) \
	$(wildcard $(KEYBOARD_DIR)/lib/*/*/*/*/*/$(1) ) \


#######################################################################
#                                                                     #
#                                                                     #
#                           chordmap                                  #
#                                                                     #
#                                                                     #
#######################################################################

PYTHON ?= python3

MCH_PYTHON_SRC += $(call LIB_INCLUDE,*.py)
MCH_PYTHON_SRC += $(call LIB_INCLUDE,*.template)


$(KEYBOARD_DIR)/keymaps/%/chordmap.c $(KEYBOARD_DIR)/keymaps/%/chordmap_data.h: $(KEYBOARD_DIR)/keymaps/%/chordmap.json $(KEYBOARD_DIR)/gen_chordmap.py $(MCH_PYTHON_SRC)
	@echo "generate chordmap for $(KEYBOARD):$*..."
	$(PYTHON) $(KEYBOARD_DIR)/gen_chordmap.py $(KEYBOARD_DIR)/keymaps/$*/chordmap.json $(KEYBOARD_DIR)/keymaps/$*/chordmap.c $(KEYBOARD_DIR)/keymaps/$*/chordmap_data.h

SRC += $(KEYBOARD_DIR)/keymaps/$(KEYMAP)/chordmap.c
SRC += $(KEYBOARD_DIR)/keymaps/$(KEYMAP)/chordmap_data.h


#######################################################################
#                                                                     #
#                                                                     #
#                           libs                                      #
#                                                                     #
#                                                                     #
#######################################################################

SRC += $(call LIB_INCLUDE,*.c)


#######################################################################
#                                                                     #
#                                                                     #
#                           QMK Flags                                 #
#                                                                     #
#                                                                     #
#######################################################################

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = vendor
