#ifndef BUTTON_ROUTINE
#define BUTTON_ROUTINE

#include "shared/dependencies.h"
#include "routines/update_screen.h"
#include "routines/run_heater.h"
#include "routines/measure_analog.h"
#include "services/wifi_settings.h"

void shutdownESP();
void buttonPress();

void buttonPress()
{
  if (digitalRead(button2Pin))
  {
    sampleRandomLED();
  }
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
      pwmOutput = 500;
      delay(50); // debounce
    }
    if ((clickCounter == 2) && (buttonTimer > SAMPLES_TO_SEC))
    {
      buttonTimer = 0;
      clickCounter = 0;
      constantHeating = true;
      heaterResistance = calculate_load();
      if ((heaterResistance < 20) && (heaterResistance > 0.2))
        pwmOutput = 500;
    }
    if ((clickCounter == 3) && (buttonTimer > (SAMPLES_TO_SEC / 2)))
    {
      buttonTimer = 0;
      powerLevel += 3;
      if (powerLevel > 45)
        powerLevel = 15;
    }
    if ((clickCounter == 4) && (buttonTimer > SAMPLES_TO_SEC))
    {
      clickCounter = 0;
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