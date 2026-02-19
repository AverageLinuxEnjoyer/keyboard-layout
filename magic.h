#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "quantum.h"   // for tap_code16, keycodes, etc.

/* ==========================================================
 * CONFIG
 * ========================================================== */

#ifndef MAGIC_HISTORY_DEPTH
#define MAGIC_HISTORY_DEPTH 8   // change as desired at compile time
#define MAX_MAGIC_RESULT 4      // Maximum characters a magic key can output
#endif

/* ==========================================================
 * PUBLIC API (what your keymap.c uses)
 * ========================================================== */

typedef struct {
    uint16_t codes[MAX_MAGIC_RESULT];
    uint8_t count;
} magic_result_t;

/* Helper to create results easily */
static inline magic_result_t magic_out(uint8_t count, ...) {
    magic_result_t res = { .count = count };
    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count && i < MAX_MAGIC_RESULT; i++) {
        res.codes[i] = (uint16_t)va_arg(ap, int);
    }
    va_end(ap);
    return res;
}

// Function signatures now use the struct
typedef magic_result_t (*magic_rule_fn)(uint16_t);

uint16_t apply_magic(magic_rule_fn magic_rules, magic_rule_fn skip_rules, uint16_t magic_keycode);
uint16_t apply_skip_magic(magic_rule_fn magic_rules, magic_rule_fn skip_rules, uint16_t skip_keycode);

bool recordable_key(uint16_t keycode);

/* ==========================================================
 * INTERNAL TYPES
 * ========================================================== */

typedef struct {
    uint16_t original;  // what was physically pressed
    uint16_t output;    // what was actually sent
    bool was_magic;     // came from magic / skip-magic?
    uint16_t time;      // timer_read() at event time
} key_event_t;

/* Ring buffer history */
static key_event_t history[MAGIC_HISTORY_DEPTH];
static uint8_t history_head = 0;   // index of most recent entry
static uint8_t history_count = 0;  // how many valid entries we have

/* ==========================================================
 * HISTORY MANAGEMENT
 * ========================================================== */

static void push_history(uint16_t original, uint16_t output, bool was_magic) {
    history_head = (history_head + 1) % MAGIC_HISTORY_DEPTH;

    history[history_head] = (key_event_t){
        .original  = original,
        .output    = output,
        .was_magic = was_magic,
        .time      = timer_read(),
    };

    if (history_count < MAGIC_HISTORY_DEPTH) {
        history_count++;
    }
}

/* Get the nth key back: 0 = most recent */
static key_event_t get_history(int n_back) {
    if (n_back >= history_count) {
        return (key_event_t){KC_NO, KC_NO, false};
    }

    int idx = (int)history_head - n_back;
    if (idx < 0) idx += MAGIC_HISTORY_DEPTH;

    return history[idx];
}

/* ==========================================================
 * TARGET-FINDING LOGIC
 * ========================================================== */

/* Find last "real" (non-magic) key for normal magic */
static key_event_t find_target_for_magic(void) {
    for (int i = 0; i < history_count; i++) {
        key_event_t ev = get_history(i);
        if (!ev.was_magic) {
            return ev;
        }
    }
    return get_history(0); // fallback
}

/* Find second-last "real" key for skip-magic */
static key_event_t find_target_for_skip_magic(void) {
    int found = 0;

    for (int i = 0; i < history_count; i++) {
        key_event_t ev = get_history(i);
        if (!ev.was_magic) {
            found++;
            if (found == 2) {
                return ev;
            }
        }
    }

    /* Fallback: return oldest we have */
    return get_history(history_count > 0 ? history_count - 1 : 0);
}

/* ==========================================================
 * PUBLIC FUNCTIONS
 * ========================================================== */

uint16_t apply_magic(magic_rule_fn magic_rules, magic_rule_fn skip_rules, uint16_t magic_keycode) {
    key_event_t target = find_target_for_magic();
    uint16_t input = target.was_magic ? target.output : target.original;

    magic_result_t result = magic_rules(input);

    for (int i = 0; i < result.count; i++) {
        tap_code16(result.codes[i]);
    }

    // We store the LAST code produced in the history so the next magic key has a reference
    uint16_t last_code = result.count > 0 ? result.codes[result.count - 1] : KC_NO;
    push_history(target.original, last_code, true);

    return last_code;
}

uint16_t apply_skip_magic(
    magic_rule_fn magic_rules,
    magic_rule_fn skip_rules,
    uint16_t skip_keycode
) {
    // 1. Find the target (the second-to-last real key)
    key_event_t target = find_target_for_skip_magic();

    // 2. Determine what to feed into the rules
    uint16_t input = target.was_magic
        ? target.output
        : target.original;

    // 3. Get the multi-key result from your skip rules
    magic_result_t result = skip_rules(input);

    // 4. Tap all resulting keys in order
    for (int i = 0; i < result.count; i++) {
        tap_code16(result.codes[i]);
    }

    // 5. Store the result in history
    // We record the physical skip_keycode as the 'original' if you want
    // to track the skip key itself, OR target.original to track the 'subject'
    uint16_t last_output = (result.count > 0) ? result.codes[result.count - 1] : KC_NO;
    push_history(target.original, last_output, true);

    return last_output;
}

/* ==========================================================
 * RECORDABLE KEYS (your original logic, unchanged)
 * ========================================================== */

bool recordable_key(uint16_t keycode) {
    if (keycode >= KC_A && keycode <= KC_Z) {
        return true;
    }

    if (keycode >= KC_1 && keycode <= KC_0) {
        return true;
    }

    if (keycode >= KC_EXLM && keycode <= KC_AMPR) {
        return true;
    }

    switch (keycode) {
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

/* ==========================================================
 * OPTIONAL: helper for your keymap
 * ========================================================== */

/* Call this from process_record_user for normal keys */
static inline void record_normal_key(uint16_t keycode) {
    if (recordable_key(keycode)) {
        push_history(keycode, keycode, false);
    }
}
