#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::stoi;
using std::stol;
using std::string;
using std::to_string;
using std::vector;

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
    if (file->d_type == DT_DIR) {
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
    }
    return memutil;
}


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


float LinuxParser::CpuUtilization() {
    string line, cpu, usert, nicet, syst, idlet, iowaitt;
    float totalt, workt;
    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open()){
        std::getline(filestream, line);
        std::istringstream stringstream(line);
        stringstream >> cpu >> usert >> nicet >> syst >> idlet >> iowaitt;
        totalt = stof(usert) + stof(nicet) + stof(syst) + stof(idlet) + stof(iowaitt);
        workt = stof(usert) + stof(nicet) + stof(syst);
    }
    return workt/totalt;
}

//processes
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

string LinuxParser::Command(int pid) {
    string line;
    std::ifstream filestream(kProcDirectory + to_string(pid)+ kCmdlineFilename);
    if (filestream.is_open()){
        std::getline(filestream, line);
    }
    return line;
}

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
            if (key == "VmSize"){ram = to_string(int(stof(value)/1024.0));}
        }
    }
    return ram;
}

string LinuxParser::Uid(int pid) {
    string line, key, value;
    string userid("none");
    std::ifstream filestream(LinuxParser::kProcDirectory + std::to_string(pid) + LinuxParser::kStatusFilename);
    if(filestream.is_open()){
        while(std::getline(filestream, line)){
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream stringstream(line);
            stringstream >> key >> value;
            if (key == "Uid"){userid = value;}
        }
    }
    return userid;
}

string LinuxParser::User(int pid) {
    string line, key, value;
    string userid = LinuxParser::Uid(pid);
    string user{"None"};
    string x;
    std::ifstream filestream(LinuxParser::kPasswordPath);
    if(filestream.is_open()){
        while(std::getline(filestream, line)){
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream stringstream(line);
            stringstream >> key >> x >> value;
            if (value == userid){user = key;}
        }
    }
    return user;
}


long LinuxParser::UpTime(int pid) {
    string line, data;
    long pstarttime{0}, puptime{0};
    std::ifstream filestream(kProcDirectory + to_string(pid)+ kStatFilename);
    if (filestream.is_open()){
        std::getline(filestream, line);
        std::istringstream stringstream (line);
        for (int count = 1; count <= 22; count++){
            stringstream >> data;
        }
        pstarttime = std::stol(data)/ sysconf(_SC_CLK_TCK); //in seconds
        puptime = LinuxParser::UpTime() - pstarttime; // total sys up time - process start time in seconds, the result is in seconds
    }
    return puptime;
}
float LinuxParser::CpuUtilization(int pid){
float ptotal_time, secondsfrompstart, cpu_usage, sysuptime = UpTime(); //sysuptime is in seconds
    string line, data, utime, stime, cutime, cstime, starttime;
    std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
    if (filestream.is_open()){
        std::getline(filestream, line);
        std::istringstream stringstream(line);
        for (int count = 1; count <=22; count ++){
            if (count == 14) {stringstream >> utime;}
            else if (count == 15) {stringstream >> stime;}
            else if (count == 16) {stringstream >> cutime;}
            else if (count == 17) {stringstream >> cstime;}
            else if (count == 22) {stringstream >> starttime;}
            else {stringstream >> data;}
        }
    }

    ptotal_time = (stof(utime) + stof(stime) + stof(cutime) + stof(cstime))/sysconf(_SC_CLK_TCK); // process time in seconds
    secondsfrompstart = sysuptime - (stof(starttime) / sysconf(_SC_CLK_TCK)); // process from the process start in seconds
    cpu_usage = ptotal_time/secondsfrompstart; // utilization = process time / time from its start
    return cpu_usage;
}