//IHardwareProfiler.h

#ifndef IHARDWAREPROFILER_H
#define IHARDWAREPROFILER_H

#include <string>

class IHardwareProfiler {
public:
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~IHardwareProfiler() {}

    // Pure virtual function to be overridden by derived classes for profiling hardware
    virtual std::string profileHardware() = 0;
};

#endif // IHARDWAREPROFILER_H
