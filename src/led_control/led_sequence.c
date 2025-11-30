#include "led_sequence.h"

#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/time.h"

void led_sequence_mode_init(sLedState* led_state)
{
    led_state->led_mode = LED_SEQUENCE;
    led_state->last_action_time = get_absolute_time();
    led_state->mode_state.sequence.current_led = 0;
}

void run_sequence_mode(sLedState* led_state)
{
    const absolute_time_t current_time = get_absolute_time();
    const int64_t time_difference = absolute_time_diff_us(led_state->last_action_time, current_time);

    if (time_difference >= led_state->interval_us)
    {
        gpio_put(led_state->led_map[led_state->mode_state.sequence.current_led], false);
        led_state->mode_state.sequence.current_led++;
        if (led_state->mode_state.sequence.current_led >= led_state->num_leds)
        {
            led_state->mode_state.sequence.current_led = 0;
        }
        gpio_put(led_state->led_map[led_state->mode_state.sequence.current_led], true);
        led_state->last_action_time = current_time;
    }
}