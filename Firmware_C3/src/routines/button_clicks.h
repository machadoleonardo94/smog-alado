#include "shared/dependencies.h"

void buttonPress()
{
  if (digitalRead(buttonPin))
  {
    int shutdownCounter = 0;
    while (digitalRead(buttonPin))
    {
      sampleRandomLED();
      shutdownCounter++;
      if (shutdownCounter > 100)
      {
        digitalWrite(latchPin, LOW);
        setLED(0, 0, 0);
        esp_deep_sleep_start();
      }
      delay(25);
    }
    idleTimer = 0;
  }
}

int buttonPress(int button)
{
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
  if (count > 800)
    state = 2;
  if (count > 5000)
    state = 3;
  if (count > 10000)
    state = 4;

  if (state == 1)
  {
    preset++;
    if (preset >= 10)
      preset = 0;
    if (sleepy == true)
    {
      sleepy = false;
      preset = 0;
      display.dim(false);
      // WiFi.forceSleepWake();
      // WiFi.begin();
    }
    Serial.printf("Clict Clect \n");
    idleTimer = 0;
    if (preset == 0)
      tempGoal = 0;
    if (preset == 1)
      tempGoal = 100;
    if (preset == 2)
      tempGoal = 120;
    if ((preset > 2) & (preset < 10))
      tempGoal = 110 + (preset * 5);
  }
  if (state == 2)
  {
    // sleepRoutine();
  }
  if (state == 3)
  {
    // TelnetStream.println("Tuning PID Parameters");
    // changeAutoTune();  // Call the autoTunePID function for tuning logic
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