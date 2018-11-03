#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace helpers
{

class Timer
{
public:
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::nanoseconds TIME;

     void start()
     {
         beginning = Clock::now();
     }

     long long int elapsed()
     {
         return std::chrono::duration_cast<TIME>(Clock::now() - beginning).count();
     }

     long double ns_to_ms(long long int time)
     {
         return static_cast<long double>(time)/1000000;
     }
private:
     Clock::time_point beginning;
};

}//namespace helpers
#endif // TIMER_H
