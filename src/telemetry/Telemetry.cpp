#include "Telemetry.h"

#include "udp/UdpServer.h"

#include <iostream>

Telemetry* Telemetry::instance = nullptr;

void Telemetry::StartUdpServer() {
    udpServer.Start();
    std::cout << "Udp Server Started." << std::endl;
}

Telemetry& Telemetry::GetInstance() {
    if (instance == nullptr) {
        instance = new Telemetry;
    }
    return *instance;
}

void Telemetry::DeleteInstance() {
    delete instance;
}