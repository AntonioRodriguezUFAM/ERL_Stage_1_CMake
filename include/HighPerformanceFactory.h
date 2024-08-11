//Step 2: Define the HighPerformanceFactory
//This factory creates components optimized for high performance.
//HighPerformanceFactory.h

#ifndef HIGHPERFORMANCEFACTORY_H
#define HIGHPERFORMANCEFACTORY_H

#include "IComponentFactory.h"
#include "SoCHighPerformance.h"
#include "AlgorithmHighPerformance.h"
#include "DataHighPerformance.h"
#include "OptimizationHighPerformance.h"
#include "ConstraintsHighPerformance.h"
#include "HistoricalDataHighPerformance.h"

class HighPerformanceFactory : public IComponentFactory {
public:
    ISoC* createSoC() override {
        return new SoCHighPerformance();
    }

    IAlgorithm* createAlgorithm() override {
        return new AlgorithmHighPerformance();
    }

    IData* createData() override {
        return new DataHighPerformance();
    }

    IOptimization* createOptimization() override {
        return new OptimizationHighPerformance();
    }

    IConstraints* createConstraints() override {
        return new ConstraintsHighPerformance();
    }

    IHistoricalData* createHistoricalData() override {
        return new HistoricalDataHighPerformance();
    }
};

#endif // HIGHPERFORMANCEFACTORY_H
