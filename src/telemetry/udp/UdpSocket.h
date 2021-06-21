#ifndef F1METER_UDPSOCKET_H
#define F1METER_UDPSOCKET_H

#include <optional>

class UdpSocket {

public:
    UdpSocket() = default;
    virtual ~UdpSocket() = default;

    virtual void Initialize() = 0;
    virtual void Bind(int port) = 0;
    virtual void Close() = 0;

    virtual std::optional<unsigned int> Recv(char* buffer, unsigned int bufferLength) = 0;

public:
    static UdpSocket* CreatePlatformSocket();

};

#endif //F1METER_UDPSOCKET_H
