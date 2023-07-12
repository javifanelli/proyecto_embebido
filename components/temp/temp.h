static const dht_sensor_type_t sensor_type = DHT_TYPE_DHT11;
int16_t humidity=0; // valor de humedad leído
int16_t temperature=0; // valor de temperatura leído
int16_t hum_old=0;
int16_t temp_old=0;
char hum_char[10]; // valor de humedad en char para mostrar
char temp_char[10]; // valor de temperatura en char para mostrar
int cont_temp=0;
int refresh=5; // tiempo en segundos para refrescar medición

void get_temp(void)
{
    while(1) {
        if (dht_read_data(sensor_type, dht_gpio, &humidity, &temperature) == ESP_OK) {
            ESP_LOGI(TAG,"Humidity: %d%% Temperature: %dC\n", humidity / 10, temperature / 10);
			if (temperature!=temp_old) {
                temp_old=temperature;
                };
            if (humidity!=hum_old) {
                hum_old=humidity;
                };
            sprintf(hum_char, "%d", humidity/10);
			sprintf(temp_char, "%d", temperature/10);
			pant_main(hum_char, temp_char);
            /* xTaskCreate(mqtt_send_info, "mqtt_send_info", 4096 * 8, NULL, 5, NULL); */
            vTaskDelay(1000*refresh / portTICK_PERIOD_MS);
        } else {
            ESP_LOGE(TAG,"Could not read data from sensor\n");
			pant_no_sensor();
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
		
   }
}