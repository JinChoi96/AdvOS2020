#include "include.h"

void *dummy_work(void *data);
void *dummy_write(void *data);
void *dummy_read(void *data);
void *crawl_webpage(void *data);
void *dummy_sort(void *data);

int num_tasks = 6;
std::array<int, 6> runtimes = {10, 10, 10, 10, 10, 10};
std::array<int, 6> deadlines = {30, 30, 30, 30, 30, 30};