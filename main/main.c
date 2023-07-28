#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <driver/ledc.h>
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
#include "../components/javi/sntp_time.h"
#include "../components/javi/wifi_con.c"
#include "../components/javi/mqtt_funcs.c"

#define QUEUE_LENGTH 10 // Define la longitud máxima de la cola
static QueueHandle_t _queue;

void app_main(void)
{
    
	ESP_ERROR_CHECK(nvs_flash_init());
	ESP_ERROR_CHECK(esp_netif_init());
	
	gpio_pad_select_gpio(LED_R);
    gpio_set_direction(LED_R, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(LED_G);
    gpio_set_direction(LED_G, GPIO_MODE_OUTPUT);
	_queue = xQueueCreate(QUEUE_LENGTH, sizeof(rotary_encoder_event_t));
    
	if (_queue == NULL)
    {
        ESP_LOGE(TAG, "No se pudo crear la cola.");
    }
	wifi_init_sta();
    if(net_con)
		mqtt_app_start();
	pwm_init();

	ESP_ERROR_CHECK(rotary_encoder_init(_queue));
	ESP_ERROR_CHECK(rotary_encoder_add(&control));
	btn_enc=false;
	set_pwm_duty(0);
	
	while(1){
		if(btn_enc && out>0){
			btn_enc=false;
			out=0;
			/* set_pwm_duty(out); */
			ESP_LOGI(TAG,"Apago luz");
		}
		if(btn_enc && out==0){
			btn_enc=false;
			out=510;
			/* set_pwm_duty(out); */
			ESP_LOGI(TAG,"Prendo luz al 50");
		}
		if(inc_enc==true){
			inc_enc=false;
			out+=102;
			if(out>1020)
				out=1020;
			/* set_pwm_duty(out); */
			ESP_LOGI(TAG,"Sube pwm");
		}
    	if(dec_enc==true){
			dec_enc=false;
			out-=102;
			if(out<1)
				out=0;
			/* set_pwm_duty(out); */
			ESP_LOGI(TAG,"Baja pwm");
		}
		set_pwm_duty(out);
	}

}
