#ifndef AUTO_WPS_H
#define AUTO_WPS_H

#include <esp_err.h>

#ifdef __cplusplus
extern "C"
{
#endif

    const uint32_t AUTO_WPS_TIMEOUT_MS = 120000;

    esp_err_t auto_wps_start();

#ifdef __cplusplus
}
#endif

#endif
