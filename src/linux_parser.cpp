#include <dirent.h>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

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
  DIR *directory = opendir(kProcDirectory.c_str());
  struct dirent *file;
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
  std::string key;  // example MemTotal:
  float value;      // example 3812372
  std::string unit; // example kB
  float memTotal{0.00};
  float memAvailable{0.00};
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
  std::string cpu{"cpu"};
  CPUStates states{};
  std::ifstream filestream("/proc" + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> states.kUser_ >> states.kNice_ >> states.kSystem_ >>
        states.kIdle_ >> states.kIOwait_ >> states.kIRQ_ >> states.kSoftIRQ_;
  }
  return states.Sum();
}

// DONE
long LinuxParser::ActiveJiffies(int pid) {
  std::string line;
  PIDStates states{};
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> states.pid_ >> states.exName >> states.state >> states.euid >>
        states.egid >> states.ppid >> states.pgrp >> states.session >>
        states.tty >> states.tpgid >> states.flags >> states.minflt >>
        states.cminflt >> states.majflt >> states.cmajflt >> states.utime >>
        states.stime >> states.cutime >> states.cstime >> states.counter >>
        states.priority >> states.timeout >> states.itrealvalue >>
        states.starttime >> states.vsize >> states.rss >> states.rlim >>
        states.startcode >> states.endcode >> states.startstack >>
        states.kstkesp >> states.kstkeip >> states.signal >> states.blocked >>
        states.sigignore >> states.sigcatch >> states.wchan >> states.sched >>
        states.sched_priority;
    return states.utime + states.stime;
  } else {
    return 0;
  }
}

// DONE
long LinuxParser::ActiveJiffies() {
  std::string line;
  std::string cpu;
  CPUStates states{};
  std::ifstream filestream("/proc" + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> states.kUser_ >> states.kNice_ >> states.kSystem_ >>
        states.kIdle_ >> states.kIOwait_ >> states.kIRQ_ >> states.kSoftIRQ_;
  }
  return states.Sum() - (states.kIdle_ + states.kIOwait_);
}

// DONE
long LinuxParser::IdleJiffies() {
  std::string line;
  std::string cpu;
  CPUStates states{};
  std::ifstream filestream("/proc" + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> states.kUser_ >> states.kNice_ >> states.kSystem_ >>
        states.kIdle_ >> states.kIOwait_ >> states.kIRQ_ >> states.kSoftIRQ_;
  }

  return states.kIdle_ + states.kIOwait_;
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
  PIDStates states{};
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> states.pid_ >> states.exName >> states.state >> states.euid >>
        states.egid >> states.ppid >> states.pgrp >> states.session >>
        states.tty >> states.tpgid >> states.flags >> states.minflt >>
        states.cminflt >> states.majflt >> states.cmajflt >> states.utime >>
        states.stime >> states.cutime >> states.cstime >> states.counter >>
        states.priority >> states.timeout >> states.itrealvalue >>
        states.starttime >> states.vsize >> states.rss >> states.rlim >>
        states.startcode >> states.endcode >> states.startstack >>
        states.kstkesp >> states.kstkeip >> states.signal >> states.blocked >>
        states.sigignore >> states.sigcatch >> states.wchan >> states.sched >>
        states.sched_priority;
    return states.exName;
  } else {
    return "NONE";
  }
}

// DONE
string LinuxParser::Ram(int pid) {
  std::string line;
  std::string value_str{"0"};
  std::string token_str;
  auto token_auto{0};
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatusFilename);
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

// DONE
string LinuxParser::Uid(int pid) {
  std::string line;
  std::string value_str{"NONE"};
  std::string token_str;
  auto token_auto{1};
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatusFilename);
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

// DONE
string LinuxParser::User(int pid) {
  std::string actual_uid{LinuxParser::Uid(pid)};
  std::string user{"None"};
  std::string line;
  std::string tmp;
  std::vector<std::string> tokens{};
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line, ':')) {
      std::istringstream linestream(line);
      while (linestream >> tmp) {
        tokens.push_back(tmp);
      }
    }
  }
  for (unsigned int i = 0; i <= tokens.size(); ++i) {
    if (tokens[i] == actual_uid && tokens[i - 1] != actual_uid) {
      user = tokens[i - 2];
      break;
    }
  }
  return user;
}

// DONE
long int LinuxParser::UpTime(int pid) {
  std::string line;
  PIDStates states{};
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> states.pid_ >> states.exName >> states.state >> states.euid >>
        states.egid >> states.ppid >> states.pgrp >> states.session >>
        states.tty >> states.tpgid >> states.flags >> states.minflt >>
        states.cminflt >> states.majflt >> states.cmajflt >> states.utime >>
        states.stime >> states.cutime >> states.cstime >> states.counter >>
        states.priority >> states.timeout >> states.itrealvalue >>
        states.starttime >> states.vsize >> states.rss >> states.rlim >>
        states.startcode >> states.endcode >> states.startstack >>
        states.kstkesp >> states.kstkeip >> states.signal >> states.blocked >>
        states.sigignore >> states.sigcatch >> states.wchan >> states.sched >>
        states.sched_priority;
    return LinuxParser::UpTime() - states.itrealvalue;
  } else {
    return 1;
  }
}