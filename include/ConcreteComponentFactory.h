
//4. Define a Concrete Factory
//ConcreteComponentFactory.h


#ifndef CONCRETECOMPONENTFACTORY_H
#define CONCRETECOMPONENTFACTORY_H

#include "IComponentFactory.h"
#include "SoCConcrete.h"
#include "AlgorithmConcrete.h"
#include "DataConcrete.h"
#include "OptimizationConcrete.h"
#include "ConstraintsConcrete.h"
#include "HistoricalDataConcrete.h"

// Include the headers for the concrete classes of Data, Optimization, Constraints, HistoricalData

class ConcreteComponentFactory : public IComponentFactory {
public:
    ISoC* createSoC() override {
        return new SoCConcrete();
    }
    IAlgorithm* createAlgorithm() override {
        return new AlgorithmConcrete();
    }
    IData* createData() override {
        // Return an instance of the concrete Data class
        return new DataConcrete();
    }
    IOptimization* createOptimization() override {
        // Return an instance of the concrete Optimization class
        return new OptimizationConcrete();
    }
    IConstraints* createConstraints() override {
        // Return an instance of the concrete Constraints class
        return new ConstraintsConcrete();
    }
    IHistoricalData* createHistoricalData() override {
        // Return an instance of the concrete HistoricalData class
        return new HistoricalDataConcrete();
    }
};

#endif // CONCRETECOMPONENTFACTORY_H
