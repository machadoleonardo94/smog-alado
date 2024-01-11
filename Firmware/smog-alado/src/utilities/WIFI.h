#if !defined(WIFI_SETUP)
#define WIFI_SETUP

#include "shared/dependencies.h"
#include "components/DISPLAY/setup.h"

char customWifiSSID[32];
char customWifiPass[32];

void configModeCallback(AsyncWiFiManager *myWiFiManager)
{
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup_WIFI()
{
  WiFi.hostname("smog-alado");
  // Set up ESPAsyncWiFiManager
  AsyncWiFiManager wifiManager(&server, &dns);
  wifiManager.setConfigPortalTimeout(APtimeout);
  wifiManager.setConnectTimeout(30);

  // Custom parameters for Wi-Fi SSID and password
  AsyncWiFiManagerParameter customSSID("SSID", "WiFi SSID", customWifiSSID, 32);
  AsyncWiFiManagerParameter customPass("password", "WiFi Password", customWifiPass, 32);
  
  // Add custom parameters to WiFiManager
  wifiManager.addParameter(&customSSID);
  wifiManager.addParameter(&customPass);

  displayWificonnect();

  // Try to connect to WiFi, or start a configuration portal if connection fails
  if (!wifiManager.autoConnect("Gnome on the Cloud"))
  {
    displayPortal();
    Serial.println("Failed to connect and hit timeout");

    // If WiFi connection failed, stay in AP mode
    WiFi.mode(WIFI_AP);
    WiFi.softAP("SmogAlado_AP", "12345678");
  }

  // Save WiFi credentials to EEPROM
  strncpy(customWifiSSID, customSSID.getValue(), 32);
  strncpy(customWifiPass, customPass.getValue(), 32);

  dns.start(53, "*", WiFi.softAPIP());

  server.begin();

  EEPROM.begin(512); // Initialize EEPROM with 512 bytes
  EEPROM.put(EEPROM_WIFI_SSID_START, customWifiSSID);
  EEPROM.put(EEPROM_WIFI_PASS_START, customWifiPass);
  EEPROM.commit();

  Serial.println("Connected to WiFi");
}

#endif // WIFI_SETUP