#if !defined(ESP_SLEEP_TIMER)
#define ESP_SLEEP_TIMER

#include "shared/dependencies.h"

//* Puts ESP12F in deep sleep for the specified number of seconds.
void esp_sleep_timer_init(int seconds)
{
    serialMon.println("[ESP_SLEEP_TIMER] Going to sleep for " + String(seconds) + " seconds.");
    ESP.deepSleep(seconds * one_second_in_microseconds);
}

#endif // ESP_SLEEP_TIMER
