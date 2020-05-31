/*
  Client.h - Base class that provides Client
  Copyright (c) 2011 Adrian McEwen.  All right reserved.

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

#ifndef _HUSARNETCLIENT_H_
#define _HUSARNETCLIENT_H_
#include <array>

struct IP6Address {
    std::array<uint8_t, 16> data;
};

#include "Arduino.h"
#include "Client.h"
#undef min
#undef max
#include <memory>

class HusarnetClientSocketHandle;

class HusarnetClient : public Client
{
protected:
    std::shared_ptr<HusarnetClientSocketHandle> clientSocketHandle;
    bool _connected;

public:
    HusarnetClient *next;
    HusarnetClient();
    HusarnetClient(int fd);
    ~HusarnetClient();
    int connect(IPAddress ip, uint16_t port);
    int connect(IP6Address ip, uint16_t port);
    int connect(const char *host, uint16_t port);
    size_t write(uint8_t data);
    size_t write(const uint8_t *buf, size_t size);
    size_t write_P(PGM_P buf, size_t size);
    int available();
    int read();
    int read(uint8_t *buf, size_t size);
    int peek();
    void flush();
    void stop();
    uint8_t connected();

    operator bool()
    {
        return connected();
    }
    HusarnetClient & operator=(const HusarnetClient &other);
    bool operator==(const bool value)
    {
        return bool() == value;
    }
    bool operator!=(const bool value)
    {
        return bool() != value;
    }
    bool operator==(const HusarnetClient&);
    bool operator!=(const HusarnetClient& rhs)
    {
        return !this->operator==(rhs);
    };

    int fd() const;

    int setSocketOption(int option, char* value, size_t len);
    int setOption(int option, int *value);
    int getOption(int option, int *value);
    int setTimeout(uint32_t seconds);
    int setNoDelay(bool nodelay);
    bool getNoDelay();

    //friend class WiFiServer;
    using Print::write;
};

#endif /* _WIFICLIENT_H_ */
