
//IData.h

#ifndef IDATA_H
#define IDATA_H

class IData {
public:
    virtual ~IData() {}
    virtual void setup() = 0;
    virtual void run() = 0; // New method for continuous execution
};

#endif // IDATA_H
