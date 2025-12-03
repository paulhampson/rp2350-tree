#include "led_random_sequence.h"

#include <stdlib.h>

#include "hardware/gpio.h"
#include "pico/time.h"

void led_random_sequence_mode_init(sLedState* led_state)
{
    led_state->led_mode = LED_RANDOM_SEQUENCE;
    led_state->last_action_time = get_absolute_time();
    led_state->mode_state.random_sequence.led_status_bit_map = 0;
}

void run_random_sequence_mode(sLedState* led_state)
{
    const absolute_time_t current_time = get_absolute_time();
    const int64_t time_difference = absolute_time_diff_us(led_state->last_action_time, current_time);

    if (time_difference >= led_state->interval_us)
    {
        const uint led_to_toggle = rand() % led_state->num_leds;
        led_state->mode_state.random_sequence.led_status_bit_map ^= 1 << led_to_toggle;
        const bool led_on_off_state = (led_state->mode_state.random_sequence.led_status_bit_map >> led_to_toggle) & 1;
        gpio_put(led_state->led_map[led_to_toggle], led_on_off_state);
        led_state->last_action_time = current_time;
    }
}