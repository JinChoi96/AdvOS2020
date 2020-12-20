#include "dummywl.h"

void *dummy_write(void *data){
    struct thread_args *args = (struct thread_args *)data;
    cpu_set_t cpuset;
    int s;

  
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
        for(int i = 0; i < args->iter; i++){
            std::fstream dummyfile ("dummytext.txt");
            if (dummyfile.is_open())
            {            
                dummyfile << "Dummy workload.\n";            
                dummyfile.close();
            }
            else{
                std::cout << "Unable to open file";
            }
        }

        sleep(10);

        CPU_ZERO(&cpuset);    
        CPU_SET(1, &cpuset);    

        s = pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
        if(s != 0){
            std::cout<<"error in pthread_setaffinity_np\n";
        }

        for(int i = 0; i < args->iter; i++){
            std::fstream dummyfile ("dummytext.txt");
            if (dummyfile.is_open())
            {            
                dummyfile << "Dummy workload.\n";            
                dummyfile.close();
            }
            else{
                std::cout << "Unable to open file";
            }
        }
    }
    else{
        sleep(10);
        for(int i = 0; i < args->iter; i++){
            std::fstream dummyfile ("dummytext.txt");
            if (dummyfile.is_open())
            {            
                dummyfile << "Dummy workload.\n";            
                dummyfile.close();
            }
            else{
                std::cout << "Unable to open file";
            }
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

	if (pthread_create(&_thread, NULL, &dummy_write, (void *)&args) != 0) { 
		perror("pthread_create"); 
	} 
	pthread_exit(NULL);

    return 0;
}