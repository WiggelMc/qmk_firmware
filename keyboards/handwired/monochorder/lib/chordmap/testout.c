

#include <stdint.h>
#include <util.h>
#include "../mch_types.h"
#include "../mch_keymap.h"
#include "testout_data.h"

// TODO: Template
const uint16_t chord_definitions[] = {
    /* 00000 00000 */ 1,
    /* */ 1,
};

// TODO: Template
#define KEY_AMOUNT 10

// TODO: Template
const uint16_t dk_mapping[][KEY_AMOUNT] = {
    /* 00000 00000 */ {[0] = 1},
};

key_value_t get_mapped_chord_key_gen(chord_t chord, layer_t layer) {
    if (layer >= ARRAY_SIZE(layer_index)) {
        goto unmapped;
    }

    uint8_t layer_i = layer_index[layer];
    if (layer_i == 0xff) {
        goto unmapped;
    }

    uint32_t chord_map_i = (uint32_t)layer_i * layer_size + chord;
    if (chord_map_i >= ARRAY_SIZE(chord_mapping) || chord_map_i >= ARRAY_SIZE(chord_mods)) {
        goto unmapped;
    }

    uint16_t chord_i   = chord_mapping[chord_map_i];
    uint8_t  modifiers = chord_mods[chord_map_i];
    if (chord_i >= ARRAY_SIZE(chord_definitions)) {
        goto unmapped;
    }

    uint16_t keycode = chord_definitions[chord_i];
    if (keycode == 0) {
        goto unmapped;
    }

    return (key_value_t){.keycode = keycode, .modifiers = modifiers};

unmapped:
    return (key_value_t){0};
}

direct_key_index_t get_direct_key_index_gen(chord_t chord) {
    if (chord >= ARRAY_SIZE(dk_index_mapping)) {
        return 0;
    }
    return dk_index_mapping[chord];
}

keycode_t get_mapped_direct_key_gen(direct_key_index_t dk_index, chord_bit_index_t bit_index) {
    if (dk_index >= ARRAY_SIZE(dk_mapping) || bit_index >= KEY_AMOUNT) {
        return 0;
    }

    return dk_mapping[dk_index][bit_index];
}

#define IS_BIT_SET(value, bit) (((value) & (1u << (bit))) != 0)
#define IS_BIT_SET_F(value, bit) (IS_BIT_SET(value, bit) ? 1 : 0)

bool read_input_uint8m_gen(chord_t chord, uint8m_t *out_data) {
    // TODO: Template

    // m7654 3210-

    bool mod = IS_BIT_SET(chord, 9);

    if (is_chord_zero(chord)) {
        out_data->byte = 0;
        out_data->mod  = mod;
        return true;
    }
    out_data->byte = (IS_BIT_SET_F(chord, 0) << 1)    // 0
                     | (IS_BIT_SET_F(chord, 1) << 2)  // 1
                     | (IS_BIT_SET_F(chord, 2) << 3)  // 2
                     | (IS_BIT_SET_F(chord, 3) << 4)  // 3
                     | (IS_BIT_SET_F(chord, 4) << 5)  // 4
                     | (IS_BIT_SET_F(chord, 5) << 6)  // 5
                     | (IS_BIT_SET_F(chord, 6) << 7)  // 6
                     | (IS_BIT_SET_F(chord, 7) << 8); // 7
    out_data->mod = mod;

    return true;
}
bool read_input_uint9_gen(chord_t chord, uint9_t *out_data) {
    // TODO: Template

    // 87654 3210-

    if (is_chord_zero(chord)) {
        *out_data = 0;
        return true;
    }
    *out_data = (IS_BIT_SET_F(chord, 0) << 1)    // 0
                | (IS_BIT_SET_F(chord, 1) << 2)  // 1
                | (IS_BIT_SET_F(chord, 2) << 3)  // 2
                | (IS_BIT_SET_F(chord, 3) << 4)  // 3
                | (IS_BIT_SET_F(chord, 4) << 5)  // 4
                | (IS_BIT_SET_F(chord, 5) << 6)  // 5
                | (IS_BIT_SET_F(chord, 6) << 7)  // 6
                | (IS_BIT_SET_F(chord, 7) << 8)  // 7
                | (IS_BIT_SET_F(chord, 8) << 9); // 8

    return true;
}

uint16_t get_option_index(chord_t chord) {
    if (chord >= ARRAY_SIZE(option_index_mapping)) {
        return 0;
    }

    return option_index_mapping[chord];
}

bool reset_option_values_gen(options_state_t *options) {
    // TODO: Template

    options->tap_code_delay = 0;
    options->tap_code_gap   = 0;

    return true;
}
bool reset_option_value_gen(chord_t chord, options_state_t *options) {
    // TODO: Template

    uint16_t index = get_option_index(chord);
    if (index == 0) {
        return false;
    }

    switch (index) {
        case 1:
            options->tap_code_delay = 0;
            return true;
        case 2:
            options->tap_code_gap = 0;
            return true;
        default:
            return false;
    }
}
bool set_option_value_gen(chord_t chord, uint9_t value, options_state_t *options) {
    // TODO: Template

    uint16_t index = get_option_index(chord);
    if (index == 0) {
        return false;
    }

    switch (index) {
        case 1:
            options->tap_code_delay = value;
            return true;
        case 2:
            options->tap_code_gap = value;
            return true;
        default:
            return false;
    }
}

#define MASK_CMP(a, b, mask) (((a) & (mask)) == ((b) & (mask)))

bool is_chord_noop_gen(chord_t chord) {
    // TODO: Template

    return MASK_CMP(chord, 0x03FF, 0x03FF)     // 11111 11111
           || MASK_CMP(chord, 0x03E0, 0x03FF)  // 11111 00000
           || MASK_CMP(chord, 0x001F, 0x03FF); // 00000 11111
}
bool is_chord_cancel_gen(chord_t chord) {
    // TODO: Template

    return MASK_CMP(chord, 0x0001, 0x03FF); // 00000 00001
}
bool is_chord_zero_gen(chord_t chord) {
    // TODO: Template

    return MASK_CMP(chord, 0x0011, 0x001F); // ----- 10001
}

const chord_bit_index_t  key_amount_gen            = KEY_AMOUNT;
// TODO: Template
const direct_key_index_t trainer_mode_dk_index_gen = 1;
