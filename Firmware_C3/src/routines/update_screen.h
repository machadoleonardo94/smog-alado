#ifndef SCREEN_ROUTINE
#define SCREEN_ROUTINE

#include "shared/dependencies.h"
#include "components/DISPLAY/setup.h"
#include "components/DISPLAY/constants.h"

// #include "utilities/WIFI.h"

#define _width 128
#define _height 64

#define COLUMN1 97

void updateDisplay();
void burnoutScreen();
void connectWiFiScreen();

void updateDisplay()
{
  int runTime = globalTimer / 1000;
  idleMinutes = runTime / 60;
  idleSeconds = (runTime % 60);

  display.clearDisplay();
  display.setTextSize(1); // Set text size to 2 (you can adjust the size as needed)
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, LINE0); // Adjust vertical position
  display.print("PWM: ");
  display.print(powerPercent);
  display.print("%");
  display.setCursor(COLUMN1 - 6, LINE0); // Adjust vertical position
  if (heaterTemperature < 100)
    display.print(heaterTemperature, 1);
  else
    display.print(heaterTemperature, 0);
  display.print(char(248));
  display.print("C");

  display.setCursor(0, LINE1);
  display.print("Session: ");
  int sessionMin = totalHeatingTime / 60000;
  int sessionSec = (totalHeatingTime / 1000) % 60;
  display.print(sessionMin);
  display.print(":");
  if (sessionSec < 10)
    display.print("0");
  display.print(sessionSec);

  display.setCursor(COLUMN1, LINE1);
  display.print(battery, 2);
  display.print("V");

  display.setCursor(0, LINE2);
  display.print("Heating: ");
  int heatingSec = heatingTime * SAMPLING_TIMER;
  display.print(heatingSec / 1000);
  display.print(".");
  display.print((heatingSec % 1000) / 100);
  display.print("s");
  display.setCursor(COLUMN1, LINE2);
  display.print(current, 2);
  display.print("A");

  display.setCursor(0, LINE3); // Adjust vertical position
  display.print("Load: ");
  display.print(heaterResistance, 2);
  display.print("R");
  display.setCursor(COLUMN1, LINE3); // Adjust vertical position
  if (powerOutput < 10)
    display.print(powerOutput, 2);
  else
    display.print(powerOutput, 1);
  display.print("W");

  // Display the IP address
  display.setCursor(0, LINE4); // Adjust vertical position
  display.print("IP: ");
  display.print(WiFi.localIP());
  display.setCursor(105, LINE4);
  // display.print("(");
  display.print(powerLevel);
  display.print("W");
  // display.print(")");

  /*
  if (constantHeating)
  {
    display.setCursor(118, LINE4);
    display.print("*");
  }
  */
  display.setCursor(118, LINE4);

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