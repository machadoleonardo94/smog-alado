//? ------------------------------------------------------------------------------------------
//*! This file contains all the hardware pinout definitions for the project.
//? ------------------------------------------------------------------------------------------

#ifndef PROJECT_GLOBAL_PINOUT
#define PROJECT_GLOBAL_PINOUT

//* ---------------------- ESP32 Project Pinout ----------------------
//* ANALOG OUT:
//#define heater 14
//* ANALOG IN:
#define analogIn0 A0
//* DIGITAL OUT:
#define ledPin 2
//* DIGITAL IN:
#define buttonPin 12
//* I2C PINS:
#define SDA 4
#define SCL 5

#define zeroCrossingPin 2 // Pin connected to zero-crossing detector
#define triacPin 14        // Pin connected to optocoupler driving the triac

//* ---------------------- ADS1115 Channels Used ----------------------
#define thermistor_channel 0

#endif // PROJECT_GLOBAL_PINOUT
