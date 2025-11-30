#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"
#include "led_control.h"
#include "pico/stdlib.h"

static cli_status_t command_help(int argc, char **argv);
static cli_status_t command_gpio(int argc, char **argv);
static cli_status_t command_led(int argc, char **argv);

static cmd_t cli_cmds[] = {
    {
        .cmd = "help",
        .func = command_help
    },
    {
        .cmd = "gpio",
        .func = command_gpio
    },
    {
        .cmd = "led",
        .func = command_led
    }
};

static uint gpio_led_map[] = {
    // gpio pin, tree ID
    2,  // star
    14, // 1
    5,  // 2
    13, // 3
    21, // 4
    25, // 5
    8,  // 6
    15, // 7
    11, // 8
    16, // 9
    17, // 10
    27, // 11
    26, // 12
    24, // 13
    12, // 14
    9,  // 15
    6,  // 16
    20, // 17
    19, // 18
    4,  // 19
    18, // 20
    10, // 21
    7,  // 22
    23, // 23
    22, // 24
};

const static uint LED_COUNT = sizeof(gpio_led_map) / sizeof(uint);

static sLedState led_state;

static cli_status_t command_help(int argc, char **argv)
{
    printf("The following commands are available:\n");
    printf("\tled flash <interval>      Flash LEDs every <interval> milliseconds\n");
    printf("\tled off                   Turn off all LEDs\n");
    printf("\tled on                    Turn on all LEDs\n");
    printf("\tgpio <pin> <value>        Set GPIO pin to defined value\n");
    printf("\thelp                      Show this help message\n");

    return CLI_OK;
}

static cli_status_t command_gpio(int argc, char **argv)
{
    if (argc != 3) {
        return CLI_E_INVALID_ARGS;
    }
    printf("GPIO pin %s set to %s\n", argv[1], argv[2]);
    const int pin = atoi(argv[1]);
    const int value = atoi(argv[2]);

    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
    gpio_put(pin, value);

    return CLI_OK;
}

static cli_status_t command_led(int argc, char **argv)
{
    if (argc < 2) {
        return CLI_E_INVALID_ARGS;
    }

    if (0 == strcmp(argv[1], "flash") && argc == 3)
    {
        const int interval_ms = atoi(argv[2]);
        led_set_mode(&led_state, LED_FLASH_ALL);
        led_set_interval_us(&led_state, interval_ms * 1000);
    } else if (0 == strcmp(argv[1], "on") && argc == 2)
    {
        led_set_mode(&led_state, LED_ALL_ON);
    } else if (0 == strcmp(argv[1], "off") && argc == 2)
    {
        led_set_mode(&led_state, LED_ALL_OFF);
    }
    else
    {
        return CLI_E_INVALID_ARGS;
    }

    return CLI_OK;
}

void user_uart_println(char *string)
{
    printf("%s\n", string);
}

bool scheduled_led(repeating_timer_t *rt)
{
    run_led_control((sLedState*)rt->user_data);
    return true;
}

int main() {
    stdio_init_all();
    printf("Welcome to the RP2350 Christmas Tree!\n");

    led_set_led_map(&led_state, gpio_led_map, LED_COUNT);
    led_set_mode(&led_state, LED_ALL_ON);

    repeating_timer_t led_timer;
    add_repeating_timer_us (-100, scheduled_led, &led_state, &led_timer);

    cli_status_t rslt = CLI_OK;

    cli_t cli = {
        .println = user_uart_println,
        .cmd_tbl = cli_cmds,
        .cmd_cnt = sizeof(cli_cmds) / sizeof(cmd_t)
    };

    if((rslt = cli_init(&cli)) != CLI_OK)
    {
        printf("CLI: Failed to initialise");
    }

    while (true)
    {
        const int getchar_result = stdio_getchar_timeout_us(1000);
        if (getchar_result != PICO_ERROR_TIMEOUT)
        {
            const char received_char = (char)getchar_result;
            cli_put(&cli, received_char);
            printf("%c", received_char);
        }
        cli_process(&cli);
    }

    return 0;
}
