#if !defined(SLEEPER)
#define SLEEPER

#include "shared/dependencies.h"

void setupSleep(){
  //enable light sleep
  //wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  //wifi_fpm_open();

  //register one or more wake-up interrupts
  gpio_pin_wakeup_enable(buttonPin, GPIO_PIN_INTR_LOLEVEL);
}

void sleepRoutine()
{
    //* Sets outputs as low to save power
    Serial.println("Going to sleep");
    preset = 0;
    tempGoal = 0;
    digitalWrite(heater, LOW);
    idleTimer = 0;
    display.clearDisplay();
    display.display();
    display.dim(true);
    sleepy = true;
    Serial.println("Turning WiFi Off");
    WiFi.mode(WIFI_OFF);
    delay(50);
    Serial.println("Yo, WAKE AND BAKE");
}

#endif