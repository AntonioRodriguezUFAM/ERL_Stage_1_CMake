// SystemManagerConcrete.h

/*

Explanation of the Code:

1 .Thread Management:
The class SystemManagerConcrete is responsible for managing different components of the system, each running in its own thread.
The runSystem method sets up these threads, allowing each component to run concurrently.

2. Component Execution:
Each component (SoC, Algorithm, Data, etc.) has its logic encapsulated in a specific thread function (e.g., runSoC, runAlgorithm).
The threads check the global running flag to determine when they should exit.

3. Thread Creation:
The createThread function handles the creation of threads and includes error checking to ensure that the threads are successfully created.

4. Main Loop:
The main loop in runSystem continuously runs system characterization and sensor data capture until the running flag is set to false.
The loop includes a sleep interval to simulate periodic monitoring and avoid busy-waiting.

5. Graceful Shutdown:
When the running flag is set to false, the main loop exits, and the threads are joined (i.e., the program waits for them to complete).
Each thread prints a message when it exits, which helps in debugging and ensures that all threads terminate properly.

6. Factory Management:
The factory is stored as a member of the SystemManagerConcrete class, allowing it to be used for dynamic component creation.
This detailed explanation and comments in the code should help you or others understand the flow and purpose of each part of the system, making it easier to maintain and debug.


*/
// This file now manages the entire flow, including when to capture sensor data:

#ifndef SYSTEMMANAGERCONCRETE_H
#define SYSTEMMANAGERCONCRETE_H
#include "ISystemManager.h"
#include <iostream>
#include <pthread.h>
#include <chrono>
#include <csignal>
#include <atomic>
#include <memory>  // For std::unique_ptr

// The 'running' variable controls the execution of the system. 
// It's defined elsewhere (e.g., in 'main.cpp') and used to stop the system gracefully.
extern std::atomic<bool> running;  

// SystemManagerConcrete class manages the overall system, including the execution of various components.
class SystemManagerConcrete : public ISystemManager {
public:

    // Constructor: Initializes the system manager with a factory for creating components.
    SystemManagerConcrete(IComponentFactory* factory) 
        : factory(factory) {}  // Use initializer list for factory

    // Function to run all system components. Each component runs in its own thread.
/*     void runSystem(ISoC* soc, IAlgorithm* algorithm, IData* data,
        IOptimization* optimization, IConstraints* constraints,
        IHistoricalData* historicalData, ISensorCapture* sensorCapture,JetsonNanoSensorCapture*  JetsonNanoSensorCapture,
        ISystemCharacterization* systemCharacterization) override { */

            // Function to run all system components. Each component runs in its own thread.
    void runSystem(ISoC* soc, IAlgorithm* algorithm, IData* data,
                   IOptimization* optimization, IConstraints* constraints,
                   IHistoricalData* historicalData, ISensorCapture* sensorCapture,
                   JetsonNanoSensorCapture* jetsonNanoSensorCapture,
                   ISystemCharacterization* systemCharacterization
                   ) override {

        const int NUM_THREADS = 7;  // Number of threads for the system components.
        pthread_t threads[NUM_THREADS];  // Array to hold thread IDs.

  
        // The main thread can perform other tasks here or simply wait for the system to be stopped.
        // In this case, we assume the main thread is responsible for running the system characterization in a loop.

      
        // Create threads for the various system components.
        createThread(&threads[0], runSoC, soc, "SoC");
        createThread(&threads[1], runAlgorithm, algorithm, "Algorithm");
        createThread(&threads[2], runData, data, "Data");
        createThread(&threads[3], runOptimization, optimization, "Optimization");
        createThread(&threads[4], runConstraints, constraints, "Constraints");
        createThread(&threads[5], runHistoricalData, historicalData, "Historical Data");


        // Main loop for managing overall system behavior.

   // Main loop for managing overall system behavior.
    while (running) {
        systemCharacterization->characterize();  // Perform system characterization.
        std::cout << "Capturing sensor data..." << std::endl;
        sensorCapture->capture();  //  Capture sensor data 
        std::this_thread::sleep_for(std::chrono::seconds(10));  // Sleep for 10 seconds.
}

        // Join threads to ensure they complete before the program exits.
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], nullptr);
        }
    }
private:
   // Helper function to create a thread and handle errors.
    void createThread(pthread_t* thread, void* (*func)(void*), void* arg, const std::string& name) {
        if (pthread_create(thread, nullptr, func, arg) != 0) {
            std::cerr << "Error creating thread for " << name << std::endl;
        }
    }

    // Static function to run the SoC component in a separate thread.
    static void* runSoC(void* arg) {
        ISoC* soc = static_cast<ISoC*>(arg);
         while (running) {
        soc->run(); // Execute the SoC logic.
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Small sleep to prevent busy-waiting
         }
         std::cout << "Exiting runSoC thread." << std::endl;
        return nullptr;
    }

    // Static function to run the Algorithm component in a separate thread.
    static void* runAlgorithm(void* arg) {
        IAlgorithm* algorithm = static_cast<IAlgorithm*>(arg);
         while (running) {
        algorithm->run(); // Execute the Algorithm logic.
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Small sleep to prevent busy-waiting
         }
         std::cout << "Exiting runAlgorithm thread." << std::endl;
        return nullptr;
    }

    // Static function to run the Data component in a separate thread.
    static void* runData(void* arg) {
        IData* data = static_cast<IData*>(arg);
         while (running) {
        data->run();   // Execute the Data logic.
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Small sleep to prevent busy-waiting
         }
          std::cout << "Exiting runData thread." << std::endl;
        return nullptr;
    }

    // Static function to run the Optimization component in a separate thread.
    static void* runOptimization(void* arg) {
        IOptimization* optimization = static_cast<IOptimization*>(arg);
         while (running) {
        optimization->run();   // Execute the Optimization logic.
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Small sleep to prevent busy-waiting
         }
        std::cout << "Exiting runOptimization thread." << std::endl;
        return nullptr;  // Execute the Constraints logic.
    }

    // Static function to run the Constraints component in a separate thread.
    static void* runConstraints(void* arg) {
        IConstraints* constraints = static_cast<IConstraints*>(arg);
         while (running) {
        constraints->run();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Small sleep to prevent busy-waiting
         }
          std::cout << "Exiting runConstraints thread." << std::endl;
        return nullptr;
    }

    // Static function to run the Historical Data component in a separate thread.
    static void* runHistoricalData(void* arg) {
        IHistoricalData* historicalData = static_cast<IHistoricalData*>(arg);
         while (running) {
        historicalData->run();  // Execute the Historical Data logic.
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Small sleep to prevent busy-waiting
         }
          std::cout << "Exiting runHistoricalData thread." << std::endl;
        return nullptr;
    }

    // Static function to run the Sensor Capture component in a separate thread.
    // Continuously captures sensor data while the system is running.
    static void* runSensorCapture(void* arg) {
        ISensorCapture* sensorCapture = static_cast<ISensorCapture*>(arg);
        while (running) {
            sensorCapture->capture();  // Continuously capture sensor data.
            std::cout<<" Run Sensor Capture: "<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Small sleep to prevent busy-waiting
        }
         std::cout << "Exiting runSensorCapture thread." << std::endl;
        return nullptr;
    }


    IComponentFactory* factory;  // Store the factory if needed for dynamic component management.
};

#endif // SYSTEMMANAGERCONCRETE_H
