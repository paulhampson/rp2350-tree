#include <stdio.h>
#include "pico/stdlib.h"
#include "cli.h"

static cli_status_t command_help(int argc, char **argv);

cmd_t cli_cmds[1] = {
    {
        .cmd = "help",
        .func = command_help
    },
};

static cli_status_t command_help(int argc, char **argv)
{
    printf("This is the help menu\n");

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
