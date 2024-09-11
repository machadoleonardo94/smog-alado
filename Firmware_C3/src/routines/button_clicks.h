#include "shared/dependencies.h"
// #include "routines/update_screen.h"

void shutdownESP();
void buttonPress();

void buttonPress()
{
  if (digitalRead(buttonPin))
  {
    burnoutCounter++;
    idleTimer = 0;
    if (buttonState == false)
    {
      clickCounter++;
      buttonState = true;
    }
  }
  else
  {
    burnoutCounter = 0;
    if (buttonState)
      delay(50); // debounce
    buttonState = false;
  }
}