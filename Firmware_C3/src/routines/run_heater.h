#include "shared/dependencies.h"

void controlPower(uint16_t power)
{
    if ((burnoutCounter > 30) && (burnoutCounter < 800))
    {
        powerOutput = power;
    }
    else
    {
        powerOutput = 0;
    }
    powerPercent = powerOutput / 10;
    ledcWrite(heater, powerOutput);
}