#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// DONE
Processor& System::Cpu() {
    return cpu_;
}

// DONE
vector<Process>& System::Processes() {
    vector<int> pids {LinuxParser::Pids()};
    for (int i: pids) {
        Process process{i};
        this->processes_.push_back(process);
    }
    return this->processes_;
}

// DONE
std::string System::Kernel() {
    return LinuxParser::Kernel();
}

// DONE
float System::MemoryUtilization() {
    return LinuxParser::MemoryUtilization();
}

// DONE
std::string System::OperatingSystem() {
    return LinuxParser::OperatingSystem();
}

// DONE
int System::RunningProcesses() {
    return LinuxParser::RunningProcesses();
}

// DONE
int System::TotalProcesses() {
    return LinuxParser::TotalProcesses();
}

// DONE
long int System::UpTime() {
    return LinuxParser::UpTime();
}