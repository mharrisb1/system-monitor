#pragma once

#include <linux_parser.h>
#include <string>

class Process {
public:
  explicit Process(int pid) : pid_(pid) {}
  int Pid() const { return pid_; }
  std::string User() const;
  std::string Command() const;
  float CpuUtilization() const;
  std::string Ram() const;
  long int UpTime() const;

private:
  int pid_{0};
};
