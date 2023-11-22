#include <EEPROM.h>

//* ---------------------- IMPORTS ----------------------
//* Shared:
#include "shared/dependencies.h"
//* Utilities:
#include "utilities/esp_sleep_timer.h"
#include "utilities/OTA.h"
#include "utilities/WIFI.h"
#include "utilities/logger.h"
//* Components:
#include "components/ADS1115/setup.h"
#include "components/THERMISTOR/setup.h"
#include "components/HEATER/setup.h"

int buttonPress(int button);

void setup()
{
  Serial.begin(115200);
  Serial.println("setup");
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(heater, OUTPUT);
  pinMode(A0, INPUT);
  digitalWrite(ledPin, LOW); // builtin LED set to ON on boot
  digitalWrite(heater, LOW); // heater set to OFF on boot

  workingADS = setup_ADS1115();
  setup_WIFI();
  setup_OTA();

  analogWriteRange(ANALOG_RANGE);
}

void loop()
{
  ArduinoOTA.handle();
  if (workingADS)
  {
    if ((millis() - adcTimer) > 200)
    {
      adcTimer = millis();
      thermistor = calculate_resistance();
      heaterTemperature = steinhart(thermistor);
      runHeater(preset);
    }
  }
  if (buttonPress(buttonPin))
  {
    preset++;
    if (preset == 0)
      tempGoal = 0;
    if ((preset > 0) & (preset < 12))
      tempGoal = 190 + (preset * 5);
    if (preset >= 12)
      preset = 0;
    Serial.printf("Clict Clect \n");
    delay(100);
  }
  if ((millis() - loopTimer) > 500)
  {
    loopTimer = millis();
    // if (preset == 0)
    digitalWrite(ledPin, state);
    // else
    //   analogWrite(ledPin, preset*90);
    state = !(state);
    run_logger();
  }
}

int buttonPress(int button)
{
  int count = 0;
  while (!digitalRead(button))
  {
    count++;
    delay(2);
  }
  if (count > 10)
    return 1;
  else
    return 0;
}