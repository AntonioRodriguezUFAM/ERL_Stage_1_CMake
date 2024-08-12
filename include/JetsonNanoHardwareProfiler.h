//JetsonNanoHardwareProfiler.h

#ifndef JETSON_NANO_HARDWARE_PROFILER_H
#define JETSON_NANO_HARDWARE_PROFILER_H

#include "IHardwareProfiler.h"
#include "JetsonNanoInfo.h"
#include "TegraStatsInfo.h"
#include <fstream>
#include <iomanip>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <iostream>

class JetsonNanoHardwareProfiler : public IHardwareProfiler {
public:
    std::string profileHardware() override {
        // Capture system statistics using TegraStats
        TegraStatsInfo tegraStats;
        std::string tegrastatsOutput = tegraStats.captureData();

        // Parse the output into a structured format
        JetsonNanoInfo info = parseTegraStats(tegrastatsOutput);

        // Format the structured data for display or logging
        std::string formattedData = formatJetsonNanoInfo(info);

        // Save the structured data to a CSV file
        const std::string filePath = "jetson_nano_tegrastats.csv";
        exportToCSV(info, filePath);

        // Display the formatted data
        std::cout << "Formatted Data: " << formattedData << std::endl;

        // Optionally return the formatted string
        return formattedData;
    }

private:
    JetsonNanoInfo parseTegraStats(const std::string& output) {
        // Regular expressions to match different metrics
        std::regex ram_pattern("RAM (\\d+)/(\\d+)MB");
        std::regex lfb_pattern("lfb (\\d+)x(\\d+)MB");
        std::regex swap_pattern("SWAP (\\d+)/(\\d+)MB");
        std::regex cached_pattern("cached (\\d+)MB");
        std::regex iram_pattern("IRAM (\\d+)/([\\d]+)kB\\(lfb ([\\d]+)kB\\)");
        std::regex cpu_pattern("CPU \\[(\\d+)%@(\\d+),(\\d+)%@(\\d+),(\\d+)%@(\\d+),(\\d+)%@(\\d+)\\]");
        std::regex emcgr3d_freq_pattern("EMC_FREQ (\\d+)% GR3D_FREQ (\\d+)%");
        std::regex temp_pattern("PLL@([\\d.]+)C CPU@([\\d.]+)C PMIC@([\\d.]+)C GPU@([\\d.]+)C AO@([\\d.]+)C thermal@([\\d.]+)C");

        std::smatch matches;
        JetsonNanoInfo info;

        // Parse RAM usage
        if (std::regex_search(output, matches, ram_pattern) && matches.size() >= 3) {
            info.RAM_In_Use_MB = std::stoi(matches[1]);
            info.Total_RAM_MB = std::stoi(matches[2]);
        }

        // Parse Largest Free Block (LFB) size
        if (std::regex_search(output, matches, lfb_pattern) && matches.size() >= 3) {
            info.LFB_Size = std::stoi(matches[1]);
            info.Block_Max_MB = std::stoi(matches[2]);
        }

        // Parse SWAP usage
        if (std::regex_search(output, matches, swap_pattern) && matches.size() >= 3) {
            info.SWAP_In_Use_MB = std::stoi(matches[1]);
            info.Total_SWAP_MB = std::stoi(matches[2]);
        }

        // Parse cached memory
        if (std::regex_search(output, matches, cached_pattern) && matches.size() >= 2) {
            info.Cached_MB = std::stoi(matches[1]);
        }

        // Parse IRAM usage
        if (std::regex_search(output, matches, iram_pattern) && matches.size() == 4) {
            info.used_IRAM_kB = std::stoi(matches[1].str());
            info.total_IRAM_kB = std::stoi(matches[2].str());
            info.lfb_kB = std::stoi(matches[3].str());
        }

        // Parse CPU utilization and frequencies
        if (std::regex_search(output, matches, cpu_pattern) && matches.size() >= 9) {
            info.CPU1_Utilization_Percent = std::stoi(matches[1]);
            info.CPU1_Frequency_MHz = std::stoi(matches[2]);
            info.CPU2_Utilization_Percent = std::stoi(matches[3]);
            info.CPU2_Frequency_MHz = std::stoi(matches[4]);
            info.CPU3_Utilization_Percent = std::stoi(matches[5]);
            info.CPU3_Frequency_MHz = std::stoi(matches[6]);
            info.CPU4_Utilization_Percent = std::stoi(matches[7]);
            info.CPU4_Frequency_MHz = std::stoi(matches[8]);
        }

        // Parse EMC and GR3D frequencies
        if (std::regex_search(output, matches, emcgr3d_freq_pattern) && matches.size() >= 3) {
            info.EMC_Frequency_Percent = std::stoi(matches[1]);
            info.GR3D_Frequency_Percent = std::stoi(matches[2]);
        }

        // Parse temperatures
        if (std::regex_search(output, matches, temp_pattern) && matches.size() >= 7) {
            info.PLL_Temperature_C = std::stof(matches[1].str());
            info.CPU_Temperature_C = std::stof(matches[2].str());
            info.PMIC_Temperature_C = std::stof(matches[3].str());
            info.GPU_Temperature_C = std::stof(matches[4].str());
            info.AO_Temperature_C = std::stof(matches[5].str());
            info.Thermal_Temperature_C = std::stof(matches[6].str());
        }

        return info;
    }

