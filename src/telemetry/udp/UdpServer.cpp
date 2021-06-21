#include "UdpServer.h"

#include "PacketProcessing.h"

#include <iostream>

#define PACKET_PADDING 100
#define BUFFER_LENGTH (F1Raw::MAX_PACKET_SIZE + PACKET_PADDING)

UdpServer::UdpServer() {
    packetBuffer = new char[BUFFER_LENGTH];
}

UdpServer::~UdpServer() {
    delete packetBuffer;
    delete socket;
    delete socketThread;
}

void UdpServer::Start() {
    socketThread = new std::thread([this]() {
        CreateSocket();
        ReceiveLoop();
    });
}


void UdpServer::Stop() {
    socket->Close();
    socketThread->join();
}

void UdpServer::CreateSocket() {
    socket = UdpSocket::CreatePlatformSocket();
    socket->Initialize();
}

void UdpServer::ReceiveLoop() {

    socket->Bind(20777);

    try {

        while (1) {
            auto result = socket->Recv(packetBuffer, BUFFER_LENGTH);
            if (result.has_value() && *result > 0) {
                ProcessPacket(*result);
            }
            std::this_thread::yield();
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

}


void UdpServer::ProcessPacket(unsigned int packetLength) {
    auto* header = reinterpret_cast<F1Raw::PacketHeader*>(packetBuffer);
    if (header->packetFormat != 2020) {
        std::cerr << "Invalid packet (format is not 2020)" << std::endl;
    }
    PacketProcessing::Process(packetBuffer, packetLength);;
}