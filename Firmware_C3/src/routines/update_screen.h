#ifndef SCREEN_ROUTINE
#define SCREEN_ROUTINE

#include "shared/dependencies.h"
#include "components/DISPLAY/setup.h"
#include "components/DISPLAY/constants.h"

// #include "utilities/WIFI.h"

#define _width 128
#define _height 64

void updateDisplay();
void burnoutScreen();
void connectWiFiScreen();

void updateDisplay()
{
  // int remainingTime = (TIME_TO_SLEEP - idleTimer) / SAMPLING_TIMER;
  // idleMinutes = remainingTime / 600;
  // idleSeconds = (remainingTime % 600) / 10;

  int runTime = globalTimer / 1000;
  idleMinutes = runTime / 60;
  idleSeconds = (runTime % 60);

  // while (inPowerMenu)
  //{
  //   cyclePowerOption();
  // }

  display.clearDisplay();
  display.setTextSize(1); // Set text size to 2 (you can adjust the size as needed)
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, LINE0);
  display.print("Session: ");
  int sessionMin = totalHeatingTime / 60000;
  int sessionSec = (totalHeatingTime / 1000) % 60;
  display.print(sessionMin);
  display.print(":");
  if (sessionSec < 10)
    display.print("0");
  display.print(sessionSec);
  /*
  display.print(idleMinutes);
  display.print(":");
  if (idleSeconds < 10)
    display.print("0");
  display.print(idleSeconds);
  */
  display.setCursor(110, LINE0);
  display.print(powerLevel);

  display.setCursor(0, LINE1); // Adjust vertical position
  display.print("PWM: ");
  display.print(powerPercent);
  display.print("%");
  display.setCursor(92, LINE1);
  display.print(battery);
  display.print("V");

  display.setCursor(0, LINE2);
  display.print("Heating: ");
  int heatingSec = heatingTime * SAMPLING_TIMER;
  display.print(heatingSec / 1000);
  display.print(".");
  display.print((heatingSec % 1000) / 100);
  display.print("s");

  // Display the IP address
  display.setCursor(0, LINE3); // Adjust vertical position
  display.print("IP: ");
  display.print(WiFi.localIP());

  display.display();
}

void burnoutScreen()
{
  display.clearDisplay();
  drawXbm(overtime, _width, _height, 0, 0);
  delay(3000);
}

void connectWiFiScreen()
{
  display.clearDisplay();
  display.setTextSize(1); // Set text size to 2 (you can adjust the size as needed)
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, LINE1);
  display.print("    WiFi setup  ");
  display.setCursor(0, LINE2);
  display.print("  Draw pretty screen  ");
  display.display();
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

#endif