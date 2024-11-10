#if !defined(READ_VOLTAGE_ADS1115)
#define READ_VOLTAGE_ADS1115

#include "components/ADS1115/setup.h"

//* Reads the voltage on an specified ADS1115 channel.
float read_voltage_ads1115(int channel)
{
    int16_t adc0, adc1, adc2, adc3;
    float volts0, volts1, volts2, volts3;

    adc0 = ads.readADC_SingleEnded(0);
    adc1 = ads.readADC_SingleEnded(1);
    adc2 = ads.readADC_SingleEnded(2);
    adc3 = ads.readADC_SingleEnded(3);

    volts0 = ads.computeVolts(adc0);
    // volts0 = map(volts0, 0, 65535, 0, 8192);

    volts1 = ads.computeVolts(adc1);
    // volts1 = map(volts1, 0, 65535, 0, 8192);

    volts2 = ads.computeVolts(adc2);
    // volts2 = map(volts2, 0, 65535, 0, 8192);

    volts3 = ads.computeVolts(adc3);
    // volts3 = map(volts3, 0, 65535, 0, 8192);

    //* Debugging prints.
    Serial.println("[ADS1115] Starting voltage readings...");
    Serial.println("[ADS1115] Channel 0 voltage: " + String(volts0, 3) + "V");
    Serial.println("[ADS1115] Channel 1 voltage: " + String(volts1, 3) + "V");
    Serial.println("[ADS1115] Channel 2 voltage: " + String(volts2, 3) + "V");
    Serial.println("[ADS1115] Channel 3 voltage: " + String(volts3, 3) + "V");

    //* Switch - case to return correct voltage reading.
    switch (channel)
    {
    case 0:
        return volts0;
        break;
    case 1:
        return volts1;
        break;
    case 2:
        return volts2;
        break;
    case 3:
        return volts3;
        break;

    default:
        return volts0;
        break;
    }
}

#endif // READ_VOLTAGE_ADS1115
