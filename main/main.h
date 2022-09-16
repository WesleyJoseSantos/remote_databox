/**
 * @file main.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __MAIN__H__
#define __MAIN__H__

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
} remote_databox_t;

#endif  //!__MAIN__H__