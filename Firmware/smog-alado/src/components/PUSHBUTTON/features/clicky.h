#if !defined(RUN_PUSHBUTTON)
#define RUN_PUSHBUTTON

#include "shared/dependencies.h"

int buttonPress(int button)
{
  int state = 1;

  if (state == 1)
  {
    if (preset >= 10)
      preset = 0;
    if (sleepy == true)
    {
      sleepy = false;
      preset = 0;
      display.dim(false);
      WiFi.forceSleepWake();
      WiFi.begin();
    }
    Serial.printf("Clict Clect \n");
    idleTimer = 0;
    if (preset == 0)
      tempGoal = 90;
  }
  if (state == 2)
  {
    sleepRoutine();
  }
  if (state == 3)
  {
    TelnetStream.println("Tuning PID Parameters");
    changeAutoTune();  // Call the autoTunePID function for tuning logic
  }
  if (state == 4)
  {
    display.clearDisplay();
    display.display();
    ESP.restart();
  }
  delay(100);
  return 1;
}

#endif // RUN_PUSHBUTTON
