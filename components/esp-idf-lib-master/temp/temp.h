#define DHT_PIN GPIO_NUM_0

static const dht_sensor_type_t sensor_type = DHT_TYPE_DHT11;
static const gpio_num_t dht_gpio = GPIO_NUM_0;
/* int8_t rssi = 0; */
wifi_ap_record_t ap_info;
int16_t humidity=0;
int16_t temperature=0;
int16_t hum_old=0;
int16_t temp_old=0;
char hum_char[10];
char temp_char[10];
char rssi_char[10];
int cont_temp=0;

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
           /*  rssi = ap_info.rssi;
            ESP_LOGI(TAG,"Potencia de señal: %d", rssi);
            sprintf(rssi_char, "%d", rssi); */
			pant_main(hum_char, temp_char, rssi_char);
            vTaskDelay(30000 / portTICK_PERIOD_MS);
        } else {
            ESP_LOGE(TAG,"Could not read data from sensor\n");
			pant_no_sensor();
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
		
   }
}