
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>
 #include <linux/unistd.h>
 #include <linux/kernel.h>
 #include <linux/types.h>
 #include <sys/syscall.h>
 #include <pthread.h>
 #include <iostream>
 #include <fstream>
 #include <string>
 #include <random>
 #include <algorithm>

 #include <vector>
 #include <thread>

 #define gettid() syscall(__NR_gettid)

 #define SCHED_DEADLINE	6
 #define HYBRID 1

 /* XXX use the proper syscall numbers */
 #ifdef __x86_64__
 #define __NR_sched_setattr		314
 #define __NR_sched_getattr		315
 #endif

 #ifdef __i386__
 #define __NR_sched_setattr		351
 #define __NR_sched_getattr		352
 #endif

 #ifdef __arm__
 #define __NR_sched_setattr		380
 #define __NR_sched_getattr		381
 #endif


#ifndef __SCHED_ATTR__
#define __SCHED_ATTR__
struct sched_attr {
	__u32 size;

	__u32 sched_policy;
	__u64 sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	__s32 sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	__u32 sched_priority;

	/* SCHED_DEADLINE (nsec) */
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
};
#endif


#ifndef __THREAD_ARGS__
#define __THREAD_ARGS__
struct thread_args{
	int iter;
	bool online;
	int cpus;
};
#endif
