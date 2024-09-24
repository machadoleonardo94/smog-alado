/*
  Ethernet Pager Server - - server.available
  and print-to-all-clients demo/test

  The example is a simple server that echoes any incoming
  messages to all connected clients. Connect two or more
  telnet sessions to see how server.available() and
  server.print() work.
*/

#include <Ethernet.h>

#if (defined(ARDUINO_ARCH_MBED) && defined(MBEDSOCKETCLASS_H))
// the EthernetServer in these libraries doesn't have print-to-all-clients and proper available()
// so we use ArduinoEthernetServer, which configures the ServerTemplate for these platforms
#include <NetApiHelpers.h>
#include <ArduinoEthernetServer.h>

ArduinoEthernetServer server(2323);

#else

EthernetServer server(2323);
#endif

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

void setup() {

  Serial.begin(115200);
  while (!Serial);

  //  Ethernet.init(10);
  Ethernet.begin(mac);

  server.begin();

  IPAddress ip = Ethernet.localIP();
  Serial.println();
  Serial.print("To access the server, connect with Telnet client to ");
  Serial.print(ip);
  Serial.println(" 2323");
}

void loop() {

  EthernetClient client = server.available(); // returns first client which has data to read or a 'false' client
  if (client) {                               // client is true only if it is connected and has data to read
    String s = client.readStringUntil('\n');  // read the message incoming from one of the clients
    s.trim();                                 // trim eventual \r
    Serial.println(s);                        // print the message to Serial Monitor
    client.print("echo: ");                   // this is only for the sending client
    server.println(s);                        // send the message to all connected clients
    server.flush();                           // flush the buffers
  }
}
