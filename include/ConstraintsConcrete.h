
#ifndef CONSTRAINTCONCRETE_H
#define CONSTRAINTCONCRETE_H


#include "IConstraints.h"
#include <iostream>
#include <thread>
#include <chrono>

class ConstraintsConcrete : public IConstraints {
public:
    void setup() override {
        std::cout << "Setting up Constraints" << std::endl;
    }

    void run() override {
        // Continuous processing logic
        while (true) {
            std::cout << "Running Constraints..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate processing interval
        }
    }
};




#endif //CONSTRAINTCONCRETE_H





