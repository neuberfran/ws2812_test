#include "ws2812.h"

#include "led_strip.h"
#include "driver/rmt_tx.h"

static led_strip_handle_t strip = NULL;

esp_err_t ws2812_init(void)
{
    led_strip_config_t strip_config = {
        .strip_gpio_num = WS2812_GPIO,
        .max_leds = WS2812_LED_COUNT,
        .led_model = LED_MODEL_WS2812,
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
        .flags = {
            .invert_out = false,
        },
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = 10 * 1000 * 1000,
        .mem_block_symbols = 64,
        .flags = {
            .with_dma = false,
        },
    };

    esp_err_t result = led_strip_new_rmt_device(
        &strip_config,
        &rmt_config,
        &strip
    );

    if (result != ESP_OK) {
        return result;
    }

    return led_strip_clear(strip);
}

esp_err_t ws2812_set_pixel(
    uint32_t led,
    uint8_t red,
    uint8_t green,
    uint8_t blue
)
{
    if (strip == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    if (led >= WS2812_LED_COUNT) {
        return ESP_ERR_INVALID_ARG;
    }

    return led_strip_set_pixel(
        strip,
        led,
        red,
        green,
        blue
    );
}

esp_err_t ws2812_refresh(void)
{
    if (strip == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    return led_strip_refresh(strip);
}

esp_err_t ws2812_clear(void)
{
    if (strip == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    return led_strip_clear(strip);
}

esp_err_t ws2812_set_all(
    uint8_t red,
    uint8_t green,
    uint8_t blue
)
{
    if (strip == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    for (uint32_t led = 0; led < WS2812_LED_COUNT; led++) {

        esp_err_t result = ws2812_set_pixel(
            led,
            red,
            green,
            blue
        );

        if (result != ESP_OK) {
            return result;
        }
    }

    return ws2812_refresh();
}