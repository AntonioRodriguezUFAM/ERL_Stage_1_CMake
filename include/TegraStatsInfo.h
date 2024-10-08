#ifndef TEGRA_STATS_INFO_H
#define TEGRA_STATS_INFO_H

#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>


class TegraStatsInfo {
private:
    std::string command;

public:
    
    TegraStatsInfo(const std::string& cmd = "tegrastats --interval 1000") : command(cmd) {std::cout << " Step 00: Running Tegrastats..."<< std::endl;}
    
    std::string captureData() {
        std::cout << "Step 02: Running Tegrastats Data Capture ..."<< std::endl;
        std::array<char, 200> buffer;
        
        std::string result;
        

        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }

        if(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
            //std::cout <<"STEP 01: Buffer!!"<<std::endl;
        }
        std::cout << "Result"<< result<<std::endl;
        
        return result;
    }

    

};

#endif // TEGRA_STATS_INFO_H
