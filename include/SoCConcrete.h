//2. Define Concrete Implementations for Each Component
//For example, here’s how you might define concrete implementations :



//SoCConcrete.h

#ifndef SOCCONCRETE_H
#define SOCCONCRETE_H

#include "ISoC.h"
#include "JetsonNanoSensorCapture.h"


class SoCConcrete : public ISoC {
public:
    void run() override {
        // Implementation of running the SoC
    }

    void setup() override {
        // Implementation of setup logic
    }

    void sensorCapture() override {
        JetsonNanoHardwareProfiler profiler;
        std::string profilingData = profiler.profileHardware();
        std::cout << "Captured Sensor Data: " << profilingData << std::endl;
    }
};


#endif // SOCCONCRETE_H
