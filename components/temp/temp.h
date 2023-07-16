static const dht_sensor_type_t sensor_type = DHT_TYPE_DHT11;
int16_t humidity=0; // valor de humedad leído
int16_t temperature=0; // valor de temperatura leído
int cont_temp=0;
int refresh=5; // tiempo en segundos para refrescar medición
int cont_mqtt=60;

void get_temp(void *pvParameter)
{
    while(1) {
        if (dht_read_data(sensor_type, dht_gpio, &humidity, &temperature) == ESP_OK) {
            ESP_LOGI(TAG,"Humidity: %d%% Temperature: %dC\n", humidity / 10, temperature / 10);
            time_t now = time(NULL);
            timeinfo = localtime(&now);
            strftime(formatted_time, sizeof(formatted_time), "%Y-%m-%d %H:%M:%S", timeinfo);
            sprintf(hum_char, "%d", humidity/10);
			sprintf(temp_char, "%d", temperature/10);
			pant_main(hum_char, temp_char);
            if(cont_mqtt==60)
                {
                cont_mqtt=0;
                mqtt_send_info();
                }
            cont_mqtt=cont_mqtt+1;    
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