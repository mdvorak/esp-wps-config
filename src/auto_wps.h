#ifndef AUTO_WPS_H
#define AUTO_WPS_H

#include <esp_err.h>

#ifdef __cplusplus
extern "C"
{
#endif

    const uint32_t AUTO_WPS_TIMEOUT = 2 * 60000; // 2min

    esp_err_t auto_wps_start(uint32_t wps_timeout);

#ifdef __cplusplus
}
#endif

#endif
