//? ------------------------------------------------------------------------------------------
//*! This file contains all the hardware pinout definitions for the project.
//? ------------------------------------------------------------------------------------------

#ifndef PROJECT_GLOBAL_PINOUT
#define PROJECT_GLOBAL_PINOUT

//* ---------------------- ESP32 Project Pinout ----------------------
//* ANALOG OUT:
#define heater 6
//* ANALOG IN:
#define analogIn0 A0
//* DIGITAL OUT:
#define LED_output 10
#define latchPin 3
//* DIGITAL IN:
#define buttonPin 7
//* I2C PINS:
#define SDA 4
#define SCL 5

//* ---------------------- ADS1115 Channels Used ----------------------
#define thermistor_channel 0

#endif // PROJECT_GLOBAL_PINOUT
