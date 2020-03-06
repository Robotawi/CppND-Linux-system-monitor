#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include <algorithm>
#include "process.h"
#include "processor.h"

class System {
 public:
  Processor & Cpu();
  std::vector<Process>& Processes();
  float MemoryUtilization();
  long UpTime();
  int TotalProcesses();
  int RunningProcesses();
  std::string Kernel();
  std::string OperatingSystem();
  static bool CompProcess(Process &a, Process &b);

 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
};

#endif