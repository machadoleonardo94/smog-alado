
#include <WiFi.h>
#include <NetApiHelpers.h>
#include <MACAddress.h>

void setup() {

  Serial.begin(115200);
  while (!Serial);

//  Serial1.begin(115200);
//  WiFi.init(Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Communication with WiFi module failed!");
    while (true) {
      delay(1);
    }
  }

  Serial.println("Scan Networks ...");
  int count = WiFi.scanNetworks();
  if (count == -1) {
    Serial.println("Couldn't get a WiFi connection");
    while (true);
  }

  Serial.print("number of available networks:");
  Serial.println(count);

  for (int i = 0; i < count; i++) {
    Serial.print(i + 1);
    Serial.print(") ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" Signal: ");
    Serial.print(WiFi.RSSI(i));
    Serial.print(" dBm");
    Serial.print("\tChannel: ");
    Serial.print(WiFi.channel(i));
    Serial.print(" Encryption: ");
    switch (WiFi.encryptionType(i)) {
      case ENC_TYPE_WEP:
        Serial.print("WEP");
        break;
      case ENC_TYPE_TKIP:
//      case ENC_TYPE_WPA:
        Serial.print("WPA");
        break;
      case ENC_TYPE_CCMP:
//      case ENC_TYPE_WPA2:
        Serial.print("WPA2");
        break;
      case ENC_TYPE_GCMP:
//      case ENC_TYPE_WPA3:
        Serial.print("WPA3");
        break;
      case ENC_TYPE_NONE:
        Serial.print("None");
        break;
      case ENC_TYPE_AUTO:
        Serial.print("Auto");
        break;
      default:
        Serial.print("Unknown");
        break;
    }
    MACAddress bssid;
    Serial.print("\tBSSID: ");
    WiFi.BSSID(i, bssid);
//    bssid = WiFi.BSSID(i);
    Serial.print(bssid);
    Serial.println();
  }

}

void loop() {
}

