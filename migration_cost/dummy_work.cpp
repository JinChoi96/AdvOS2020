#include "dummywl.h"

void *dummy_work(void *data){
    struct thread_args *args = (struct thread_args *)data;
    unsigned int iter = 600000 * args->iter;
    int sum = 0;
    int s;
    cpu_set_t cpuset;

  
    CPU_ZERO(&cpuset);    
    CPU_SET(0, &cpuset);

    s = pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
    if(s != 0){
        std::cout<<"error in pthread_setaffinity_np\n";
    }
    for (int j = 0; j < CPU_SETSIZE; j++)
               if (CPU_ISSET(j, &cpuset))
                   printf("    CPU %d\n", j);
    
    auto start = std::chrono::high_resolution_clock::now(); 

    if(args->cpus == 2){
        for(unsigned i = 0; i < args->iter/2; i++){
            sum += i;
        }

        sleep(10);

        CPU_ZERO(&cpuset);    
        CPU_SET(1, &cpuset);    

        s = pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
        if(s != 0){
            std::cout<<"error in pthread_setaffinity_np\n";
        }

        for(unsigned i = 0; i < args->iter/2; i++){
            sum += i;
        }
    }
    else{
        sleep(10);

        for(unsigned i = 0; i < args->iter; i++){
            sum += i;
        }
    }
    for (int j = 0; j < CPU_SETSIZE; j++)
               if (CPU_ISSET(j, &cpuset))
                   printf("    CPU %d\n", j);
    
    auto end = std::chrono::high_resolution_clock::now();    
    std::chrono::milliseconds elapsedNS = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);    
    std::cout<<"time: "<< elapsedNS.count()<<" ms\n";
}

int main(int argc, char** argv){
    struct thread_args args;
	args.online = false;
	args.iter = atoi(argv[1]);
	args.cpus = atoi(argv[2]);

	pthread_t _thread;

	if (pthread_create(&_thread, NULL, &dummy_work, (void *)&args) != 0) { 
		perror("pthread_create"); 
	} 
	pthread_exit(NULL);

    return 0;
}