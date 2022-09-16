/**
 * @file net_app.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "net_app.h"
#include "esp_log.h"
#include "tasks_common.h"

typedef struct net_app
{
    TaskHandle_t task;
    QueueHandle_t queue;
    httpd_handle_t http;
    int err;
} net_app_t;

const char *TAG = "net.h";

static net_app_t this;

static void net_app_task(void *pvParameter)
{
    net_app_queue_msg_t msg;
    net_app_wifi_init();
    for(;;)
    {
        if(xQueueReceive(this.queue, &msg, portMAX_DELAY))
        {
            switch (msg.id)
            {
            case NET_APP_MSG_ID_START_HTTP_SERVER:
                this.err = httpd_start(this.http, (httpd_config_t*)&msg.cfg);
                break;
            case NET_APP_MSG_ID_START_WIFI_AP:
                net_app_wifi_ap_start((wifi_ap_config_t*)&msg.cfg);
                break;
            case NET_APP_MSG_ID_START_WIFI_STA:
                net_app_wifi_sta_start((wifi_sta_config_t*)&msg.cfg);
                break;
            default:
                break;
            }
        }
    }
}

static int net_app_wifi_init()
{
    wifi_init_config_t init_cfg = WIFI_INIT_CONFIG_DEFAULT();
    this.err = esp_wifi_init(&init_cfg);
    if(this.err != ESP_OK) return this.err;
}

static void net_app_wifi_ap_start(wifi_ap_config_t *cfg)
{
    wifi_mode_t wifi_mode;
    ESP_ERROR_CHECK(esp_wifi_get_mode(&wifi_mode));
    wifi_mode = wifi_mode == WIFI_MODE_STA ? WIFI_MODE_APSTA : WIFI_MODE_STA;

    ESP_ERROR_CHECK(esp_wifi_set_mode(wifi_mode));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, (wifi_config_t*)&cfg));
    ESP_ERROR_CHECK(esp_wifi_start());
}

static void net_app_wifi_sta_start(wifi_sta_config_t *cfg)
{
    wifi_mode_t wifi_mode;
    ESP_ERROR_CHECK(esp_wifi_get_mode(&wifi_mode));
    wifi_mode = wifi_mode == WIFI_MODE_AP ? WIFI_MODE_APSTA : WIFI_MODE_STA;

    ESP_ERROR_CHECK(esp_wifi_set_mode(wifi_mode));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, (wifi_config_t*)&cfg));
    ESP_ERROR_CHECK(esp_wifi_start());
}

BaseType_t net_app_send_msg(net_app_queue_msg_t *msg)
{
    return xQueueSend(this.queue, &msg, portMAX_DELAY);
}

void net_app_start(void)
{
    ESP_LOGI(TAG, "Start network application");

    this.queue = xQueueCreate(5, sizeof(net_app_queue_msg_t));

    xTaskCreatePinnedToCore(&net_app_task, "net_app_task", NET_APP_TASK_STACK_SIZE, NULL, NET_APP_TASK_PRIORITY, this.task, NET_APP_TASK_CORE_ID);
}
