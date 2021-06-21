#ifndef F1METER_UDPSOCKETWINDOWS_H
#define F1METER_UDPSOCKETWINDOWS_H

#include "../UdpSocket.h"

#include <winsock2.h>

class UdpSocketWindows : public UdpSocket {

    WSADATA wsaData;
    SOCKET receivingSocket;
    SOCKADDR_IN receiverAddress;

public:
    UdpSocketWindows();
    UdpSocketWindows(const UdpSocketWindows&) = delete;
    UdpSocketWindows(UdpSocketWindows&&) = delete;

    ~UdpSocketWindows() override = default;

    void Initialize() override;
    void Bind(int port) override;
    void Close() override;
    std::optional<unsigned int> Recv(char* buffer, unsigned int bufferLength) override;

private:
    void InitializeWSAData();
    void CreateSocket();

    void CleanUp();

    bool IsReadyToRead();

};


#endif //F1METER_UDPSOCKETWINDOWS_H
