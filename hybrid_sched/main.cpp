#inlude <pthread.h>

#include "include.h"
#include "Task.h"
#include "Plan.h"

#define ITERATION 10000
#define DATA_SIZE 2048
#define NUM_TASKS 6

int HYBRID = 1;

std::array<int, NUM_TASKS> runtimes = {10, 10, 10, 10, 10, 10};
std::array<int, NUM_TASKS> deadlines = {30, 30, 30, 30, 30, 30};
pthread_t t1, t2, t3, t4, t5, t6;
std::array<pthread_t, NUM_TASKS> threads = {t1, t2, t3, t4, t5, t6};

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
	for(int i = 0; i < NUM_TASKS ; i ++){
		pthread_create(&(threads[i]), NULL, tasks[i].thread_function, NULL);
	}
	
	for(int i = 0 ; i < NUM_TASKS ; i ++){
		threads[i].join();
	}
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

	// parse each task's tag and set tag to the task

	struct sched_attr attr;

	for(int i = 0;i<NUM_TASKS;i++){
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
