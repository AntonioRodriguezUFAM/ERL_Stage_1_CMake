# CMakeList.txt : CMake project for ERL_Stage_1_CMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("ERL_Stage_1_CMake")

# Add source to this project's executable.
add_executable (ERL_Stage_1_CMake "ERL_Stage_1_CMake.cpp"    "include/SystemCharacterizationConcrete.h" "include/ISystemCharacterization.h" "include/ISensorCapture.h" "include/SensorCaptureConcrete.h" "include/ISoC.h" "include/IAlgorithm.h" "include/IOptimization.h" "include/IConstraints.h" "include/IHistoricalData.h" "include/SoCConcrete.h" "include/AlgorithmConcrete.h" "include/DataConcrete.h" "include/OptimizationConcrete.h" "include/ConstraintsConcrete.h" "include/HistoricalDataConcrete.h" "include/IComponentFactory.h" "include/ConcreteComponentFactory.h" "include/HighPerformanceFactory.h" "include/EnergySavingFactory.h" "include/DefaultFactory.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ERL_Stage_1_CMake PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
