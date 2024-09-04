//* ---------------------- IMPORTS ----------------------
//* Shared:
#include "shared/dependencies.h"

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(latchPin, HIGH);
  Serial.begin(115200);
  Serial.println("setup");
  setup_LEDS();
  setup_ESP32();
  workingDisplay = setup_display();
}

void loop()
{
  ArduinoOTA.handle();

  buttonPress();

  if ((logTimer > SAMPLES_TO_SEC)) // logs variables every 1s if awake
  {
    logTimer = 0;
    battery = analogReadMilliVolts(1) * 8.2 / 4095;
    updateDisplay();
    sampleRandomLED();
  }

  if ((millis() - globalTimer) > SAMPLING_TIMER)
  {
    thermistor = calculate_resistance();
    heaterTemperature = steinhart(thermistor);
    globalTimer = millis();
    idleTimer++;
    logTimer++;
    adcTimer++;
  }

  if (idleTimer > (240 * SAMPLES_TO_SEC))
  {
    // setLED(0, 0, 0);
    // digitalWrite(latchPin, LOW);
    // esp_deep_sleep_start();
  }
}