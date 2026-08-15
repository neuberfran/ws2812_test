#include "effects.h"
#include "ws2812.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

const rgb_color_t COLOR_WHITE = {
    .red = 35,
    .green = 35,
    .blue = 35
};

const rgb_color_t COLOR_RED = {
    .red = 35,
    .green = 0,
    .blue = 0
};

const rgb_color_t COLOR_GREEN = {
    .red = 0,
    .green = 35,
    .blue = 0
};

const rgb_color_t COLOR_BLUE = {
    .red = 0,
    .green = 0,
    .blue = 35
};


esp_err_t effect_fill(
    rgb_color_t color,
    uint32_t delay_ms
)
{
    ESP_ERROR_CHECK(ws2812_clear());

    for (uint32_t led = 0; led < WS2812_LED_COUNT; led++) {

        esp_err_t result = ws2812_set_pixel(
            led,
            color.red,
            color.green,
            color.blue
        );

        if (result != ESP_OK) {
            return result;
        }

        result = ws2812_refresh();

        if (result != ESP_OK) {
            return result;
        }

        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }

    return ESP_OK;
}


esp_err_t effect_clear_forward(
    uint32_t delay_ms
)
{
    for (uint32_t led = 0; led < WS2812_LED_COUNT; led++) {

        esp_err_t result = ws2812_set_pixel(
            led,
            0,
            0,
            0
        );

        if (result != ESP_OK) {
            return result;
        }

        result = ws2812_refresh();

        if (result != ESP_OK) {
            return result;
        }

        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }

    return ESP_OK;
}


esp_err_t effect_clear_reverse(
    uint32_t delay_ms
)
{
    for (int led = WS2812_LED_COUNT - 1; led >= 0; led--) {

        esp_err_t result = ws2812_set_pixel(
            led,
            0,
            0,
            0
        );

        if (result != ESP_OK) {
            return result;
        }

        result = ws2812_refresh();

        if (result != ESP_OK) {
            return result;
        }

        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }

    return ESP_OK;
}


esp_err_t effect_fill_and_clear(
    rgb_color_t color,
    uint32_t delay_ms,
    uint32_t hold_ms
)
{
    esp_err_t result;

    result = effect_fill(
        color,
        delay_ms
    );

    if (result != ESP_OK) {
        return result;
    }

    vTaskDelay(pdMS_TO_TICKS(hold_ms));

    result = effect_clear_forward(
        delay_ms
    );

    return result;
}