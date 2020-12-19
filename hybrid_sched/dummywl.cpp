#include "dummywl.h"

void *dummy_work(void *data){
    struct thread_args *args = (struct thread_args *)data;
    unsigned int iter = 600000 * args->iter;
    int sum = 0;
    int s;
    cpu_set_t cpuset;

    CPU_SET(args->cpus,&cpuset);
    s = pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
    if(s != 0){
        std::cout<<"error in pthread_setaffinity_np\n";
    }

    for(unsigned i = 0; i < iter; i++){
        sum += i;
    }
}

void *dummy_write(void *data){
    struct thread_args *args = (struct thread_args *)data;
    int s;
    cpu_set_t cpuset;

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

void *dummy_read(void *data){
    struct thread_args *args = (struct thread_args *)data;
    std::string line;
    int s;
    cpu_set_t cpuset;

    s = pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
    if(s != 0){
        std::cout<<"error in pthread_setaffinity_np\n";
    }

    for(int i = 0; i < args->iter; i++){
        std::fstream dummyfile ("dummytext.txt");
        
        if (dummyfile.is_open())
        {        
            while(std::getline(dummyfile,line)){
                std::cout << line << '\n';
            }      
            dummyfile.close();
        }
        else{
            std::cout << "Unable to open file";
        }
    }
}

void *dummy_sort(void *data){
    struct thread_args *args = (struct thread_args *)data;

    int size = 1000;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> dis(0,1000);
    int iarr[size] = {0};
    int s;
    cpu_set_t cpuset;

    s = pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
    if(s != 0){
        std::cout<<"error in pthread_setaffinity_np\n";
    }

    for(int i = 0; i < args->iter; i++){
        for(int j = 0; j < size; j++){
            iarr[j] = dis(gen);
        }
        std::sort(iarr,iarr+size);
    }   
}