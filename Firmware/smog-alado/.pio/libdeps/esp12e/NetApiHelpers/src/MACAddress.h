/*
 MACAddress.h - Base class that provides MACAddress

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

#pragma once

#include <Arduino.h>

class MACAddress: public Printable {
private:
  uint8_t _bytes[6] = {0};
  char _separator = ':';

public:

  MACAddress() {};
  MACAddress(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4, uint8_t o5, uint8_t o6);
  MACAddress(const uint8_t *mac);
  MACAddress(const char *mac);

  void setSeparator(char separator) {_separator = separator;}

  void reverse();

  bool fromString(const char *mac);
  bool fromString(const String &mac) {
    return fromString(mac.c_str());
  }

  operator uint8_t*() {
    return _bytes;
  }

  bool operator==(const MACAddress &mac) const;
  bool operator!=(const MACAddress &mac) const {
    return !(*this == mac);
  }

  bool operator==(const uint8_t *mac) const;

  // Overloaded index operator to allow getting and setting individual octets of the mac
  uint8_t operator[](int index) const;
  uint8_t& operator[](int index);

  // Overloaded copy operators to allow initialisation of MACAddress objects from other types
  MACAddress& operator=(const uint8_t *mac);
  MACAddress& operator=(const char *mac);

  virtual size_t printTo(Print &p) const;
  String toString() const;
};
