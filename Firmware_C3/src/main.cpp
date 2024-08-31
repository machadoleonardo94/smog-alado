//* ---------------------- IMPORTS ----------------------
//* Shared:
#include "shared/dependencies.h"
//* Utilities:
//* Components:
#include "components/PUSHBUTTON/setup.h"
#include "components/DISPLAY/setup.h"

void setup()
{
  Serial.begin(115200);
  Serial.println("setup");
  pinMode(buttonPin, INPUT_PULLUP);
  setup_ESP32();
  workingDisplay = setup_display();
  setup_LEDS();
  digitalWrite(latchPin, HIGH);
}

void loop()
{
  ArduinoOTA.handle();

  if ((logTimer > SAMPLES_TO_SEC)) // logs variables every 1s if awake
  {
    logTimer = 0;
    if (workingDisplay)
      updateDisplay();
    Serial.print(".");
  }

  if ((millis() - globalTimer) > SAMPLING_TIMER)
  {
    globalTimer = millis();
    idleTimer++;
    logTimer++;
    adcTimer++;
  }
  if (millis() > 30000)
  {
    setLED(0, 0, 0);
    digitalWrite(latchPin, LOW);
    esp_deep_sleep_start();
  }
}
