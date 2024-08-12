//JetsonNanoSensorCapture.h
#ifndef JETSONNANOSENSORCAPTURE_H
#define JETSONNANOSENSORCAPTURE_H

#include "ISensorCapture.h"
#include "JetsonNanoHardwareProfiler.h"

class JetsonNanoSensorCapture : public ISensorCapture {
public:
    void capture() override {
        // Capture system statistics using TegraStats
        JetsonNanoHardwareProfiler profiler;
        profilingData = profiler.profileHardware();
    }

    void load() override {
        // Load the captured data into the system
        std::cout << "Jetson Nano Profiling Data Loaded: " << profilingData << std::endl;
    }

private:
    std::string profilingData;  // To store captured data
};

#endif // JETSONNANOSENSORCAPTURE_H
