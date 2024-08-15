// main.cpp
#include "ConcreteComponentFactory.h"
#include "SystemManagerConcrete.h"
#include <csignal>
#include <atomic>
#include <iostream>

std::atomic<bool> running(true);

void signalHandler(int signal) {
    std::cout << "Termination signal (" << signal << ") received. Exiting..." << std::endl;
    running = false;
}

int main() {
    // Register signal handler for graceful shutdown
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    // Instantiate the factory
    IComponentFactory* factory = new ConcreteComponentFactory();

    // Create components using the factory
  // Create components using the factory
    ISoC* soc = factory->createSoC();
    if (!soc) {
        std::cerr << "Failed to create SoC component" << std::endl;
        delete factory;
        return -1;
    }

    IAlgorithm* algorithm = factory->createAlgorithm();
    if (!algorithm) {
        std::cerr << "Failed to create Algorithm component" << std::endl;
        delete soc; delete factory;
        return -1;
    }

    IData* data = factory->createData();
    if (!data) {
        std::cerr << "Failed to create Data component" << std::endl;
        delete soc; delete algorithm; delete factory;
        return -1;
    }

    IOptimization* optimization = factory->createOptimization();
    if (!optimization) {
        std::cerr << "Failed to create Optimization component" << std::endl;
        delete soc; delete algorithm; delete data; delete factory;
        return -1;
    }

    IConstraints* constraints = factory->createConstraints();
    if (!constraints) {
        std::cerr << "Failed to create Constraints component" << std::endl;
        delete soc; delete algorithm; delete data; delete optimization; delete factory;
        return -1;
    }

    IHistoricalData* historicalData = factory->createHistoricalData();
    if (!historicalData) {
        std::cerr << "Failed to create HistoricalData component" << std::endl;
        delete soc; delete algorithm; delete data; delete optimization; delete constraints; delete factory;
        return -1;
    }

    ISystemCharacterization* systemCharacterization = factory->createSystemCharacterization();
    if (!systemCharacterization) {
        std::cerr << "Failed to create SystemCharacterization component" << std::endl;
        delete soc; delete algorithm; delete data; delete optimization; delete constraints; delete historicalData; delete factory;
        return -1;
    }
    // Run the system
    // Create System Manager and run the system
    SystemManagerConcrete systemManager(factory);
    systemManager.run();

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
