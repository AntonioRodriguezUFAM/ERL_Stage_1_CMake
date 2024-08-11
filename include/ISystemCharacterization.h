// 2. Define the System Characterization Interface and Concrete Class
//System Characterization will process the data captured by the SensorCaptureConcrete and characterize the system based on the input data.
//This could involve various analyses and computations depending on the system's objectives.

#ifndef ISYSTEMCHARACTERIZATION_H
#define ISYSTEMCHARACTERIZATION_H

class ISystemCharacterization {
public:
    virtual ~ISystemCharacterization() {}
    virtual void characterize() = 0;  // Method to perform system characterization
};

#endif // ISYSTEMCHARACTERIZATION_H
