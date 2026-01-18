#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    OP_NONE,
    OP_MAGIC,
    OP_SKIP_MAGIC,
} kc_kind_t;

void record_key(uint16_t keycode);
void record_key_internal(uint16_t keycode, kc_kind_t kind, uint16_t result);
bool recordable_key(uint16_t keycode);

uint16_t apply_magic(
    uint16_t (*magic_rules)(uint16_t),
    uint16_t (*skip_rules)(uint16_t),
    uint16_t magic_keycode
);

uint16_t apply_skip_magic(
    uint16_t (*magic_rules)(uint16_t),
    uint16_t (*skip_rules)(uint16_t),
    uint16_t skip_keycode
);
