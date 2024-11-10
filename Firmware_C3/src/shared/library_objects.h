#if !defined(PROJECT_GLOBAL_OBJECTS)
#define PROJECT_GLOBAL_OBJECTS

#include "shared/dependencies.h"
#include "pinout.h"

//* ---------------------- GLOBAL OBJECT INSTANCES ----------------------

//* Fancy LED WS2812B
Adafruit_NeoPixel ws2812b(1, LED_output, NEO_GRB + NEO_KHZ800);

//* ADS1115 - Analog to digital converter global instance.
Adafruit_ADS1115 ads; /* Use this for the 16-bit version */

#endif // PROJECT_GLOBAL_OBJECTS