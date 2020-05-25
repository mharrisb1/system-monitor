#include <string>

#include "format.h"

std::string Format::ElapsedTime(long seconds) {
  long int hours, mins;
  std::string hh, mm, ss;

  // hours
  seconds %= (24 * 60 * 60);
  hours = seconds / (60 * 60);
  hours < 10 ? hh = '0' + std::to_string(hours) : hh = std::to_string(hours);

  // minutes
  seconds %= (60 * 60);
  mins = seconds / 60;
  mins < 10 ? mm = '0' + std::to_string(mins) : mm = std::to_string(mins);

  // seconds
  seconds %= 60;
  seconds < 10 ? ss = '0' + std::to_string(seconds)
               : ss = std::to_string(seconds);

  return hh + ':' + mm + ':' + ss; // OUTPUT: hh:mm:ss
}