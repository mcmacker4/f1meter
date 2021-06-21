#include "UdpSocketWindows.h"

#include <exception>

UdpSocketWindows::UdpSocketWindows() : UdpSocket(),
                                       wsaData(),
                                       receiverAddress() {}

void UdpSocketWindows::Initialize() {
    InitializeWSAData();
    CreateSocket();
}

void UdpSocketWindows::Bind(int port) {
    receiverAddress.sin_family = AF_INET;
    receiverAddress.sin_port = htons(port);
    receiverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int result = bind(receivingSocket, (SOCKADDR*) &receiverAddress, sizeof(receiverAddress));
    if (result == SOCKET_ERROR) {
        Close();
        CleanUp();
        throw std::exception("Error binding socket to port.");
    }
}

void UdpSocketWindows::Close() {
    if (closesocket(receivingSocket) != 0) {
        CleanUp();
        throw std::exception("Failed to close socket.");
    }
    CleanUp();
}

std::optional<unsigned int> UdpSocketWindows::Recv(char* buffer, unsigned int bufferLength) {
    if (!IsReadyToRead())
        return std::nullopt;
    int result = recv(receivingSocket, buffer, bufferLength, 0);
    if (result < 0)
        throw std::exception("Error reading from socket.");
    return std::optional(result);
}

void UdpSocketWindows::InitializeWSAData() {
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        throw std::exception("Could not initialize WinSock API.");
    }
}

void UdpSocketWindows::CreateSocket() {
    receivingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (receivingSocket == INVALID_SOCKET) {
        CleanUp();
        throw std::exception("Failure creating UDP Socket");
    }
}


void UdpSocketWindows::CleanUp() {
    WSACleanup();
}

bool UdpSocketWindows::IsReadyToRead() {
    struct timeval timeout;
    struct fd_set fds;

    timeout.tv_sec = 0;
    timeout.tv_usec = 100000; // 100 milliseconds

    FD_ZERO(&fds);
    FD_SET(receivingSocket, &fds);

    int result = select(0, &fds, 0, 0, &timeout);
    if (result == 0) {
        return false;
    } else if (result > 0) {
        return true;
    } else {
        throw std::exception("Socket Error while checking availability.");
    }

}