
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
    return 0;
}
