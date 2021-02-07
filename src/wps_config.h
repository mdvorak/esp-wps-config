#ifndef AUTO_WPS_H
#define AUTO_WPS_H

#include <esp_err.h>

#ifdef __cplusplus
extern "C"
{
#endif

    const uint32_t WPS_CONFIG_TIMEOUT_MS = 120000;

    esp_err_t wps_config_start();

#ifdef __cplusplus
}
#endif

#endif
