#include <string>
#include <array>
#include <charconv>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(int seconds) {
     int    hour,
                min;

    std::string hh,
                mm,
                ss;

    // hours
    seconds %= (24 * 60 * 60);
    hour =     seconds / 3600;

    // minutes
    seconds %= 3600;
    min =      seconds / 60;

    // seconds
    seconds %= 60;

    hh = std::to_string(hour);
    mm = std::to_string(min);
    ss = std::to_string(seconds);

    return hh + ':' + mm + ':' + ss;
}