#if !defined(RUN_PUSHBUTTON)
#define RUN_PUSHBUTTON

#include "shared/dependencies.h"

int buttonPress(int button)
{
  bool pumpState = false;
  int count = 0;
  int state = 0;
  while (!digitalRead(button))
  {
    count++;
    delay(1);
  }
  if (count < 10)
    return 0;
  if (count > 20)
    state = 1;
  if (count > 3000) // Adjusted for 3-second hold
    state = 2;

  if (sleepy && state >= 1) { // Wake up if sleeping and button is pressed
    sleepy = false;
    preset = 90;
    display.dim(false);
    WiFi.forceSleepWake();
    WiFi.begin();
    idleTimer = 0;
    return 1; 
  }

  if (state == 1) // Single click
  {
    if (pumpState == HIGH) {
      pumpState = LOW;
      digitalWrite(pumpPin, pumpState);
    } else {
      pumpState = HIGH;
      digitalWrite(pumpPin, pumpState);
    }
    Serial.printf("Pump toggled \n");
    idleTimer = 0;
  }
  if (state == 2) // 3-second hold
  {
    sleepRoutine();
  }
  delay(100);
  return 1;
}

#endif // RUN_PUSHBUTTON
