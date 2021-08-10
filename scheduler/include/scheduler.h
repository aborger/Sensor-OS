#pragma once
#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "process.h"
#include <queue>

namespace Sense
{
    class Scheduler
    {
        public:
            Scheduler();
            ~Scheduler();
            void run();
            void add_process(Process* new_proc);
            Process* select_next_process();
            void cleanup();
        private:
            //Process current;
            std::queue<Process*> run_queue;
            std::queue<Process*> sleep_queue;

    };
    //int drive(int power, Process &proc);


}

#endif