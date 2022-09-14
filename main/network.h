/**
 * @file network.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __NETWORK__H__
#define __NETWORK__H__

#include "esp_wifi.h"
#include "mqtt_client.h"

typedef struct network_config
{
    wifi_ap_config_t ap;
    wifi_sta_config_t sta;
    esp_mqtt_client_config_t mqtt;
} network_config_t;

#endif  //!__NETWORK__H__