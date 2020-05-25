#pragma once

#include "linux_parser.h"
#include <vector>

class Processor {
public:
  [[nodiscard]] float Utilization() const;

private:
  float cpu_utilization{LinuxParser::CpuUtilization()};
};
