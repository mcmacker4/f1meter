#ifndef F1METER_TELEMETRY_H
#define F1METER_TELEMETRY_H

#include "data/TelemetryData.h"
#include "udp/UdpServer.h"

class Telemetry {

    CarTelemetryData carTelemetryData;

    UdpServer udpServer;

private:
    Telemetry() = default;

public:
    Telemetry(const Telemetry&) = delete;
    Telemetry(Telemetry&&) = delete;

    void StartUdpServer();

    CarTelemetryData& GetCarTelemetryData() { return carTelemetryData; }

public:
    static Telemetry& GetInstance();
private:
    static Telemetry* instance;
    static void DeleteInstance();

    friend class Application;

};

#endif //F1METER_TELEMETRY_H
