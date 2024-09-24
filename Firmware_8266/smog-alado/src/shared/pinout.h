//? ------------------------------------------------------------------------------------------
//*! This file contains all the hardware pinout definitions for the project.
//? ------------------------------------------------------------------------------------------

#ifndef PROJECT_GLOBAL_PINOUT
#define PROJECT_GLOBAL_PINOUT

//* ---------------------- ESP32 Project Pinout ----------------------
//* ANALOG IN:
#define analogIn0 A0
//* DIGITAL OUT:
#define pumpPin 2
//* DIGITAL IN:
#define buttonPin 12
//* I2C PINS:
#define SDA 4
#define SCL 5
//AC zero-crossing detector and triac
#define zeroCrossingPin 16
#define triacPin 14

//* ---------------------- ADS1115 Channels Used ----------------------
#define thermistor_channel 0

#endif // PROJECT_GLOBAL_PINOUT
