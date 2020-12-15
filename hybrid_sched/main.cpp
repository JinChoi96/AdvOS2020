#include "include.h"
#include "Task.h"
#include "Plan.h"

 static volatile int done;
 
 void *run_deadline(void *data)
 {
	// struct sched_attr attr;
	// int x = 0;
	// int ret;
	// unsigned int flags = 0;

	// printf("deadline thread started [%ld]\n", gettid());

	// attr.size = sizeof(attr);
	// attr.sched_flags = 0;
	// attr.sched_nice = 0;
	// attr.sched_priority = 0;

	// /* This creates a 10ms/30ms reservation */
	// attr.sched_policy = SCHED_DEADLINE;
	// attr.sched_runtime = 10 * 1000 * 1000;
	// attr.sched_period = attr.sched_deadline = 30 * 1000 * 1000;

	// ret = sched_setattr(0, &attr, flags);
	// if (ret < 0) {
	// 	done = 0;
	// 	perror("sched_setattr");
	// 	exit(-1);
	// }

	// while (!done) {
	// 	x++;
	// }

	// printf("deadline thread dies [%ld]\n", gettid());
	// return NULL;
 }


int main (int argc, char **argv)
{
	std::vector<Task> tasks;
	Plan plan;
 	// create tasks and set parameters
 	initialize(tasks);
 	
#ifndef HYBRID
	// memory locking of tagged tasks
	tasks = plan.memory_locking(tasks);
	// set affinity 
	tasks = plan.set_affinity(tasks);
	
#endif	
	
	// check current time
	
	// main 
	
	// uninitialize
	
#ifndef HYBRID
	// free memory
#endif

	return 0;
}

void initialize(std::vector<Task> tasks)
{
	
}
