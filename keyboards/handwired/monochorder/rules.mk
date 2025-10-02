PYTHON ?= python3
KEYBOARD_DIR = keyboards/$(KEYBOARD)

$(KEYBOARD_DIR)/keymaps/%/chordmap.c: $(KEYBOARD_DIR)/keymaps/%/chordmap.json $(KEYBOARD_DIR)/lib/gen_chordmap.py
	@echo "generate chordmap for $(KEYBOARD):$*..."
	$(PYTHON) $(KEYBOARD_DIR)/lib/gen_chordmap.py $(KEYBOARD_DIR)/keymaps/$*/chordmap.json $(KEYBOARD_DIR)/keymaps/$*/chordmap.c

SRC += $(KEYBOARD_DIR)/keymaps/$(KEYMAP)/chordmap.c

SRC += lib/mch_keyboard.c lib/mch_keymap.c

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = vendor
