//Step 1: Define the run Method in Each Component Interface
//Each component interface should have a run method that will be called repeatedly to perform continuous monitoring or processing.Here’s how you can define the run method in the interfaces.


#ifndef ISOC_H
#define ISOC_H

class ISoC {
public:
    virtual ~ISoC() {}
    virtual void setup() = 0;
    virtual void run() = 0; // New method for continuous execution

    // Pure virtual function for profiling hardware
    virtual std::string profileHardware() = 0;
};

#endif // ISOC_H
