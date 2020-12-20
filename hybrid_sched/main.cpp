#include <pthread.h>

#include "include.h"
#include "Task.h"
#include "Plan.h"
#include <string>
#include <iostream>
#include <fstream>

#define ITERATION 10000
#define DATA_SIZE 2048
#define NUM_TASKS 5

int HYBRID = 1;

std::array<int, NUM_TASKS> runtimes = {10, 10, 10, 10, 10};
std::array<int, NUM_TASKS> deadlines = {30, 30, 30, 30, 30};
pthread_t t1, t2, t3, t4, t5;
std::array<pthread_t, NUM_TASKS> threads = {t1, t2, t3, t4, t5};


void initialize(std::vector<Task> tasks, std::string tags);
void parse_tags(std::string tags, std::vector<Task> tasks);

int main (int argc, char **argv)
{
	std::vector<Task> tasks;
	Plan plan;
 	// create tasks and set parameters
	std::string tags = "example_tasks";
 	initialize(tasks, tags);
 	
if(HYBRID){
	char data[DATA_SIZE];
	std::string line,text;
   	std::ifstream in("dummytext.txt");
   	while(std::getline(in, line))
   	{
    	   text += line + "\n";
   	}
   	const char* data = text.c_str();
	// memory locking of tagged tasks
	for (int i = 0; i < NUM_TASKS; i++){
		if(tags[i] != 0){
			tasks = plan.memory_locking(tasks[i], data, DATA_SIZE);
		}
	}
	
	// set affinity 
	tasks = plan.set_affinity(tasks);
}
	
	// check current time
	
	// main 
	for(int i = 0; i < NUM_TASKS ; i ++){
		pthread_create(&(threads[i]), NULL, tasks[i].thread_function(), NULL);
	}
	
	for(int i = 0 ; i < NUM_TASKS ; i ++){
		threads[i].join();
	}
	// uninitialize
	
if(HYBRID){
	// free memory
	char data[DATA_SIZE];
	tasks = plan.memory_unlocking(tasks, data, DATA_SIZE);
}

	return 0;
}

void initialize(std::vector<Task> tasks, std::string tags)
{
	struct sched_attr attr;

	for(int i = 0;i<NUM_TASKS;i++){
		attr.size = sizeof(attr);
		attr.sched_flags = 0;
		attr.sched_nice = 0;
		attr.sched_priority = 0;

		attr.sched_policy = SCHED_DEADLINE;
		attr.sched_runtime = runtimes[i] * 1000 * 1000;
		attr.sched_period = attr.sched_deadline = deadlines[i] * 1000 * 1000;

		tasks.push_back(Task(attr));
	}
	// parse each task's tag and set tag to the task
	parse_tags(tags, tasks);

	return;
}

void parse_tags(std::string tags, std::vector<Task> tasks){
    std::ifstream in(tags);
	std::string line;
	int thread_id;
	int i = 0;
	while(getline(in, line)){
		// std::cout << line << std::endl;
		if(i % 2 == 0){
			thread_id = std::stoi(line);
			
		}else{
			tasks[thread_id].set_tag(std::stoi(line));
		}
		i++;	
	}
	return;
}
