#pragma once

#include <linux_parser.h>
#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
public:
    explicit Process(int pid) : pid_(pid) {}
    int Pid() {return pid_;}
    std::string User();
    std::string Command();
    float CpuUtilization();
    std::string Ram();
    long int UpTime();
    bool operator<(Process const& a) const;

 private:
    int pid_{0};
};
