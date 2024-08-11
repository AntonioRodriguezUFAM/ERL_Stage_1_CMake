

//DataConcrete.h

#ifndef DATACONCRETE_H
#define DATACONCRETE_H


#include "IData.h"
#include <iostream>

class DataConcrete : public IData {
public:
    void setup() override {
        std::cout << "Setting up Data" << std::endl;
    }

    void run() override {
        // Continuous processing logic
        while (true) {
            std::cout << "Running Data..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate processing interval
        }
    }

};

#endif // !DATACONCRETE_H
