#include <string>
#include "format.h"

using std::string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string formatSMH(int hours){
    string strhours{""};
    if (hours < 10){
        strhours = "0" + std::to_string(hours);
    }
    else{
        strhours = std::to_string(hours);
    }
    return strhours;
}

string Format::ElapsedTime(long seconds) {
    int hours{0}, minutes{0};
    string ftime;
    minutes = seconds / 60;
    hours = minutes / 60;

    //further formatting

//    ftime = std::to_string(hours)+":"+std::to_string(int(minutes%60))+":"+std::to_string(int(seconds%60));
    ftime = formatSMH(hours)+":"+formatSMH(int(minutes%60))+":"+formatSMH(int(seconds%60));
    return ftime;
}