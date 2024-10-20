#ifndef BUTTON_ROUTINE
#define BUTTON_ROUTINE

#include "shared/dependencies.h"
#include "routines/update_screen.h"
#include "routines/run_heater.h"
#include "services/wifi_settings.h"

void shutdownESP();
void buttonPress();

void buttonPress()
{
  if (digitalRead(buttonPin))
  {
    idleTimer = 0;
    if (clickCounter > 0)
      buttonTimer++;

    heatingTime = buttonTimer;
    if (buttonState == false)
    {
      clickCounter++;
      buttonState = true;
      constantHeating = false;
      delay(50); // debounce
    }
    if ((clickCounter == 2) && (buttonTimer > (SAMPLES_TO_SEC / 2)))
    {
      buttonTimer = 0;
      powerLevel++;
      if (powerLevel > 7)
        powerLevel = 1;
    }
    if ((clickCounter == 3) && (buttonTimer > SAMPLES_TO_SEC))
    {
      buttonTimer = 0;
      constantHeating = true;
    }
    if ((clickCounter == 4) && (buttonTimer > SAMPLES_TO_SEC))
    {
      connectWiFiScreen();
      setup_WIFI();
      setup_OTA();
    }
  }
  else
  {
    // if (buttonState)
    //{
    //   totalHeatingTime += (buttonTimer * SAMPLING_TIMER);
    // }
    buttonState = false;
    burnout = false;
    buttonTimer = 0;
  }
}

#endif