#if !defined(RUN_PUSHBUTTON)
#define RUN_PUSHBUTTON

#include "shared/dependencies.h"
//* Adicione o arquivo setup.h caso a feature atual faça uso de outras features do mesmo componente.
// #include "components/0-TEMPLATE/setup.h"

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
      WiFi.begin();
    }
    Serial.printf("Clict Clect \n");
    idleTimer = 0;
    if (preset == 0)
      tempGoal = 0;
    if (preset == 1)
      tempGoal = 100;
    if (preset == 2)
      tempGoal = 150;
    if ((preset > 2) & (preset < 10))
      tempGoal = 160 + (preset * 5);
  }
  if (state == 2)
  {
    sleepRoutine();
  }
  if (state == 3)
  {
    TelnetStream.println("Tuning PID Parameters");
    autoTunePID();
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
