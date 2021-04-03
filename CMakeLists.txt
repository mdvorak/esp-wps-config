cmake_minimum_required(VERSION 3.11.0)

idf_component_register(
        SRCS src/wps_config.c
        INCLUDE_DIRS include
        REQUIRES freertos log esp_wifi wpa_supplicant
)
