#pragma once
#include "pico/types.h"

#include "led_types.h"



/**
 * Run the LED control actions based on the provided state.
 *
 * @param led_state State information
 */
void run_led_control(sLedState* led_state);

/**
 * Configure LED numbering map to via a list of GPIOs
 *
 * @param led_state LED State
 * @param led_map LED to gpio map
 * @param num_leds Number of LEDs in the map
 */
void led_set_led_map(sLedState* led_state, uint* led_map, uint num_leds);

/**
 * Set LED operating mode
 *
 * @param led_state LED State
 * @param led_mode Set new mode
 */
void led_set_mode(sLedState* led_state, eLedMode led_mode);

/**
 * Set the desired interval for LED transitions
 *
 * @param led_state LED State
 * @param interval_us Desired interval for LED transitions in microseconds
 */
void led_set_interval_us(sLedState* led_state, uint interval_us);