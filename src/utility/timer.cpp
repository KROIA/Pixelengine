#include "timer.h"

Timer::Timer()
{
    m_interval      = 0;
    m_runtime       = 0;
    m_timerStarted  = false;
    m_autorestart   = false;
    m_infiniteMode  = false;
}

Timer::~Timer()
{

}


bool Timer::start(float sec)
{
    TIMER_FUNCTION("Timer::start",profiler::colors::Teal);
    if(m_infiniteMode)
        return false;
    m_interval = sec;
    if(m_interval <= 0)
        return true;

    if(!m_timerStarted)
    {
        m_timerStarted = true;
        m_timer_start = std::chrono::high_resolution_clock::now();
    }
    else
    {
        return update();
    }
    return false;
}
void Timer::startInfinite()
{
    m_infiniteMode = true;
    m_timerStarted = true;
    m_timer_start = std::chrono::high_resolution_clock::now();
}
float Timer::stop()
{
    TIMER_FUNCTION("Timer::stop",profiler::colors::Teal50);
    float time = getTime();
    m_timerStarted = false;
    m_infiniteMode = false;
    m_runtime      = 0;
    return time;
}
bool Timer::update()
{
    TIMER_FUNCTION("Timer::update",profiler::colors::Teal100);
    if(m_infiniteMode)
        return false;
    m_timer_end = std::chrono::high_resolution_clock::now();
    m_time_span = m_timer_end - m_timer_start;
    m_runtime = m_time_span.count();

    if(m_runtime >= m_interval)
    {
        // Timer finished
        stop();
        if(m_autorestart)
            this->start(m_interval);
        return true;
    }
    return false;
}

void Timer::setAutorestart(bool enable)
{
    m_autorestart = enable;
}

float Timer::getTime()
{
    TIMER_FUNCTION("Timer::getTime",profiler::colors::Teal200);
    if(!m_timerStarted)
        return 0;
    m_timer_end = std::chrono::high_resolution_clock::now();
    m_time_span = m_timer_end - m_timer_start;
    m_runtime = m_time_span.count();
    return m_runtime;
}
