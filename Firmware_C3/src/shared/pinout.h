#ifndef PROJECT_GLOBAL_PINOUT
#define PROJECT_GLOBAL_PINOUT

//* Board version
// #define GnomeC3
#define GnomeC3V2

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
#define button2Pin 0
//* I2C PINS:
#define SDA 4
#define SCL 5

//* ---------------------- ADS1115 Channels Used ----------------------
#define TH0 0   // Thermistor 0
#define TH1 1   // Thermistor 1
#define Rsns 2  // Rsense
#define VBATT 3 // Vin

#endif // PROJECT_GLOBAL_PINOUT
