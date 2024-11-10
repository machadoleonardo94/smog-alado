#if !defined(ESP_SLEEP_TIMER)
#define ESP_SLEEP_TIMER

#include "shared/dependencies.h"

//* Puts ESP32 in deep sleep for the specified number of seconds.
void esp_sleep_timer_init(int seconds)
{
    Serial.println("[ESP_SLEEP_TIMER] Going to sleep for " + String(seconds) + " seconds.");
    esp_sleep_enable_timer_wakeup(seconds * one_second_in_microseconds);
    esp_deep_sleep_start();
}

#endif // ESP_SLEEP_TIMER
