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
//* Async WiFi and WEB services
AsyncWebServer server(80);
DNSServer dns;
AsyncWiFiManager wifiManager(&server, &dns);

//* Heater variables
double thermistor = 500;
double heaterTemperature = 0;
double tempGoal = 0;
double error = 0;
double power = 0;
double powerPercent = 0;
int preset = 0;
uint16_t adcRaw = 1000;
uint16_t adcFiltered = 1000;

//*Old PID
/*
double integral = 0;
double proportional = 0;
double derivative = 0;
double prevError = 0;
*/

// PID control and Tune
double Kp = 7, Ki = 0.6, Kd = 180;
double aggKp = (Kp * 2), aggKi = (Ki * 2), aggKd = (Kd * 2);
double TKp, TKi, TKd;
boolean tuning = false;
bool autoTuneInProgress = true;
unsigned long autoTuneStartTime;
uint16_t maxAutoTuneDurationMinutes = 10;

PID myPID(&heaterTemperature, &power, &tempGoal, Kp, Ki, Kd, P_ON_M, DIRECT);
PID_ATune aTune(&heaterTemperature, &power);

//* Timers for ilusion of threads
double globalTimer = 0;
uint16_t adcTimer = 0;
uint16_t logTimer = 0;
uint16_t idleTimer = 0;
uint16_t idleMinutes = 0;
uint16_t idleSeconds = 0;
uint16_t remainingTime = 100;
uint16_t APtimeout = 180;
uint16_t minutes = 10;

//* Booleans to check if functions will be called
bool workingADS = false;
bool workingWIFI = false;
bool workingOTA = false;
bool workingDisplay = false;
bool timeZoneSet = false;
bool sleepy = false;

#endif // PROJECT_GLOBAL_VARIABLES
