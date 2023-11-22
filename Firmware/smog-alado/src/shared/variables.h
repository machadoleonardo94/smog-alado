#if !defined(PROJECT_GLOBAL_VARIABLES)
#define PROJECT_GLOBAL_VARIABLES

#include "shared/dependencies.h"
#include "pinout.h"

//* ---------------------- GLOBAL VARIABLES ----------------------
//* ADS1115 - Analog to digital converter global instance.
Adafruit_ADS1115 ads; /* Use this for the 16-bit version */
// Adafruit_ADS1015 ads; /* Use this for the 12-bit version */

double thermistor = 500;
double heaterTemperature = 0;
double tempGoal = 0;
double error = 0;
double integral = 0;
double proportional = 0;
int power = 0;
int preset = 0;
bool debouncedButton = false;
bool state = false;
uint16_t adcRaw = 1000;
uint16_t adcFiltered = 1000;

double globalTimer = 0;
double adcTimer = 0;
double logTimer = 0;
double idleTimer = 0;

bool workingADS = false;

#endif // PROJECT_GLOBAL_VARIABLES
