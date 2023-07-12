#include "../ssd1306/ssd1306.h"
#include "../ssd1306/font8x8_basic.h"

SSD1306_t devd;

void config_dis (void);
void pant_bienv (void);
void pant_conex (void);
void pant_estado (char*, char *, char*);
void pant_nocon(void);
void pant_main (char*, char *);
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

void pant_conok (char* ssid, char* ip_add, char* mac_add)
{
	ssd1306_clear_screen(&devd, false);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	ssd1306_display_text(&devd, 0, "Red... OK", 9, true);
	ssd1306_display_text(&devd, 1, "Server... OK", 12, true);
	ssd1306_display_text(&devd, 2, "IP address:", 11, false);
	ssd1306_display_text(&devd, 3, IPSTR, strlen(IPSTR), true);
	ssd1306_display_text(&devd, 4, "MAC address:", 12, false);
	ssd1306_display_text(&devd, 5, mac_add, strlen(mac_add), true);
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

void pant_main(char* humedad, char* temperatura)
{
    ssd1306_display_text(&devd, 0, "Hora", 4, false);
    ssd1306_display_text_with_value(&devd, 1, "Temperatura: ", 13, temperatura, strlen(temperatura), false);
    ssd1306_display_text_with_value(&devd, 2, "Humedad %: ", 11, humedad, strlen(humedad), false);
	ssd1306_display_text(&devd, 3, "Set point: ", 11, false);
	ssd1306_display_text(&devd, 4, "Salida: ", 8, false);
	ssd1306_display_text(&devd, 7, "Menu", 4, true);

}

void pant_no_sensor(void)
{
	ssd1306_clear_screen(&devd, false);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	ssd1306_display_text(&devd, 0, "No hay sensor", 13, false);
	ssd1306_display_text(&devd, 1, "conectado", 9, false);
	ssd1306_clear_screen(&devd, false);
}