// SystemManagerConcrete.h
#ifndef SYSTEMMANAGERCONCRETE_H
#define SYSTEMMANAGERCONCRETE_H

#include "ISystemManager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>
#include <atomic>

class SystemManagerConcrete : public ISystemManager {
public:
    void runSystem(ISoC* soc, IAlgorithm* algorithm, IData* data,
        IOptimization* optimization, IConstraints* constraints,
        IHistoricalData* historicalData, ISystemCharacterization* systemCharacterization) {

        const int NUM_THREADS = 6;
        pthread_t threads[NUM_THREADS];

        // Create threads for each system component
        pthread_create(&threads[0], nullptr, runSoC, static_cast<void*>(soc));
        pthread_create(&threads[1], nullptr, runAlgorithm, static_cast<void*>(algorithm));
        pthread_create(&threads[2], nullptr, runData, static_cast<void*>(data));
        pthread_create(&threads[3], nullptr, runOptimization, static_cast<void*>(optimization));
        pthread_create(&threads[4], nullptr, runConstraints, static_cast<void*>(constraints));
        pthread_create(&threads[5], nullptr, runHistoricalData, static_cast<void*>(historicalData));

        // Main loop for continuous data capture and system characterization
        while (running) {
            soc->sensorCapture(); // Capture data from the sensors through the SoC
            systemCharacterization->characterize(); // Perform system characterization based on the data

            std::cout << "Running Capture, Characterize..." << std::endl;

            // Sleep for a fixed interval before the next cycle (simulates periodic monitoring)
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Capture data every 1 second
        }

        // Join threads (this won't be reached since the loop runs indefinitely)
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], nullptr);
        }
    }

};

#endif // SYSTEMMANAGERCONCRETE_H
