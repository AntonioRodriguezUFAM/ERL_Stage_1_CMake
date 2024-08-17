//JetsonNanoSensorCapture.h
// file and let it focus only on capturing data when requested

#ifndef JETSONNANOSENSORCAPTURE_H
#define JETSONNANOSENSORCAPTURE_H

#include "ISensorCapture.h"
#include "JetsonNanoHardwareProfiler.h"

#include <fstream>  // For file handling
#include <iostream>
#include <chrono>  // For time 



#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>


class JetsonNanoSensorCapture : public ISensorCapture {
public:
    // Implement the capture function to collect hardware profiling data
    void capture() override {
        
        std::cout <<" Create Jetson Nano 2024ooo...."<<std::endl;
        //TegraStatsInfo tegraStatsInfo;


        //TegraStatsInfo tegraStats;
        TegraStatsInfo tegraStats;
        std::cout <<"STEP 01"<<std::endl;
        std::string tegrastatsOutput = tegraStats.captureData();
         std::cout <<"STEP 02"<<std::endl;
            
        std::cout << tegrastatsOutput << std::endl;
         std::cout <<"STEP 03"<<std::endl;
        // Create an instance of the hardware profiler
        JetsonNanoHardwareProfiler profiler;
         std::cout <<"STEP 04"<<std::endl;
        
        // Open the CSV file for writing
        std::ofstream csvFile("jetson_nano_data.csv", std::ios::app);
        if (!csvFile.is_open()) {
            std::cerr << "Failed to open CSV file for writing." << std::endl;
            return;
        }

        // Write the CSV header if the file is new
        if (csvFile.tellp() == 0) {
            csvFile << "Timestamp,ProfilingData" << std::endl;
        }
        
        // Capture system statistics using TegraStats
        std::string profilingData = profiler.profileHardware();
        std::cout << profilingData << " Captured Data!" << std::endl;

        // Get the current timestamp
           auto now = std::chrono::system_clock::now();
           auto now_c = std::chrono::system_clock::to_time_t(now);
            std::string timestamp = std::ctime(&now_c);
            timestamp.pop_back(); // Remove trailing newline

            // Write the profiling data to the CSV file
            csvFile << timestamp << "," << profilingData << std::endl;

            // Sleep for 3 seconds to simulate processing interval
        //    std::this_thread::sleep_for(std::chrono::seconds(3));
        

        // Close the CSV file when done
        csvFile.close();
    }

    void load() override {
     // Load the captured data into the system (this might not be necessary if data is directly saved to CSV)
        std::cout << "Jetson Nano Profiling Data Loaded: " << profilingData << std::endl;
    }


private:
    std::string profilingData;  // To store captured data
};

#endif // JETSONNANOSENSORCAPTURE_H
