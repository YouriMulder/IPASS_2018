#ifndef TIME_HPP
#define TIME_HPP

#include <cstdint>

class time {
public:
    const uint8_t minSeconds = 0;
    const uint8_t minMinutes = 0;
    const uint8_t minDate = 0;
    const uint8_t minYear = 0;
    const uint8_t minHours = 1;
    const uint8_t minDay = 1;
    const uint8_t minMonth = 1;
    const uint8_t maxDay = 7;
    const uint8_t maxDate = 31;
    const uint8_t maxMonth = 12;
    const uint8_t maxSeconds = 59;
    const uint8_t maxMinutes = 59;
    const uint8_t maxHours = 23;
    const uint8_t maxYear = 99;

private:
    const static uint8_t centuryIncreaseValue = 100;
public:
    static int currentCentury;

public:
    static void increaseCentury();

public:
    bool isSecondsValid(uint8_t seconds);
    bool isMinutesValid(uint8_t minutes);
    bool isHoursValid(uint8_t hours);
    bool isDayValid(uint8_t day);
    bool isDateValid(uint8_t date);
    bool isMonthValid(uint8_t month);
    bool isYearValid(uint8_t year);
    bool isCenturyValid(int century);
};

#endif // TIME_HPP
