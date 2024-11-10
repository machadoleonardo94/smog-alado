#ifndef HEATER_ROUTINE
#define HEATER_ROUTINE

#include "shared/dependencies.h"
#include "routines/measure_analog.h"

void controlPowerV(uint16_t power);
void controlPowerW(uint16_t power);

void controlPowerV(uint16_t power)
{
    if ((clickCounter == 1) || constantHeating)
    {
        totalHeatingTime += SAMPLING_TIMER;
    }
    if (buttonTimer > (8 * SAMPLES_TO_SEC))
    {
        burnout = true;
        pwmOutput = 0;
        setLED(255, 0, 0);
        burnoutScreen();
        return;
    }
    if (constantHeating)
    {
        pwmOutput = power * 130;
        pwmOutput = constrain(pwmOutput, 0, 1000);
    }
    else
    {
        if ((clickCounter == 1) && (!burnout) && (buttonTimer > 10))
        {
            pwmOutput = power * 130;
            int powerCeiling = 100 + (buttonTimer * 10);
            powerCeiling = constrain(powerCeiling, 0, 1000);
            pwmOutput = constrain(pwmOutput, 0, powerCeiling);
        }
        else
        {
            pwmOutput = 0;
        }
    }
    powerPercent = pwmOutput / 10;
    ledcWrite(heater, pwmOutput);
}

void controlPowerW(uint16_t power)
{
    if ((clickCounter == 1) || constantHeating)
    {
        totalHeatingTime += SAMPLING_TIMER;
    }
    if (buttonTimer > (8 * SAMPLES_TO_SEC))
    {
        burnout = true;
        pwmOutput = 0;
        ledcWrite(heater, 0);
        setLED(255, 0, 0);
        burnoutScreen();
        return;
    }
    if (constantHeating)
    {
        if (powerOutput < (power))
            pwmOutput += 3;
        else if ((powerOutput - 1) > (power))
            pwmOutput--;
        pwmOutput = constrain(pwmOutput, 0, 1000);
    }
    else if ((clickCounter == 1) && (!burnout) && (buttonTimer > 10))
    {
        if (buttonTimer % 3 == 0)
        {
            if ((powerOutput + 0.5) < (power))
                pwmOutput += 5;
            if ((powerOutput - 1) > (power))
                pwmOutput -= 1;
        }
        pwmOutput = constrain(pwmOutput, 0, 1000);
    }
    else
    {
        pwmOutput = 0;
    }
    powerPercent = pwmOutput / 10;
    ledcWrite(heater, pwmOutput);
}

#endif