#include "UdpSocket.h"

#ifdef WIN32
#include "platform/UdpSocketWindows.h"
#else
#error "Platform not supported"
#endif

UdpSocket* UdpSocket::CreatePlatformSocket() {
#ifdef WIN32
    return new UdpSocketWindows();
#else
#error "Platform not supported"
#endif
}