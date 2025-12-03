#pragma once
#include "pico/types.h"



typedef enum
{
    LED_FLASH_ALL,
    LED_SEQUENCE,
    LED_ALL_ON,
    LED_ALL_OFF,
    LED_RANDOM_SEQUENCE,
} eLedMode;

typedef struct sLedFlashModeState
{
    bool is_on;
} sLedFlashModeState;

typedef struct sLedSequenceState
{
    uint current_led;
} sLedSequenceState;

typedef struct sLedRandomSequenceState
{
    uint led_status_bit_map;
} sLedRandomSequenceState;

typedef struct sLedState
{
    eLedMode led_mode;
    absolute_time_t last_action_time;
    uint interval_us;
    uint* led_map;
    uint num_leds;
    union {
        sLedFlashModeState flash_all;
        sLedSequenceState sequence;
        sLedRandomSequenceState random_sequence;
    } mode_state;
} sLedState;