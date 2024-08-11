

//HistoricalDataConcrete.h

#ifndef HISTORICALDATACONCRETE_H
#define HISTORICALDATACONCRETE_H


#include "IHistoricalData.h"
#include <iostream>
#include <thread>
#include <chrono>

class HistoricalDataConcrete : public IHistoricalData {
public:
    void setup() override {
        std::cout << "Setting up HistoricalData" << std::endl;
    }

    void run() override {
        // Continuous processing logic
        while (true) {
            std::cout << "Running HistoricalData..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate processing interval
        }
    }
};


#endif // !HISTORICALDATACONCRETE_H
