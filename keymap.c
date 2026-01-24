/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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
 */



#include "magic.h"
#include "adaptive.h"
#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE,  // default layer
    NUM,   // numbers and misc
    SYMB,  // symbols
    MDIA,  // media keys
};

enum custom_keycodes {
    CUST_KEY = SAFE_RANGE,
};

magic_result_t magic_rules(uint16_t keycode) {
    switch(keycode) {
        case KC_I: return magic_out(2, KC_O, KC_U);
        case KC_A: return magic_out(1, KC_O);
        case KC_G: return magic_out(1, KC_S);
        case KC_H: return magic_out(1, KC_Y);
        case KC_U: return magic_out(1, KC_E);
        case KC_X: return magic_out(1, KC_T);
        case KC_Y: return magic_out(1, KC_H);
        default: return magic_out(1, keycode);
    }
}

magic_result_t skip_magic_rules(uint16_t keycode) {
    switch(keycode) {
        case KC_A: return magic_out(1, KC_O);
        case KC_B: return magic_out(1, KC_N);
        case KC_D: return magic_out(1, KC_T);
        case KC_F: return magic_out(1, KC_S);
        case KC_G: return magic_out(1, KC_S);
        case KC_H: return magic_out(1, KC_Y);
        case KC_J: return magic_out(1, KC_Y);
        case KC_K: return magic_out(1, KC_T);
        case KC_L: return magic_out(1, KC_R);
        case KC_M: return magic_out(1, KC_K);
        case KC_O: return magic_out(1, KC_A);
        case KC_P: return magic_out(1, KC_N);
        case KC_Q: return magic_out(1, KC_E);
        case KC_R: return magic_out(1, KC_L);
        case KC_U: return magic_out(1, KC_E);
        case KC_V: return magic_out(1, KC_T);
        case KC_X: return magic_out(1, KC_T);
        case KC_Y: return magic_out(1, KC_H);
        case KC_COMM: return magic_out(1, KC_I);
        case KC_DOT: return magic_out(1, KC_I);
        case KC_MINS: return magic_out(1, KC_I);
        case KC_SLSH: return magic_out(1, KC_A);
        case KC_SCLN: return magic_out(1, KC_E);
        default: return magic_out(1, keycode);
    }
}


const uint16_t PROGMEM q_key[] = {KC_B, KC_G, COMBO_END};
const uint16_t PROGMEM x_key[] = {KC_V, OSL(NUM), COMBO_END};
const uint16_t PROGMEM underscore_key[] = {KC_W, OSL(SYMB), COMBO_END};
// const uint16_t PROGMEM test_combo2[] = {KC_C, KC_D, COMBO_END};
combo_t key_combos[] = {
    COMBO(q_key, KC_Q),
    COMBO(x_key, KC_X),
    COMBO(underscore_key, KC_UNDS),
};

// clang-format off
// alt, ctrl, shift, linux
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,         _______,     _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    KC_B,       KC_G,       KC_D,       KC_K,       _______,         _______,     KC_Z,       KC_C,       KC_O,       KC_U,       _______,    _______,
        _______,    KC_H,       KC_N,       KC_S,       KC_T,       KC_M,       _______,         _______,     KC_F13,     KC_F14,     KC_A,       KC_E,       KC_I,       _______,
        _______,    KC_Y,       KC_P,       KC_F,       KC_V,       OSL(NUM),                                 OSL(SYMB),  KC_W,       KC_DOT,     KC_COMM,    KC_SLSH,    _______,
        _______,    _______,    _______,    _______,    KC_R,                   _______,         _______,                 KC_J,       _______,    _______,    _______,    _______,
                                                        KC_L,       KC_NO,      KC_NO,           KC_NO,       KC_NO,      KC_SPC
    ),

    [NUM] = LAYOUT(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,         _______,     _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,         _______,     KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    _______,    _______,
        _______,    KC_9,       KC_5,       KC_0,       KC_3,       KC_7,       _______,         _______,     KC_6,       KC_2,       KC_1,       KC_4,       KC_8,       _______,
        _______,    _______,    _______,    _______,    KC_X,       _______,                                  KC_TAB,     KC_ENT,     KC_BSPC,    KC_ESC,     _______,    _______,
        _______,    _______,    _______,    _______,    _______,                _______,         _______,                 _______,    _______,    _______,    _______,    _______,
                                                        _______,    _______,    _______,         _______,     _______,    _______
    ),

    [SYMB] = LAYOUT(
        _______, _______, _______, _______,  _______, _______,_______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_EXLM, KC_LCBR, KC_RCBR, KC_PIPE, _______,           _______, KC_TILD, KC_COLN, KC_SCLN, KC_NUBS, _______, _______,
        _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_AMPR, _______,           _______, KC_PLUS, KC_MINS, KC_QUOT, KC_DQUO, KC_GRV,  _______,
        _______, _______, KC_CIRC, KC_LBRC, KC_RBRC, KC_ASTR,                             _______, KC_UNDS,  KC_EQL, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,           _______,          _______, _______, _______, _______,  _______,
                                            _______, _______, _______,           _______, _______, _______
    ),

    [MDIA] = LAYOUT(
        LED_LEVEL,_______,_______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, QK_BOOT,
        _______, _______, _______, MS_UP,   _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, MS_LEFT, MS_DOWN, MS_RGHT, _______, _______,           _______, _______, _______, _______, _______, _______, KC_MPLY,
        _______, _______, _______, _______, _______, _______,                             _______, _______, KC_MPRV, KC_MNXT, _______, _______,
        _______, _______, _______, MS_BTN1, MS_BTN2,         _______,            _______,          KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    if (try_adaptive_key(keycode)) {
        return false;
    }

    switch (keycode) {
        case KC_B:
            /* Arm: after B, H → Y */
            arm_adaptive_key(KC_B, KC_H, KC_Y);

            record_normal_key(KC_B);
            return true;
        case KC_F13:
            apply_magic(magic_rules, skip_magic_rules, KC_F13);
            return false;   // stop QMK from also sending F13

        case KC_F14:
            apply_skip_magic(magic_rules, skip_magic_rules, KC_F14);
            return false;

        default:
            record_normal_key(keycode);
            return true;
    }
}

