#include "led_control.h"
#include "hardware/gpio.h"
#include "led_flash_mode.h"

void led_set_led_map(sLedState* led_state, uint* led_map, const uint num_leds)
{
    led_state->led_map = led_map;
    led_state->num_leds = num_leds;

    for (uint idx = 0; idx < num_leds; idx++)
    {
        gpio_init(led_map[idx]);
        gpio_set_dir(led_map[idx], GPIO_OUT);
    }
}

void led_set_interval_us(sLedState* led_state, const uint interval_us)
{
    led_state->interval_us = interval_us;
}

void led_set_mode(sLedState* led_state, const eLedMode led_mode)
{
    switch (led_mode)
    {
        case LED_FLASH_ALL:
            led_flash_mode_init(led_state);
            break;
        default:
            // do nothing
            break;
    }
    led_state->led_mode = led_mode;
}

void run_led_control(sLedState* led_state)
{
    switch (led_state->led_mode)
    {
        case LED_FLASH_ALL:
            run_flash_mode(led_state);
            break;
        default:
            // do nothing
            break;
       }
}