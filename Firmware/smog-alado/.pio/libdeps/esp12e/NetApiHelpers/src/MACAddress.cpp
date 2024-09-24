/*
 MACAddress.cpp - Base class that provides MACAddress

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

#include "MACAddress.h"

MACAddress::MACAddress(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4, uint8_t o5, uint8_t o6) {
  _bytes[0] = o1;
  _bytes[1] = o2;
  _bytes[2] = o3;
  _bytes[3] = o4;
  _bytes[4] = o5;
  _bytes[5] = o6;
}

MACAddress::MACAddress(const uint8_t *mac) {
  memcpy(_bytes, mac, sizeof(_bytes));
}

MACAddress::MACAddress(const char *mac) {
  fromString(mac);
}

void MACAddress::reverse() {
  uint8_t temp[sizeof(_bytes)];
  memcpy(temp, _bytes, sizeof(_bytes));
  for (uint8_t i = 0; i < sizeof(_bytes); i++) {
    _bytes[i] = temp[sizeof(_bytes) - 1 - i];
  }
}

String MACAddress::toString() const {
  char szRet[20];
  if (_separator) {
    snprintf(szRet, sizeof(szRet), "%02X%c%02X%c%02X%c%02X%c%02X%c%02X",
        _bytes[0], _separator, _bytes[1], _separator, _bytes[2], _separator,
        _bytes[3], _separator, _bytes[4], _separator, _bytes[5]);
  } else {
    snprintf(szRet, sizeof(szRet), "%02X%02X%02X%02X%02X%02X",
        _bytes[0], _bytes[1], _bytes[2],
        _bytes[3], _bytes[4], _bytes[5]);
  }
  return String(szRet);
}

static bool isHexDigit(char c) {
	return (c >= '0' && c <= '9') || (c >= 'a' && c <='f') || (c >= 'A' && c <='F');
}

bool MACAddress::fromString(const char *mac) {

  size_t l = strlen(mac);
  if (l != sizeof(_bytes) * 2 && l != (sizeof(_bytes) * 3 - 1))
    return false;
  uint8_t n = (l == sizeof(_bytes) * 2) ? 2 : 3;
  char sep = (n == 2) ? 0 : mac[2];
  if (sep != '-' && sep != ':' && sep != 0 && sep != ' ')
    return false;
  for (uint8_t i = 0, j = 0; i < sizeof(_bytes); i++, j += n) {
    if (!isHexDigit(mac[j]) || !isHexDigit(mac[j + 1])
        || (i < 5 && sep != 0 && sep != mac[j + 2]))
      return false;
  }
  char hh[3] = { 0 };
  for (uint8_t i = 0, j = 0; i < sizeof(_bytes); i++, j += n) {
    hh[0] = mac[j];
    hh[1] = mac[j + 1];
    _bytes[i] = strtol(hh, NULL, 16);
  }
  return true;
}

MACAddress& MACAddress::operator=(const uint8_t *mac) {
  memcpy(_bytes, mac, sizeof(_bytes));
  return *this;
}

MACAddress& MACAddress::operator=(const char *mac) {
  fromString(mac);
  return *this;
}

bool MACAddress::operator==(const MACAddress &mac) const {
  return (memcmp(mac._bytes, _bytes, sizeof(_bytes)) == 0);
}

bool MACAddress::operator==(const uint8_t *mac) const {
  return memcmp(mac, _bytes, sizeof(_bytes)) == 0;
}

uint8_t MACAddress::operator[](int index) const {
  return _bytes[index];
}

uint8_t& MACAddress::operator[](int index) {
  return _bytes[index];
}

size_t MACAddress::printTo(Print &p) const {
  size_t n = 0;

  for (int i = 0; i < 6; i++) {
    if (i > 0 && _separator) {
      n += p.print(_separator);
    }
    if (_bytes[i] < 0x10) {
      n += p.print('0');
    }
    n += p.print(_bytes[i], HEX);
  }
  return n;
}

