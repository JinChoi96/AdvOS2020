/*

<argument>
tasks: task vector which containts all tasks 

*/

#include "include.h"
#include "Task.h"

Task::Task()
{
	
}

Task::Task(struct sched_attr attr_input)
{
	struct sched_attr attr = attr_input;
	// attr.size = sizeof(attr_input);
	// attr.sched_flags = attr_input.sched_flags;
	// attr.sched_nice = attr_input.sched_nice;
	// attr.sched_priority = attr_input.sched_priority;
	
	// attr.sched_policy = attr_input.sched_policy;
	// attr.sched_runtime = attr_input.sched_runtime;
	// attr.sched_period = attr_input.sched_period;
	// attr.sched_deadline = attr_input.sched_deadline;

	pid = 0;
	tag = 0;
	migration_cost = 0;
}

// when the thread is made and starts to actually running, 
// this function is used to set the attribute of 
// SCHED_DEADLINE
int Task::sched_setattr(pid_t pid,
		  		  unsigned int flags)
 {
	 
	return syscall(__NR_sched_setattr, pid, attr, flags);
 }

 int Task::sched_getattr(pid_t pid,
		  struct sched_attr *attr,
		  unsigned int size,
		  unsigned int flags)
 {
	return syscall(__NR_sched_getattr, pid, attr, size, flags);
 }

