#include "testkit/tester.hpp"
#include <fstream>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <vector>
#include <map>

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

        return idle_jif + iowait_jif;
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

        std::vector<long int> active_jiffies {user_jif, nice_jif, sys_jif,
                                       irq_jif, softirq_jif, sum_jiffies};

        for (auto j: active_jiffies) {
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

    float CpuUtilization() {
        return (float)ActiveJiffies() / (float)Jiffies();
    }

    long ActiveJiffies(int pid) {
        std::string line;

        int           pid_;
        std::string   exName;
        char          state;
        unsigned      euid,
                      egid;
        int           ppid;
        int           pgrp;
        int           session;
        int           tty;
        int           tpgid;
        unsigned int  flags;
        unsigned int  minflt;
        unsigned int  cminflt;
        unsigned int  majflt;
        unsigned int  cmajflt;
        int           utime;    // 16
        int           stime;    // 17
        int		      cutime;
        int           cstime;
        int           counter;
        int           priority;
        unsigned int  timeout;
        unsigned int  itrealvalue;
        int           starttime;
        unsigned int  vsize;
        unsigned int  rss;
        unsigned int  rlim;
        unsigned int  startcode;
        unsigned int  endcode;
        unsigned int  startstack;
        unsigned int  kstkesp;
        unsigned int  kstkeip;
        int		      signal;
        int           blocked;
        int           sigignore;
        int           sigcatch;
        unsigned int  wchan;
        int		      sched,
                      sched_priority;

        std::ifstream filestream("../test/proc/" + std::to_string(pid) + "/stat");
        if (filestream.is_open()) {
            std::getline(filestream, line);
            std::istringstream linestream(line);
            linestream >> pid_ >> exName >> state >> euid >> egid >> ppid >> pgrp >> session >> tty >> tpgid >> flags
                       >> minflt >> cminflt >> majflt >> cmajflt >> utime >> stime >> cutime >> cstime >> counter
                       >> priority >> timeout >> itrealvalue >> starttime >> vsize >> rss >> rlim >> startcode
                       >> endcode >> startstack >> kstkesp >> kstkeip >> signal >> blocked >> sigignore >> sigcatch
                       >> wchan >> sched >> sched_priority;
            return utime + stime;
        } else {
            return 0;
        }
    }

    std::string Command(int pid) {
        std::string line;

        int           pid_;
        std::string   exName;
        char          state;
        unsigned      euid,
                      egid;
        int           ppid;
        int           pgrp;
        int           session;
        int           tty;
        int           tpgid;
        unsigned int  flags;
        unsigned int  minflt;
        unsigned int  cminflt;
        unsigned int  majflt;
        unsigned int  cmajflt;
        int           utime;    // 16
        int           stime;    // 17
        int		      cutime;
        int           cstime;
        int           counter;
        int           priority;
        unsigned int  timeout;
        unsigned int  itrealvalue;
        int           starttime;
        unsigned int  vsize;
        unsigned int  rss;
        unsigned int  rlim;
        unsigned int  startcode;
        unsigned int  endcode;
        unsigned int  startstack;
        unsigned int  kstkesp;
        unsigned int  kstkeip;
        int		      signal;
        int           blocked;
        int           sigignore;
        int           sigcatch;
        unsigned int  wchan;
        int		      sched,
                      sched_priority;

        std::ifstream filestream("../test/proc/" + std::to_string(pid) + "/stat");
        if (filestream.is_open()) {
            std::getline(filestream, line);
            std::istringstream linestream(line);
            linestream >> pid_ >> exName >> state >> euid >> egid >> ppid >> pgrp >> session >> tty >> tpgid >> flags
                       >> minflt >> cminflt >> majflt >> cmajflt >> utime >> stime >> cutime >> cstime >> counter
                       >> priority >> timeout >> itrealvalue >> starttime >> vsize >> rss >> rlim >> startcode
                       >> endcode >> startstack >> kstkesp >> kstkeip >> signal >> blocked >> sigignore >> sigcatch
                       >> wchan >> sched >> sched_priority;
            return exName;
        } else {
            return "NONE";
        }
    }

    std::string Ram(int pid) {
        std::string line;
        std::string value_str{"NONE"};
        std::string token_str;
        auto token_auto{0};
        std::ifstream filestream("../test/proc/" + std::to_string(pid) + "/status");
        if (filestream.is_open()) {
            while (std::getline(filestream, line)) {
                std::istringstream linestream(line);
                while (linestream >> token_str >> token_auto) {
                    if (token_str == "VmSize:") {
                        value_str = std::to_string(token_auto);
                    }
                }
            }
        }
        return value_str;
    }

    std::string Uid(int pid) {
        std::string line;
        std::string value_str{"NONE"};
        std::string token_str;
        auto token_auto{1};
        std::ifstream filestream("../test/proc/" + std::to_string(pid) + "/status");
        if (filestream.is_open()) {
            while (std::getline(filestream, line)) {
                std::istringstream linestream(line);
                while (linestream >> token_str >> token_auto) {
                    if (token_str == "Uid:") {
                        value_str = std::to_string(token_auto);
                    }
                }
            }
        }
        return value_str;
    }

    std::string User(int pid) {
        std::string actual_uid{LinuxParser::Uid(pid)};
        std::string user{"None"};
        std::string line;
        std::string tmp;
        std::vector<std::string> tokens{};
        std::ifstream filestream("../test/proc/passwd");
        if (filestream.is_open()) {
            while (std::getline(filestream, line, ':')) {
                std::istringstream linestream(line);
                while (linestream >> tmp) {
                        tokens.push_back(tmp);
                    }
                }
            }
        for (int i = 0; i < tokens.size(); ++i) {
            if (tokens[i] == actual_uid && tokens[i-1] != actual_uid) {
                user = tokens[i-2];
                break;
            }
        }
        return user;
    }

    long UpTime(int pid) {
        std::string line;

        int           pid_;
        std::string   exName;
        char          state;
        unsigned      euid,
                egid;
        int           ppid;
        int           pgrp;
        int           session;
        int           tty;
        int           tpgid;
        unsigned int  flags;
        unsigned int  minflt;
        unsigned int  cminflt;
        unsigned int  majflt;
        unsigned int  cmajflt;
        int           utime;    // 16
        int           stime;    // 17
        int		      cutime;
        int           cstime;
        int           counter;
        int           priority;
        unsigned int  timeout;
        unsigned int  itrealvalue;
        int           starttime;
        unsigned int  vsize;
        unsigned int  rss;
        unsigned int  rlim;
        unsigned int  startcode;
        unsigned int  endcode;
        unsigned int  startstack;
        unsigned int  kstkesp;
        unsigned int  kstkeip;
        int		      signal;
        int           blocked;
        int           sigignore;
        int           sigcatch;
        unsigned int  wchan;
        int		      sched,
                sched_priority;

        std::ifstream filestream("../test/proc/" + std::to_string(pid) + "/stat");
        if (filestream.is_open()) {
            std::getline(filestream, line);
            std::istringstream linestream(line);
            linestream >> pid_ >> exName >> state >> euid >> egid >> ppid >> pgrp >> session >> tty >> tpgid >> flags
                       >> minflt >> cminflt >> majflt >> cmajflt >> utime >> stime >> cutime >> cstime >> counter
                       >> priority >> timeout >> itrealvalue >> starttime >> vsize >> rss >> rlim >> startcode
                       >> endcode >> startstack >> kstkesp >> kstkeip >> signal >> blocked >> sigignore >> sigcatch
                       >> wchan >> sched >> sched_priority;
            return utime;
        } else {
            return 1;
        }
    }

}  // namespace LinuxParser

