#include "processor.h"

void Processor::AddToVector() {
    if (this->cpu_utilization_t.size() > 10) {
        this->total_utilization -= this->cpu_utilization_t.front();
        this->cpu_utilization_t.erase(this->cpu_utilization_t.begin());
    } else {
        this->cpu_utilization_t.push_back(LinuxParser::CpuUtilization());
    }
}

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    Processor::AddToVector();
    for (float i: this->cpu_utilization_t) {
        this->total_utilization += i;
    }
    return total_utilization / this->cpu_utilization_t.size();
}

