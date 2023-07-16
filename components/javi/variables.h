// Pin conectado al DHT11 usado em temp.h
#define dht_gpio 0

// Variables usadas para la conexion Wi-Fi usadas en wifi_con.c
#define EXAMPLE_ESP_WIFI_SSID "JaviRomi_Wifi" // Red local
#define EXAMPLE_ESP_WIFI_PASS "SanLorenzo4781" // Wifi pass
#define EXAMPLE_ESP_MAXIMUM_RETRY 10

// Valores de configuración del display usados en pantallas.c
#define SDA_DIS	5 // Puerto SDA del i2c
#define SCL_DIS	6 // Puerto SCL del i2c
#define RST_DIS	-1 // Puerto Reset del i2c
#define HOR_RES	128 // Resolución horizontal
#define VER_RES	64 // Resolución vertical
#define	CONTRAST 0x0F // Contraste del display
#define DELAY_BIENV 5000 // Delay de pantalla de bienvenida
#define DELAY_CON 5000 // Delay de pantalla de conexión

// Variables usadas para configurar el protocolo MQTT en mqtt_funcs.c
#define BROKER_URI "mqtts://192.168.0.70" // IP del broker (Raspberry Pi)
#define seconds 30 // Segundos de delay en actualizar temperatura
// Certificados usados para la conexión segura con el broker
extern const uint8_t client_cert_pem_start[] asm("_binary_client_pem_start");
extern const uint8_t client_cert_pem_end[] asm("_binary_client_pem_end");
extern const uint8_t client_key_pem_start[] asm("_binary_client_key_start");
extern const uint8_t client_key_pem_end[] asm("_binary_client_key_end");
extern const uint8_t server_cert_pem_start[] asm("_binary_ca_pem_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_ca_pem_end");

// Variables globales usadas
char hum_char[10]; // valor de humedad en char para mostrar
char temp_char[10]; // valor de temperatura en char para mostrar
uint8_t mac[6]; // MAC del dispositivo ESP32
static char mac_str[18]; // MAC del dispositivo ESP32 en char
static char mac_short[12]; // MAC del dispositivo ESP32 en char sin los :
static char ip[16]; // IP del dispositivo ESP32
static char gw[16]; // IP del gateway de red
char formatted_time[20]; // Fecha y hora en char
wifi_ap_record_t ap_info;
static int8_t rssi = 0; // Potencia de la señal
char RSSI_CHAR[10]; // Potencia de la señal en char
bool net_con = false; // Variable para detectar el estado de conexión a la red
bool mqtt_state = false; // Variable para detectar el estado de conexión al servidor por MQTT
bool out = false; // Variable para detectar el estado de la salida de relé
static char TOPIC[50]="/home/temperatura/data"; // Topic de MQTT

struct tm *timeinfo;
struct timeval tv;

