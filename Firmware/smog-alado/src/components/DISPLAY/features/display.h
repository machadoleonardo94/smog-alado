#if !defined(FEATURE_QUALQUER)
#define FEATURE_QUALQUER

#include "shared/dependencies.h"
//* Adicione o arquivo setup.h caso a feature atual faça uso de outras features do mesmo componente.
// ADICIONAR AQUI OS IMPORTS DE LIBS NECESSÁRIOS.

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1); // Set text size to 2 (you can adjust the size as needed)
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Temperature: ");
  display.print(heaterTemperature);
  display.print((char)247);
  display.print("C");

  display.setCursor(0, 16); // Adjust vertical position
  display.print("Temp. Goal:  ");
  display.print(tempGoal);
  display.print((char)247);
  display.print("C");

  display.setCursor(0, 32); // Adjust vertical position
  display.print("PWM: ");
  display.print(powerPercent);
  display.print("%");

  // Display the IP address
  display.setCursor(0, 48); // Adjust vertical position
  display.print("IP: ");
  display.print(WiFi.localIP());

  display.display();
}

#endif // FEATURE_QUALQUER
