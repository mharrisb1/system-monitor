#include "testkit/tester.hpp"
#include <fstream>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <vector>

namespace LinuxParser {

    float MemoryUtilization() {
        std::string line;
        std::string key;   // example MemTotal:
        float value;       // example 3812372
        std::string unit;  // example kB
        float memTotal{0.00};
        float memAvailable{0.00};
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

    long Jiffies() {
        std::string line;
        std::string cpu;
        long user_jif;
        long nice_jif;
        long sys_jif;
        long idle_jif;
        long iowait_jif;
        long irq_jif;
        long softirq_jif;
        long sum_jiffies {0};
        std::ifstream filestream("../test/proc/stat");
        if (filestream.is_open()){
            std::getline(filestream, line);
            std::istringstream linestream(line);
            linestream >> cpu >> user_jif >> nice_jif >> sys_jif >> idle_jif
                       >> iowait_jif >> irq_jif >> softirq_jif;
        }

        std::vector<long int> jiffies {user_jif, nice_jif, sys_jif, idle_jif, iowait_jif,
                                       irq_jif, softirq_jif, sum_jiffies};

        for (auto j: jiffies) {
            sum_jiffies += j;
        }

        return sum_jiffies;
    }

    long IdleJiffies() {
        std::string line;
        std::string cpu;
        long user_jif;
        long nice_jif;
        long sys_jif;
        long idle_jif;
        long iowait_jif;
        long irq_jif;
        long softirq_jif;
        std::ifstream filestream("../test/proc/stat");
        if (filestream.is_open()){
            std::getline(filestream, line);
            std::istringstream linestream(line);
            linestream >> cpu >> user_jif >> nice_jif >> sys_jif >> idle_jif
                       >> iowait_jif >> irq_jif >> softirq_jif;
        }

        return idle_jif;
    }

    long ActiveJiffies() {
        std::string line;
        std::string cpu;
        long user_jif;
        long nice_jif;
        long sys_jif;
        long idle_jif;
        long iowait_jif;
        long irq_jif;
        long softirq_jif;
        long sum_jiffies {0};
        std::ifstream filestream("../test/proc/stat");
        if (filestream.is_open()){
            std::getline(filestream, line);
            std::istringstream linestream(line);
            linestream >> cpu >> user_jif >> nice_jif >> sys_jif >> idle_jif
                       >> iowait_jif >> irq_jif >> softirq_jif;
        }

        std::vector<long int> jiffies {user_jif, nice_jif, sys_jif, iowait_jif,
                                       irq_jif, softirq_jif, sum_jiffies};

        for (auto j: jiffies) {
            sum_jiffies += j;
        }

        return sum_jiffies;
    }

    int TotalProcesses() {
        std::string line;
        std::string str;
        std::string str_int;
        int value{0};
        std::ifstream filestream("../test/proc/stat");
        if (filestream.is_open()) {
            while (std::getline(filestream, line)) {
                std::istringstream linestream(line);
                while (linestream >> str >> str_int) {
                    if (str == "processes") {
                        value = std::stoi(str_int);
                    }
                }
            }
        }
        return value;
    }

    int RunningProcesses() {
        std::string line;
        std::string str;
        std::string str_int;
        int value{0};
        std::ifstream filestream("../test/proc/stat");
        if (filestream.is_open()) {
            while (std::getline(filestream, line)) {
                std::istringstream linestream(line);
                while (linestream >> str >> str_int) {
                    if (str == "procs_running") {
                        value = std::stoi(str_int);
                    }
                }
            }
        }
        return value;
    }

}  // namespace LinuxParser

int main() {
    Test<float> test1(LinuxParser::MemoryUtilization(), 0.07354476);
    printf("1: Looking for %f and got %f\n", test1.CheckValue(), test1.TestValue());

    Test<long int> test2(LinuxParser::UpTime(), 32831);
    printf("2: Looking for %ld and got %ld\n", test2.CheckValue(), test2.TestValue());

    Test<long int> test3(LinuxParser::Jiffies(), 559594);
    printf("3: Looking for %ld and got %ld\n", test3.CheckValue(), test3.TestValue());

    Test<long int> test4(LinuxParser::IdleJiffies(), 552713);
    printf("4: Looking for %ld and got %ld\n", test4.CheckValue(), test4.TestValue());

    Test<long int> test5(LinuxParser::ActiveJiffies(), 6881);
    printf("5: Looking for %ld and got %ld\n", test5.CheckValue(), test5.TestValue());

    Test<int> test6(LinuxParser::TotalProcesses(), 1870);
    printf("6: Looking for %i and got %i\n", test6.CheckValue(), test6.TestValue());

    Test<int> test7(LinuxParser::RunningProcesses(), 2);
    printf("6: Looking for %i and got %i\n", test7.CheckValue(), test7.TestValue());

    // Check that all tests pass
    if (test1.TestValue() - test1.CheckValue() < 0.001 &&
        test2.Pass() &&
        test3.Pass() &&
        test4.Pass() &&
        test5.Pass() &&
        test6.Pass()) {
        return 0;  // pass
    } else {
        return 1;  // fail
    }

}