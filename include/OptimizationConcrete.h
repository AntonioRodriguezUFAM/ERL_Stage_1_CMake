
//OptimizationConcrete.h


#ifndef OPTIMIZATIONCONCRETE_H
#define OPTIMIZATIONCONCRETE_H

#include "IOptimization.h"
#include <iostream>
#include <thread>
#include <chrono>

class OptimizationConcrete : public IOptimization {
public:
    void setup() override {
        std::cout << "Setting up Optimization" << std::endl;
    }

    void run() override {
        // Continuous processing logic
        while (true) {
            std::cout << "Running Optimization..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate processing interval
        }
    }
};


#endif // OPTIMIZATIONCONCRETE_H
