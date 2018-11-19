#include "current_time_.h"

int CurrentTime::milliseconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
              (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

int CurrentTime::microseconds()
{
    return std::chrono::duration_cast<std::chrono::microseconds>
              (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

int CurrentTime::nanoseconds()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>
              (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}
void CurrentTime::timings(int &nano, int &micro, int &milli)
{
        nano = std::chrono::duration_cast<std::chrono::nanoseconds>
              (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    micro = std::chrono::duration_cast<std::chrono::microseconds>
              (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        milli = std::chrono::duration_cast<std::chrono::milliseconds>
              (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}
