#ifndef TIME_HPP
#define TIME_HPP

#include <cstdint>

class time {
private:
    static const uint8_t centuryIncreaseValue = 100;

public:
    static const uint8_t minSeconds = 0;
    static const uint8_t minMinutes = 0;
    static const uint8_t minDate = 0;
    static const uint8_t minYear = 0;
    static const uint8_t minHours = 1;
    static const uint8_t minDay = 1;
    static const uint8_t minMonth = 1;
    static const uint8_t maxDay = 7;
    static const uint8_t maxDate = 31;
    static const uint8_t maxMonth = 12;
    static const uint8_t maxSeconds = 59;
    static const uint8_t maxMinutes = 59;
    static const uint8_t maxHours = 23;
    static const uint8_t maxYear = 99;

public:
    static int currentCentury;

public:
    static void increaseCentury();

public:
    static bool isSecondsValid(uint8_t seconds);
    static bool isMinutesValid(uint8_t minutes);
    static bool isHoursValid(uint8_t hours);
    static bool isDayValid(uint8_t day);
    static bool isDateValid(uint8_t date);
    static bool isMonthValid(uint8_t month);
    static bool isYearValid(uint8_t year);
    static bool isCenturyValid(int century);
};

#endif // TIME_HPP
