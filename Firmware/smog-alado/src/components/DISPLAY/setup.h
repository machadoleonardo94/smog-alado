#if !defined(SETUP_DISPLAY)
#define SETUP_DISPLAY

#include "shared/dependencies.h"

// ADICIONAR AQUI OS IMPORTS DOS ARQUIVOS DAS FEATURES.
 #include "components/DISPLAY/features/display.h"
 
int setup_display()
{
 if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    return 0;
  }
  display.clearDisplay();
  return 1;
}
#endif // SETUP_DISPLAY