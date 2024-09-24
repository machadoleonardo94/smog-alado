
# Arduino Networking API Helper classes library

A library to support Arduino Networking libraries development. It accompanies the [Arduino Networking API usage guidelines](https://github.com/JAndrassy/Arduino-Networking-API/blob/main/ArduinoNetAPIDev.md).

The purpose of this library is to help networking library developers to ensure that their library can be used as a replacement of existing Arduino networking libraries and to simplify development of the Arduino Networking API in their library.

The library is in Library Manager.

## MACAddress

The class MACAddress works similar as the well known IPAddress class from Arduino Core.

It is compatible with an uint8_t array, implements Printable, can be parsed from string and formatted to string.

Some existing libraries return the byte array with values in reversed order. Method reverse() reverses the order of bytes in an MACAddress object.

## Tests

### Tests for the WiFi object

Every WiFi library should be able to run the WiFiTest and WiFiScanNetworks sketches with no or minimal modifications.

### Tests for the Ethernet object

The LegacyEthernetTest has what would be good to have in a classic Ethernet library.

ModernEtherneTest is for Ethernet libraries with API aligned with WiFi libraries, especially method `config` for static IP configuration.

### Tests for server implementation

* AdvancedChatServer - example and test for server.accept()
* PagerServer - example and test for server.available() and print-to-all-clients 

## Server Helpers

### ServerNew

ServerNew is an abstract class template with all pure virtual functions. It helps to code a modern Server class with accept(), begin(port), end() and operator bool. It is not useful at runtime and takes same memory so eventually remove it from the published version of your networking library.

ServerNew is what users ask and old Arduino Server implementations don't have.

Usage:
```
#include <ServerNew.h>
#include "EthernetClient.h"

class EthernetServer
  : public ServerNew<EthernetClient>
{

public:
...
```


### ServerTemplate

ServerTemplate implements method available() and print-to-all-clients using accept() method of a class from which it inherits. It is a template with Server type and Client type as template parameters.

Implement a ServerNew realization, don't inherit it from Server or Print. Name it EthernetServerNew or WiFiServerNew. Then define EthernetServer/WiFiServer in your library as 
```
typedef ServerTemplate<EthernetServerNew, EthernetClient> EthernetServer;
```
or
```
typedef ServerTemplate<WiFiServerNew, WiFiClient> WiFiServer;
```

This way your library will have a legacy Arduino Server.

ServerTemplate is configurable with some #defines. See the header file for the details.

Note: ServerTemplate requires a proper implementation of the Client class.

### ArduinoWiFiSever/ArduinoEthernetServer

The ArduinoWiFiSever and ArduinoEthernetServer use ServerTemplate to implement server class with proper available() and print-to-all-clients for some existing libraries where the WiFiServer/EthernetServer doesn't have it.


