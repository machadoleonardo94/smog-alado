#include "shared/dependencies.h"
#include "shared/pinout.h"

void check_wakeup_reason()
{
    //* Wakeup
    esp_sleep_wakeup_cause_t wakeup_reason;
    wakeup_reason = esp_sleep_get_wakeup_cause();
}