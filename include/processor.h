#pragma once

#include "linux_parser.h"
#include <vector>

class Processor {
public:
    void AddToVector();
    float Utilization();  // TODO: See src/processor.cpp


  // TODO: Declare any necessary private members
private:
    std::vector<float> cpu_utilization_t {LinuxParser::CpuUtilization()};
    float total_utilization{0};
};

