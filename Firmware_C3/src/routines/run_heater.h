#ifndef HEATER_ROUTINE
#define HEATER_ROUTINE

#include "shared/dependencies.h"

void controlPower(uint16_t power)
{
    if ((clickCounter == 1) || constantHeating)
    {
        totalHeatingTime += SAMPLING_TIMER;
    }
    if (buttonTimer > (8 * SAMPLES_TO_SEC))
    {
        burnout = true;
        powerOutput = 0;
        setLED(255, 0, 0);
        burnoutScreen();
    }
    if (!constantHeating)
    {
        if ((clickCounter == 1) && (!burnout) && (buttonTimer > 10))
        {
            powerOutput = power * 130;
            int powerCeiling = 100 + (buttonTimer * 10);
            powerCeiling = constrain(powerCeiling, 0, 1000);
            powerOutput = constrain(powerOutput, 0, powerCeiling);
        }
        else
        {
            powerOutput = 0;
        }
    }
    else
    {
        powerOutput = power * 130;
        powerOutput = constrain(powerOutput, 0, 1000);
    }
    powerPercent = powerOutput / 10;
    ledcWrite(heater, powerOutput);
}

#endif