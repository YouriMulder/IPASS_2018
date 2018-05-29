#ifndef TIME_HPP
#define TIME_HPP

#include <cstdint>

class time {
private:
    const static uint8_t centuryIncreaseValue = 100;

public:
    const static uint8_t minSeconds = 0;
    const static uint8_t minMinutes = 0;
    const static uint8_t minDate = 0;
    const static uint8_t minYear = 0;
    const static uint8_t minHours = 1;
    const static uint8_t minDay = 1;
    const static uint8_t minMonth = 1;
    const static uint8_t maxDay = 7;
    const static uint8_t maxDate = 31;
    const static uint8_t maxMonth = 12;
    const static uint8_t maxSeconds = 59;
    const static uint8_t maxMinutes = 59;
    const static uint8_t maxHours = 23;
    const static uint8_t maxYear = 99;

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
