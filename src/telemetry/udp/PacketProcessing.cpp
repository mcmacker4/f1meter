#include "PacketProcessing.h"

#include "PacketTypes.h"
#include "../Telemetry.h"

#include <iostream>

#define CHECK_PACKET_LENGTH(l, p) {                                                                                         \
    if ((l) < sizeof(p)) {                                                                                                  \
        std::cerr << "Packet length differs from expected. Expected: " << (sizeof(p)) << " Actual: " << (l) << std::endl;   \
        return;                                                                                                             \
    }                                                                                                                       \
}

namespace PacketProcessing {

    void ProcessCarTelemetryPacket(char* buffer, unsigned int packetLength);

    void Process(char* buffer, unsigned int packetLength) {
        if (packetLength < sizeof(F1Raw::PacketHeader))
            std::cerr << "Packet size is less than header size. Silently Dropping." << std::endl;
        auto* header = reinterpret_cast<F1Raw::PacketHeader*>(buffer);
        switch (header->packetId) {
            case F1Raw::PacketId::CAR_TELEMETRY:
                ProcessCarTelemetryPacket(buffer, packetLength);
                break;
            default:
                std::cout << "Unimplemented packet id " << header->packetId << std::endl;
        }
    }

    void ProcessCarTelemetryPacket(char* buffer, unsigned int packetLength) {
        CHECK_PACKET_LENGTH(packetLength, F1Raw::PacketCarTelemetryData)
        auto* packet = reinterpret_cast<F1Raw::PacketCarTelemetryData*>(buffer);

        auto playerCarIndex = packet->header.playerCarIndex;

        auto* rawdata = packet->carTelemetryData + playerCarIndex;
        auto& cardata = Telemetry::GetInstance().GetCarTelemetryData();

        CarTelemetryDataPoint dataPoint;
        dataPoint.time = packet->header.sessionTime;
        dataPoint.speed = rawdata->speed;
        dataPoint.throttle = rawdata->throttle;
        dataPoint.steer = rawdata->steer;
        dataPoint.brake = rawdata->brake;
        dataPoint.engineRPM = rawdata->engineRPM;
        //dataPoint.brakesTemperature[4] = TODO: Copy
        //dataPoint.tyresSurfaceTemperature[4] = TODO: Copy
        //dataPoint.tyresInnerTemperature[4] = TODO: Copy
        dataPoint.engineTemperature = rawdata->engineTemperature;
        //dataPoint.tyresPressure[4] = TODO: Copy

        cardata.Insert(dataPoint);

    }

}