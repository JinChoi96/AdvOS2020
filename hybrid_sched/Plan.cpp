/*

<argument>
tasks: task vector which containts all tasks 

*/
#include "include.h"
#include "Plan.h"
#include <unistd.h>
#include <sys/mman.h>

Plan::Plan()
{
	
}

std::vector<Task> Plan::get_migration_cost(std::vector<Task> tasks)
{

}

std::vector<Task> Plan::set_affinity(std::vector<Task> tasks)
{

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
