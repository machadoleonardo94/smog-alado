#ifndef HEATER_ROUTINE
#define HEATER_ROUTINE

#include "shared/dependencies.h"

void controlPower(uint16_t power)
{
    if (buttonTimer > (8 * SAMPLES_TO_SEC))
    {
        burnout = true;
        powerOutput = 0;
        setLED(255, 0, 0);
        burnoutScreen();
    }
    if ((clickCounter == 1) && (!burnout) && (buttonTimer > 10))
    {
        powerOutput = power * 180 * (pow((4.2 / battery), 2));
        constrain(powerOutput, 0, 1000);
    }
    else
    {
        powerOutput = 0;
    }
    powerPercent = powerOutput / 10;
    ledcWrite(heater, powerOutput);
}

#endif