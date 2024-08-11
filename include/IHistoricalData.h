

//IHistoricalData.h

#ifndef IHISTORICALDATA_H
#define IHISTORICALDATA_H

class IHistoricalData {
public:
    virtual ~IHistoricalData() {}
    virtual void setup() = 0;
    virtual void run() = 0; // New method for continuous execution
};

#endif // IHISTORICALDATA_H
