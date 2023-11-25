//* ---------------------- IMPORTS ----------------------
//* Shared:
#include "shared/dependencies.h"
//* Utilities:
#include "utilities/OTA.h"
#include "utilities/WIFI.h"
#include "utilities/logger.h"
#include "utilities/nuke_eeprom.h"
#include "utilities/lightsleep.h"
#include "utilities/telnet.h"
//* Components:
#include "components/ADS1115/setup.h"
#include "components/THERMISTOR/setup.h"
#include "components/HEATER/setup.h"
#include "components/PUSHBUTTON/setup.h"
#include "components/DISPLAY/setup.h"

int buttonPress(int button);

void setup()
{
  BLINKY
  delay(1000);
  Serial.begin(115200);
  Serial.println("setup");
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(heater, OUTPUT);
  pinMode(A0, INPUT);
  digitalWrite(ledPin, LOW); // builtin LED set to ON on boot
  digitalWrite(heater, LOW); // heater set to OFF on boot

  workingADS = setup_ADS1115();
  workingDisplay = setup_display();
  setup_WIFI();
  setup_OTA();
  timeZoneSet = setup_TELNET();
  // TODO: implement a routine to periodicaly check if timezone is set, otherwise telnete won't work
  
  analogWriteRange(ANALOG_RANGE);
}

void loop()
{
  ArduinoOTA.handle();

  buttonPress(buttonPin);

  if ((workingADS) && (adcTimer > (SAMPLES_TO_SEC/5))) //reads ADC every 200ms
  {
    adcTimer = 0;
    thermistor = calculate_resistance();
    heaterTemperature = steinhart(thermistor);
    runHeater(preset);
  }
  
  if (!sleepy && (logTimer > SAMPLES_TO_SEC))  //logs variables every 1s if awake
  {
    logTimer = 0;
    digitalWrite(ledPin, !digitalRead(ledPin));
    run_logger();
    TelnetPrint();
    if (workingDisplay)
      updateDisplay();
  }

  if (idleTimer > (10 * 60 * SAMPLES_TO_SEC))  //shutdown after 10 minutes 
  {
    sleepRoutine();
  }

  if ((millis() - globalTimer) > SAMPLING_TIMER)
  {
    globalTimer = millis();
    idleTimer++;
    logTimer++;
    adcTimer++;
  }
}