#define LED_R_PIN 0 // Pin GPIO para el LED rojo
#define LED_G_PIN 2 // Pin GPIO para el LED verde
#define LED_B_PIN 4 // Pin GPIO para el LED azul


wifi_ap_record_t ap_info;
struct tm *timeinfo;
struct timeval tv;

rotary_encoder_t control = {
    .pin_a = 33,       // Número del GPIO al que está conectado el pin "A" del encoder
    .pin_b = 32,       // Número del GPIO al que está conectado el pin "B" del encoder
    .pin_btn = 35,     // Número del GPIO al que está conectado el botón del encoder
};

