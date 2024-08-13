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
    TegraStatsInfo(const std::string& cmd = "tegrastats --interval 10 &") : command(cmd) {}

    std::string captureData() {
        std::array<char, 200> buffer;
        std::string result;

  /*      std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }*/

      /*  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }*/

        return result;
    }
};

#endif // TEGRA_STATS_INFO_H