    std::string formatJetsonNanoInfo(const JetsonNanoInfo& info) {
        // Format the parsed data into a readable string
        std::stringstream ss;
        ss << "Jetson Nano Profiling Data:\n";
        ss << "RAM Usage: " << info.RAM_In_Use_MB << "/" << info.Total_RAM_MB << " MB\n";
        ss << "Largest Free Block (LFB): " << info.LFB_Size << "x" << info.Block_Max_MB << " MB\n";
        ss << "SWAP Usage: " << info.SWAP_In_Use_MB << "/" << info.Total_SWAP_MB << " MB\n";
        ss << "Cached: " << info.Cached_MB << " MB\n";
        ss << "IRAM Usage: " << info.used_IRAM_kB << "/" << info.total_IRAM_kB << " kB (LFB " << info.lfb_kB << " kB)\n";
        ss << "CPU Utilization: " << "\n";
        ss << "  CPU1: " << info.CPU1_Utilization_Percent << "% @ " << info.CPU1_Frequency_MHz << " MHz\n";
        ss << "  CPU2: " << info.CPU2_Utilization_Percent << "% @ " << info.CPU2_Frequency_MHz << " MHz\n";
        ss << "  CPU3: " << info.CPU3_Utilization_Percent << "% @ " << info.CPU3_Frequency_MHz << " MHz\n";
        ss << "  CPU4: " << info.CPU4_Utilization_Percent << "% @ " << info.CPU4_Frequency_MHz << " MHz\n";
        ss << "EMC Frequency: " << info.EMC_Frequency_Percent << "%, GR3D Frequency: " << info.GR3D_Frequency_Percent << "%\n";
        ss << "Temperatures (Celsius): \n";
        ss << "  PLL: " << info.PLL_Temperature_C << " C, CPU: " << info.CPU_Temperature_C << " C\n";
        ss << "  PMIC: " << info.PMIC_Temperature_C << " C, GPU: " << info.GPU_Temperature_C << " C\n";
        ss << "  AO: " << info.AO_Temperature_C << " C, Thermal: " << info.Thermal_Temperature_C << " C\n";

        return ss.str();
    }

    void exportToCSV(const JetsonNanoInfo& info, const std::string& filePath) {
        std::ofstream file(filePath, std::ios::app);

        // Get the current time as a string
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
        std::string currentTime = ss.str();

        // Write header only if file is newly created
        if (file.tellp() == 0) {
            file << "Timestamp,RAM_In_Use_MB,Total_RAM_MB,"
                << "LFB_Size,Block_Max_MB,"
                << "SWAP_In_Use_MB,Total_SWAP_MB,Cached_MB,"
                << "used_IRAM_kB,total_IRAM_kB, lfb_kB,"
                << "CPU1_Utilization_Percent,CPU1_Frequency_MHz,"
                << "CPU2_Utilization_Percent,CPU2_Frequency_MHz,"
                << "CPU3_Utilization_Percent,CPU3_Frequency_MHz,"
                << "CPU4_Utilization_Percent,CPU4_Frequency_MHz,"
                << "EMC_Frequency_Percent,GR3D_Frequency_Percent,"
                << "PLL_Temperature_C,CPU_Temperature_C,PMIC_Temperature_C,GPU_Temperature_C,AO_Temperature_C,Thermal_Temperature_C\n";
        }

        // Append new data with timestamp
        file << currentTime << "," << info.RAM_In_Use_MB << "," << info.Total_RAM_MB << ","
            << info.LFB_Size << "," << info.Block_Max_MB << ","
            << info.SWAP_In_Use_MB << "," << info.Total_SWAP_MB << "," << info.Cached_MB << ","
            << info.used_IRAM_kB << "," << info.total_IRAM_kB << "," << info.lfb_kB << ","
            << info.CPU1_Utilization_Percent << "," << info.CPU1_Frequency_MHz << ","
            << info.CPU2_Utilization_Percent << "," << info.CPU2_Frequency_MHz << ","
            << info.CPU3_Utilization_Percent << "," << info.CPU3_Frequency_MHz << ","
            << info.CPU4_Utilization_Percent << "," << info.CPU4_Frequency_MHz << ","
            << info.EMC_Frequency_Percent << "," << info.GR3D_Frequency_Percent << ","
            << info.PLL_Temperature_C << "," << info.CPU_Temperature_C << ","
            << info.PMIC_Temperature_C << "," << info.GPU_Temperature_C << ","
            << info.AO_Temperature_C << "," << info.Thermal_Temperature_C << "\n";

        file.close();
    }
};

#endif // JETSON_NANO_HARDWARE_PROFILER_H
