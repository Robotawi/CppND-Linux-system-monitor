#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
#include <iostream>
#include <algorithm>

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
    if (!processes_.empty()){
        processes_.clear();
    }

    std::vector<int> procesids = LinuxParser::Pids();
    for (auto & id : procesids){
        processes_.push_back(Process(id));
    }
    //sort the processes
    std::sort(processes_.begin(), processes_.end(), CompProcess);
    return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
    kernel = LinuxParser::Kernel();
    return kernel;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() {
    memutil = LinuxParser::MemoryUtilization();
    return memutil;
}

// TODO: Return the operating system name
std::string System::OperatingSystem() {
    os = LinuxParser::OperatingSystem();
    return os; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() {
    runprocesses = LinuxParser::RunningProcesses();
    return runprocesses;
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
    processes = LinuxParser::TotalProcesses();
    return processes;
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() {
    uptime = LinuxParser::UpTime();
    return uptime;
}

 bool System::CompProcess(Process &a, Process &b) {
    return a < b ;
}