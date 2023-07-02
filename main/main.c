#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "mqtt_client.h"
#include "../components/esp-idf-lib-master/dht/dht.h"
#include "../components/javi/config_dis.h"
#include "../components/javi/wifi_con.c"
#include "../components/javi/pantallas.c"
#include "../components/esp-idf-lib-master/temp/temp.h"
#include "../components/sntp/sntp_time.h"
#include "../components/mqtt/mqtt_funcs.c"

bool time_sinc_ok = false;

void app_main(void)
{
	ESP_ERROR_CHECK(nvs_flash_init());
	ESP_ERROR_CHECK(esp_netif_init());
	
	config_dis ();
	pant_bienv ();
	pant_conectando ();
    
	initialize_sntp();
    while (!time_sinc_ok) vTaskDelay(100 * 1);
    obtain_time();
	
    mqtt_app_start();
	get_temp();
}