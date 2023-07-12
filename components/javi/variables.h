// Pin conectado al DHT11 usado em temp.h
#define dht_gpio 0

// Variables usadas para la conexion Wi-Fi usadas en wifi_con.c
#define EXAMPLE_ESP_WIFI_SSID "JaviRomi_Wifi" // Red local
#define EXAMPLE_ESP_WIFI_PASS "SanLorenzo4781" // Wifi pass
#define EXAMPLE_ESP_MAXIMUM_RETRY 10

// Valores de configuración del display usados en pantallas.c
#define tag 		"SH1106"
#define SDA_DIS		5		            // Puerto SDA del i2c
#define SCL_DIS		6		            // Puerto SCL del i2c
#define RST_DIS		-1		            // Puerto Reset del i2c
#define HOR_RES		128		            // Resolución horizontal
#define VER_RES		64		            // Resolución vertical
#define	CONTRAST	0x0F	            // Contraste del display
#define DELAY_BIENV 5000                // Delay de pantalla de bienvenida
#define DELAY_CON 2000                  // Delay de pantalla de conexión