
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_err.h"
#include "esp_log.h"

#include "ws2812.h"
#include "effects.h"

static const char *TAG = "NATAL";

void app_main(void)
{
    ESP_LOGI(TAG, "Inicializando WS2812B");

    ESP_ERROR_CHECK(ws2812_init());

    while (1)
    {
        ESP_LOGI(TAG, "Efeito branco");

        ESP_ERROR_CHECK(
            effect_fill_and_clear(
                COLOR_WHITE,
                10,      // 10 ms entre LEDs
                1500     // fica cheia por 1,5 segundo
            )
        );

        vTaskDelay(pdMS_TO_TICKS(3200));
    }
}