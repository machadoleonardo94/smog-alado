/*
  ArduinoEthernetServer.h - a realization of the ServerTemplate
  for Ethernet libraries without proper server.available()
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

#ifndef ARDUINO_ETHERNET_SERVER_H
#define ARDUINO_ETHERNET_SERVER_H

#if defined(ARDUINO_ARCH_MBED) && defined(MBEDSOCKETCLASS_H)
#define SERVER_DONT_INHERIT_FROM_PRINT
#define SERVER_USE_SUPER_AVAILABLE
#define SERVER_SUPER_END_FNC // no server.end()
#else
#error "Platform not supported"
#endif

#include <EthernetServer.h>
#include "ServerTemplate.h"

typedef ServerTemplate<EthernetServer, EthernetClient> ArduinoEthernetServer;


#endif
