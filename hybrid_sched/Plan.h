#include "include.h"
#include "Task.h"
#include "dummywl.h"
#include <unistd.h>
#include <sys/mman.h>


#ifndef __PLAN_H__
#define __PLAN_H__
class Plan
{
public: 
    Plan();

    std::vector<Task> get_migration_cost(std::vector<Task> tasks);
    std::vector<Task> set_affinity(std::vector<Task> *tasks);
    std::vector<Task> memory_locking(std::vector<Task> *tasks, char *addr, size_t size);
    std::vector<Task> memory_unlocking(std::vector<Task> *tasks, char *addr, size_t size);
};
#endif