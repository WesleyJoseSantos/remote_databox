/**
 * @file net.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __NET__H__
#define __NET__H__

#include "esp_wifi.h"
#include "mqtt_client.h"
#include "esp_http_server.h"

typedef enum net_msg_id
{
    NET_MSG_ID_START_HTTP_SERVER,
    NET_MSG_ID_START_WIFI_AP,
    NET_MSG_ID_START_WIFI_STA,
    NET_MSG_ID_START_MQTT,
} net_msg_id_t;

typedef struct net_config_queue_msg
{
    net_msg_id_t msg_id;
    net_interface_cfg_t cfg;
} net_config_queue_msg_t;

typedef union net_interface_cfg
{
    httpd_config_t http_server;
    wifi_ap_config_t wifi_ap;
    wifi_sta_config_t wifi_sta;
    esp_mqtt_client_config_t mqtt;
} net_interface_cfg_t;

typedef struct net_cfg
{
    httpd_config_t http_server;
    wifi_ap_config_t wifi_ap;
    wifi_sta_config_t wifi_sta;
    esp_mqtt_client_config_t mqtt;
} net_cfg_t;

#endif  //!__NET__H__