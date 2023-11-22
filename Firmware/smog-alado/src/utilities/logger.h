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
    Serial.print(">Proportional part: ");
    Serial.println(proportional);
    Serial.print(">Integral part: ");
    Serial.println(integral);
    Serial.print(">Power output: ");
    Serial.println(power);
    //  Serial.print(">Filtered ADC: ");
    //  Serial.println(adcFiltered);
    Serial.println();
    Serial.println();
}

#endif // LOGGER