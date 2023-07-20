#define dht_gpio 0 // Pin conectado al DHT11

static const dht_sensor_type_t sensor_type = DHT_TYPE_DHT11;
int16_t humidity=0; // valor de humedad leído
int16_t temperature=0; // valor de temperatura leído
int cont_temp=0; // variable auxiliar para no mostrar la primera medición de temperatura
int refresh=5; // tiempo en segundos para refrescar medición en display
const int min_mqtt=5; // tiempo en minutos para enviar el mensaje MQTT
int cont_mqtt= min_mqtt * 12;
bool time_sinc_ok = false;

void get_temp(void *pvParameter)
{
    while(1) {
        if (dht_read_data(sensor_type, dht_gpio, &humidity, &temperature) == ESP_OK) {
            ESP_LOGI(TAG,"Humidity: %d%% Temperature: %dC\n", humidity / 10, temperature / 10);
            if (!time_sinc_ok)
                {
                vTaskDelay(100 * 1);
                obtain_time();
                }
            time_t now = time(NULL);
            timeinfo = localtime(&now);
            strftime(pant_time, sizeof(pant_time), "%H:%M %d-%m-%Y", timeinfo);
            sprintf(hum_char, "%d", humidity/10);
			sprintf(temp_char, "%d", temperature/10);
            if(cont_mqtt==60)
                {
                cont_mqtt=0;
                mqtt_send_info();
                }
            cont_mqtt++;
            esp_wifi_sta_get_ap_info(&ap_info);
            net_con = (ap_info.authmode != WIFI_AUTH_OPEN);
            pant_main();
            vTaskDelay(1000*refresh / portTICK_PERIOD_MS);
        } else {
            if (cont_temp > 5){
                ESP_LOGE(TAG,"Could not read data from sensor\n");
			    pant_no_sensor();
                vTaskDelay(1000 / portTICK_PERIOD_MS);
                }
            cont_temp++;
            vTaskDelay(100 * 1);
        }
		
   }
   vTaskDelete(NULL);
}