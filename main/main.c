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

#include "main.h"

static remote_databox_t databox;

static const char *TAG = "main";

static void nvs_init(void);
static void vfs_fat_init(void);

void app_main(void)
{
    nvs_init();
    vfs_fat_init();
    datalogger_init();
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
    esp_err_t err = esp_vfs_fat_spiflash_mount(CONFIG_BASEPATH, "data", &mount_cfg, &databox.vfs_fat);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to mount partition FATFS (%s)", esp_err_to_name(err));
    }else{
        ESP_LOGI(TAG, "FATFS partition successfully mounted.");
    }
}