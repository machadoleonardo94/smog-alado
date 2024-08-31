#if !defined(CONNECT_WIFI)
#define CONNECT_WIFI

#include "shared/dependencies.h"
#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "Silvia";
const char *password = "1011121314";

bool setup_WIFI()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    int dropCounter = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        dropCounter++;
        delay(500);
        if (dropCounter > 10)
            break;
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println(WiFi.localIP());
        Serial.println("Connected");
        return 1;
    }
    return 0;
}

#endif // CONNECT_WIFI
