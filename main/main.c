#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "esp_log.h"
#include "mqtt_client.h"
#include "cJSON.h"
#include "../components/javi/variables.h"
#include "../components/esp-idf-lib-master/components/encoder/encoder.h"
#include "../components/javi/init.h"
#include "../components/esp-idf-lib-master/components/dht/dht.h"
#include "../components/javi/pantallas.c"
#include "../components/javi/sntp_time.h"
#include "../components/javi/wifi_con.c"
#include "../components/javi/mqtt_funcs.c"
#include "../components/temp/temp.h"


void app_main(void)
{
    
	ESP_ERROR_CHECK(nvs_flash_init());
	ESP_ERROR_CHECK(esp_netif_init());
	gpio_pad_select_gpio(LED_R);
    gpio_set_direction(LED_R, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(LED_G);
    gpio_set_direction(LED_G, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(DIMMER);
    gpio_set_direction(LED_R, GPIO_MODE_OUTPUT);
	wifi_init_sta();
    mqtt_app_start();
	
	rotary_encoder_init(&control);
	rotary_encoder_add(&control);
	btn_enc=false;

	while(1)
	{
		gpio_set_level(DIMMER, 1);
		vTaskDelay(pdMS_TO_TICKS(1000));
		gpio_set_level(DIMMER, 0);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
       
}
