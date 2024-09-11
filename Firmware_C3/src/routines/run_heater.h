#include "shared/dependencies.h"

void controlPower(uint16_t power)
{
    if ((burnoutCounter > 30) && (burnoutCounter < 800))
    {
        powerOutput = power;
        powerPercent = powerOutput / 10;
    }
    else
    {
        powerOutput = 0;
    }
    ledcWrite(heater, powerOutput);
}