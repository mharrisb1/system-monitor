#include <cstddef>
#include <set>
#include <string>
#include <unistd.h>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// DONE
Processor &System::Cpu() { return cpu_; }

// DONE
vector<Process> &System::Processes() {
    this->processes_.clear();
  for (int i : this->pids_) {
    Process process{i};
    this->processes_.push_back(process);
  }
  std::sort(this->processes_.begin(), this->processes_.end(),
            [](Process a, Process b) {
              return a.CpuUtilization() > b.CpuUtilization();
            });
  return this->processes_;
}

// DONE
std::string System::Kernel() { return LinuxParser::Kernel(); }

// DONE
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// DONE
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// DONE
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// DONE
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// DONE
long int System::UpTime() { return LinuxParser::UpTime(); }