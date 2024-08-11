
//IOptimization.h

#ifndef IOPTIMIZATION_H
#define IOPTIMIZATION_H

class IOptimization {
public:
    virtual ~IOptimization() {}
    virtual void setup() = 0;
    virtual void run() = 0; // New method for continuous execution
};

#endif // IOPTIMIZATION_H
