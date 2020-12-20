#define _GNU_SOURCE
 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>
 #include <iostream>
 #include <fstream>
 #include <string>
 #include <random>
 #include <algorithm>
 #include <pthread.h>
 #include <vector>
 #include <thread>
 #include <chrono>
 #include <ctime>


struct thread_args{
	int iter;
	bool online;
	int cpus;
};