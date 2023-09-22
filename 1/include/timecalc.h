#pragma once // говорит компилятору что данный файл должен быть включен только один раз

#include <string>
#include <sstream>

std::string convertTo24HourFormat(int hour, int minute, const std::string& period);
