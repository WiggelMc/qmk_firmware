#ifndef CHORDMAP_H
#define CHORDMAP_H

#include <stdbool.h>
#include <stdint.h>

typedef uint16_t keycode_t;
typedef uint8_t  layer_t;
typedef uint8_t  chord_bit_index_t;
typedef uint16_t direct_key_index_t;

typedef struct {
    uint8_t byte;
    bool    mod;
} uint8m_t;
typedef uint16_t uint9_t;
typedef uint16_t chord_t;

typedef struct {
    uint9_t tap_code_delay;
} options_state_t;

extern bool read_input_uint8m(chord_t chord, uint8m_t *out_data);
extern bool read_input_uint9(chord_t chord, uint9_t *out_data);
extern bool read_input_chord(chord_t chord, chord_t *out_data);

extern bool reset_option_values(options_state_t *options);
extern bool reset_option_value(chord_t chord, options_state_t *options);
extern bool set_option_value(chord_t chord, uint9_t value, options_state_t *options);

extern const chord_bit_index_t key_amount;

extern bool is_chord_noop(chord_t chord);
extern bool is_chord_cancel(chord_t chord);
extern bool is_chord_zero(chord_t chord);

extern keycode_t get_mapped_chord_key(chord_t chord, layer_t layer);

extern direct_key_index_t get_direct_key_index(chord_t chord);
extern keycode_t          get_mapped_direct_key(direct_key_index_t dk_index, chord_bit_index_t bit_index);

extern const direct_key_index_t trainer_mode_dk_index;

#endif
