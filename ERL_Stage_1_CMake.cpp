// ERL_Stage_1_CMake.cpp : Defines the entry point for the application.
// 3. Integrate with the Main Application
//Finally, integrate these new classes into the main application, allowing the system to capture, load, and characterize data in a continuous loop or based on user input.
// 
//



using namespace std;

#include "include/ConcreteComponentFactory.h"
#include "include/SensorCaptureConcrete.h"
#include "include/SystemCharacterizationConcrete.h"

//#include "include/HighPerformanceFactory.h"
////#include "include/EnergySavingFactory.h"
//#include "include/DefaultFactory.h"
#include "include/ConcreteComponentFactory.h"


#include <thread>
#include <iostream>

// Function to run the main system components in separate threads
void runSystem(ISoC* soc, IAlgorithm* algorithm, IData* data,
    IOptimization* optimization, IConstraints* constraints,
    IHistoricalData* historicalData, ISensorCapture* sensorCapture,
    ISystemCharacterization* systemCharacterization) {

    // Run each component in its own thread for concurrent execution
    std::thread socThread(&ISoC::run, soc);
    std::thread algorithmThread(&IAlgorithm::run, algorithm);
    std::thread dataThread(&IData::run, data);
    std::thread optimizationThread(&IOptimization::run, optimization);
    std::thread constraintsThread(&IConstraints::run, constraints);
    std::thread historicalDataThread(&IHistoricalData::run, historicalData);

    // Main loop for continuous data capture and system characterization
    while (true) {
        sensorCapture->capture();        // Capture data from the sensors
        sensorCapture->load();           // Load the captured data into the system
        systemCharacterization->characterize(); // Perform system characterization based on the data

        // Sleep for a fixed interval before the next cycle (simulates periodic monitoring)
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Example interval of 5 seconds
    }

    // Join threads (this won't be reached since the loop runs indefinitely)
    socThread.join();
    algorithmThread.join();
    dataThread.join();
    optimizationThread.join();
    constraintsThread.join();
    historicalDataThread.join();
}

int main(int argc, char* argv[]) {


   // User-defined configuration determines which factory to use
    //std::string config = argc > 1 ? argv[1] : "default"; // Get configuration from command line or default to "default"

    // Directly set the configuration to "default"
    //std::string config = "default";
   
    //IComponentFactory* factory = nullptr;

    // //Select factory based on user-defined configuration
    //if (config == "high_performance") {
    //    factory = new HighPerformanceFactory();  // Factory for high-performance configuration
    //}
    //else if (config == "energy_saving") {
    //    factory = new EnergySavingFactory();     // Factory for energy-saving configuration
    //}
    //else {
    //    factory = new DefaultFactory();          // Default factory configuration
    //}


       // Directly instantiate the DefaultFactory
    IComponentFactory* factory = new ConcreteComponentFactory();

    if (factory == nullptr) {
        std::cerr << "Factory initialization failed! Exiting program." << std::endl;
        return EXIT_FAILURE;
    }


    // Create components using the selected factory
    ISoC* soc = factory->createSoC();
    IAlgorithm* algorithm = factory->createAlgorithm();
    IData* data = factory->createData();
    IOptimization* optimization = factory->createOptimization();
    IConstraints* constraints = factory->createConstraints();
    IHistoricalData* historicalData = factory->createHistoricalData();

    // Create instances of sensor capture and system characterization
    SensorCaptureConcrete sensorCapture;
    SystemCharacterizationConcrete systemCharacterization;

    // Setup each component before starting the system
    soc->setup();
    algorithm->setup();
    data->setup();
    optimization->setup();
    constraints->setup();
    historicalData->setup();

    // Start running the system components along with the sensor capture and system characterization
    runSystem(soc, algorithm, data, optimization, constraints, historicalData, &sensorCapture, &systemCharacterization);

    // Clean up memory (note: this code won't be reached due to the infinite loop)
    delete soc;
    delete algorithm;
    delete data;
    delete optimization;
    delete constraints;
    delete historicalData;
    delete factory;

    return 0;
}