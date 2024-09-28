//* ---------------------- IMPORTS ----------------------
//* Shared:
#include "shared/dependencies.h"

void shutdownESP();

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(latchPin, OUTPUT);
  digitalWrite(latchPin, HIGH);
  pinMode(heater, OUTPUT);
  ledcAttach(heater, 1000, 10);
  digitalWrite(heater, 0);

  Serial.begin(115200);
  Serial.println("setup");
  workingDisplay = setup_display();
  setup_LEDS();

  setLED(redLED);
  long wakeupTimer = millis();
  while (((millis() - wakeupTimer) < 2000) && clickCounter < 3)
  {
    buttonPress();
    delay(50);
  }
  if (clickCounter < 2)
  {
    shutdownESP();
  }
  setLED(greenLED);
  clickCounter = 0;

  setup_ESP32();
}

void loop()
{
  ArduinoOTA.handle();

  if ((millis() - globalTimer) > SAMPLING_TIMER)
  {
    buttonPress();
    thermistor = calculate_resistance();
    heaterTemperature = steinhart(thermistor);
    controlPower(powerLevel);
    globalTimer = millis();
    idleTimer++;
    logTimer++;
    adcTimer++;
    screenTimer++;
  }

  if ((logTimer > (SAMPLES_TO_SEC / 10))) // logs variables every 100ms if awake
  {
    logTimer = 0;
    battery = analogReadMilliVolts(1) * 8.2 / 4095;
  }

  if (screenTimer > SAMPLES_TO_SEC / 10)
  {
    screenTimer = 0;
    updateDisplay();
    sampleRandomLED();
  }

  if (idleTimer > (SAMPLES_TO_SEC / 2))
  {
    clickCounter = 0;
    // setLED(0, 0, 0);
    // digitalWrite(latchPin, LOW);
    // esp_deep_sleep_start();
  }

  if (clickCounter > 3)
    shutdownESP();
}

void shutdownESP()
{
  digitalWrite(latchPin, LOW);
  setLED(0, 0, 0);
  esp_deep_sleep_start();
}