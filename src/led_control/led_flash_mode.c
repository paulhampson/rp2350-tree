#include "led_flash_mode.h"

#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/time.h"

void led_flash_mode_init(sLedState* led_state)
{
    led_state->led_mode = LED_FLASH_ALL;
    led_state->last_action_time = get_absolute_time();
    led_state->mode_state.flash_all.is_on = false;
}

void run_flash_mode(sLedState* led_state)
{
    const absolute_time_t current_time = get_absolute_time();
    const int64_t time_difference = absolute_time_diff_us(led_state->last_action_time, current_time);

    if (time_difference >= led_state->interval_us)
    {
        led_state->mode_state.flash_all.is_on = !led_state->mode_state.flash_all.is_on;
        for (uint i = 0; i < led_state->num_leds; i++)
        {
            gpio_put(led_state->led_map[i], led_state->mode_state.flash_all.is_on);
        }
        led_state->last_action_time = current_time;
    }
}