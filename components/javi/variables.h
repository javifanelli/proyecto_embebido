// Variables globales usadas

uint8_t mac[6]; // MAC del dispositivo ESP32
static char mac_str[18]; // MAC del dispositivo ESP32 en char
static char mac_short[13]; // MAC del dispositivo ESP32 en char sin los :
static char ip[16]; // IP del dispositivo ESP32
static char gw[16]; // IP del gateway de red
char formatted_time[20]; // Fecha y hora en char para mandar por MQTT
char pant_time[20]; // Fecha y hora en char para mostrar en display

bool net_con = false; // Variable global para almacenar el estado de la conexión WiFi
bool mqtt_state = false; // Variable para detectar el estado de conexión al servidor por MQTT

char out_char[10];
bool btn_enc = false; // Variable para detectar el botón pulsado
bool inc_enc = false; // Variable para detectar el giro horario del encoder
bool dec_enc = false; // Variable para detectar el giro antihorario del encoder

char tipo_disp[50]="Dimmer";
