#include "process.h"

using namespace Sense;

Process::Process() {
    m_isStop = false;
    m_isPause = true;
    run = std::thread(&Process::run_func, this);
}
Process::~Process() {}

void Process::sleep()
{
    pause();
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, [this]{return !m_isPause;});
}

// not implemented yet
/*
void Process::wait_for_interrupt()
{
    sleep(); 
}
*/

void Process::run_func() {}

void Process::pause()
{
    std::unique_lock<decltype(m_mutex)> l(m_mutex);
    m_isPause = true;
}


void Process::resume()
{
    std::unique_lock<decltype(m_mutex)> l(m_mutex);
    m_isPause = false;
    m_cv.notify_all();
}

void Process::stop()
{
    m_isStop = true;
    m_isPause = false;
}
// close_process() Could be the same as stop() ^^
void Process::close_process() {}