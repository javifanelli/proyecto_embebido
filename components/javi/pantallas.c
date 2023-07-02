#include "ssd1306.h"
#include "font8x8_basic.h"

#define DELAY_BIENV 7000
#define DELAY_CON 5000

SSD1306_t devd;

void config_dis (void);
void pant_bienv (void);
void pant_conex (void);
void pant_estado (char*, char *, char*);
void pant_nocon(void);
void pant_main (char*, char *, char*);
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
}

void pant_bienv (void)
{
    //MENSAJE DE BIENVENIDA
	ssd1306_clear_screen(&devd, false);
	ssd1306_contrast(&devd, CONTRAST);
  	ssd1306_display_text(&devd, 0, "   Bienvenido", 13, false);
	ssd1306_display_text(&devd, 1, "   Sistema de", 13, false);
	ssd1306_display_text(&devd, 2, "    domotica", 12, false);
	ssd1306_display_text(&devd, 3, "  UBA Posgrado", 14, false);
	ssd1306_display_text(&devd, 4, "  Esp. en IoT", 13, false);
	ssd1306_display_text(&devd, 5, " Proyecto final", 15, false);
	ssd1306_display_text(&devd, 6, " Javier Fanelli", 15, false);
	ssd1306_display_text(&devd, 7, " Bs. As. - 2023", 15, false);
	vTaskDelay(DELAY_BIENV / portTICK_PERIOD_MS);
	ssd1306_fadeout(&devd);			// Fade Out
	ssd1306_clear_screen(&devd, false);
}

void pant_conectando (void)
{	
	//PANTALLA DE CONEXION
	ssd1306_clear_screen(&devd, false);
	ssd1306_display_text(&devd, 0, "Conectando a la", 15, false);
	ssd1306_display_text(&devd, 1, "red...", 6, false);
	wifi_init_sta(); // Conexión a la red Wi-Fi
	ssd1306_display_text(&devd, 1, "red... OK", 9, false);
	vTaskDelay(500 / portTICK_PERIOD_MS);
	ssd1306_display_text(&devd, 2, "Conectando al", 13, false);
	ssd1306_display_text(&devd, 3, "servidor...", 11, false);
	vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void pant_conok (char* ssid, char* ip_add, char* mac_add)
{
	ssd1306_clear_screen(&devd, false);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	ssd1306_display_text(&devd, 0, "Estado:", 7, false);
	ssd1306_display_text(&devd, 1, "Conectado", 9, true);
	ssd1306_display_text(&devd, 2, "SSID:", 5, false);
	ssd1306_display_text(&devd, 3, ssid, strlen(ssid), true);
	ssd1306_display_text(&devd, 4, "IP address:", 11, false);
	ssd1306_display_text(&devd, 5, ip_add, strlen(ip_add), true);
	ssd1306_display_text(&devd, 6, "MAC address:", 12, false);
	ssd1306_display_text(&devd, 7, mac_add, strlen(mac_add), true);
	vTaskDelay(DELAY_CON / portTICK_PERIOD_MS);
}

void pant_nocon(void)
{
	ssd1306_clear_screen(&devd, false);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	ssd1306_display_text(&devd, 0, "Estado:", 7, false);
	ssd1306_display_text(&devd, 1, "Error conexion", 14, true);
	ssd1306_display_text(&devd, 2, "SSID:", 5, false);
	ssd1306_display_text(&devd, 3, "--------", 8, true);
	ssd1306_display_text(&devd, 4, "IP address:", 11, false);
	ssd1306_display_text(&devd, 5, "--------", 8, true);
	ssd1306_display_text(&devd, 6, "MAC address:", 12, false);
	ssd1306_display_text(&devd, 7, "--------", 8, true);
	vTaskDelay(5000 / portTICK_PERIOD_MS);
	ssd1306_clear_screen(&devd, false);
	ssd1306_display_text(&devd, 0, "Error conexion", 14, true);
	ssd1306_display_text(&devd, 1, "Revisa la", 9, true);
	ssd1306_display_text(&devd, 2, "configuracion", 13, true);
	ssd1306_clear_screen(&devd, false);
}

void pant_main(char* humedad, char* temperatura, char* rssi)
{
    ssd1306_display_text(&devd, 0, "Conectado", 9, false);
    ssd1306_display_text_with_value(&devd, 1, "Temperatura: ", 13, temperatura, strlen(temperatura), false);
    ssd1306_display_text_with_value(&devd, 2, "Humedad %: ", 11, humedad, strlen(humedad), false);
	ssd1306_display_text_with_value(&devd, 3, "RSSI: ", 7, rssi, strlen(rssi), false);
}

void pant_no_sensor(void)
{
	ssd1306_clear_screen(&devd, false);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	ssd1306_display_text(&devd, 0, "No hay sensor", 13, false);
	ssd1306_display_text(&devd, 1, "conectado", 9, false);
	ssd1306_clear_screen(&devd, false);
}