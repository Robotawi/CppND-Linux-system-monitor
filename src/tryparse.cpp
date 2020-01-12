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

//The system uptime
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
/*
//The process related
string LinuxParser::User(int pid) {
    string line, key, value;
    string user("none");
    std::ifstream filestream(LinuxParser::kProcDirectory + std::to_string(pid) + LinuxParser::kStatusFilename);
    if(filestream.is_open()){
        while(std::getline(filestream, line)){
            std::replace(line.begin(), line.end(), ':', ' ');
            //std::cout<<line<<"\n";
            std::istringstream stringstream(line);
            stringstream >> key >> value;
            if (key == "Uid"){user = value;}
        }
    }
    std::cout << "User id is "+ user +" \n";
//    return user;
    filestream.close();
    string x;
    filestream.open(LinuxParser::kPasswordPath);
    if(filestream.is_open()){
        while(std::getline(filestream, line)){
            std::replace(line.begin(), line.end(), ':', ' ');
            std::cout<<line<<"\n";
            std::istringstream stringstream(line);
            stringstream >> key >> x >> value;
            if (value == user){user = key;}
        }
    }
    std::cout << "Username is "+ user +" \n";
    return user;
}
int main(){
    LinuxParser::User(3);
    return 0;
}
 */
/*
string LinuxParser::Command(int pid) {
    string line;
    std::ifstream filestream(kProcDirectory + to_string(pid)+ kCmdlineFilename);
    if (filestream.is_open()){
        std::getline(filestream, line);
    }
    return line;
}
int main(){
    std::cout << "command is "<< LinuxParser::Command(24166)<<"\n";

    return 0;
}
 */
//uptime
/*
#include <unistd.h>
#include "../include/format.h"
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
using std::string;
using std::to_string;
string Format::ElapsedTime(long seconds) {
    int hours{0}, minutes{0};
    string ftime;
    minutes = seconds / 60;
    hours = minutes / 60;
    ftime = to_string(hours)+":"+to_string(int(minutes%60))+":"+to_string(int(seconds%60));
    return ftime;
}
int main(){
    long uptime = LinuxParser::UpTime(9577);
    string ftime = Format::ElapsedTime(uptime);
    std::cout << "process uptime is " << uptime << ", which is " << ftime+"\n";
    return 0;
}

 */

//ram
/*
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

int main(){
    std::cout << "Ram is "<< LinuxParser::Ram(10694)<<"MB \n";

    return 0;
}
 */