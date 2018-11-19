#ifndef CURRENT_TIME_H
#define CURRENT_TIME_H

#include <chrono>
#include <cstdint>

class CurrentTime {

public:
    int milliseconds();
    int microseconds();
    int nanoseconds();
    void timings(int &nano, int &micro, int &milli);
};

#endif  /* CURRENT_TIME_H */
