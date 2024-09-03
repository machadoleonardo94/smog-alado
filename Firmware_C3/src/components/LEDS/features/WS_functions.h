#if !defined(START_BREATHING_EFFECT_LEDS)
#define START_BREATHING_EFFECT_LEDS

#define azulNC 0x0, 0x0, 0x50
#define redLED 0xFF, 0x0, 0x0
#define greenLED 0x0, 0xFF, 0x0
#define blueLED 0x0, 0x0, 0xFF



void blinkLED(int R, int G, int B, int repeat = 3, int waitTime = 1000)
{
    for (int k = 0; k < repeat; k++)
    {
        ws2812b.clear();
        ws2812b.setPixelColor(0, ws2812b.Color(R, G, B)); // it only takes effect if pixels.show() is called
        ws2812b.show();                                   // update to the WS2812B Led Strip
        delay(waitTime);
        ws2812b.setPixelColor(0, ws2812b.Color(0, 0, 0)); // it only takes effect if pixels.show() is called
        ws2812b.show();                                   // update to the WS2812B Led Strip
        delay(waitTime);
    }
}

void setLED(int R, int G, int B)
{
    ws2812b.clear();
    ws2812b.setPixelColor(0, ws2812b.Color(R, G, B)); // it only takes effect if pixels.show() is called
                                                      //    ws2812b.setPixelColor(0, ws2812b.Color(R, G, B)); // it only takes effect if pixels.show() is called
    ws2812b.show();                                   // update to the WS2812B Led Strip
    // delay(waitTime);
    // ws2812b.setPixelColor(0, ws2812b.Color(0, 0, 0)); // it only takes effect if pixels.show() is called
    // ws2812b.show();                                   // update to the WS2812B Led Strip
}

void sampleRandomLED()
{
    uint8_t ledColor = esp_random() % 8;
    Serial.println(ledColor);
    bool red = ledColor & 1;
    bool green = ledColor & 2;
    bool blue = ledColor & 4;
    setLED(50 * red, 50 * green, 50 * blue);
}

#endif // START_BREATHING_EFFECT_LEDS
