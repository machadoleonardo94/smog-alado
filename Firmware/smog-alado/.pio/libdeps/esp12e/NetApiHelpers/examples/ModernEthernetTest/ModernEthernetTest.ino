
#include <W5500lwIP.h>
#include <NetApiHelpers.h>
#include <MACAddress.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF };

Wiznet5500lwIP Ethernet(17);
#define EthernetClient WiFiClient

void setup() {

  Serial.begin(115200);
  delay(500);
  while (!Serial);
  Serial.println("START");
  Serial.println();

//  SPI.begin();
//  SPI.setClockDivider(SPI_CLOCK_DIV4);
//  SPI.setBitOrder(MSBFIRST);
//  SPI.setDataMode(SPI_MODE0);

  Serial.println("Attempting to connect with DHCP ...");
  Ethernet.setHostname("arduino");
  testEthernet();

  Serial.println("Checking link ...");
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("\tretry...");
    delay(500);
  }
  switch (Ethernet.linkStatus()) {
    case LinkOFF:
      Serial.println("\tEthernet cable is not connected.");
      break;
    case LinkON:
      Serial.println("\tEthernet cable is connected.");
      break;
    default:
      Serial.println("\tLink state unknown.");
      break;
  }
  Serial.println();

  IPAddress ip = Ethernet.localIP();
  IPAddress gw = Ethernet.gatewayIP();
  IPAddress mask = Ethernet.subnetMask();
  IPAddress dns = Ethernet.dnsIP();

  const char *serverName = "www.google.com";
  Serial.print("Resolve IP for ");
  Serial.println(serverName);
  IPAddress resolvedIP;
  Ethernet.hostByName("www.google.com", resolvedIP);
  Serial.print("\t");
  Serial.println(resolvedIP);
  Serial.println();

  Ethernet.end();

//  IPAddress ip(192, 168, 1, 177);
//  IPAddress gw(192, 168, 1, 1);
//  IPAddress dns(192, 168, 1, 1);
//  IPAddress mask(255, 255, 255, 0);

  Serial.print("Configuring static IP ");
  ip[3] = 177;
  Serial.println(ip);
  Ethernet.config(ip, dns, gw, mask);
  if (Ethernet.dnsIP() == mask) {
    Serial.println("ERROR: config() has wrong ordering of parameters");
    while (true) {
      delay(1);
    }
  }
  testEthernet();
  if (ip != Ethernet.localIP()) {
    Serial.println("ERROR: Static IP was not used.");
    while (true) {
      delay(1);
    }
  }

  IPAddress dnsIP2(8, 8, 8, 8);
  Ethernet.setDNS(Ethernet.dnsIP(), dnsIP2);
  if (Ethernet.dnsIP(1) != dnsIP2) {
    Serial.print("ERROR: DNS IP setter or getter error. dnsIP(1) returned ");
    Serial.println(Ethernet.dnsIP(1));
    Serial.println();
  }

  Ethernet.end();

  Serial.println("Attempting to connect without resetting static IP configuration"); // <-------
  testEthernet();
  if (ip != Ethernet.localIP()) {
    Serial.println("ERROR: Static IP was cleared.");
  }
  Ethernet.end();

  Serial.print("Configuring with automatic gateway, DNS and mask with static IP "); // <-------
  ip[3] = 178;
  Serial.println(ip);
  Ethernet.config(ip);
  testEthernet();
  if (ip != Ethernet.localIP()) {
    Serial.println("ERROR: Static IP was not used.");
    while (true) {
      delay(1);
    }
  }
  IPAddress autoIP(ip);
  autoIP[3] = 1;
  IPAddress defaultMask(255, 255, 255, 0);
  if (Ethernet.gatewayIP() == autoIP && Ethernet.dnsIP() == autoIP && Ethernet.subnetMask() == defaultMask) {
    Serial.println("Automatic config values are OK");
  } else {
    Serial.println("ERROR: Automatic config values are wrong");
    if (Ethernet.gatewayIP() != autoIP) {
      Serial.print("\tgateway IP Address: ");
      Serial.println(Ethernet.gatewayIP());
    }
    if (Ethernet.subnetMask() != defaultMask) {
      Serial.print("\tsubnet IP mask: ");
      Serial.println(Ethernet.subnetMask());
    }
    if (Ethernet.dnsIP() != autoIP) {
      Serial.print("\tDNS server: ");
      Serial.println(Ethernet.dnsIP());
    }
  }
  Serial.println();

  Ethernet.end();

  Serial.println("Attempting to connect with DHCP again ...");
  Ethernet.setHostname("arduino");
  Ethernet.config(INADDR_NONE);
  testEthernet();
  if (Ethernet.localIP() == INADDR_NONE) {
    Serial.println("ERROR: DHCP didn't run.");
  } else if (Ethernet.localIP() == ip) {
    Serial.println("ERROR: The IP didn't change from static IP to DHCP assigned IP.");
  } else {
    Serial.println("Check on router the hostname and MAC address.");
  }
  Serial.println();

  Serial.println("END");
}

void loop() {
}

void testEthernet() {
  Ethernet.begin(mac);
  while (Ethernet.status() == WL_DISCONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println();
  if (Ethernet.status() != WL_CONNECTED) {
    Serial.println("ERROR:  Ethenet didn't connect");
    printStatus();
    while (true) {
      delay(1);
    }
  } else {
    Serial.println("\t...success");
  }
  Serial.println();

  printEthernetInfo();
  Serial.println();

  Serial.print("Attempt to connect to port 80 on ");
  Serial.println(Ethernet.gatewayIP());
  EthernetClient client;
  if (client.connect(Ethernet.gatewayIP(), 80)) {
    Serial.println("\t...success");
  } else {
    Serial.println("\t...ERROR");
  }
  client.stop();
  Serial.println();
}

void printEthernetInfo() {

  MACAddress mac;
  Ethernet.macAddress(mac);
  Serial.print("MAC: ");
  Serial.println(mac);

  Serial.print("IP Address: ");
  Serial.println(Ethernet.localIP());

  Serial.print("gateway IP Address: ");
  Serial.println(Ethernet.gatewayIP());

  Serial.print("subnet IP mask: ");
  Serial.println(Ethernet.subnetMask());

  Serial.print("DNS server: ");
  IPAddress dns = Ethernet.dnsIP();
  if (dns == INADDR_NONE) {
    Serial.println("not set");
  } else {
    Serial.println(dns);
    IPAddress dns2 = Ethernet.dnsIP(1);
    if (dns2 != INADDR_NONE) {
      Serial.print("DNS server2: ");
      Serial.println(dns2);
    }
  }
}

void printStatus() {
  int status = Ethernet.status();
  const char* msg = nullptr;
  switch (status) {
    case WL_NO_SHIELD:
      msg = "NO_SHIELD";
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