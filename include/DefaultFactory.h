//Step 4: Define the DefaultFactory
//This factory creates components that provide a balanced configuration.

//DefaultFactory.h

#ifndef DEFAULTFACTORY_H
#define DEFAULTFACTORY_H

#include "IComponentFactory.h"
#include "SoCDefault.h"
#include "AlgorithmDefault.h"
#include "DataDefault.h"
#include "OptimizationDefault.h"
#include "ConstraintsDefault.h"
#include "HistoricalDataDefault.h"

class DefaultFactory : public IComponentFactory {
public:
    ISoC* createSoC() override {
        return new SoCDefault();
    }

    IAlgorithm* createAlgorithm() override {
        return new AlgorithmDefault();
    }

    IData* createData() override {
        return new DataDefault();
    }

    IOptimization* createOptimization() override {
        return new OptimizationDefault();
    }

    IConstraints* createConstraints() override {
        return new ConstraintsDefault();
    }

    IHistoricalData* createHistoricalData() override {
        return new HistoricalDataDefault();
    }
};

#endif // DEFAULTFACTORY_H
