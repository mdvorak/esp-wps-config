#include <esp_log.h>
#include <esp_netif.h>
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <wps_config.h>

static const char TAG[] = "example";

static void setup()
{
    esp_log_level_set("wifi", ESP_LOG_WARN);
    esp_log_level_set("auto_wps", ESP_LOG_DEBUG);

    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Events
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_event_handler_register(
        WPS_CONFIG, WPS_CONFIG_EVENT_START, [](void *, esp_event_base_t, int32_t, void *) { ESP_LOGI(TAG, "wps started event"); }, NULL);

    // Initalize WiFi
    ESP_ERROR_CHECK(esp_netif_init());
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_FLASH));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    // Start WPS
    ESP_ERROR_CHECK(wps_config_start());

    // Setup complete
    ESP_LOGI(TAG, "started");
}

static void run()
{
}

extern "C" void app_main()
{
    setup();
    run();
}
