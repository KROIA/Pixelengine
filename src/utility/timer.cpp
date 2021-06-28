#include "timer.h"

Timer::Timer()
{
    m_interval      = 0;
    m_runtime       = 0;
    m_timerStarted  = false;
    m_autorestart   = false;
}

Timer::~Timer()
{

}


bool Timer::start(float sec)
{
    EASY_FUNCTION(profiler::colors::Teal);
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

void Timer::stop()
{
    EASY_FUNCTION(profiler::colors::Teal50);
    m_timerStarted = false;
    m_runtime      = 0;
}
bool Timer::update()
{
    EASY_FUNCTION(profiler::colors::Teal100);
    m_timer_end = std::chrono::high_resolution_clock::now();
    m_time_span = std::chrono::duration_cast<std::chrono::microseconds>(m_timer_end - m_timer_start);
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
    EASY_FUNCTION(profiler::colors::Teal200);
    if(!m_timerStarted)
        return 0;
    this->update();
    return m_runtime;
}
