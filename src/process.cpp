#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// DONE
float Process::CpuUtilization() const {
    return (float)LinuxParser::ActiveJiffies(this->pid_) / (float)LinuxParser::Jiffies();
}

// DONE
string Process::Command() const {
    return LinuxParser::Command(this->pid_);
}

// DONE
string Process::Ram() const {
    return LinuxParser::Ram(this->pid_);
}

// DONE
string Process::User() const {
    return LinuxParser::User(this->pid_);
}

// DONE
long int Process::UpTime() const {
    return LinuxParser::UpTime(this->pid_);
}

//// TODO: Overload the "less than" comparison operator for Process objects
//// REMOVE: [[maybe_unused]] once you define the function
//bool Process::operator<(Process const& a[[maybe_unused]]) const {this->CpuUtilization() > a.CpuUtilization()}