#ifndef TIMER_H
#define TIMER_H

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
    bool start(double sec);
    void stop();

    bool update();

    void setAutorestart(bool enable);

    double getTime();


private:

    double m_interval;
    double m_runtime;
    bool m_timerStarted;
    bool m_autorestart;

    std::chrono::high_resolution_clock::time_point m_timer_start;
    std::chrono::high_resolution_clock::time_point m_timer_end;
    std::chrono::duration<double> m_time_span;
};
#endif // TIMER_H
