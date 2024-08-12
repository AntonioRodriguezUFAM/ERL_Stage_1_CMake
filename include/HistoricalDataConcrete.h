

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
        int count = 0;
        while (true) {
            std::cout << "Running HistoricalData..."<<count << std::endl;
            count =count + 1;
            std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate processing interval
        }
    }
};


#endif // !HISTORICALDATACONCRETE_H
