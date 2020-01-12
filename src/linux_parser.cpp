#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::stoi;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);

      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
    string key, value;
    string line;
    float memutil{7.0}, memt{0.0}, memf{0.0};
    std::ifstream filestream(kProcDirectory+kMeminfoFilename);
    if (filestream.is_open()){
        while(std::getline(filestream, line)){
            //std::cout << line <<" \n";
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream stringstream(line);
            stringstream >> key >> value ;
            //std::cout << "got this " << key << ", and value " <<value << "\n";
            if (key == "MemTotal"){memt = stof(value);}
            if (key == "MemFree"){memf = stof(value);}
        }
        memutil = (memt - memf) / memt;
        //std::cout <<"Memory utilization is "<< memutil << "\n";
    }
    return memutil;
}

// TODO: Read and return the system uptime
long int LinuxParser::UpTime() {
    long int uptime;
    string value, line;
    std::ifstream filestream(LinuxParser::kProcDirectory+LinuxParser::kUptimeFilename);
    if(filestream.is_open()){
        std::getline(filestream, line);
        std::istringstream stringstream(line);
        stringstream >> value;
        uptime = std::stol(value);
    }
    return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }



// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

//processes
// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
    int processes{0};
    string key, value, line;

    std::ifstream filestream(kProcDirectory+kStatFilename);
    if (filestream.is_open()){
        while(std::getline(filestream, line)){
            std::istringstream stringstream(line);
            stringstream >> key >> value;
            if (key == "processes") {processes = stoi(value);}
        }
    }
    return processes;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
    int runprocesses{0};
    string key, value, line;

    std::ifstream filestream(kProcDirectory+kStatFilename);
    if (filestream.is_open()){
        while(std::getline(filestream, line)){
            std::istringstream stringstream(line);
            stringstream >> key >> value;
            if (key == "procs_running") {runprocesses = stoi(value);}
        }
    }
    return runprocesses;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
    string line;
    std::ifstream filestream(kProcDirectory + to_string(pid)+ kCmdlineFilename);
    if (filestream.is_open()){
        std::getline(filestream, line);
    }
    return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
    string line, key, value;
    string ram("none");
    std::ifstream filestream(LinuxParser::kProcDirectory + std::to_string(pid) + LinuxParser::kStatusFilename);
    if(filestream.is_open()){
        while(std::getline(filestream, line)){
            std::replace(line.begin(), line.end(), ':', ' ');
            //std::cout << line << "\n";
            std::istringstream stringstream(line);
            stringstream >> key >> value;
            if (key == "VmSize"){ram = to_string(stof(value)/1024.0);}
        }
    }
    return ram;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
    string line, key, value;
    string user("none");
    std::ifstream filestream(LinuxParser::kProcDirectory + std::to_string(pid) + LinuxParser::kStatusFilename);
    if(filestream.is_open()){
        while(std::getline(filestream, line)){
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream stringstream(line);
            stringstream >> key >> value;
            if (key == "Uid"){user = value;}
        }
    }
    return user;
}

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid) {
    string line, key, value;
    string user("none");
    std::ifstream filestream(LinuxParser::kProcDirectory + std::to_string(pid) + LinuxParser::kStatusFilename);
    if(filestream.is_open()){
        while(std::getline(filestream, line)){
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream stringstream(line);
            stringstream >> key >> value;
            if (key == "Uid"){user = value;}
        }
    }
    filestream.close();
    string x;
    filestream.open(LinuxParser::kPasswordPath);
    if(filestream.is_open()){
        while(std::getline(filestream, line)){
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream stringstream(line);
            stringstream >> key >> x >> value;
            if (value == user){user = key;}
        }
    }
    return user;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
    string line, data;
    long uptime{0};
    std::ifstream filestream(kProcDirectory + to_string(pid)+ kStatFilename);
    if (filestream.is_open()){
        std::getline(filestream, line);
        std::istringstream stringstream (line);
        for (int count = 1; count <= 22; count++){
            stringstream >> data;
            std::cout << "data is "<<data << "\n";
        }
        uptime = std::stol(data);
        uptime = uptime / sysconf(_SC_CLK_TCK);
    }
    return uptime;
}