#define LED_R GPIO_NUM_15
#define LED_G GPIO_NUM_4

#define PWM_CHANNEL      LEDC_CHANNEL_0
#define PWM_GPIO_NUM     GPIO_NUM_13
#define PWM_FREQ_HZ      1000
#define PWM_RESOLUTION   LEDC_TIMER_10_BIT // Resolución de 10 bits (0-1023)


wifi_ap_record_t ap_info;
struct tm *timeinfo;
struct timeval tv;

rotary_encoder_t control = {
    .pin_a = 33,       // Número del GPIO al que está conectado el pin "A" del encoder
    .pin_b = 32,       // Número del GPIO al que está conectado el pin "B" del encoder
    .pin_btn = 35,     // Número del GPIO al que está conectado el botón del encoder
};

void pwm_init()
{
    // Configurar el módulo LEDC
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = PWM_RESOLUTION,
        .freq_hz = PWM_FREQ_HZ,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .channel = PWM_CHANNEL,
        .duty = 0,
        .gpio_num = PWM_GPIO_NUM,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER_0
    };
    ledc_channel_config(&ledc_channel);
    ledc_fade_func_install(0);
}

void set_pwm_duty(uint32_t duty)
{
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL, duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL);
}
