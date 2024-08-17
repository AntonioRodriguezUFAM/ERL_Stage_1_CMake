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
<<<<<<< HEAD
#include "JetsonNanoSensorCapture.h"  // Include the Jetson Nano-specific Sensor Capture
=======
>>>>>>> 06ba67a782fc6ebd6ffe5bcf594acd23e136bf8c
#include "ISystemCharacterization.h"

class ISystemManager {
public:
    virtual ~ISystemManager() {}
    virtual void runSystem(ISoC* soc, IAlgorithm* algorithm, IData* data,
        IOptimization* optimization, IConstraints* constraints,
<<<<<<< HEAD
        IHistoricalData* historicalData, ISensorCapture* sensorCapture,JetsonNanoSensorCapture* JetsonNanoSensorCapture,
=======
        IHistoricalData* historicalData, ISensorCapture* sensorCapture,
>>>>>>> 06ba67a782fc6ebd6ffe5bcf594acd23e136bf8c
        ISystemCharacterization* systemCharacterization) = 0;
};

#endif // ISYSTEMMANAGER_H
<<<<<<< HEAD



=======
>>>>>>> 06ba67a782fc6ebd6ffe5bcf594acd23e136bf8c
