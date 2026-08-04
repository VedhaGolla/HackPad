#include QMK_KEYBOARD_H

// Matrix column order (from keyboard.json matrix_pins.direct):
//   col0 = SW1   col1 = SW2   col2 = SW3   col3 = SW4
//   col4 = SW5   col5 = SW6 (encoder 1 click)   col6 = SW7 (encoder 2 click)

enum layers {
    _BASE,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   MO(_FN), KC_MUTE
    ),

    [_FN] = LAYOUT(
        KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,   KC_TRNS, KC_TRNS
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_FN]   = { ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_HOME, KC_END) },
};
#endif
