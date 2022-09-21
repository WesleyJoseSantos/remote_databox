/**
 * @file net_app.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __NET_APP__H__
#define __NET_APP__H__

#include "esp_wifi.h"
#include "mqtt_client.h"
#include "esp_http_server.h"

typedef enum net_app_msg_id
{
    NET_APP_MSG_ID_START_HTTP_SERVER,
    NET_APP_MSG_ID_START_WIFI_AP,
    NET_APP_MSG_ID_START_WIFI_STA,
    NET_APP_MSG_ID_START_MQTT,
} net_app_msg_id_t;

typedef struct net_app_queue_msg
{
    net_app_msg_id_t id;
    net_app_interface_cfg_t cfg;
} net_app_queue_msg_t;

typedef union net_app_interface_cfg
{
    httpd_config_t http_server;
    wifi_ap_config_t wifi_ap;
    wifi_sta_config_t wifi_sta;
    esp_mqtt_client_config_t mqtt;
} net_app_interface_cfg_t;

/**
 * @brief Sends a message to network queue
 * 
 * @param msg msg to be sended to queue
 * @return BaseType_t pvTRUE if an intem was sucessfully added to the queue otherwise pdFALSE
 */
BaseType_t net_app_send_msg(net_app_queue_msg_t *msg);

/**
 * @brief Starts the network RTOS task
 * 
 */
void net_app_start(void);

#endif  //!__NET_APP__H__