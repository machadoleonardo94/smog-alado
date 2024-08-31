#if !defined(SETUP_LEDS)
#define SETUP_LEDS

#include "shared/dependencies.h"
#include "components/LEDS/features/WS_functions.h"
#include "components/LEDS/features/turn_off.h"
#include "components/LEDS/features/turn_on.h"

void setup_LEDS()
{
    serialMon.println("[LEDS] SETUP STARTED!");

    ws2812b.begin();
    ws2812b.clear();
    ws2812b.setPixelColor(0, ws2812b.Color(50, 0, 0)); // it only takes effect if pixels.show() is called
    ws2812b.show();                                    // update to the WS2812B Led Strip
    delay(500);
    ws2812b.setPixelColor(0, ws2812b.Color(0, 50, 0)); // it only takes effect if pixels.show() is called
    ws2812b.show();                                    // update to the WS2812B Led Strip
    delay(500);
    ws2812b.setPixelColor(0, ws2812b.Color(0, 0, 50)); // it only takes effect if pixels.show() is called
    ws2812b.show();                                    // update to the WS2812B Led Strip
    delay(500);
    // ws2812b.setPixelColor(0, ws2812b.Color(0, 0, 0)); // it only takes effect if pixels.show() is called
    // ws2812b.show();

    serialMon.println("[LEDS] SETUP FINISHED!");
}

#endif // SETUP_LEDS
