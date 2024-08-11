//Step 3: Define the EnergySavingFactory
//This factory creates components optimized for energy efficiency.
//EnergySavingFactory.h 


#ifndef ENERGYSAVINGFACTORY_H
#define ENERGYSAVINGFACTORY_H

#include "IComponentFactory.h"
#include "SoCEnergySaving.h"
#include "AlgorithmEnergySaving.h"
#include "DataEnergySaving.h"
#include "OptimizationEnergySaving.h"
#include "ConstraintsEnergySaving.h"
#include "HistoricalDataEnergySaving.h"

class EnergySavingFactory : public IComponentFactory {
public:
    ISoC* createSoC() override {
        return new SoCEnergySaving();
    }

    IAlgorithm* createAlgorithm() override {
        return new AlgorithmEnergySaving();
    }

    IData* createData() override {
        return new DataEnergySaving();
    }

    IOptimization* createOptimization() override {
        return new OptimizationEnergySaving();
    }

    IConstraints* createConstraints() override {
        return new ConstraintsEnergySaving();
    }

    IHistoricalData* createHistoricalData() override {
        return new HistoricalDataEnergySaving();
    }
};

#endif // ENERGYSAVINGFACTORY_H
