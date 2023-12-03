#if !defined(TELNET_SETUP)
#define TELNET_SETUP

#include "shared/dependencies.h"

#define TIME_ZONE TZ_America_Sao_Paulo

int setup_TELNET(){
    int counter = 0;
    configTime(TIME_ZONE, "pool.ntp.org");
    time_t now = time(nullptr);
    while (now < SECS_YR_2000) {
        delay(100);
        now = time(nullptr);
        counter++;
        if (counter > 20){
            Serial.println("Timezone timeout");
            return 0;
        }
    }
  setTime(now);
  TelnetStream.begin();
  return 1;
}

void TelnetPrint() {
  static int i = 0;

  char timeStr[20];
  sprintf(timeStr, "%02d-%02d-%02d %02d:%02d:%02d", year(), month(), day(), hour(), minute(), second());

  TelnetStream.print(i++);
  TelnetStream.print(" ");
  TelnetStream.println(timeStr);
  TelnetStream.println("----------Device variables----------");
  TelnetStream.print("Idle timer: ");
  TelnetStream.println(idleTimer);
  TelnetStream.print("Temperature reading: ");
  TelnetStream.println(heaterTemperature);
  TelnetStream.printf("Temperature Goal: ");
  TelnetStream.println(tempGoal);
  TelnetStream.print("Thermistor resistance: ");
  TelnetStream.println(thermistor);
  TelnetStream.print("Power output: ");
  TelnetStream.println(powerPercent);
  TelnetStream.print("Proportional part: ");
  TelnetStream.println(proportional);
  TelnetStream.print("Integral part: ");
  TelnetStream.println(integral);
  TelnetStream.print("Derivative part: ");
  TelnetStream.println(derivative);
  TelnetStream.println("");
  TelnetStream.println("");
}

#endif