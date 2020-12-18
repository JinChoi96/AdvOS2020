#include "include.h"
#include "Task.h"

class Plan
{
public: 
    Plan();

    std::vector<Task> Plan::get_migration_cost(std::vector<Task>* tasks);
    std::vector<Task> Plan::set_affinity(std::vector<Task>* tasks);
    std::vector<Task> Plan::memory_locking(std::vector<Task>* tasks, char *addr, size_t size);
    std::vector<Task> Plan::memory_unlocking(std::vector<Task>* tasks, char *addr, size_t size);
};