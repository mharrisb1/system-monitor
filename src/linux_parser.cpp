#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// TODO: Update this to use std::filesystem (bonus)
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE
float LinuxParser::MemoryUtilization() {
    std::string line;
    std::string key;   // example MemTotal:
    float value;       // example 3812372
    std::string unit;  // example kB
    float memTotal {0.00};
    float memAvailable {0.00};
    std::ifstream filestream("/proc" + kMeminfoFilename);
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

// DONE
long LinuxParser::UpTime() {
    float upTime{0.};
    float idleTime{0.};
    std::string line;
    std::ifstream filestream("/proc" + kUptimeFilename);
    if (filestream.is_open()) {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> upTime >> idleTime;
    }
    return static_cast<long>(upTime);
}

// DONE
long LinuxParser::Jiffies() {
    std::string line;
    std::string cpu {"cpu"};
    long user_jif {0};
    long nice_jif {0};
    long sys_jif {0};
    long idle_jif {0};
    long iowait_jif {0};
    long irq_jif {0};
    long softirq_jif {0};
    long sum_jiffies {0};
    std::ifstream filestream("/proc" + kStatFilename);
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

// DONE
long LinuxParser::ActiveJiffies(int pid) {
    std::string line;

    int           pid_;
    char          exName [_POSIX_PATH_MAX];
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

    std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
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

// DONE
long LinuxParser::ActiveJiffies() {
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
    std::ifstream filestream("/proc" + kStatFilename);
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

// DONE
long LinuxParser::IdleJiffies() {
    std::string line;
    std::string cpu;
    long user_jif;
    long nice_jif;
    long sys_jif;
    long idle_jif;
    long iowait_jif;
    long irq_jif;
    long softirq_jif;
    std::ifstream filestream("/proc" + kStatFilename);
    if (filestream.is_open()){
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> cpu >> user_jif >> nice_jif >> sys_jif >> idle_jif
                   >> iowait_jif >> irq_jif >> softirq_jif;
    }

    return idle_jif;
}

// DONE
float LinuxParser::CpuUtilization() {
    return (float)ActiveJiffies() / (float)Jiffies();
}

// DONE
int LinuxParser::TotalProcesses() {
    std::string line;
    std::string str;
    std::string str_int;
    int value{0};
    std::ifstream filestream("/proc" + kStatFilename);
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

// DONE
int LinuxParser::RunningProcesses() {
    std::string line;
    std::string str;
    std::string str_int;
    int value{0};
    std::ifstream filestream("/proc" + kStatFilename);
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

// DONE
string LinuxParser::Command(int pid) {
    std::string line;

    int           pid_;
    char          exName [_POSIX_PATH_MAX];
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

    std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
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

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }