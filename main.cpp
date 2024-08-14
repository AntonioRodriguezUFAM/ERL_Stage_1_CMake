// main.cpp
#include "ConcreteComponentFactory.h"
#include "SystemManagerConcrete.h"

int main() {
    // Instantiate the factory
    IComponentFactory* factory = new ConcreteComponentFactory();

    // Create components using the factory
    ISoC* soc = factory->createSoC();
    IAlgorithm* algorithm = factory->createAlgorithm();
    IData* data = factory->createData();
    IOptimization* optimization = factory->createOptimization();
    IConstraints* constraints = factory->createConstraints();
    IHistoricalData* historicalData = factory->createHistoricalData();
    ISystemCharacterization* systemCharacterization = factory->createSystemCharacterization();

    // Run the system
    runSystem(soc, algorithm, data, optimization, constraints, historicalData, systemCharacterization);

    // Clean up memory (note: this code won't be reached due to the infinite loop)
    delete soc;
    delete algorithm;
    delete data;
    delete optimization;
    delete constraints;
    delete historicalData;
    delete systemCharacterization;
    delete factory;

    return 0;
}
