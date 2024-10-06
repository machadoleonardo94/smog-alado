#if !defined(CONNECT_WIFI)
#define CONNECT_WIFI

#include "shared/dependencies.h"
#include <WiFi.h>
#include <EEPROM.h>
#include <WiFiManager.h>

void saveCredentials(const char *ssid, const char *password)
{
    EEPROM.begin(512);
    for (int i = 0; i < 32; ++i)
    {
        EEPROM.write(EEPROM_WIFI_SSID_START + i, ssid[i]);
        EEPROM.write(EEPROM_WIFI_PASS_START + i, password[i]);
    }
    EEPROM.commit();
}

void loadCredentials(char *ssid, char *password)
{
    EEPROM.begin(512);
    for (int i = 0; i < 32; ++i)
    {
        ssid[i] = EEPROM.read(EEPROM_WIFI_SSID_START + i);
        password[i] = EEPROM.read(EEPROM_WIFI_PASS_START + i);
    }
    ssid[32] = '\0';
    password[32] = '\0';
}

bool setup_WIFI()
{

    WiFiManager wifiManager;
    wifiManager.setAPCallback([](WiFiManager *myWiFiManager)
                              {
        Serial.println("Entered config mode");
        Serial.println(WiFi.softAPIP());
        Serial.println(myWiFiManager->getConfigPortalSSID()); });

    wifiManager.setSaveConfigCallback([]()
                                      { Serial.println("Should save config"); });

    wifiManager.setConfigPortalTimeout(60); // Set timeout to 1 minute
    wifiManager.setHostname("Gnomo Alado");

    if (!wifiManager.autoConnect("Gnomo Alado"))
    {
        Serial.println("Failed to connect and hit timeout");
        return false;
    }

    Serial.println("Connected to WiFi");

    // Save credentials to EEPROM
    saveCredentials(WiFi.SSID().c_str(), WiFi.psk().c_str());

    return true;
}

/*
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
*/

#endif // CONNECT_WIFI