int main() {
    Test<float> test1(LinuxParser::MemoryUtilization(), 0.07354476);
    printf("1: Looking for %f and got %f\n", test1.CheckValue(), test1.TestValue());

    Test<long int> test2(LinuxParser::UpTime(), 32831);
    printf("2: Looking for %ld and got %ld\n", test2.CheckValue(), test2.TestValue());

    Test<long int> test3(LinuxParser::Jiffies(), 559594);
    printf("3: Looking for %ld and got %ld\n", test3.CheckValue(), test3.TestValue());

    Test<long int> test4(LinuxParser::IdleJiffies(), 552816);
    printf("4: Looking for %ld and got %ld\n", test4.CheckValue(), test4.TestValue());

    Test<long int> test5(LinuxParser::ActiveJiffies(), 6778);
    printf("5: Looking for %ld and got %ld\n", test5.CheckValue(), test5.TestValue());

    Test<int> test6(LinuxParser::TotalProcesses(), 1870);
    printf("6: Looking for %i and got %i\n", test6.CheckValue(), test6.TestValue());

    Test<int> test7(LinuxParser::RunningProcesses(), 2);
    printf("7: Looking for %i and got %i\n", test7.CheckValue(), test7.TestValue());

    Test<double> test8(LinuxParser::CpuUtilization(), 0.01211235);
    printf("8: Looking for %f and got %f\n", test8.CheckValue(), test8.TestValue());

    Test<long> test9(LinuxParser::ActiveJiffies(1), 3236);
    printf("9: Looking for %ld and got %ld\n", test9.CheckValue(), test9.TestValue());

    Test<long> test10(LinuxParser::ActiveJiffies(10), 0);
    printf("10: Looking for %ld and got %ld\n", test10.CheckValue(), test10.TestValue());

    Test<long> test11(LinuxParser::ActiveJiffies(103), 0);
    printf("11: Looking for %ld and got %ld\n", test11.CheckValue(), test11.TestValue());

    Test<std::string> test12(LinuxParser::Command(1), "(systemd)");
    printf("12: Looking for %s and got %s\n", test12.CheckValue().c_str(), test12.TestValue().c_str());

    Test<std::string> test13(LinuxParser::Command(10), "(rcu_preempt)");
    printf("13: Looking for %s and got %s\n", test13.CheckValue().c_str(), test13.TestValue().c_str());

    Test<std::string> test14(LinuxParser::Command(103), "(scsi_eh_0)");
    printf("14: Looking for %s and got %s\n", test14.CheckValue().c_str(), test14.TestValue().c_str());

    Test<std::string> test15(LinuxParser::Ram(1), "33768");
    printf("15: Looking for %s and got %s\n", test15.CheckValue().c_str(), test15.TestValue().c_str());

    Test<std::string> test16(LinuxParser::Ram(10), "NONE");
    printf("16: Looking for %s and got %s\n", test16.CheckValue().c_str(), test16.TestValue().c_str());

    Test<std::string> test17(LinuxParser::Uid(1), "0");
    printf("17: Looking for %s and got %s\n", test17.CheckValue().c_str(), test17.TestValue().c_str());

    Test<std::string> test18(LinuxParser::User(1), "root");
    printf("18: Looking for %s and got %s\n", test18.CheckValue().c_str(), test18.TestValue().c_str());

    Test<long> test19(LinuxParser::UpTime(1), 2338);
    printf("19: Looking for %ld and got %ld\n", test19.CheckValue(), test19.TestValue());


    // Check that all tests pass
    if (test1.TestValue() - test1.CheckValue() < 0.001 &&
        test2.Pass() &&
        test3.Pass() &&
        test4.Pass() &&
        test5.Pass() &&
        test6.Pass() &&
        test7.Pass() &&
        test8.TestValue() - test8.CheckValue() < 0.001 &&
        test9.Pass() &&
        test10.Pass() &&
        test11.Pass() &&
        test12.Pass() &&
        test13.Pass() &&
        test14.Pass() &&
        test15.Pass() &&
        test16.Pass() &&
        test17.Pass() &&
        test18.Pass()) {
        return 0;  // pass
    } else {
        return 1;  // fail
    }

}