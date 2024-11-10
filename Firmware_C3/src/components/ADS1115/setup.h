#if !defined(SETUP_ADS1115)
#define SETUP_ADS1115

#include "shared/dependencies.h"
#include "components/ADS1115/features/read_voltage.h"

//* Initializes ADC module i2c communication.
int setup_ADS1115()
{
    Serial.println("[ADS1115] SETUP STARTED!");

    //* Begin i2c communication.
    if (!ads.begin())
    {
        Serial.println("Failed to initialize ADS.");
        return 0;
    }

    //* Set gain.
    // The ADC input range (or gain) can be changed via the following
    // functions, but be careful never to exceed VDD +0.3V max, or to
    // exceed the upper and lower limits if you adjust the input range!
    // Setting these values incorrectly may destroy your ADC!
    //                                                                ADS1015  ADS1115
    //                                                                -------  -------
    // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
    ads.setGain(GAIN_ONE); // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
    // ads.setGain(GAIN_TWO); // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV

    Serial.println("[ADS1115] SETUP FINISHED!");
    return 1;
}

#endif // SETUP_ADS1115
