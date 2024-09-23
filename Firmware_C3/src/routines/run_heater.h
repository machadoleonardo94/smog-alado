#ifndef HEATER_ROUTINE
#define HEATER_ROUTINE

#include "shared/dependencies.h"

void controlPower(uint16_t power)
{
    if ((clickCounter == 2) && (!burnout))
    {
        powerOutput = power * 130 * (4.2 / battery);
        if (powerOutput > 900)
            powerOutput = 900;
    }
    else
    {
        powerOutput = 0;
    }
    powerPercent = powerOutput / 10;
    ledcWrite(heater, powerOutput);
}

#endif