#include "include.h"

class Task
{

public:

private:
    
    struct sched_attr attr;
    std::thread task;
    pid_t pid;
    int tag;
    long migration_cost;


public:

    Task();
    Task(struct sched_attr attr_input);

    // function to run in a thread
    void thread_function();
    int sched_setattr(pid_t pid, const struct sched_attr *attr,
		  unsigned int flags);
    int sched_getattr(pid_t pid, struct sched_attr *attr,
		  unsigned int size, unsigned int flags);
    void set_pid(pid_t pid_input);
    void set_tag(int cpu);
    void set_migration_cost(long migration_cost_input);

    pid_t get_pid();
    int get_tag();
    int get_migration_cost();

};