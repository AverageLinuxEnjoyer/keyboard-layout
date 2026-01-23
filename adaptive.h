#pragma once

#include <stdbool.h>
#include <stdint.h>

static bool adaptive_armed = false;
static uint16_t adaptive_trigger = KC_NO;   // e.g. KC_B
static uint16_t adaptive_target  = KC_NO;   // e.g. KC_M
static uint16_t adaptive_output  = KC_NO;   // e.g. KC_Y
static uint16_t adaptive_timer   = 0;

#define ADAPTIVE_TIMEOUT 300  // ms

static void arm_adaptive_key(uint16_t trigger,
                             uint16_t target,
                             uint16_t output) {
    adaptive_armed   = true;
    adaptive_trigger = trigger;
    adaptive_target  = target;
    adaptive_output  = output;
    adaptive_timer   = timer_read();
}

static void disarm_adaptive_key(void) {
    adaptive_armed = false;
}

static bool adaptive_expired(void) {
    return adaptive_armed &&
           timer_elapsed(adaptive_timer) > ADAPTIVE_TIMEOUT;
}


static bool try_adaptive_key(uint16_t keycode) {
    if (!adaptive_armed) {
        return false;
    }

    if (adaptive_expired()) {
        disarm_adaptive_key();
        return false;
    }

    if (keycode == adaptive_target) {
        tap_code16(adaptive_output);

        /* record as if adaptive_output was typed */
        push_history(adaptive_target, adaptive_output, true);

        disarm_adaptive_key();
        return true;  // consumed
    }

    /* Any other key cancels the adaptive rule */
    disarm_adaptive_key();
    return false;
}

