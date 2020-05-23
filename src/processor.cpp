#include "processor.h"

void Processor::AddToVector() {
    while (true) {
        if (this->cpu_utilization_t.size() > 10) {
            this->cpu_utilization_t.pop_back();
        } else {
            this->cpu_utilization_t.push_back(LinuxParser::CpuUtilization());
        }
    }
}

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    for (float i: this->cpu_utilization_t) {
        this->total_utilization += i;
    }
    return total_utilization / this->cpu_utilization_t.size();
}

