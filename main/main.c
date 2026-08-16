#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_err.h"
#include "esp_log.h"

#include "ws2812.h"
#include "effects.h"

static const char *TAG = "NATAL";

typedef enum {
    COR_BRANCO = 0,
    COR_AZUL,
    COR_VERMELHO,
    COR_VERDE
} cor_id_t;

static cor_id_t cor_atual = COR_BRANCO;

static rgb_color_t obter_cor(cor_id_t cor)
{
    switch (cor)
    {
        case COR_AZUL:
            return COLOR_BLUE;

        case COR_VERMELHO:
            return COLOR_RED;

        case COR_VERDE:
            return COLOR_GREEN;

        case COR_BRANCO:
        default:
            return COLOR_WHITE;
    }
}

static const char *nome_cor(cor_id_t cor)
{
    switch (cor)
    {
        case COR_AZUL:
            return "AZUL";

        case COR_VERMELHO:
            return "VERMELHO";

        case COR_VERDE:
            return "VERDE";

        case COR_BRANCO:
        default:
            return "BRANCO";
    }
}

/*
 * Futuramente será chamada quando o Raspberry
 * mandar o comando COR_PADRAO pela UART.
 */
static void cor_padrao(void)
{
    cor_atual = COR_BRANCO;
}

/*
 * Futuramente será chamada quando o Raspberry
 * mandar MUDAR_COR pela UART.
 *
 * Ciclo:
 * BRANCO -> AZUL
 * AZUL -> VERMELHO
 * VERMELHO -> VERDE
 * VERDE -> AZUL
 */
static void proxima_cor(void)
{
    switch (cor_atual)
    {
        case COR_BRANCO:
            cor_atual = COR_AZUL;
            break;

        case COR_AZUL:
            cor_atual = COR_VERMELHO;
            break;

        case COR_VERMELHO:
            cor_atual = COR_VERDE;
            break;

        case COR_VERDE:
        default:
            cor_atual = COR_AZUL;
            break;
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "Inicializando WS2812B");

    ESP_ERROR_CHECK(ws2812_init());

    /*
     * Começa obrigatoriamente no branco.
     */
    cor_padrao();

    while (1)
    {
        rgb_color_t cor = obter_cor(cor_atual);

        ESP_LOGI(
            TAG,
            "Cor atual: %s",
            nome_cor(cor_atual)
        );

        ESP_ERROR_CHECK(
            effect_fill_and_clear(
                cor,
                10,
                1500
            )
        );

        vTaskDelay(pdMS_TO_TICKS(3200));

        /*
         * SOMENTE PARA TESTE AGORA.
         *
         * Faz o ESP32 simular cada clique
         * futuro no botão "Mudar de cor".
         */
        proxima_cor();
    }
}