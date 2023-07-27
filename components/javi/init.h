#define LED_R GPIO_NUM_15
#define LED_G GPIO_NUM_4
#define DIMMER GPIO_NUM_13

wifi_ap_record_t ap_info;
struct tm *timeinfo;
struct timeval tv;

rotary_encoder_t control = {
    .pin_a = 1,       // Número del GPIO al que está conectado el pin "A" del encoder
    .pin_b = 2,       // Número del GPIO al que está conectado el pin "B" del encoder
    .pin_btn = 3,     // Número del GPIO al que está conectado el botón del encoder
};

