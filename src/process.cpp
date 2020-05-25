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
float Process::CpuUtilization() {
    return (float)LinuxParser::ActiveJiffies(this->pid_) / (float)LinuxParser::Jiffies();
}

// DONE
string Process::Command() {
    return LinuxParser::Command(this->pid_);
}

// DONE
string Process::Ram() {
    return LinuxParser::Ram(this->pid_);
}

// DONE
string Process::User() {
    return LinuxParser::User(this->pid_);
}

// DONE
long int Process::UpTime() {
    return LinuxParser::UpTime(this->pid_);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }