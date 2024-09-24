/*
  ServerTemplate.h - a template for Arduino Server
  with proper implementation of available() and print-to-all-clients
  Copyright (c) 2023 Juraj Andrassy

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef SERVER_TEMPLATE_H
#define SERVER_TEMPLATE_H

#ifndef SERVER_MAX_MONITORED_CLIENTS
#define SERVER_MAX_MONITORED_CLIENTS 5
#endif

#ifndef SERVER_CTOR_DEFAULT_PORT
#define SERVER_CTOR_DEFAULT_PORT 80
#endif

#ifndef SERVER_SUPER_END_FNC
#define SERVER_SUPER_END_FNC TServer::end()
#endif

template <class TServer, class TClient>
class ServerTemplate :
#ifdef SERVER_DONT_INHERIT_FROM_PRINT
  public TServer
#else
  public TServer, public Print
#endif
{
public:

#ifdef SERVER_CTOR_WITH_IP
  ServerTemplate(const IPAddress& addr, uint16_t port) : TServer(addr, port) {}
#endif
  ServerTemplate(uint16_t port = SERVER_CTOR_DEFAULT_PORT) : TServer(port) {}
  virtual ~ServerTemplate() {}

  // https://www.arduino.cc/en/Reference/WiFiServerAvailable
  TClient available() {

    acceptClients();

    // find next client with data available
    for (uint8_t i = 0; i < SERVER_MAX_MONITORED_CLIENTS; i++) {
      if (index == SERVER_MAX_MONITORED_CLIENTS) {
        index = 0;
      }
      TClient& client = connectedClients[index];
      index++;
      if (client.available())
        return client;
    }
    return TClient(); // no client with data found
  }

  virtual size_t write(uint8_t b) override {
    return write(&b, 1);
  }

  virtual size_t write(const uint8_t *buf, size_t size) override {
    static uint32_t lastCheck;
    uint32_t m = millis();
    if (m - lastCheck > 100) {
      lastCheck = m;
      acceptClients();
    }
    if (size == 0)
      return 0;
    size_t ret = 0;
#ifndef SERVER_USE_AVAIL4WRITE
    for (uint8_t i = 0; i < SERVER_MAX_MONITORED_CLIENTS; i++) {
      if (established(connectedClients[i])) {
        ret = connectedClients[i].write(buf, size);
      }
    }
#else
    size_t a = size;
    while (true) {
      for (uint8_t i = 0; i < SERVER_MAX_MONITORED_CLIENTS; i++) {
        WiFiClient& client = connectedClients[i];
        if (established(client) && client.availableForWrite() < (int) a) {
          a = client.availableForWrite();
        }
      }
      if (a == 0)
        break;
      for (uint8_t i = 0; i < SERVER_MAX_MONITORED_CLIENTS; i++) {
        if (established(connectedClients[i])) {
          connectedClients[i].write(buf, a);
        }
      }
      ret += a;
      if (ret == size)
        break;
      buf += a;
      a = size - ret;
    }
#endif
    return ret;
  }

  using Print::write;

  virtual void flush() override {
#ifndef SERVER_DONT_FLUSH_CLIENTS
    for (uint8_t i = 0; i < SERVER_MAX_MONITORED_CLIENTS; i++) {
      if (established(connectedClients[i])) {
        connectedClients[i].flush();
      }
    }
#endif
  }

  void end() {
    SERVER_SUPER_END_FNC;
    for (uint8_t i = 0; i < SERVER_MAX_MONITORED_CLIENTS; i++) {
      if (connectedClients[i]) {
        connectedClients[i].stop();
      }
    }
  }

private:
  TClient connectedClients[SERVER_MAX_MONITORED_CLIENTS];
  uint8_t index = 0;

  void acceptClients() {
    for (uint8_t i = 0; i < SERVER_MAX_MONITORED_CLIENTS; i++) {
      TClient& client = connectedClients[i];
      if (!client.connected() && !client.available()) {
#ifdef SERVER_USE_SUPER_AVAILABLE
        client = TServer::available();
#else
        client = TServer::accept();
#endif
      }
    }
  }

  bool established(TClient& client) {
#ifdef SERVER_USE_CLIENT_STATUS
  	return client.status() == ESTABLISHED;
#else
    return client.connected();
#endif
  }
};

#endif
