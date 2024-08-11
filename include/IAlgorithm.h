
//IAlgorithm.h

#ifndef IALGORITHM_H
#define IALGORITHM_H

class IAlgorithm {
public:
    virtual ~IAlgorithm() {}
    virtual void setup() = 0;
    virtual void run() = 0; // New method for continuous execution
};

#endif // IALGORITHM_H
