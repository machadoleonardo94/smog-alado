#if !defined(LOGGER)
#define LOGGER

#include "shared/dependencies.h"

void run_logger()
{
    Serial.println("---------DEBUG VARIABLES---------");
    Serial.print(">Thermistor resistence: ");
    Serial.println(thermistor);
    Serial.print(">Temperature reading: ");
    Serial.println(heaterTemperature);
    Serial.print(">Temperature Goal: ");
    Serial.println(tempGoal);
    Serial.print(">Power output: ");
    Serial.println(power);
    Serial.print("ADS status: ");
    Serial.println(workingADS);
    Serial.print("Display status: ");
    Serial.println(workingDisplay);
    Serial.println();
    Serial.println();
}

#endif // LOGGER