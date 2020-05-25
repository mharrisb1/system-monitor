#include <string>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

float Process::CpuUtilization() const {
  return (float)LinuxParser::ActiveJiffies(this->pid_) /
         (float)LinuxParser::Jiffies();
}

string Process::Command() const { return LinuxParser::Command(this->pid_); }

string Process::Ram() const { return LinuxParser::Ram(this->pid_); }

string Process::User() const { return LinuxParser::User(this->pid_); }

long int Process::UpTime() const { return LinuxParser::UpTime(this->pid_); }
