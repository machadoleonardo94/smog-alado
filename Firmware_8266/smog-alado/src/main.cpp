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
#include "utilities/PID.h"
#include "utilities/webserver.h"
//* Components:
#include "components/ADS1115/setup.h"
#include "components/THERMISTOR/setup.h"
#include "components/HEATER/setup.h"
#include "components/PUSHBUTTON/setup.h"
#include "components/DISPLAY/setup.h"

void setup()
{
  BLINKY
  delay(1000);
  Serial.begin(115200);
  Serial.println("setup");
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  //pinMode(heater, OUTPUT);
  pinMode(A0, INPUT);

  pinMode(zeroCrossingPin, INPUT_PULLUP);
  pinMode(triacPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(zeroCrossingPin), zeroCrossingISR, RISING);

  digitalWrite(ledPin, LOW); // builtin LED set to ON on boot
  //digitalWrite(heater, LOW); // heater set to OFF on boot
  WiFi.mode(WIFI_OFF);

  workingDisplay = setup_display();
  workingADS = setup_ADS1115();
  analogWriteRange(ANALOG_RANGE);
  LittleFS.begin();
  // LittleFS.format();
  setup_WIFI();
  setup_OTA();
  setupPID();
  setupWebServer();

  workingADS = setup_ADS1115();
  timeZoneSet = setup_TELNET();
  // TODO: implement a routine to periodicaly check if timezone is set, otherwise telnet won't work
  analogWriteRange(ANALOG_RANGE);

  myPID.SetOutputLimits(0, ANALOG_RANGE);
  myPID.SetMode(AUTOMATIC);
  // changeAutoTune();  // Initiate auto-tuning at startup

  os_update_cpu_frequency(10);
}

void loop()
{
  ArduinoOTA.handle();

  myPID.Compute();
  runHeater(preset);

  buttonPress(buttonPin);

  if (adcTimer > (SAMPLES_TO_SEC / 5)) // reads ADC every 200ms
  {
    adcTimer = 0;
    thermistor = calculate_resistance();
    heaterTemperature = steinhart(thermistor);
    //runHeater(preset);
  }

  if (!sleepy && (logTimer > SAMPLES_TO_SEC)) // logs variables every 1s if awake
  {
    logTimer = 0;
    digitalWrite(ledPin, !digitalRead(ledPin));
    run_logger();
    TelnetPrint();
    if (workingDisplay)
      updateDisplay();
  }

  if (idleTimer > (TIME_TO_SLEEP)) // sleep after 10 minutes
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