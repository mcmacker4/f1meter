#ifndef F1METER_UDPSERVER_H
#define F1METER_UDPSERVER_H

#include "PacketTypes.h"
#include "UdpSocket.h"

#include <thread>


class UdpServer {

    UdpSocket* socket;
    std::thread* socketThread;

    char* packetBuffer;

public:
    UdpServer();
    UdpServer(const UdpServer&) = delete;
    UdpServer(UdpServer&&) = delete;

    ~UdpServer();

    void Start();
    void Stop();

private:

    void CreateSocket();
    void ReceiveLoop();
    void ProcessPacket(unsigned int packetLenght);

};

#endif //F1METER_UDPSERVER_H
