#if !defined(TELNET_SETUP)
#define TELNET_SETUP

#include "shared/dependencies.h"

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

  sprintf(timeStr, "%02d-%02d-%02d %02d:%02d:%02d", year(), month(), day(), hour(), minute(), second());

  TelnetStream.print(i++);
  TelnetStream.print(" ");
  TelnetStream.println(timeStr);
  TelnetStream.println("Connected to WiFi. Hostname: " + WiFi.hostname());
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
  TelnetStream.print("KP: ");
  TelnetStream.println(myPID.GetKp());
  TelnetStream.print("KI: ");
  TelnetStream.println(myPID.GetKi());
  TelnetStream.print("KD: ");
  TelnetStream.println(myPID.GetKd());
  TelnetStream.println("");
  TelnetStream.println("");
}

#endif // TELNET_SETUP