#ifndef AUTO_WPS_H
#define AUTO_WPS_H

#include <esp_err.h>

#ifdef __cplusplus
extern "C"
{
#endif

    esp_err_t auto_wps_start(uint32_t wps_timeout_ms);

#ifdef __cplusplus
}
#endif

#endif
