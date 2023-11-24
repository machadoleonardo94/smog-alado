#if !defined(PROJECT_GLOBAL_VARIABLES)
#define PROJECT_GLOBAL_VARIABLES

#include "shared/dependencies.h"
#include "shared/constants.h"
#include "pinout.h"

//* ---------------------- GLOBAL VARIABLES ----------------------
//* ADS1115 - Analog to digital converter global instance.
Adafruit_ADS1115 ads; /* Use this for the 16-bit version */
//* 0.96" OLED I2C display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//* Heater variables
double thermistor = 500;
double heaterTemperature = 0;
double tempGoal = 0;
double error = 0;
double integral = 0;
double proportional = 0;
double derivative = 0;
int power = 0;
double powerPercent = 0;
int preset = 0;
uint16_t adcRaw = 1000;
uint16_t adcFiltered = 1000;

//* Timers for ilusion of threads
double globalTimer = 0;
double adcTimer = 0;
double logTimer = 0;
double idleTimer = 0;

//* Booleans to check if functions will be called 
bool workingADS = false;
bool workingWIFI = false;
bool workingOTA = false;
bool workingDisplay = false;
bool timeZoneSet = false;
bool sleepy = false;

#endif // PROJECT_GLOBAL_VARIABLES
