#include "../include/timecalc.h"

std::string convertTo24HourFormat(int hour, int minute, const std::string& period) {
    if (period == "am" && hour == 12) {
        // 12:00 am corresponds to 00:00 in 24-hour format
        hour = 0;
    } else if (period == "pm" && hour != 12) {
        // Add 12 hours to afternoon times (except 12:00 pm)
        hour += 12;
    }

    // Format the result as a four-digit string
    return (hour < 10 ? "0" : "") + std::to_string(hour) +
           (minute < 10 ? "0" : "") + std::to_string(minute);
}