//
// Created by zozo on 1/11/20.
//
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
//#include <dirent.h>
//#include <regex>
#include <algorithm>
#include "../include/linux_parser.h"
#include "../include/format.h"
using std::stof;
using std::string;
using std::to_string;
using std::vector;
#include <iomanip>

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
    std::cout << "command is "<< LinuxParser::Command(16264)<<"\n";

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
            if (key == "VmSize"){ram = to_string(int(stof(value)/1024.0));}
        }
    }
    return ram;
}

int main(){
    std::cout << "Ram is "<< LinuxParser::Ram(6538)<<" MB \n";

    return 0;
}
*/

//uid and user
/*
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
//
//// TODO: Read and return the user associated with a process, may need the input
string LinuxParser::User(int pid) {
    string line, key, value;
    string userid = LinuxParser::Uid(pid);
    std::cout << "The UID is " << userid <<std::endl;
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


int main(){
//    std::cout << "The UID is " << LinuxParser::Uid(6426)<<std::endl;
    std::cout << "The user is " << LinuxParser::User(6426)<<std::endl;

}
*/
/*
//uptime-process
long LinuxParser::UpTime(int pid) {
    string line, data;
    long pstarttime{0}, puptime{0};
    std::ifstream filestream(kProcDirectory + to_string(pid)+ kStatFilename);
    if (filestream.is_open()){
        std::getline(filestream, line);
        std::istringstream stringstream (line);
        for (int count = 1; count <= 22; count++){
            stringstream >> data;
//            std::cout << "data is "<<data << "\n";
        }
        pstarttime = std::stol(data)/ sysconf(_SC_CLK_TCK); //in seconds
        puptime = LinuxParser::UpTime() - pstarttime; // to convert to seconds
    }
    return puptime;
}
//uptime-system
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

string Format::ElapsedTime(long seconds) {
    int hours{0}, minutes{0};
    string ftime;
    minutes = seconds / 60;
    hours = minutes / 60;
    ftime = std::to_string(hours)+":"+std::to_string(int(minutes%60))+":"+std::to_string(int(seconds%60));
    return ftime;
}

int main(){
    std::cout << "System uptime is " << LinuxParser::UpTime() << std::endl;
    std::cout << "System uptime formatted is " << Format::ElapsedTime(LinuxParser::UpTime()) << std::endl;

    std::cout << "Process up time is " << LinuxParser::UpTime(16264) << std::endl;
    std::cout << "Process up time formatted is " << Format::ElapsedTime(LinuxParser::UpTime(16264)) << std::endl;


}
*/
//cpu
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
float LinuxParser::CpuUtilization(int pid)
{float ptotal_time, secondsfrompstart, cpu_usage, sysuptime = UpTime(); //sysuptime is in seconds
    string line, data, utime, stime, cutime, cstime, starttime; string format_cpu;
    std::ostringstream ostring;
    ostring << std::fixed;
    ostring << std::setprecision(2);

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
    cpu_usage = 100 * (ptotal_time/secondsfrompstart); // utilization = process time / time from its start


//    ostring << cpu_usage;
//    format_cpu = ostring.str();
//    cpu_usage = stof(cpu_usage);
    return cpu_usage;
}
int main(){
    std::cout << "CPU utilization is " << LinuxParser::CpuUtilization(5689) << std::endl;
}
*/
