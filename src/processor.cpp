#include "processor.h"

void Processor::AddToVector() {
    if (this->cpu_utilization_t.size() > 1000) {
        this->total_utilization -= this->cpu_utilization_t.front();
        this->cpu_utilization_t.erase(this->cpu_utilization_t.begin());
    } else {
        this->cpu_utilization_t.push_back(LinuxParser::CpuUtilization());
        this->total_utilization += this->cpu_utilization_t.back();
    }
}

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    Processor::AddToVector();
    return (total_utilization / this->cpu_utilization_t.size()) * 100;
}

