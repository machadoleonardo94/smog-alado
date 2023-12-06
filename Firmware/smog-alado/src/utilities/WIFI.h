#if !defined(WIFI_SETUP)
#define WIFI_SETUP

#include "shared/dependencies.h"
#include "components/DISPLAY/setup.h"

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

  WiFi.setPhyMode(WIFI_PHY_MODE_11N); // WiFi N mode, best speed, lower range, lower power
  WiFi.setOutputPower(20.5f);         // Output power of WiFi, dBm range: max +20.5dBm  min 0dBm
  // WiFi.setSleepMode(WIFI_LIGHT_SLEEP, 1);   // Lowest WiFi power setting

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  // Try to load WiFi credentials from EEPROM
  EEPROM.begin(512); // Initialize EEPROM with 512 bytes
  EEPROM.get(EEPROM_WIFI_SSID_START, customWifiSSID);
  EEPROM.get(EEPROM_WIFI_PASS_START, customWifiPass);

  // Set the custom parameters for WiFiManager
  WiFiManagerParameter customSSID("SSID", "WiFi SSID", customWifiSSID, 32);
  WiFiManagerParameter customPass("password", "WiFi Password", customWifiPass, 32);

  wifiManager.addParameter(&customSSID);
  wifiManager.addParameter(&customPass);

  displayWificonnect();
  wifiManager.setConfigPortalTimeout(APtimeout);

  // Try to connect to WiFi, or start a configuration portal if connection fails
  if (!wifiManager.autoConnect("Gnome on the Cloud"))
  {
    displayPortal();
    Serial.println("Failed to connect and hit timeout");
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
