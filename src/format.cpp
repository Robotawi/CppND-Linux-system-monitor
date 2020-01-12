#include <string>
#include "format.h"

using std::string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    int hours{0}, minutes{0};
    string ftime;
    minutes = seconds / 60;
    hours = minutes / 60;
    ftime = std::to_string(hours)+":"+std::to_string(int(minutes%60))+":"+std::to_string(int(seconds%60));
    return ftime;
}