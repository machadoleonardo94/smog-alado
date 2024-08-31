#if !defined(READ_ESP32_WIFI_STATE)
#define READ_ESP32_WIFI_STATE

// todo implement this feature correctly.

bool read_state_wifi_esp32()
{
    if (WiFi.status() == WL_CONNECTED)
        return true;
    return false;
}

#endif // READ_ESP32_WIFI_STATE
