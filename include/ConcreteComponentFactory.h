

//4. Define a Concrete Factory
//ConcreteComponentFactory.h


#ifndef CONCRETECOMPONENTFACTORY_H
#define CONCRETECOMPONENTFACTORY_H

#include <iostream>
#include <stdexcept>  // For handling exceptions
#include "IComponentFactory.h"
#include "SoCConcrete.h"
#include "AlgorithmConcrete.h"
#include "DataConcrete.h"
#include "OptimizationConcrete.h"
#include "ConstraintsConcrete.h"
#include "HistoricalDataConcrete.h"
#include "JetsonNanoSensorCapture.h"  // Include the Jetson Nano-specific Sensor Capture
#include "SystemCharacterizationConcrete.h"

// ConcreteComponentFactory class
// This class implements the IComponentFactory interface and provides concrete
// implementations for creating various system components. Each method in this
// factory returns a new instance of a specific concrete class that implements
// the corresponding interface.
//
// The factory integrates with the Jetson Nano hardware platform by using
// JetsonNanoSensorCapture for the sensor capture component.
//
// Error handling is included to throw exceptions if component creation fails.
class ConcreteComponentFactory : public IComponentFactory {
public:
    // Function: createSoC
    // Purpose: Creates and returns an instance of the concrete SoC class.
    // This function logs the creation process and checks for successful allocation.
    ISoC* createSoC() override {
        std::cout << "Creating SoC..." << std::endl;
        ISoC* soc = new (std::nothrow) SoCConcrete();
        if (!soc) {
            throw std::runtime_error("Failed to create SoC");
        }
        return soc;
    }

    // Function: createAlgorithm
    // Purpose: Creates and returns an instance of the concrete Algorithm class.
    // This function logs the creation process and checks for successful allocation.
    IAlgorithm* createAlgorithm() override {
        std::cout << "Creating Algorithm..." << std::endl;
        IAlgorithm* algorithm = new (std::nothrow) AlgorithmConcrete();
        if (!algorithm) {
            throw std::runtime_error("Failed to create Algorithm");
        }
        return algorithm;
    }

    // Function: createData
    // Purpose: Creates and returns an instance of the concrete Data class.
    // This function logs the creation process and checks for successful allocation.
    IData* createData() override {
        std::cout << "Creating Data..." << std::endl;
        IData* data = new (std::nothrow) DataConcrete();
        if (!data) {
            throw std::runtime_error("Failed to create Data");
        }
        return data;
    }

    // Function: createOptimization
    // Purpose: Creates and returns an instance of the concrete Optimization class.
    // This function logs the creation process and checks for successful allocation.
    IOptimization* createOptimization() override {
        std::cout << "Creating Optimization..." << std::endl;
        IOptimization* optimization = new (std::nothrow) OptimizationConcrete();
        if (!optimization) {
            throw std::runtime_error("Failed to create Optimization");
        }
        return optimization;
    }

    // Function: createConstraints
    // Purpose: Creates and returns an instance of the concrete Constraints class.
    // This function logs the creation process and checks for successful allocation.
    IConstraints* createConstraints() override {
        std::cout << "Creating Constraints..." << std::endl;
        IConstraints* constraints = new (std::nothrow) ConstraintsConcrete();
        if (!constraints) {
            throw std::runtime_error("Failed to create Constraints");
        }
        return constraints;
    }

    // Function: createHistoricalData
    // Purpose: Creates and returns an instance of the concrete HistoricalData class.
    // This function logs the creation process and checks for successful allocation.
    IHistoricalData* createHistoricalData() override {
        std::cout << "Creating HistoricalData..." << std::endl;
        IHistoricalData* historicalData = new (std::nothrow) HistoricalDataConcrete();
        if (!historicalData) {
            throw std::runtime_error("Failed to create HistoricalData");
        }
        return historicalData;
    }

      // Function: createSensorCapture
    // Purpose: Creates and returns an instance of the Jetson Nano-specific SensorCapture class.
    // This function logs the creation process and checks for successful allocation.
   ISensorCapture*  createSensorCapture() override {
        std::cout << "Creating Jetson NANO Sensor Capture..." << std::endl;
        ISensorCapture*  sensorCapture = new (std::nothrow) JetsonNanoSensorCapture();
        if (!sensorCapture) {
            throw std::runtime_error("Failed to create Sensor Capture");
        }
        return sensorCapture;
    }

    // Function: createSensorCapture
    // Purpose: Creates and returns an instance of the Jetson Nano-specific SensorCapture class.
    // This function logs the creation process and checks for successful allocation.
   JetsonNanoSensorCapture*  JetsoncreateSensorCapture() override {
        std::cout << "Creating Jetson NANO Sensor Capture..." << std::endl;
        JetsonNanoSensorCapture*  JetsonsensorCapture = new (std::nothrow) JetsonNanoSensorCapture();
        if (!JetsonsensorCapture) {
            throw std::runtime_error("Failed to create Sensor Capture");
        }
        return JetsonsensorCapture;
    }

    // Function: createSystemCharacterization
    // Purpose: Creates and returns an instance of the concrete SystemCharacterization class.
    // This function logs the creation process and checks for successful allocation.
    ISystemCharacterization* createSystemCharacterization() override {
        std::cout << "Creating SystemCharacterization..." << std::endl;
        ISystemCharacterization* systemCharacterization = new (std::nothrow) SystemCharacterizationConcrete();
        if (!systemCharacterization) {
            throw std::runtime_error("Failed to create SystemCharacterization");
        }
        return systemCharacterization;
    }
};

#endif // CONCRETECOMPONENTFACTORY_H
