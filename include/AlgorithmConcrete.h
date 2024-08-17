

//AlgorithmConcrete.h

#ifndef ALGORITHMCONCRETE_H
#define ALGORITHMCONCRETE_H

#include "IAlgorithm.h"
#include <iostream>
#include <thread>
#include <chrono>

class AlgorithmConcrete : public IAlgorithm {
public:
    void setup() override {
        std::cout << "Setting up Algorithm" << std::endl;
    }

    void run() override {
        // Continuous processing logic
        while (true) {
            //std::cout << "Running Algorithm..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate processing interval
        }
    }
};

#endif // ALGORITHMCONCRETE_H
