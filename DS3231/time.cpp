#include "time.hpp"

int time::currentCentury = 2000;

void time::increaseCentury() {
    currentCentury += centuryIncreaseValue;
}
