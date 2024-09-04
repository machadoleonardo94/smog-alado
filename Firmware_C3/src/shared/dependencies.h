//? ------------------------------------------------------------------------------------------
//*! This file contains all the common definitions and includes for the project.
//? ------------------------------------------------------------------------------------------

#ifndef PROJECT_GLOBAL_DEPENDENCIES
#define PROJECT_GLOBAL_DEPENDENCIES

//* ----------------------- Framework -------------------------
#include <Arduino.h>

//* ------------------------ Pinout ---------------------------
#include "pinout.h"

//* ---------------------- Interfaces -------------------------
#include "interfaces.h"

//* ---------------------- Libraries --------------------------
//* ADS1115 analog to digital converter and other dependencies:
#include <SPI.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_ADS1X15.h>
//* OLED I2C display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//* WiFi
#include <WiFi.h>
//* EEPROM
#include <EEPROM.h>
#include <LittleFS.h>
//* Over the Air update
#include <ArduinoOTA.h>
//* Fancy LED WS2812B
#include <Adafruit_NeoPixel.h>
//* RNG
#include "esp_random.h"

//* ----------------------- SHARED ----------------------------
//* Constants
#include "constants.h"
//* Interfaces
#include "interfaces.h"
//* Macros
#include "macros.h"
//* Pinout
#include "pinout.h"
//* Library Objects
#include "library_objects.h"
//* Variables
#include "variables.h"

//* --------------------- Components --------------------------
#include "components/DISPLAY/setup.h"
#include "components/ESP32/setup.h"
#include "components/LEDS/setup.h"

//* --------------------- Routines ------------------------
#include "routines/button_clicks.h"
#include "routines/measure_analog.h"
#include "routines/run_heater.h"
#include "routines/update_screen.h"

#endif // PROJECT_GLOBAL_DEPENDENCIES
