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
        _______,     _______,      _______,      _______,      _______,      _______,      _______,         _______,      _______,      _______,      _______,      _______,      _______,     _______,
        _______,     _______,      KC_B,         KC_G,         KC_D,         KC_K,         _______,         _______,      KC_Z,         KC_C,         KC_O,         KC_U,         _______,     _______,
        _______,     KC_H,         ALT_T(KC_N),  CTL_T(KC_S),  SFT_T(KC_T),  GUI_T(KC_M),  _______,         _______,      GUI_T(KC_F13),SFT_T(KC_F14),CTL_T(KC_A),  ALT_T(KC_E),  KC_I,        _______,
        _______,     KC_Y,         KC_P,         KC_F,         KC_V,         KC_X,                                        KC_MINS,      KC_W,         KC_COMM,      KC_DOT,       KC_SLSH,     _______,
        _______,     _______,      _______,      _______,      LT(NUM, KC_R),              _______,         _______,                    LT(SYMB,KC_J),_______,      _______,      _______,     _______,
                                                               KC_L,        KC_NO,         KC_NO,           KC_NO,        KC_NO,        KC_SPC
    ),

    [NUM] = LAYOUT(
        _______,     _______,      _______,      _______,      _______,      _______,      _______,         _______,      _______,      _______,      _______,      _______,      _______,     _______,
        _______,     _______,      KC_Q,         _______,      _______,      _______,      _______,         _______,      KC_LEFT,      KC_DOWN,      KC_UP,        KC_RGHT,      _______,     _______,
        _______,     KC_9,         ALT_T(KC_5),  CTL_T(KC_0),  SFT_T(KC_3),  GUI_T(KC_7),  _______,         _______,      GUI_T(KC_6),  SFT_T(KC_2),  CTL_T(KC_1),  ALT_T(KC_4),  KC_8,        _______,
        _______,     _______,      _______,      _______,      _______,      _______,                                     KC_TAB,       KC_ENT,       KC_BSPC,      KC_ESC,       _______,     _______,
        _______,     _______,      _______,      _______,      _______,                    _______,         _______,                    _______,      _______,      _______,      _______,     _______,
                                                               _______,      _______,      _______,         _______,      _______,      _______
    ),

    [SYMB] = LAYOUT(
        _______,     _______,      _______,      _______,      _______,      _______,     _______,          _______,      _______,      _______,      _______,      _______,      _______,     _______,
        _______,     _______,      KC_EXLM,      KC_LCBR,      KC_RCBR,      KC_PIPE,     _______,          _______,      KC_TILD,      KC_COLN,      KC_SCLN,      KC_NUBS,      _______,     _______,
        _______,     KC_HASH, ALT_T(KC_DLR),CTL_T(KC_LPRN),SFT_T(KC_RPRN),GUI_T(KC_AMPR), _______,          _______,   GUI_T(KC_PLUS),SFT_T(KC_MINS),CTL_T(KC_QUOT),ALT_T(KC_DQUO),KC_GRV,     _______,
        _______,     _______,      KC_CIRC,      KC_LBRC,      KC_RBRC,      KC_ASTR,                                     _______,      KC_UNDS,      KC_EQL,       _______,      _______,     _______,
        _______,     _______,      _______,      _______,      _______,                   _______,          _______,                    _______,      _______,      _______,      _______,     _______,
                                                               _______,      _______,     _______,          _______,      _______,      _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // extract the base keycode if it's a Mod-Tap or Layer-Tap
    uint16_t base_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);

    if (!record->event.pressed) {
        return true;
    }

    if (try_adaptive_key(keycode)) {
        return false;
    }

    switch (base_keycode) {
        case KC_B:
            /* Arm: after B, H → Y */
            arm_adaptive_key(KC_B, KC_H, KC_Y);

            record_normal_key(KC_B);
            return true;
        case KC_R:
            /* Arm: after R, / → L */
            arm_adaptive_key(KC_R, KC_SLSH, KC_L);

            record_normal_key(KC_R);
            return true;
        case KC_F13:
            // Only fire magic if the key was TAPPED
            // If count > 0, it's a tap. If 0, it's a hold for the modifier.
            if (record->tap.count > 0) {
                apply_magic(magic_rules, skip_magic_rules, KC_F13);
                return false; // Don't send the F13 tap to the OS
            }
            break; // Let QMK handle the 'hold' for GUI_T
        case KC_F14:
            if (record->tap.count > 0) {
                apply_skip_magic(magic_rules, skip_magic_rules, KC_F14);
                return false;
            }
            break;
        default:
            record_normal_key(base_keycode);
            return true;
    }

    return true;
}

