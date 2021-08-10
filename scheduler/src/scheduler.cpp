#include "scheduler.h"


using namespace Sense;

Scheduler::Scheduler()
{

}

Scheduler::~Scheduler()
{

}

/*
void Scheduler::run()
{
    Process *running_proc = run_queue.front();
    run_queue.pop();
    running_proc->pause();
    sleep_queue.push(running_proc);
    Process *sleeping_proc = sleep_queue.front();
    sleep_queue.pop();
    sleeping_proc->resume();
    run_queue.push(sleeping_proc);
}
*/

void Scheduler::run()
{
    Process *running_proc = run_queue.front();
    run_queue.pop();
    running_proc->pause();
    sleep_queue.push(running_proc);

    Process* next_proc = sleep_queue.front();
    sleep_queue.pop();
    next_proc->resume();
    run_queue.push(next_proc);
}

// Also reorganizes queue
Process* Scheduler::select_next_process()
{
    Process *next_proc = sleep_queue.front();
    sleep_queue.pop();
    next_proc->resume();
    run_queue.push(next_proc);
    return next_proc;
}

void Scheduler::add_process(Process* new_proc)
{
    sleep_queue.push(new_proc);
}

void Scheduler::cleanup()
{
    while (!run_queue.empty()) {
        run_queue.front()->pause();
        run_queue.front()->close_process();
        run_queue.pop();
    }
    while (!sleep_queue.empty()) {
        sleep_queue.front()->close_process();
        sleep_queue.pop();
    }
}


/*
int Sense::drive(int power, Process &proc)
{
    if (power != 0) {
        switch(power)
        {
            case 1:
                proc.pause();
                break;
            case 2:
                proc.resume();
                break;
            case 3:
                proc.stop();
                break;
        }
    }
    return proc.get_power();
}
*/