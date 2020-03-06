#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <iostream>

using std::stof;
using std::string;
using namespace LinuxParser;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    return LinuxParser::CpuUtilization();
}