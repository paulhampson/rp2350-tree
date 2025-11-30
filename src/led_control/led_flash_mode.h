#pragma once
#include "led_types.h"

/**
 * Initialise flash mode
 *
 * @param led_state LED State
 */
void led_flash_mode_init(sLedState *led_state);

/**
 * Execute flash mode actions
 *
 * @param led_state LED State
 */
void run_flash_mode(sLedState *led_state);