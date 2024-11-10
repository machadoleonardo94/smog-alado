//* ---------------------- IMPORTS ----------------------
//* Shared:
#include "shared/dependencies.h"

//************************************************************************************************
//  All the code in this project was writen under the GoHorse method: it just works, until it does not.
//
//

void shutdownESP();

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup begin...");
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(heater, OUTPUT);

  ledcAttach(heater, 20000, 10);
  digitalWrite(heater, 0);

  pinMode(latchPin, OUTPUT);
  if (!digitalRead(buttonPin))
    shutdownESP();
  digitalWrite(latchPin, HIGH);
  setLED(redLED);
  long wakeupTimer = millis();
  while (((millis() - wakeupTimer) < 2000) && clickCounter < 3)
  {
    buttonPress();
    delay(50);
  }
  if (clickCounter < 2)
    shutdownESP();

  workingDisplay = setup_display();
  setup_LEDS();
  workingADS = setup_ADS1115();
  setLED(greenLED);
  clickCounter = 0;

  setup_ESP32();
  battery = calculate_battery();
  if (workingADS)
    heaterResistance = calculate_load();
}

void loop()
{
  ArduinoOTA.handle();

  if ((millis() - globalTimer) > SAMPLING_TIMER)
  {
    buttonPress();
    controlPowerW(powerLevel);
    globalTimer = millis();
    idleTimer++;
    logTimer++;
    adcTimer++;
    screenTimer++;
  }

  if ((logTimer > (SAMPLES_TO_SEC / 2))) // logs variables every 500ms if awake
  {
    logTimer = 0;
    battery = calculate_battery();
    current = calculate_current();
    loadVoltage = powerPercent * battery / 100;
    powerOutput = loadVoltage * current;
    // thermistor = calculate_resistance(TH0, 2200);
    thermistor = calculate_resistance(TH1, 33000);
    heaterTemperature = steinhart(thermistor);
  }

  if (screenTimer > SAMPLES_TO_SEC / 10)
  {
    screenTimer = 0;
    updateDisplay();
    if ((buttonState) && (!constantHeating))
      sampleRandomLED();
    else if (constantHeating)
      setLED(255, 50, 100);
    else
      setLED(0, 50, 0);
  }

  if (idleTimer > (SAMPLES_TO_SEC / 2))
  {
    clickCounter = 0;
    // setLED(0, 0, 0);
    // digitalWrite(latchPin, LOW);
    // esp_deep_sleep_start();
  }

  if ((clickCounter > 5) || (idleTimer > (5 * SAMPLES_TO_MIN)))
    shutdownESP();
}

void shutdownESP()
{
  setLED(0, 0, 0);
  display.clearDisplay();
  digitalWrite(latchPin, LOW);
  delay(200);
  esp_deep_sleep_start();
}