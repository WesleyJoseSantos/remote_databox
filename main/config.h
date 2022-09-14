/**
 * @file config.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __CONFIG__H__
#define __CONFIG__H__

#define CONFIG_BASEPATH "/"

#define CONFIG_VFS_FAT_MOUNT() {                        \
    .max_files = 4,                                     \
    .format_if_mount_failed = true,                     \
    .allocation_unit_size = CONFIG_WL_SECTOR_SIZE       \
}

#define CONFIG_HTTP_SERVER() {      \
    .port = 80,                     \
}

#define CONFIG_WIFI_AP() {              \
    .ssid = "Remote Databox",           \
    .password = "administrator",        \
    .authmode = WIFI_AUTH_WPA2_PSK,     \
    .max_connection = 1                 \
}

#define CONFIG_WIFI_STA() {         \
    .ssid = "CABO CANAVERAL 3",     \
    .password = "16192020",         \
    .max_connection = 1,            \
}

#endif  //!__CONFIG__H__