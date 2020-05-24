#pragma once

#include "linux_parser.h"
#include <vector>

class Processor {
public:
    float Utilization();

private:
    void AddToVector();
    std::vector<float> cpu_utilization_t {LinuxParser::CpuUtilization()};
    float total_utilization{0};
};

