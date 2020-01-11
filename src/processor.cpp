#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <iostream>

using std::stof;
using std::string;
using namespace LinuxParser;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
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