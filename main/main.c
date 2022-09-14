/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "freertos/task.h"

#include "config.h"
#include "datalogger.h"
#include "esp_http_server.h"
#include "esp_wifi.h"
#include "nvs_flash.h"

typedef struct remote_databox
{
    wl_handle_t vfs_fat;
    httpd_handle_t http_server;  
} remote_databox_t;

static remote_databox_t databx;

static const char *TAG = "main";

static void nvs_init(void);
static void vfs_fat_init(void);
static void http_server_start(void);
static void wifi_ap_start(void);

void app_main(void)
{
    nvs_init();
    vfs_fat_init();
    datalogger_init();
    http_server_start();
    wifi_ap_start();
}

static void nvs_init(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(ret);
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
}

static void vfs_fat_init(void)
{
    esp_vfs_fat_mount_config_t mount_cfg = CONFIG_VFS_FAT_MOUNT();
    esp_err_t err = esp_vfs_fat_spiflash_mount(CONFIG_BASEPATH, "data", &mount_cfg, &databx.vfs_fat);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to mount partition FATFS (%s)", esp_err_to_name(err));
    }else{
        ESP_LOGI(TAG, "FATFS partition successfully mounted.");
    }
}

static void http_server_start(void)
{
    httpd_config_t httpd_config = HTTPD_DEFAULT_CONFIG();

    int err = httpd_start(databx.http_server, &httpd_config);

    if(err == ESP_OK)
    {
        ESP_LOGI(TAG, "Http server started on port '%d'", httpd_config.server_port);
    }
    else
    {
        ESP_LOGE(TAG, "Failed to start http server [%d]", err);
    }
}

static void wifi_ap_start(void)
{
    wifi_init_config_t init_cfg = WIFI_INIT_CONFIG_DEFAULT();
    wifi_ap_config_t ap = CONFIG_WIFI_AP();

    ESP_ERROR_CHECK(esp_wifi_init(&init_cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, (wifi_config_t*)&ap));
    ESP_ERROR_CHECK(esp_wifi_start());
}