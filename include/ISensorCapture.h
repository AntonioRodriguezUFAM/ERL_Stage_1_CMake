

//1. Define the System Capture / Loader Interface and Concrete Class
//This part of the system is responsible for capturing the data from the setup componentsand loading it into the system for further processing.
//
//ISensorCapture.h

#ifndef ISENSORCAPTURE_H
#define ISENSORCAPTURE_H

class ISensorCapture {
public:
    virtual ~ISensorCapture() {}
    virtual void capture() = 0;  // Method to capture data from sensors
    virtual void load() = 0;     // Method to load data into the system
};

#endif // ISENSORCAPTURE_H
