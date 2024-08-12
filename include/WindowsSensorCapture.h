//WindowsSensorCapture.h

#ifndef WINDOWSSENSORCAPTURE_H
#define WINDOWSSENSORCAPTURE_H

#include "ISensorCapture.h"
#include "WindowsHardwareProfiler.h"  // Assuming you have a similar profiler for Windows

class WindowsSensorCapture : public ISensorCapture {
public:
    void capture() override {
        // Capture system statistics using Windows Performance Recorder (WPR)
        WindowsHardwareProfiler profiler;
        profilingData = profiler.profileHardware();
    }

    void load() override {
        // Load the captured data into the system
        std::cout << "Windows Profiling Data Loaded: " << profilingData << std::endl;
    }

private:
    std::string profilingData;  // To store captured data
};

#endif // WINDOWSSENSORCAPTURE_H
