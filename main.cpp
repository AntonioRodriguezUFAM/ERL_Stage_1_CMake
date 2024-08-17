<<<<<<< HEAD

// main.cpp
/*
Explanation:

1 .Signal Handling:
The signalHandler function ensures the program can respond to external signals (like Ctrl+C) by setting the running flag to false, which will stop all threads and allow the program to exit gracefully.

2. Component Creation and Management:
Components are created using std::unique_ptr, which automatically handles memory management. This means you don't have to worry about manually freeing the memory, reducing the risk of memory leaks.

3. Dynamic Casting:
The dynamic cast ensures that sensorCapture is correctly cast to JetsonNanoSensorCapture*. This is necessary if specific functionality of JetsonNanoSensorCapture is required.

4. Running the System:
The SystemManagerConcrete orchestrates the system's operation by running all components in their respective threads. The runSystem method continues until the running flag is set to false.

5. Automatic Memory Management:
By using std::unique_ptr, the program avoids manual memory management. Resources are automatically freed when the unique_ptr objects go out of scope, making the program safer and more reliable.
This version of your main.cpp is well-structured, easy to read, and follows modern C++ practices for memory management and program control.

*/


#include "ConcreteComponentFactory.h"
#include "SystemManagerConcrete.h"
#include <atomic>
#include <csignal>
#include <iostream>
#include <memory> // for unique_ptr

// Global variable to control the running state of the program.
// This variable is accessed by the SystemManagerConcrete class to determine if the system should keep running.
std::atomic<bool> running(true);

// Signal handler function that catches termination signals (e.g., SIGINT and SIGTERM).
// When a termination signal is received, this function sets the running variable to false,
// signaling the system to gracefully shut down.
void signalHandler(int signal) {
    std::cout << "Signal (" << signal << ") received. Shutting down..." << std::endl;
    running = false;
    std::cout <<"Running :"<<running<<std::endl;
}

int main() {
    // Register signal handlers for SIGINT (e.g., triggered by Ctrl+C) and SIGTERM (termination request).
    // This allows the program to respond to these signals by invoking the signalHandler function.
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    // Instantiate the component factory, which will be responsible for creating various system components.
    //IComponentFactory* factory = new ConcreteComponentFactory();


    // Factory creation and component instantiation using unique_ptr
    std::unique_ptr<IComponentFactory> factory = std::make_unique<ConcreteComponentFactory>();// Pass raw pointer to factory

    // Use unique_ptr to manage component lifetimes
    std::unique_ptr<ISoC> soc(factory->createSoC());
    std::unique_ptr<IAlgorithm> algorithm(factory->createAlgorithm());
    std::unique_ptr<IData> data(factory->createData());
    std::unique_ptr<IOptimization> optimization(factory->createOptimization());
    std::unique_ptr<IConstraints> constraints(factory->createConstraints());
    std::unique_ptr<IHistoricalData> historicalData(factory->createHistoricalData());
    std::unique_ptr<ISensorCapture> sensorCapture(factory->createSensorCapture());

    // Dynamic casting for specific sensor capture type
    JetsonNanoSensorCapture* jetsonNanoSensorCapture = dynamic_cast<JetsonNanoSensorCapture*>(sensorCapture.get());
    if (!jetsonNanoSensorCapture) {
        std::cerr << "Failed to cast sensorCapture to JetsonNanoSensorCapture!" << std::endl;
        return -1;  // Handle error appropriately
    }

        std::unique_ptr<ISystemCharacterization> systemCharacterization(factory->createSystemCharacterization());

    // Create and run the system manager
SystemManagerConcrete systemManager(factory.get());
systemManager.runSystem(
    soc.get(), 
    algorithm.get(), 
    data.get(), 
    optimization.get(), 
    constraints.get(), 
    historicalData.get(), 
    sensorCapture.get(), 
    jetsonNanoSensorCapture,
    systemCharacterization.get()
);
    

        std::cout << "System stopped. Exiting program." << std::endl;

    // No need for explicit deletes; unique_ptr will automatically release memory
=======
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

>>>>>>> 06ba67a782fc6ebd6ffe5bcf594acd23e136bf8c
    return 0;
}
