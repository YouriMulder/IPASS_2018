#ifndef TIME_HPP
#define TIME_HPP

#include <cstdint>
#include "hwlib.hpp"

class time {
private:
    static const uint8_t centuryIncreaseValue = 100;

public:
    static const uint8_t minSeconds, minMinutes, minDate, minYear = 0;
    static const uint8_t minHours, minDay, minMonth = 1;
    static const uint8_t maxDay = 7;
    static const uint8_t maxDate = 31;
    static const uint8_t maxMonth = 12;
    static const uint8_t maxSeconds, maxMinutes = 59;
    static const uint8_t maxHours = 23;
    static const uint16_t maxYear = 99;

    static int currentCentury;

public:
    static void increaseCentury();
};

#endif // TIME_HPP
