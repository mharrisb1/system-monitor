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
    [[nodiscard]] int Pid() const {return pid_;}
    [[nodiscard]] std::string User() const;
    [[nodiscard]] std::string Command() const;
    [[nodiscard]] float CpuUtilization() const;
    [[nodiscard]] std::string Ram() const;
    [[nodiscard]] long int UpTime() const;
//    bool operator<(Process const& a) const;

 private:
    int pid_{0};
};
