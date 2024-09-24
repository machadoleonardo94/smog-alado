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
  delay(1000);
  Serial.begin(115200);
  Serial.println("setup");
  pinMode(pumpPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(A0, INPUT);

  pinMode(zeroCrossingPin, INPUT_PULLUP);
  pinMode(triacPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(zeroCrossingPin), zeroCrossingISR, RISING);

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

  analogWriteRange(ANALOG_RANGE);

  myPID.SetOutputLimits(0, ANALOG_RANGE);
  myPID.SetMode(AUTOMATIC);

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
  }

  if (!sleepy && (logTimer > SAMPLES_TO_SEC)) // logs variables every 1s if awake
  {
    logTimer = 0;
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