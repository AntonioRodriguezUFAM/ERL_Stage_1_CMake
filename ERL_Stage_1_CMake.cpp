// ERL_Stage_1_CMake.cpp : Defines the entry point for the application.
// 3. Integrate with the Main Application
//Finally, integrate these new classes into the main application, allowing the system to capture, load, and characterize data in a continuous loop or based on user input.
// 
//



using namespace std;

#define _CRT_SECURE_NO_WARNINGS

#include "include/ConcreteComponentFactory.h"
#include "include/SensorCaptureConcrete.h"
#include "include/SystemCharacterizationConcrete.h"

//#include "include/HighPerformanceFactory.h"
////#include "include/EnergySavingFactory.h"
//#include "include/DefaultFactory.h"
#include "include/ConcreteComponentFactory.h"

#include "include/WindowsSensorCapture.h"
#include "include/JetsonNanoSensorCapture.h"



// ERL_Stage_1_CMake.cpp : Defines the entry point for the application.
// 3. Integrate with the Main Application
// Finally, integrate these new classes into the main application, allowing the system to capture, load, and characterize data in a continuous loop or based on user input.
#include <pthread.h>
#include <iostream>
#include <unistd.h>

// Define thread wrapper functions for each component
void* runSoC(void* arg) {
    ISoC* soc = static_cast<ISoC*>(arg);
    soc->run();
    return nullptr;
}

void* runAlgorithm(void* arg) {
    IAlgorithm* algorithm = static_cast<IAlgorithm*>(arg);
    algorithm->run();
    return nullptr;
}

void* runData(void* arg) {
    IData* data = static_cast<IData*>(arg);
    data->run();
    return nullptr;
}

void* runOptimization(void* arg) {
    IOptimization* optimization = static_cast<IOptimization*>(arg);
    optimization->run();
    return nullptr;
}

void* runConstraints(void* arg) {
    IConstraints* constraints = static_cast<IConstraints*>(arg);
    constraints->run();
    return nullptr;
}

void* runHistoricalData(void* arg) {
    IHistoricalData* historicalData = static_cast<IHistoricalData*>(arg);
    historicalData->run();
    return nullptr;
}

void* runSensorCapture(void* arg) {
    ISensorCapture* sensorCapture = static_cast<ISensorCapture*>(arg);
    while (true) {
        sensorCapture->capture();
        sensorCapture->load();
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Example interval of 10 seconds
    }
    return nullptr;
}


void runSystem(ISoC* soc, IAlgorithm* algorithm, IData* data,
    IOptimization* optimization, IConstraints* constraints,
    IHistoricalData* historicalData, ISensorCapture* sensorCapture,
    ISystemCharacterization* systemCharacterization) {

    const int NUM_THREADS = 7;
    pthread_t threads[NUM_THREADS];

    // Create threads for each system component
    pthread_create(&threads[0], nullptr, runSoC, static_cast<void*>(soc));
    pthread_create(&threads[1], nullptr, runAlgorithm, static_cast<void*>(algorithm));
    pthread_create(&threads[2], nullptr, runData, static_cast<void*>(data));
    pthread_create(&threads[3], nullptr, runOptimization, static_cast<void*>(optimization));
    pthread_create(&threads[4], nullptr, runConstraints, static_cast<void*>(constraints));
    pthread_create(&threads[5], nullptr, runHistoricalData, static_cast<void*>(historicalData));

    // Create thread for sensor capture (capture method)
    pthread_create(&threads[6], nullptr, runSensorCapture, static_cast<void*>(sensorCapture));


    // Main loop for continuous data capture and system characterization
    while (true) {
       // sensorCapture->capture();        // Capture data from the sensors
        //sensorCapture->load();           // Load the captured data into the system
        systemCharacterization->characterize(); // Perform system characterization based on the data

        std::cout << "Running Capture, Load, Characterize..." << std::endl;

        // Sleep for a fixed interval before the next cycle (simulates periodic monitoring)
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Example interval of 10 seconds
    }

    // Join threads (this won't be reached since the loop runs indefinitely)
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], nullptr);
    }
}

int main(int argc, char* argv[]) {
    // Platform-specific sensor capture initialization
   /*ISensorCapture* sensorCapture = nullptr;

    std::cout<< " Start JetsonNanoSensorCapture"<<std::endl;
    sensorCapture = new JetsonNanoSensorCapture();
    std::cout<<"SensorCapture: " << sensorCapture<<std::endl;   
    */ 




    // Instantiate the factory
    IComponentFactory* factory = new ConcreteComponentFactory();

    if (!factory) {
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
    ISensorCapture* sensorCapture = factory->createSensorCapture();  // Use factory to create sensor capture

    // Create system characterization instance
    ISystemCharacterization* systemCharacterization = new SystemCharacterizationConcrete();

    // Setup each component before starting the system
    std::cout << "Setting up each component..." << std::endl;
    soc->setup();
    algorithm->setup();
    data->setup();
    optimization->setup();
    constraints->setup();
    historicalData->setup();

    std::cout << "Starting system..." << std::endl;

    // Start running the system components along with sensor capture and system characterization
    runSystem(soc, algorithm, data, optimization, constraints, historicalData, sensorCapture, systemCharacterization);

    // Clean up memory (note: this code won't be reached due to the infinite loop)
    delete soc;
    delete algorithm;
    delete data;
    delete optimization;
    delete constraints;
    delete historicalData;
    delete sensorCapture;
    delete systemCharacterization;
    delete sensorCapture;
    delete factory;

    return 0;
}
