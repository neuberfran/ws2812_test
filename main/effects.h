#ifndef EFFECTS_H
#define EFFECTS_H

#include <stdint.h>
#include "esp_err.h"

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} rgb_color_t;

extern const rgb_color_t COLOR_WHITE;
extern const rgb_color_t COLOR_RED;
extern const rgb_color_t COLOR_GREEN;
extern const rgb_color_t COLOR_BLUE;

esp_err_t effect_fill(
    rgb_color_t color,
    uint32_t delay_ms
);

esp_err_t effect_clear_forward(
    uint32_t delay_ms
);

esp_err_t effect_clear_reverse(
    uint32_t delay_ms
);

esp_err_t effect_fill_and_clear(
    rgb_color_t color,
    uint32_t delay_ms,
    uint32_t hold_ms
);

#endif