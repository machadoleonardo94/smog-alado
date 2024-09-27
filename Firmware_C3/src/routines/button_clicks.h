#ifndef BUTTON_ROUTINE
#define BUTTON_ROUTINE

#include "shared/dependencies.h"
#include "routines/update_screen.h"
#include "routines/run_heater.h"

void shutdownESP();
void buttonPress();

void buttonPress()
{
  if (digitalRead(buttonPin))
  {
    idleTimer = 0;
    if (clickCounter == 1)
      buttonTimer++;

    heatingTime = buttonTimer;
    if (buttonState == false)
    {
      buttonState = true;
      clickCounter++;
      if (clickCounter == 2)
        powerLevel++;
      if (powerLevel > 5)
        powerLevel = 1;
    }
    if (buttonTimer > (8 * SAMPLES_TO_SEC))
    {
      burnout = true;
      controlPower(0);
      setLED(255, 0, 0);
      burnoutScreen();
    }
  }
  else
  {
    if (buttonState)
    {
      delay(50); // debounce
      totalHeatingTime += (buttonTimer * SAMPLING_TIMER);
    }
    buttonState = false;
    burnout = false;
    buttonTimer = 0;
  }
}

#endif