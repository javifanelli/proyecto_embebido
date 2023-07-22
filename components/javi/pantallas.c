#include "../ssd1306/ssd1306.h"
#include "../ssd1306/font8x8_basic.h"
#define tag "SH1106"

#define SDA_DIS	5 // Puerto SDA del i2c
#define SCL_DIS	6 // Puerto SCL del i2c
#define RST_DIS	-1 // Puerto Reset del i2c
#define HOR_RES	128 // Resolución horizontal
#define VER_RES	64 // Resolución vertical
#define DELAY_BIENV 5000 // Delay de pantalla de bienvenida
#define DELAY_CON 5000 // Delay de pantalla de conexión

SSD1306_t devd;

void config_dis (void);
void pant_bienv (void);
void pant_inicio (void);
void pant_nocon(void);
void pant_main ();
void pant_no_sensor(void);

void config_dis (void)
{
	//CONFIG I2C FOR DISPLAY
	ESP_LOGI(tag, "DISPLAY INTERFACE is i2c");
	ESP_LOGI(tag, "SDA_DIS=%d",SDA_DIS);
	ESP_LOGI(tag, "SCL_DIS=%d",SCL_DIS);
	i2c_master_init(&devd, SDA_DIS, SCL_DIS, RST_DIS);
	ESP_LOGI(tag, "Panel is 128x64");
	ssd1306_init(&devd, HOR_RES, VER_RES);
	ssd1306_clear_screen(&devd, false);
	ssd1306_contrast(&devd, CONTRAST);
}

void pant_bienv (void)
{
    //MENSAJE DE BIENVENIDA
	ssd1306_clear_screen(&devd, false);
  	ssd1306_display_text(&devd, 0, "   Bienvenido", 13, false);
	ssd1306_display_text(&devd, 1, "   Sistema de", 13, false);
	ssd1306_display_text(&devd, 2, "    domotica", 12, false);
	ssd1306_display_text(&devd, 3, "  UBA Posgrado", 14, false);
	ssd1306_display_text(&devd, 4, "  Esp. en IoT", 13, false);
	ssd1306_display_text(&devd, 5, " Proyecto final", 15, false);
	ssd1306_display_text(&devd, 6, " Javier Fanelli", 15, false);
	ssd1306_display_text(&devd, 7, " Bs. As. - 2023", 15, false);
	vTaskDelay(1500 / portTICK_PERIOD_MS);
	ssd1306_fadeout(&devd);			// Fade Out
	ssd1306_clear_screen(&devd, false);
}

void pant_inicio ()
{
	ssd1306_display_text(&devd, 0, "Iniciando el", 12, false);
    ssd1306_display_text(&devd, 1, "sistema...", 10, false);
}
void pant_conok ()
{
	TickType_t last_wake_time = xTaskGetTickCount();
	ssd1306_clear_screen(&devd, false);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	ssd1306_display_text(&devd, 0, "IP address:", 11, false);
	ssd1306_display_text(&devd, 1, ip, strlen(ip), true);
	ssd1306_display_text(&devd, 2, "MAC address:", 12, false);
	ssd1306_display_text(&devd, 3, mac_short, strlen(mac_short), true);
	ssd1306_display_text(&devd, 4, "Gateway IP:", 11, false);
	ssd1306_display_text(&devd, 5, gw, strlen(gw), true);
	ssd1306_display_text_with_value(&devd, 6, "Pot senal: ", 11, RSSI_CHAR, strlen(RSSI_CHAR), false);
	vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(5000));
	ssd1306_clear_screen(&devd, false);
}

void pant_nocon(void)
{
	TickType_t last_wake_time = xTaskGetTickCount();
	ssd1306_clear_screen(&devd, false);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	ssd1306_display_text(&devd, 0, "IP address:", 11, false);
	ssd1306_display_text(&devd, 1, "---.---.---.---", 15, true);
	ssd1306_display_text(&devd, 2, "MAC address:", 12, false);
	ssd1306_display_text(&devd, 3, "XXXXXXXX", 8,true);
	ssd1306_display_text(&devd, 4, "Gateway IP:", 11, false);
	ssd1306_display_text(&devd, 5, "---.---.---.---", 15, true);
	ssd1306_display_text(&devd, 6, "Pot senal: XX", 11, false);
	ssd1306_display_text(&devd, 7, "Error conexion", 14, false);
	vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(5000));
	ssd1306_clear_screen(&devd, false);
}

void pant_main()
{
	ssd1306_display_text(&devd, 0, pant_time, strlen(pant_time), true);
    ssd1306_display_text_with_value(&devd, 1, "Temperatura: ", 13, temp_char, strlen(temp_char), false);
    ssd1306_display_text_with_value(&devd, 2, "Humedad %: ", 11, hum_char, strlen(hum_char), false);
	if (out_temp == false){
		ssd1306_display_text(&devd, 3, "Salida: OFF", 11, false);
	}
	else {
		ssd1306_display_text(&devd, 3, "Salida: ON", 10, false);
	}
	if (net_con == true){
		ssd1306_display_text(&devd, 4, "Red: OK   ", 10, false);
		// Encender el LED en color verde
		
	}
	else if (net_con == false) {
		ssd1306_display_text(&devd, 4, "Red: ERROR", 10, false);
		// Encender el LED en color rojo
		
	}
	if (mqtt_state == true){
		ssd1306_display_text(&devd, 5, "Server: ONLINE ", 15, false);
	}
	else if (mqtt_state ==  false) {
		ssd1306_display_text(&devd, 5, "Server: OFFLINE", 15, false);
	}
	ssd1306_display_text(&devd, 7, "Menu", 4, true);
	if (btn_enc){
		pant_conok();
		btn_enc=false;
	}
}

void pant_no_sensor(void)
{
	ssd1306_clear_screen(&devd, false);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	ssd1306_display_text(&devd, 0, "No hay sensor", 13, false);
	ssd1306_display_text(&devd, 1, "conectado", 9, false);
	ssd1306_clear_screen(&devd, false);
}