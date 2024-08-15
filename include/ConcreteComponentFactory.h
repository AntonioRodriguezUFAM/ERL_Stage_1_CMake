
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
#include "SystemCharacterizationConcrete.h"

// Include the headers for the concrete classes of Data, Optimization, Constraints, HistoricalData, SystemCharacterization

class ConcreteComponentFactory : public IComponentFactory {
public:
    ISoC* createSoC() override {
        std::cout << "Create SoC..." << std::endl;
        return new SoCConcrete();  // Return an instance of the concrete SoC class
    }

    IAlgorithm* createAlgorithm() override {
        std::cout << "Create Algorithm..." << std::endl;
        return new AlgorithmConcrete();  // Return an instance of the concrete Algorithm class
    }

    IData* createData() override {
        std::cout << "Create Data..." << std::endl;
        return new DataConcrete();  // Return an instance of the concrete Data class
    }

    IOptimization* createOptimization() override {
        std::cout << "Create Optimization..." << std::endl;
        return new OptimizationConcrete();  // Return an instance of the concrete Optimization class
    }

    IConstraints* createConstraints() override {
        std::cout << "Create Constraints..." << std::endl;
        return new ConstraintsConcrete();  // Return an instance of the concrete Constraints class
    }

    IHistoricalData* createHistoricalData() override {
        std::cout << "Create HistoricalData..." << std::endl;
        return new HistoricalDataConcrete();  // Return an instance of the concrete HistoricalData class
    }

    ISystemCharacterization* createSystemCharacterization() override {
        std::cout << "Create SystemCharacterization..." << std::endl;
        return new SystemCharacterizationConcrete();  // Return an instance of the concrete SystemCharacterization class
    }
};

#endif // CONCRETECOMPONENTFACTORY_H

