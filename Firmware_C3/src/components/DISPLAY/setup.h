#if !defined(SETUP_DISPLAY)
#define SETUP_DISPLAY

#include "shared/dependencies.h"

// ADICIONAR AQUI OS IMPORTS DOS ARQUIVOS DAS FEATURES.
#include "components/DISPLAY/features/display.h"
#include "components/DISPLAY/constants.h"

int setup_display()
{
  Serial.println("SSD1306 setup");
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println("SSD1306 allocation failed");
    return 0;
  }
  display.clearDisplay();
  drawXbm(logo_bits, _width, _height, 0, 0);
  Serial.println("SSD1306 setup correctly finished");
  delay(5000);
  return 1;
}
#endif // SETUP_DISPLAY