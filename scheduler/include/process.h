#pragma once
#ifndef PROCESS_H_
#define PROCESS_H_

#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

namespace Sense
{
    class Process
    {
        public:
            // run Function is passed into constructor
            Process();
            ~Process();
            int start_time;
            int* power;

            void sleep();
            void pause();
            void resume();
            void stop();

            //template <typename func_type>
            void set_thread(void (*func)());
            void close_process();
        private:
            bool m_isStop;
            bool m_isPause;

            virtual void run_func();
            std::thread run;
            std::mutex m_mutex;
            std::condition_variable m_cv;
    };
    
}

#endif