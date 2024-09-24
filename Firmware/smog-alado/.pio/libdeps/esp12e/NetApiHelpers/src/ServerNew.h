
#include <inttypes.h>

template <class TClient>
class ServerNew {

  virtual void begin(uint16_t port) = 0;

  virtual void end() = 0;

  virtual explicit operator bool() = 0;

  virtual TClient accept() = 0;

};
