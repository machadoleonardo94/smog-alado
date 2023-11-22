#if !defined(WIFI_SETUP)
#define WIFI_SETUP

#include "shared/dependencies.h"

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

char customWifiSSID[32];
char customWifiPass[32];

void configModeCallback(WiFiManager *myWiFiManager)
{
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup_WIFI()
{
  // Set up WiFiManager
  WiFiManager wifiManager;
  wifiManager.setTimeout(30);
  wifiManager.setAPCallback(configModeCallback);

  // Try to load WiFi credentials from EEPROM
  EEPROM.begin(512); // Initialize EEPROM with 512 bytes
  EEPROM.get(EEPROM_WIFI_SSID_START, customWifiSSID);
  EEPROM.get(EEPROM_WIFI_PASS_START, customWifiPass);

  // Set the custom parameters for WiFiManager
  WiFiManagerParameter customSSID("SSID", "WiFi SSID", customWifiSSID, 32);
  WiFiManagerParameter customPass("password", "WiFi Password", customWifiPass, 32);

  wifiManager.addParameter(&customSSID);
  wifiManager.addParameter(&customPass);

  // Try to connect to WiFi, or start a configuration portal if connection fails
  if (!wifiManager.autoConnect("AutoConnectAP"))
  {
    Serial.println("Failed to connect and hit timeout");
    delay(3000);
    // Reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }

  // Save WiFi credentials to EEPROM
  strncpy(customWifiSSID, customSSID.getValue(), 32);
  strncpy(customWifiPass, customPass.getValue(), 32);
  EEPROM.put(EEPROM_WIFI_SSID_START, customWifiSSID);
  EEPROM.put(EEPROM_WIFI_PASS_START, customWifiPass);
  EEPROM.commit();

  // If you get here, you have connected to the WiFi
  Serial.println("Connected to WiFi");
}

#endif // ESP_WIFI
