#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <iostream>

using std::stof;
using std::string;
using namespace LinuxParser;

float Processor::Utilization() {
    return LinuxParser::CpuUtilization();
}