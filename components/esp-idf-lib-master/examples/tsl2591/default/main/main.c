#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include <tsl2591.h>

#ifndef APP_CPU_NUM
#define APP_CPU_NUM PRO_CPU_NUM
#endif

void tsl2591_test(void *pvParameters)
{
    tsl2591_t dev = { 0 };

    ESP_ERROR_CHECK(tsl2591_init_desc(&dev, 0, CONFIG_EXAMPLE_I2C_MASTER_SDA, CONFIG_EXAMPLE_I2C_MASTER_SCL));
    ESP_ERROR_CHECK(tsl2591_init(&dev));

    float lux;
    esp_err_t res;
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(100));

        if ((res = tsl2591_get_lux(&dev, &lux)) != ESP_OK)
            printf("Could not read lux value: %d\n", res);
        else
            printf("Lux: %f\n", lux);
    }
}

void app_main()
{
    ESP_ERROR_CHECK(i2cdev_init());

    xTaskCreatePinnedToCore(tsl2591_test, "tsl2591_test", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL, APP_CPU_NUM);
}

