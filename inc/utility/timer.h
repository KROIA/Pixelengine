#ifndef TIMER_H
#define TIMER_H

#include "base.h"

#include <ctime>
#include <ratio>
#include <chrono>

class Timer
{
public:
    Timer();
    virtual ~Timer();

    // Starts the timer.
    // Returns true, if the time is over, otherwise false
    bool start(float sec);
    void startInfinite();
    float stop();

    bool update();

    void setAutorestart(bool enable);

    float getTime();


private:

    float m_interval;
    float m_runtime;
    bool m_timerStarted;
    bool m_autorestart;
    bool m_infiniteMode;

    std::chrono::high_resolution_clock::time_point m_timer_start;
    std::chrono::high_resolution_clock::time_point m_timer_end;
    std::chrono::duration<float> m_time_span;
};
#endif // TIMER_H
