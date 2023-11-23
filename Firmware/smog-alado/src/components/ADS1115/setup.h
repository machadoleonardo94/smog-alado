#if !defined(SETUP_ADS1115)
#define SETUP_ADS1115

#include "shared/dependencies.h"
#include "components/ADS1115/features/read_voltage.h"

//* Initializes ADC module i2c communication.
void setup_ADS1115()
{
    serialMon.println("[ADS1115] SETUP STARTED!");

    //* Begin i2c communication.
    if (!ads.begin())
    {
        serialMon.println("Failed to initialize ADS.");
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
    // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
    // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
    // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
    // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

    //* Sets CD4067 to read an unused channel (CH15) in case fuckups blow up the least amount of circuit
    //* In case of adding an IO expander, use one GPIO to set an inhibitor pin so all inputs go high impedance
    BLINKY
    serialMon.println("[ADS1115] SETUP FINISHED!");
}

#endif // SETUP_ADS1115
