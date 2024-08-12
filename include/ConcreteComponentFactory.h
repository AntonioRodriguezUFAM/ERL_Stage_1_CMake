
//4. Define a Concrete Factory
//ConcreteComponentFactory.h


#ifndef CONCRETECOMPONENTFACTORY_H
#define CONCRETECOMPONENTFACTORY_H

#include <iostream>
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
        std::cout << "Create SoC..." << std::endl;
        return new SoCConcrete();
    }
    IAlgorithm* createAlgorithm() override {
        std::cout << "Create Algorithm..." << std::endl;
        return new AlgorithmConcrete();
    }
    IData* createData() override {
        // Return an instance of the concrete Data class
        std::cout << "Create Data..." << std::endl;
        return new DataConcrete();
    }
    IOptimization* createOptimization() override {
        // Return an instance of the concrete Optimization class
        std::cout << "Create Optimization..." << std::endl;
        return new OptimizationConcrete();
    }
    IConstraints* createConstraints() override {
        // Return an instance of the concrete Constraints class
        std::cout << "Create Constraints..." << std::endl;
        return new ConstraintsConcrete();
    }
    IHistoricalData* createHistoricalData() override {
        // Return an instance of the concrete HistoricalData class
        std::cout << "Create HistoricalData..." << std::endl;
        return new HistoricalDataConcrete();
    }
};

#endif // CONCRETECOMPONENTFACTORY_H
