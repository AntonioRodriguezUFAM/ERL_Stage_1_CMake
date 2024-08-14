//Step 1: Define the run Method in Each Component Interface
//Each component interface should have a run method that will be called repeatedly to perform continuous monitoring or processing.Here�s how you can define the run method in the interfaces.


#ifndef ISOC_H
#define ISOC_H

class ISoC {
public:
    virtual ~ISoC() {}
    virtual void run() = 0;
    virtual void setup() = 0;
    virtual void captureSensorData() = 0;  // New method for capturing sensor data
};


#endif // ISOC_H
