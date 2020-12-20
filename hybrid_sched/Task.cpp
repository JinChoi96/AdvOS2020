#include "Task.h"

Task::Task()
{
	
}

Task::Task(struct sched_attr attr_input)
{
	attr = attr_input;
	
	pid = 0;
	tag = 0;
	// migration_cost = 0;
}

// when the thread is made and starts to actually running, 
// this function is used to set the attribute of 
// SCHED_DEADLINE
int Task::sched_setattr(pid_t pid,
				const struct sched_attr *attr,
				unsigned int flags)
 {
	 
	return syscall(__NR_sched_setattr, pid, attr, flags);
 }

void Task::set_pid(pid_t pid_input){
	pid = pid_input;
	return;
}

void Task::set_tag(int cpu){
	tag = cpu;
	return;
}

// void Task::set_migration_cost(long migration_cost_input){
// 	migration_cost = migration_cost_input;
// }

struct sched_attr Task::get_attr(){
	return attr;
}

pid_t Task::get_pid(){
	return pid;
}

int Task::get_tag(){
	return tag;
}

// int Task::get_migration_cost(){
// 	return migration_cost;
// }
