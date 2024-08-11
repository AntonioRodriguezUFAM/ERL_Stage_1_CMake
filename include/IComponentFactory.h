//3. Define a Factory Interface
//IComponentFactory.h

#ifndef ICOMPONENTFACTORY_H
#define ICOMPONENTFACTORY_H

#include "ISoC.h"
#include "IAlgorithm.h"
#include "IData.h"
#include "IOptimization.h"
#include "IConstraints.h"
#include "IHistoricalData.h"

class IComponentFactory {
public:
    virtual ~IComponentFactory() {}
    virtual ISoC* createSoC() = 0;
    virtual IAlgorithm* createAlgorithm() = 0;
    virtual IData* createData() = 0;
    virtual IOptimization* createOptimization() = 0;
    virtual IConstraints* createConstraints() = 0;
    virtual IHistoricalData* createHistoricalData() = 0;
};

#endif // ICOMPONENTFACTORY_H
