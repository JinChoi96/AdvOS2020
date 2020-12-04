#include "include.hh"

 static volatile int done;
 
 void *run_deadline(void *data)
 {
	struct sched_attr attr;
	int x = 0;
	int ret;
	unsigned int flags = 0;

	printf("deadline thread started [%ld]\n", gettid());

	attr.size = sizeof(attr);
	attr.sched_flags = 0;
	attr.sched_nice = 0;
	attr.sched_priority = 0;

	/* This creates a 10ms/30ms reservation */
	attr.sched_policy = SCHED_DEADLINE;
	attr.sched_runtime = 10 * 1000 * 1000;
	attr.sched_period = attr.sched_deadline = 30 * 1000 * 1000;

	ret = sched_setattr(0, &attr, flags);
	if (ret < 0) {
		done = 0;
		perror("sched_setattr");
		exit(-1);
	}

	while (!done) {
		x++;
	}

	printf("deadline thread dies [%ld]\n", gettid());
	return NULL;
 }

int main (int argc, char **argv)
{
 	// create tasks and set parameters
 	initialize();
 	
#ifndef HYBRID
	// memory locking of tagged tasks
#endif


#ifndef HYBRID
	// set affinity 
#endif	
	
	// check current time
	
	// main 
	
	// uninitialize
	
#ifndef HYBRID
	// free memory
#endif

	return 0;
}
