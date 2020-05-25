#pragma once

#include "linux_parser.h"
#include <vector>

class Processor {
public:
    float Utilization();

private:
    float cpu_utilization{0.};
};

