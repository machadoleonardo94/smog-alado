
#include <WiFi.h>
#include <NetApiHelpers.h>
#include <MACAddress.h>

#include "arduino_secrets.h"
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

void setup() {

  Serial.begin(115200);
  delay(500);
  while (!Serial);
  Serial.println("START");
  Serial.println();

//  Serial1.begin(115200);
//  WiFi.init(Serial1);
//  WiFi.setPersistent(false);
//  WiFi.persistent(false);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println();
    Serial.println("ERROR: Communication with WiFi module failed!");
    // don't continue
    while (true) {
      delay(1);
    }
  }

  Serial.print("firmware version: ");
  Serial.println(WiFi.firmwareVersion());
  Serial.println();

  Serial.print("Attempting to connect to SSID \"");
  Serial.print(ssid);
  Serial.println("\" with DHCP ..."); // <-------
  WiFi.setHostname("arduino");
  testWiFi();

  IPAddress ip = WiFi.localIP();
  IPAddress gw = WiFi.gatewayIP();
  IPAddress mask = WiFi.subnetMask();
  IPAddress dns = WiFi.dnsIP();

  const char *serverName = "www.google.com";
  Serial.print("Resolve IP for ");
  Serial.println(serverName);
  IPAddress resolvedIP;
  if (WiFi.hostByName("www.google.com", resolvedIP) == 1) {
    Serial.print("\t");
    Serial.println(resolvedIP);
  } else {
    Serial.println("\t...ERROR");
  }
  Serial.println();

  WiFi.disconnect();

//  IPAddress ip(192, 168, 1, 177);
//  IPAddress gw(192, 168, 1, 1);
//  IPAddress dns(192, 168, 1, 1);
//  IPAddress mask(255, 255, 255, 0);

  Serial.print("Attempting to connect to SSID \"");
  Serial.print(ssid);
  Serial.print("\" with static IP "); // <-------
  ip[3] = 177;
  Serial.println(ip);
  WiFi.config(ip, dns, gw, mask);
  if (WiFi.dnsIP() == mask) {
    Serial.println("ERROR: config() has wrong ordering of parameters");
    while (true) {
      delay(1);
    }
  }
  testWiFi();
  if (ip != WiFi.localIP()) {
    Serial.println("ERROR: Static IP was not used.");
    while (true) {
      delay(1);
    }
  }

  IPAddress dnsIP2(8, 8, 8, 8);
  WiFi.setDNS(WiFi.dnsIP(), dnsIP2);
  if (WiFi.dnsIP(1) != dnsIP2) {
    Serial.print("ERROR: DNS IP setter or getter error. dnsIP(1) returned ");
    Serial.println(WiFi.dnsIP(1));
    Serial.println();
  }

  WiFi.disconnect();

  Serial.println("Attempting to connect without resetting static IP configuration"); // <-------
  testWiFi();
  if (ip != WiFi.localIP()) {
    Serial.println("ERROR: Static IP was cleared.");
    Serial.println();
  }
  WiFi.disconnect();

  Serial.print("Attempting to connect to SSID \"");
  Serial.print(ssid);
  Serial.print("\" with automatic gateway, DNS and mask with static IP "); // <-------
  ip[3] = 178;
  Serial.println(ip);
  WiFi.config(ip);
  testWiFi();
  if (ip != WiFi.localIP()) {
    Serial.println("ERROR: Static IP was not used.");
    while (true) {
      delay(1);
    }
  }
  IPAddress autoIP(ip);
  autoIP[3] = 1;
  IPAddress defaultMask(255, 255, 255, 0);
  if (WiFi.gatewayIP() == autoIP && WiFi.dnsIP() == autoIP && WiFi.subnetMask() == defaultMask) {
    Serial.println("Automatic config values are OK");
  } else {
    Serial.println("ERROR: Automatic config values are wrong");
    if (WiFi.gatewayIP() != autoIP) {
      Serial.print("\tgateway IP Address: ");
      Serial.println(WiFi.gatewayIP());
    }
    if (WiFi.subnetMask() != defaultMask) {
      Serial.print("\tsubnet IP mask: ");
      Serial.println(WiFi.subnetMask());
    }
    if (WiFi.dnsIP() != autoIP) {
      Serial.print("\tDNS server: ");
      Serial.println(WiFi.dnsIP());
    }
  }
  Serial.println();

  WiFi.disconnect();

  Serial.print("Attempting to connect to SSID \"");
  Serial.print(ssid);
  Serial.println("\" with DHCP again..."); // <-------
  WiFi.setHostname("arduino");
  WiFi.config(INADDR_NONE);
  testWiFi();
  if (WiFi.localIP() == INADDR_NONE) {
    Serial.println("ERROR: DHCP didn't run.");
  } else if (WiFi.localIP() == ip) {
    Serial.println("ERROR: The IP didn't change from static IP to DHCP assigned IP.");
  } else {
    Serial.println("Check on router the hostname and MAC address.");
  }
  Serial.println();

  Serial.println("END");
}

void loop() {
}

void testWiFi() {
  WiFi.begin(ssid, pass);
  while (WiFi.status() == WL_DISCONNECTED || WiFi.status() == WL_IDLE_STATUS) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("ERROR:  STA didn't connect");
    printWiFiStatus();
    while (true) {
      delay(1);
    }
  } else {
    Serial.println("\t...success");
  }
  Serial.println();

  printWiFiInfo();
  Serial.println();

  Serial.print("Attempt to connect to port 80 on ");
  Serial.println(WiFi.gatewayIP());
  WiFiClient client;
  if (client.connect(WiFi.gatewayIP(), 80)) {
    Serial.println("\t...success");
  } else {
    Serial.println("\t...ERROR");
  }
  client.stop();
  Serial.println();
}

void printWiFiInfo() {

  MACAddress mac;
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.println(mac);
  if (mac[0] & 1) { // multicast bit is set
    Serial.println("\t is the ordering of the MAC address bytes reversed?");
  }

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  MACAddress bssid;
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  Serial.println(bssid);
  if (bssid[0] & 1) { // multicast bit is set
    Serial.println("\t is the ordering of the BSSID bytes reversed?");
  }

  Serial.print("RSSI:");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.print("gateway IP Address: ");
  Serial.println(WiFi.gatewayIP());

  Serial.print("subnet IP mask: ");
  Serial.println(WiFi.subnetMask());

  Serial.print("DNS server: ");
  IPAddress dns = WiFi.dnsIP();
  if (dns == INADDR_NONE) {
    Serial.println("not set");
  } else {
    Serial.println(dns);
    IPAddress dns2 = WiFi.dnsIP(1);
    if (dns2 != INADDR_NONE) {
      Serial.print("DNS server2: ");
      Serial.println(dns2);
    }
  }
}

void printWiFiStatus() {
  int status = WiFi.status();
  const char* msg = nullptr;
  switch (status) {
    case WL_NO_SHIELD:
      msg = "NO_SHIELD";
      break;
    case WL_IDLE_STATUS:
      msg = "IDLE_STATUS";
      break;
    case WL_NO_SSID_AVAIL:
      msg = "NO_SSID_AVAIL";
      break;
    case WL_CONNECTED:
      msg = "CONNECTED";
      break;
    case WL_CONNECT_FAILED:
      msg = "CONNECT_FAILED";
      break;
    case WL_CONNECTION_LOST:
      msg = "CONNECTION_LOST";
      break;
    case WL_DISCONNECTED:
      msg = "DISCONNECTED";
      break;
  }
  Serial.print("status: ");
  if (msg != nullptr) {
    Serial.println(msg);
  } else {
    Serial.println(status);
  }
}