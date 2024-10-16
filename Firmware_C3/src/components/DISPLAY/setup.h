#if !defined(SETUP_DISPLAY)
#define SETUP_DISPLAY

#include "shared/dependencies.h"

// ADICIONAR AQUI OS IMPORTS DOS ARQUIVOS DAS FEATURES.
#include "components/DISPLAY/features/display.h"
#include "components/DISPLAY/constants.h"

int setup_display()
{
  Serial.println("SSD1306 setup");
  Wire.end();
  Wire.setPins(4, 5);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println("SSD1306 allocation failed");
    return 0;
  }
  display.invertDisplay(false);
  display.setRotation(2);
  display.clearDisplay();
  drawXbm(logo_bits, _width, _height, 0, 0);
  display.display();
  Serial.println("SSD1306 setup correctly finished");
  return 1;
}
#endif // SETUP_DISPLAY