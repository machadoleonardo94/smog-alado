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
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_ADS1X15.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <TelnetStream.h>
#include <TimeLib.h>
#include <sntp.h>
#include <TZ.h>
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>

//* ---------------------- Constants --------------------------
#include "constants.h"

//* ----------------------- Macros ----------------------------
#include "macros.h"

//* ---------------------- Variables --------------------------
#include "variables.h"

#endif
