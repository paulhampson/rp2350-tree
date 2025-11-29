#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "cli.h"

static cli_status_t command_help(int argc, char **argv);
static cli_status_t command_gpio(int argc, char **argv);

cmd_t cli_cmds[] = {
    {
        .cmd = "help",
        .func = command_help
    },
    {
        .cmd = "gpio",
        .func = command_gpio
    }
};

static cli_status_t command_help(int argc, char **argv)
{
    printf("The following commands are available:\n");
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

void user_uart_println(char *string)
{
    printf("%s\n", string);
}

int main() {
    stdio_init_all();
    printf("Welcome to the RP2350 Christmas Tree!\n");

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
