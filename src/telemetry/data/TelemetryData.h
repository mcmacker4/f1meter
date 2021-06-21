#ifndef F1METER_TELEMETRYDATA_H
#define F1METER_TELEMETRYDATA_H

#include <mutex>
#include <vector>

#include <imgui/imgui.h>

struct DataPoint {
    float time;
};

template <typename T>
class TelemetryData {
    std::vector<T> data;
    std::mutex mutex;
public:
    TelemetryData() = default;

    int Count();
    T& operator[](int i);

    void Insert(const T& dataPoint);
};

template<typename T>
int TelemetryData<T>::Count() {
    std::lock_guard guard(mutex);
    return data.size();
}

template<typename T>
T& TelemetryData<T>::operator[](int i) {
    std::lock_guard guard(mutex);
    if (i < 0 || i >= data.size()) {
        throw std::exception("Out of bounds data");
    }
    return data[i];
}

template<typename T>
void TelemetryData<T>::Insert(const T& dataPoint) {
    std::lock_guard guard(mutex);
    data.push_back(dataPoint);
}

struct CarTelemetryDataPoint : public DataPoint {
    uint16_t speed;
    float throttle;
    float steer;
    float brake;
    uint16_t engineRPM;
    uint16_t brakesTemperature[4];
    uint8_t tyresSurfaceTemperature[4];
    uint8_t tyresInnerTemperature[4];
    uint16_t engineTemperature;
    float tyresPressure[4];
};

class CarTelemetryData : public TelemetryData<CarTelemetryDataPoint> {};

#endif //F1METER_TELEMETRYDATA_H
