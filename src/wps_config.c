#include "wps_config.h"
#include <esp_log.h>
#include <esp_wifi.h>
#include <esp_wps.h>
#include <freertos/event_groups.h>
#include <string.h>

static const char TAG[] = "auto_wps";

ESP_EVENT_DEFINE_BASE(WPS_CONFIG_EVENT);

static bool initialized = false;

static inline bool is_ssid_stored()
{
    wifi_config_t conf;
    esp_err_t err = esp_wifi_get_config(WIFI_IF_STA, &conf);
    return err == ESP_OK && conf.sta.ssid[0] != '\0';
}

static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    switch (event_id)
    {
    case WIFI_EVENT_STA_WPS_ER_SUCCESS: {
        ESP_ERROR_CHECK_WITHOUT_ABORT(esp_wifi_wps_disable());
        ESP_LOGI(TAG, "wps succeeded, connecting to wifi");

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 1, 1)
        // NOTE when only one credential is received from WPS, evt maight be null and they are stored automatically by the framework
        wifi_event_sta_wps_er_success_t *evt = (wifi_event_sta_wps_er_success_t *)event_data;
        if (evt)
        {
            wifi_config_t wifi_config = {};
            memcpy(wifi_config.sta.ssid, evt->ap_cred[0].ssid, sizeof(evt->ap_cred[0].ssid));
            memcpy(wifi_config.sta.password, evt->ap_cred[0].passphrase, sizeof(evt->ap_cred[0].passphrase));

            ESP_ERROR_CHECK_WITHOUT_ABORT(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
        }
#endif

        // Connect immediately
        ESP_ERROR_CHECK_WITHOUT_ABORT(esp_wifi_connect());
        break;
    }

    case WIFI_EVENT_STA_WPS_ER_FAILED:
        ESP_ERROR_CHECK_WITHOUT_ABORT(esp_wifi_wps_disable());

        if (is_ssid_stored())
        {
            ESP_LOGI(TAG, "wps failed, trying last known ssid");
            ESP_ERROR_CHECK_WITHOUT_ABORT(esp_wifi_connect());
        }
        else
        {
            ESP_LOGI(TAG, "wps failed, no wifi configured, no network will be available");
        }
        break;

    case WIFI_EVENT_STA_WPS_ER_TIMEOUT:
        ESP_ERROR_CHECK_WITHOUT_ABORT(esp_wifi_wps_disable());
        if (is_ssid_stored())
        {
            ESP_LOGI(TAG, "wps timeout, trying last known ssid");
            ESP_ERROR_CHECK_WITHOUT_ABORT(esp_wifi_connect());
        }
        else
        {
            ESP_LOGI(TAG, "wps timeout, no wifi configured, no network will be available");
        }
        break;
    }
}

esp_err_t wps_config_start()
{
    esp_err_t err;

    // Support multiple calls
    if (!initialized)
    {
        initialized = true;

        // Register handler
        err = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
        if (err != ESP_OK)
            return err;

        // Config
        esp_wps_config_t wps_config = WPS_CONFIG_INIT_DEFAULT(WPS_TYPE_PBC);
        err = esp_wifi_wps_enable(&wps_config);
        if (err != ESP_OK)
            return err;
    }

    // Start
    ESP_LOGI(TAG, "starting wps");
    ESP_ERROR_CHECK_WITHOUT_ABORT(esp_event_post(WPS_CONFIG_EVENT, WPS_CONFIG_EVENT_START, NULL, 0, portMAX_DELAY));

    return esp_wifi_wps_start(0); // NOTE timeout is ignored as of IDF 4.2
}
