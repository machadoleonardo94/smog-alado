//? ------------------------------------------------------------------------------------------
//*! This file contains all macros used in the project.
//? ------------------------------------------------------------------------------------------

#ifndef PROJECT_GLOBAL_MACROS
#define PROJECT_GLOBAL_MACROS

//* Hardware pinout.
#include "pinout.h"

//* ---------------------- Macros ----------------------

//*  --- MUX MACROS ---
#define BLINKY                      \
    digitalWrite(ledPin, HIGH);     \
    delay(50);                      \
    digitalWrite(ledPin, LOW);      \
    delay(50);                      
#endif
