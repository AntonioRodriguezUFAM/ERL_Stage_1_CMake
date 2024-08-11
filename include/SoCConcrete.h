//2. Define Concrete Implementations for Each Component
//For example, here’s how you might define concrete implementations :



//SoCConcrete.h

#ifndef SOCCONCRETE_H
#define SOCCONCRETE_H

#include "ISoC.h"
#include <iostream>
#include <thread>
#include <chrono>

class SoCConcrete : public ISoC {
public:
    void setup() override {
        std::cout << "Setting up SoC" << std::endl;
    }

    void run() override {
        // Continuous monitoring logic
        while (true) {
            std::cout << "Monitoring SoC performance..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate monitoring interval
        }
    }
};

#endif // SOCCONCRETE_H
