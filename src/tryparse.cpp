//
// Created by zozo on 1/11/20.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
//#include <dirent.h>
//#include <regex>
#include <algorithm>
#include "../include/linux_parser.h"
using std::stof;
using std::string;
using std::to_string;
using std::vector;
/*
int main (){
    string key, value;
    string line;
    float memutil{0.0}, memt{0.0}, memf{0.0};
//    const string filepath = "/proc/meminfo";

//    std::ifstream filestream(filepath);
    std::ifstream filestream(LinuxParser::kProcDirectory+LinuxParser::kMeminfoFilename);

    if (filestream.is_open()){
        while(std::getline(filestream, line)){
            std::cout << line <<" \n";
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream stringstream(line);
            stringstream >> key >> value ;
            //std::cout << "got this " << key << ", and value " <<value << "\n";
            if (key == "MemTotal"){memt = stof(value);}
            if (key == "MemFree"){memf = stof(value);}
        }
        memutil = (memt - memf) / memt * 100;
        std::cout <<"Memory utilization is "<< memutil << "\n";
    }

    return 0;
}*/

/*
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

int main(){
    long int uptime;
    uptime = LinuxParser::UpTime();
    std::cout << "timy is " <<uptime << "\n";
}
*/

