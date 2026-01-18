#include "magic.h"
#include "keycodes.h"
#include "quantum.h"
#include <stdint.h>

typedef struct {
    kc_kind_t kind;
    uint16_t kc;
    uint16_t result;
} last_kc_t;

static last_kc_t history[2] = {
    { OP_NONE, KC_NO, KC_NO },
    { OP_NONE, KC_NO, KC_NO },
};

void record_key(uint16_t keycode) {
    if(!recordable_key(keycode)) {
        return;
    }

    record_key_internal(keycode, OP_NONE, keycode);
}

void record_key_internal(uint16_t keycode, kc_kind_t kind, uint16_t result) {
    history[1] = history[0];

    history[0].kind = kind;
    history[0].kc = keycode;
    history[0].result = result;
}

uint16_t apply_magic(
        uint16_t (*magic_rules)(uint16_t),
        uint16_t (*skip_rules)(uint16_t),
        uint16_t magic_keycode
    ) {

    last_kc_t target = history[0].kind == OP_SKIP_MAGIC ? history[1] : history[0];
    uint16_t input = target.kind == OP_NONE ? target.kc : target.result;
    uint16_t result = history[0].kind == OP_SKIP_MAGIC ? skip_rules(input) : magic_rules(input);

    tap_code16(result);
    record_key_internal(magic_keycode, OP_MAGIC, result);
    return result;
}

uint16_t apply_skip_magic(
        uint16_t (*magic_rules)(uint16_t),
        uint16_t (*skip_rules)(uint16_t),
        uint16_t magic_keycode
    ) {

    last_kc_t target = history[1].kind == OP_MAGIC ? history[0] : history[1];
    uint16_t input = target.kind == OP_NONE ? target.kc : target.result;
    uint16_t result = history[1].kind == OP_MAGIC ? magic_rules(input) : skip_rules(input);

    tap_code16(result);
    record_key_internal(magic_keycode, OP_SKIP_MAGIC, result);
    return result;
}

bool recordable_key(uint16_t keycode) {
    if(keycode >= KC_A && keycode <= KC_Z) {
        return true;
    }

    if(keycode >= KC_1 && keycode <= KC_0) {
        return true;
    }

    if(keycode >= KC_EXLM && keycode <= KC_AMPR) {
        return true;
    }

    switch(keycode) {
        case KC_SPACE:
        case KC_COMM:
        case KC_DOT:
        case KC_MINS:
        case KC_SCLN:
        case KC_SLSH:
        case KC_EQL:
        case KC_QUOT:
        case KC_LBRC:
        case KC_RBRC:
        case KC_BSLS:
        case KC_GRV:
            return true;
        default:
            return false;
    }
}
