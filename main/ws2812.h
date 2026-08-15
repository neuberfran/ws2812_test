#ifndef WS2812_H
#define WS2812_H

#include <stdint.h>
#include "esp_err.h"

#define WS2812_GPIO       18
#define WS2812_LED_COUNT  300

esp_err_t ws2812_init(void);

esp_err_t ws2812_set_pixel(
    uint32_t led,
    uint8_t red,
    uint8_t green,
    uint8_t blue
);

esp_err_t ws2812_refresh(void);

esp_err_t ws2812_clear(void);

esp_err_t ws2812_set_all(
    uint8_t red,
    uint8_t green,
    uint8_t blue
);

#endif