#if !defined(PROJECT_GLOBAL_VARIABLES)
#define PROJECT_GLOBAL_VARIABLES

#include "shared/dependencies.h"
#include "shared/constants.h"
#include "pinout.h"

#include "components/DISPLAY/constants.h"

//* ---------------------- GLOBAL VARIABLES ----------------------
//* 0.96" OLED I2C display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//* Heater variables
double thermistor = 500;
double heaterTemperature = 0;
double tempGoal = 0;
double error = 0;
uint8_t powerLevel = 1;
double powerOutput = 0;
double powerPercent = 0;
int preset = 0;
uint16_t adcRaw = 1000;
uint16_t adcFiltered = 1000;
bool constantHeating = false;

double battery = 0;

int clickCounter = 0;
uint16_t buttonTimer = 0;
uint16_t heatingTime = 0;
uint32_t totalHeatingTime = 0;
bool burnout = false;

// PID control and Tune
double Kp = 1, Ki = 1, Kd = 1;
bool tuning = false;

//* Timers for ilusion of threads
double globalTimer = 0;
uint16_t adcTimer = 0;
uint16_t logTimer = 0;
uint16_t idleTimer = 0;
uint16_t screenTimer = 0;
uint16_t idleMinutes = 0;
uint16_t idleSeconds = 0;
uint16_t constantheatingSecs = 0;
uint16_t remainingTime = 100;
uint16_t APtimeout = 180;
uint16_t minutes = 10;
char timeStr[20];

//* Booleans to check if functions will be called
bool workingADS = false;
bool workingWIFI = false;
bool workingOTA = false;
bool workingDisplay = false;
bool timeZoneSet = false;
bool sleepy = false;
bool buttonState = false;

#endif // PROJECT_GLOBAL_VARIABLES