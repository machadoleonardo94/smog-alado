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

//* ---------------------- Constants --------------------------
#include "constants.h"

//* ----------------------- Macros ----------------------------
#include "macros.h"

//* ---------------------- Variables --------------------------
#include "variables.h"

#endif
