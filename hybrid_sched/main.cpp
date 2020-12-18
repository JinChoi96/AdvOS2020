#include "include.h"
#include "Task.h"
#include "Plan.h"
#include "dummywl.h"

#define DATA_SIZE 2048

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

int HYBRID = 1;

int main (int argc, char **argv)
{
	std::vector<Task> tasks;
	Plan plan;
 	// create tasks and set parameters
 	initialize(&tasks);
 	
if(HYBRID){
	// memory locking of tagged tasks
	char data[DATA_SIZE];
	tasks = plan.memory_locking(&tasks, data, DATA_SIZE);
	// set affinity 
	tasks = plan.set_affinity(&tasks);
}
	
	// check current time
	
	// main 
	
	// uninitialize
	
if(HYBRID){
	// free memory
	char data[DATA_SIZE];
	tasks = plan.memory_unlocking(&tasks, data, DATA_SIZE);
}

	return 0;
}

void initialize(std::vector<Task>* tasks)
{
	struct sched_attr attr;

	for(int i = 0;i<num_tasks;i++){
		attr.size = sizeof(attr);
		attr.sched_flags = 0;
		attr.sched_nice = 0;
		attr.sched_priority = 0;

		attr.sched_policy = SCHED_DEADLINE;
		attr.sched_runtime = runtimes[i] * 1000 * 1000;
		attr.sched_period = attr.sched_deadline = deadlines[i] * 1000 * 1000;

		tasks.push_back(Task::Task(attr));
	}
}
