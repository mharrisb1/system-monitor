#include "../testkit/tester.hpp"
#include <fstream>
#include <sstream>
#include <cstdio>

float MemoryUtilization() {
    std::string line;
    std::string key;   // example MemTotal:
    float value;       // example 3812372
    std::string unit;  // example kB
    float memTotal {0.00};
    float memAvailable {0.00};
    std::ifstream filestream("/Users/michaelharris/cpp-projects/system-monitor/test/linux_parser_tests/proc/meminfo");
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> value >> unit) {
                if (key == "MemTotal:") {
                    memTotal = value;
                } else if (key == "MemAvailable:") {
                    memAvailable = value;
                }
            }
        }
    }
    return 1 - (memAvailable / memTotal);
}

int main() {
    /* Test 1
     *
     * INPUT:           test/linux_parser_tests/proc/meminfo
     * EXPECTED OUTPUT: 0.073545
     *
     */
    Test<float> test(MemoryUtilization(), 0.07354476);
    printf("Looking for %f and got %f", test.CheckValue(), test.TestValue());

    if (test.TestValue() - test.CheckValue() < 0.001) {
        return 0;  // pass
    } else {
        return 1;  // fail
    }

}