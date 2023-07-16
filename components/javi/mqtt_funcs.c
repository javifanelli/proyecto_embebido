#include "sntp_time.h"

#define TAG "sensor"

static const char *ID ="1";

static char buffer_mqtt[150];
/* static const char *TAG = "sensor"; */
static esp_mqtt_client_handle_t client;

static void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0) {
        ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
    }
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    esp_mqtt_event_handle_t event = event_data;
    /* esp_mqtt_client_handle_t  */client = event->client;
    int msg_id;

    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        mqtt_state = true;
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        msg_id = esp_mqtt_client_subscribe(client, TOPIC, 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
        ssd1306_clear_screen(&devd, false);
        break;

    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        mqtt_state = false;
        break;
    
    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        /* buffer_in = event->data; */
        break;
    
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
            log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
            ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));
        }
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}

static void mqtt_app_start(void)
{
    esp_wifi_get_mac(ESP_IF_WIFI_STA, mac);
    sprintf(mac_str, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    const esp_mqtt_client_config_t mqtt_cfg = {
        .uri = BROKER_URI,
        .client_cert_pem = (const char *)client_cert_pem_start,
        .client_key_pem = (const char *)client_key_pem_start,
        .cert_pem = (const char *)server_cert_pem_start,
    };
    
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}

void mqtt_send_info(void)
{
    buffer_mqtt[0] = 0;
    RSSI_CHAR[0] = 0;
    esp_wifi_sta_get_ap_info(&ap_info);
    /* time_t now = time(NULL);
    timeinfo = localtime(&now);
    strftime(formatted_time, sizeof(formatted_time), "%Y-%m-%d %H:%M:%S", timeinfo); */
    memset(buffer_mqtt, 0, sizeof(buffer_mqtt));
    rssi = ap_info.rssi;
    sprintf(RSSI_CHAR, "%d", rssi);
    ESP_LOGI(TAG, "RSSI: %d ", ap_info.rssi);
    strcat(buffer_mqtt, "{\n\"ID\": ");
    strcat(buffer_mqtt, ID);
    strcat(buffer_mqtt, ",\n");
    strcat(buffer_mqtt, "\"RSSI\": ");
    strcat(buffer_mqtt, RSSI_CHAR);
    strcat(buffer_mqtt, ",\n");
    strcat(buffer_mqtt, "\"time\": \"");
    strcat(buffer_mqtt, formatted_time);
    strcat(buffer_mqtt, "\",\n");
    strcat(buffer_mqtt, "\"valor\": ");
    strcat(buffer_mqtt, temp_char);
    strcat(buffer_mqtt, ",\n");
    strcat(buffer_mqtt, "\"MAC\": \"");
    strcat(buffer_mqtt, mac_str);
    strcat(buffer_mqtt, "\"\n}");
    esp_mqtt_client_publish(client, TOPIC, buffer_mqtt, 0, 0, 0);
}
