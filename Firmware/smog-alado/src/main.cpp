#include <EEPROM.h>

//* ---------------------- IMPORTS ----------------------
//* Shared:
#include "shared/dependencies.h"
//* Utilities:
#include "utilities/OTA.h"
#include "utilities/WIFI.h"
#include "utilities/logger.h"
//* Components:
#include "components/ADS1115/setup.h"
#include "components/THERMISTOR/setup.h"
#include "components/HEATER/setup.h"
#include "components/PUSHBUTTON/setup.h"

int buttonPress(int button);

void setup()
{
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
  setup_WIFI();
  workingOTA = setup_OTA();

  analogWriteRange(ANALOG_RANGE);

  //enable light sleep
  //wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  //wifi_fpm_open();

  // register one or more wake-up interrupts
  //gpio_pin_wakeup_enable(buttonPin, GPIO_PIN_INTR_LOLEVEL);
}

void loop()
{
  if (workingOTA)
    ArduinoOTA.handle();

  click = buttonPress(buttonPin);
  if (click == 1)
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
    idleTimer = 0;
  }
  if (click == 2)
  {
    Serial.println("Going to sleep");
    preset = 0;
    tempGoal = 0;
    digitalWrite(heater, LOW);
    //wifi_set_sleep_type(LIGHT_SLEEP_T);
    delay(10);
    Serial.println("Yo, WAKE AND BAKE");
  }

  if (workingADS)
  {
    if (adcTimer > (SAMPLES_TO_SEC/5)) //reads ADC eveery 200ms
    {
      adcTimer = 0;
      thermistor = calculate_resistance();
      heaterTemperature = steinhart(thermistor);
      runHeater(preset);
    }
  }
  
  if (logTimer > SAMPLES_TO_SEC)  //logs variables every 1s
  {
    logTimer = 0;
    digitalWrite(ledPin, state);
    state = !(state);
    run_logger();
  }

  if (idleTimer > (5 * 60 * SAMPLES_TO_SEC))  //shutdown after 5 minutes 
  {
    Serial.println("Going to sleep");
    preset = 0;
    tempGoal = 0;
    digitalWrite(heater, LOW);
    //wifi_set_sleep_type(LIGHT_SLEEP_T);
    delay(10);
    Serial.println("Yo, WAKE AND BAKE");
  }

  if ((millis() - globalTimer) > SAMPLING_TIMER)
  {
    globalTimer = millis();
    idleTimer++;
    logTimer++;
    adcTimer++;
  }
}