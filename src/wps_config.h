#ifndef AUTO_WPS_H
#define AUTO_WPS_H

#include <esp_err.h>
#include <esp_event_base.h>

#ifdef __cplusplus
extern "C"
{
#endif

    const uint32_t WPS_CONFIG_TIMEOUT_MS = 120000;

    ESP_EVENT_DECLARE_BASE(WPS_CONFIG);

    typedef enum
    {
        WPS_CONFIG_EVENT_START, /** WPS has been started */
        WPS_CONFIG_EVENT_MAX,   /** Invalid event ID */
    } wps_config_event_t;

    esp_err_t wps_config_start();

#ifdef __cplusplus
}
#endif

#endif
