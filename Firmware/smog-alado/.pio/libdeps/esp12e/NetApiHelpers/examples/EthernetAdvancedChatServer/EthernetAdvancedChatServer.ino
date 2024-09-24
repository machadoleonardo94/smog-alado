/*
 Advanced Chat Server - server.accept() demo/test

 A more advanced server that distributes any incoming messages
 to all connected clients but the client the message comes from.
 To use, telnet to your device's IP address and type.
 You can see the client's input in the serial monitor as well.
*/

#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

EthernetServer server(2323);

EthernetClient clients[8];

void setup() {

  Serial.begin(115200);
  while (!Serial);

  //  Ethernet.init(10);
  Ethernet.begin(mac);

  // start listening for clients
  server.begin();

  IPAddress ip = Ethernet.localIP();
  Serial.println();
  Serial.print("To access the server, connect with Telnet client to ");
  Serial.print(ip);
  Serial.println(" 2323");
}

void loop() {
  // check for any new client connecting, and say hello (before any incoming data)
  EthernetClient newClient = server.accept();
  if (newClient) {
    for (byte i=0; i < 8; i++) {
      if (!clients[i]) {
        Serial.print("We have a new client #");
        Serial.println(i);
        newClient.print("Hello, client number: ");
        newClient.println(i);
        // Once we "accept", the client is no longer tracked by EthernetServer
        // so we must store it into our list of clients
        clients[i] = newClient;
        break;
      }
    }
  }

  // check for incoming data from all clients
  for (byte i=0; i < 8; i++) {
    if (clients[i] && clients[i].available() > 0) {
      // read bytes from a client
      byte buffer[80];
      int count = clients[i].read(buffer, 80);
      // write the bytes to all other connected clients
      for (byte j=0; j < 8; j++) {
        if (j != i && clients[j].connected()) {
          clients[j].write(buffer, count);
        }
      }
    }
  }

  // stop any clients which disconnect
  for (byte i=0; i < 8; i++) {
    if (clients[i] && !clients[i].connected()) {
      Serial.print("disconnect client #");
      Serial.println(i);
      clients[i].stop();
    }
  }
}
