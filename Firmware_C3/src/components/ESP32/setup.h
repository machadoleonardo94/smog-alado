#if !defined(SETUP_ESP32)
#define SETUP_ESP32

#include "shared/dependencies.h"
#include "components/ESP32/features/enable_deep_sleep.h"
#include "components/ESP32/features/update_firmware_ota.h"

void setup_ESP32()
{
    Serial.println("[ESP32] SETUP STARTED!");

    //* Setup bluetooth
    btStop();

    // Sets input voltage ADC attenuation
    // analogReadResolution(14);
    analogSetPinAttenuation(A1, ADC_11db);
    analogSetPinAttenuation(A0, ADC_0db);

    //* Setup Watchdog
    // esp_task_wdt_init(60, true);
    // esp_task_wdt_add(NULL);

    Serial.println("[ESP32] SETUP FINISHED!");
}

#endif // SETUP_ESP32