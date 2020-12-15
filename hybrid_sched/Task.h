#include "include.h"

class Task
{

public:

private:
    
    struct sched_attr attr;
    std::thread task;
    int pid;
    int tag;
    long migration_cost;


public:

    Task();
    Task(struct sched_attr attr_input);

    // function to run in a thread
    void thread_function();

private:
    int sched_setattr(pid_t pid, const struct sched_attr *attr,
		  unsigned int flags);
    int sched_getattr(pid_t pid, struct sched_attr *attr,
		  unsigned int size, unsigned int flags);
};