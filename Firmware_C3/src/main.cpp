//* ---------------------- IMPORTS ----------------------
//* Shared:
#include "shared/dependencies.h"
//* Utilities:
//* Components:
#include "components/PUSHBUTTON/setup.h"
#include "components/DISPLAY/setup.h"

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

  if (digitalRead(buttonPin))
  {
    while (digitalRead(buttonPin))
      idleTimer = 0;
    // setLED(greenLED);
  }

  if ((logTimer > SAMPLES_TO_SEC)) // logs variables every 1s if awake
  {
    logTimer = 0;
    if (workingDisplay)
      updateDisplay();
    Serial.print(".");
    uint8_t ledColor = esp_random() % 8;
    Serial.println(ledColor);
    bool red = ledColor & 1;
    bool green = ledColor & 2;
    bool blue = ledColor & 4;
    setLED(50 * red, 50 * green, 50 * blue);
    if (!workingDisplay)
      workingDisplay = setup_display();
  }

  if ((millis() - globalTimer) > SAMPLING_TIMER)
  {
    globalTimer = millis();
    idleTimer++;
    logTimer++;
    adcTimer++;
  }

  if (idleTimer > (120 * SAMPLES_TO_SEC))
  {
    setLED(0, 0, 0);
    digitalWrite(latchPin, LOW);
    esp_deep_sleep_start();
  }
}