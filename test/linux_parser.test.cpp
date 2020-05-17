#include "testkit/tester.hpp"
#include <fstream>
#include <sstream>
#include <cstdio>
#include <iostream>

float MemoryUtilization() {
    std::string line;
    std::string key;   // example MemTotal:
    float value;       // example 3812372
    std::string unit;  // example kB
    float memTotal {0.00};
    float memAvailable {0.00};
    std::ifstream filestream("../test/proc/meminfo");
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

long UpTime() {
    float upTime{0.};
    float idleTime{0.};
    std::string line;
    std::ifstream filestream("../test/proc/uptime");
    if (filestream.is_open()) {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> upTime >> idleTime;
    }
    return upTime;
}

int main() {
    /* Test 1
     *
     * INPUT:           test/linux_parser_tests/proc/meminfo
     * EXPECTED OUTPUT: 0.073545
     *
     */
    Test<float> test1(MemoryUtilization(), 0.07354476);
    printf("Looking for %f and got %f\n", test1.CheckValue(), test1.TestValue());

    /* Test 2
     *
     * INPUT:           test/linux_parser_tests/proc/uptime
     * EXPECTED OUTPUT: 34406
     *
     */
    Test<long int> test2(UpTime(), 32831);
    printf("Looking for %ld and got %ld\n", test2.CheckValue(), test2.TestValue());

    if (test1.TestValue() - test1.CheckValue() < 0.001 &&
        test2.Pass()) {
        return 0;  // pass
    } else {
        return 1;  // fail
    }

}