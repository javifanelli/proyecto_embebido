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
#include "../components/javi/variables.h"
#include "../components/esp-idf-lib-master/components/dht/dht.h"
#include "../components/javi/pantallas.c"
#include "../components/javi/wifi_con.c"
#include "../components/javi/sntp_time.h"
#include "../components/javi/mqtt_funcs.c"
#include "../components/temp/temp.h"
bool time_sinc_ok = false;

/*static char* SSID;
static char* MAC;
bool wifi_state=0; */

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
	ESP_ERROR_CHECK(esp_netif_init());
	
	config_dis ();
	pant_bienv ();

	wifi_init_sta();
    initialize_sntp();
    while (!time_sinc_ok) vTaskDelay(100 * 1);
    obtain_time();
    /* mqtt_app_start(); */
	
    /*
	if (strlen(IP)==0)
	{
		wifi_state = false;
		pant_nocon();
	}
	else{
		wifi_state = true;
		pant_conok (SSID, IP, MAC);
	} */

	get_temp();
}
