#include "Plan.h"

Plan::Plan()
{
	
}

std::vector<Task> Plan::set_affinity(std::vector<Task> tasks)
{
	
}

std::vector<Task> Plan::get_migration_cost(std::vector<Task> tasks)
{
	struct thread_args args;
	args.online = false;
	args.iter = 1000;
	args.cpus = 2;

	pthread_t _thread[10];

	if (pthread_create(&_thread[0], NULL, &dummy_work, (void *)&args) != 0) { 
		perror("pthread_create"); 
	} 
	pthread_exit(NULL); 

}

std::vector<Task> Plan::memory_locking(std::vector<Task> tasks, char *addr, size_t size)
{

    unsigned long page_offset, page_size;

    page_size =  sysconf(_SC_PAGE_SIZE);
	page_offset = (unsigned long) addr  % page_size;
	 
	addr -= page_offset;
	size += page_offset;

	mlock(addr, size);
}

std::vector<Task> Plan::memory_unlocking(std::vector<Task> tasks, char *addr, size_t size)
{
    unsigned long page_offset, page_size;

    page_size =  sysconf(_SC_PAGE_SIZE);
	page_offset = (unsigned long) addr  % page_size;
	 
	addr -= page_offset;
	size += page_offset;

	munlock(addr, size);
}
