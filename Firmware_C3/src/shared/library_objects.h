#if !defined(PROJECT_GLOBAL_OBJECTS)
#define PROJECT_GLOBAL_OBJECTS

#include "shared/dependencies.h"
#include "pinout.h"

//* ---------------------- GLOBAL OBJECT INSTANCES ----------------------

//* Fancy LED WS2812B
Adafruit_NeoPixel ws2812b(1, LED_output, NEO_GRB + NEO_KHZ800);

#endif // PROJECT_GLOBAL_OBJECTS