
#include "shared/dependencies.h"
#include "components/DISPLAY/setup.h"
#include "components/DISPLAY/constants.h"

// #include "utilities/WIFI.h"

#define _width 128
#define _height 64

void updateDisplay();

void updateDisplay()
{
  // int remainingTime = (TIME_TO_SLEEP - idleTimer) / SAMPLING_TIMER;
  // idleMinutes = remainingTime / 600;
  // idleSeconds = (remainingTime % 600) / 10;

  int runTime = globalTimer / 1000;
  idleMinutes = runTime / 60;
  idleSeconds = (runTime % 60);

  display.clearDisplay();
  display.setTextSize(1); // Set text size to 2 (you can adjust the size as needed)
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, LINE0);
  display.print(idleMinutes);
  display.print(":");
  if (idleSeconds < 10)
    display.print("0");
  display.print(idleSeconds);

  display.setCursor(0, LINE1); // Adjust vertical position
  display.print("PWM: ");
  display.print(powerPercent);
  display.print("%");
  display.setCursor(92, LINE1);
  display.print(battery);
  display.print("V");

  // Display the IP address
  display.setCursor(0, LINE3); // Adjust vertical position
  display.print("IP: ");
  display.print(WiFi.localIP());

  display.display();
}

void burnoutScreen()
{
  display.clearDisplay();
  drawXbm(logo_bits, _width, _height, 0, 0);
  delay(3000);
}

void updateDisplayTemps()
{
  display.clearDisplay();
  display.setTextSize(1); // Set text size to 2 (you can adjust the size as needed)
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, LINE0);
  display.print("Temperature: ");
  if (heaterTemperature < 100)
    display.print(" ");
  display.print(heaterTemperature);
  display.print((char)247);
  display.print("C");

  display.setCursor(0, LINE1); // Adjust vertical position
  display.print("Temp. Goal:  ");

  if (tempGoal < 100)
    display.print(" 0");
  display.print(tempGoal);
  display.print((char)247);
  display.print("C");
  display.display();
}