//2. Define Concrete Implementations for Each Component
//For example, here�s how you might define concrete implementations :



//SoCConcrete.h

#ifndef SOCCONCRETE_H
#define SOCCONCRETE_H

#include "ISoC.h"
#include "JetsonNanoSensorCapture.h"


class SoCConcrete : public ISoC {
public:
    void run() override {
        // Implementation of running the SoC
<<<<<<< HEAD
        JetsonNanoHardwareProfiler profiler;
        std::string profilingData = profiler.profileHardware();
        std::cout << "Captured Sensor Data: " << profilingData << std::endl;
=======
>>>>>>> 06ba67a782fc6ebd6ffe5bcf594acd23e136bf8c
    }

    void setup() override {
        // Implementation of setup logic
    }

    void sensorCapture() override {
<<<<<<< HEAD
        std::cout << " Start sensor Capture class!! " << std::endl;
=======
>>>>>>> 06ba67a782fc6ebd6ffe5bcf594acd23e136bf8c
        JetsonNanoHardwareProfiler profiler;
        std::string profilingData = profiler.profileHardware();
        std::cout << "Captured Sensor Data: " << profilingData << std::endl;
    }
};


#endif // SOCCONCRETE_H
