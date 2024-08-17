// ISystemManager.h
#ifndef ISYSTEMMANAGER_H
#define ISYSTEMMANAGER_H

#include "ISoC.h"
#include "IAlgorithm.h"
#include "IData.h"
#include "IOptimization.h"
#include "IConstraints.h"
#include "IHistoricalData.h"
#include "ISensorCapture.h"
#include "JetsonNanoSensorCapture.h"  // Include the Jetson Nano-specific Sensor Capture
#include "ISystemCharacterization.h"

class ISystemManager {
public:
    virtual ~ISystemManager() {}
    virtual void runSystem(ISoC* soc, IAlgorithm* algorithm, IData* data,
        IOptimization* optimization, IConstraints* constraints,
        IHistoricalData* historicalData, ISensorCapture* sensorCapture,JetsonNanoSensorCapture* JetsonNanoSensorCapture,
        ISystemCharacterization* systemCharacterization) = 0;
};

#endif // ISYSTEMMANAGER_H



