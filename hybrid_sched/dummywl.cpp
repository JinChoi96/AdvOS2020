#include "dummywl.h"

void *dummy_work(void *data){
    if(HYBRID){
        Task *task = (Task*)data;
        struct sched_attr attr = task->get_attr();
        int ret;
        unsigned int flags = 0;

        ret = task->sched_setattr(0, &attr, flags);
        if(ret < 0){
            perror("sched_setattr");
            exit(-1);
        }
    }
    int iter = 10000000;
    int sum = 0;
    
    for(unsigned i = 0; i < iter; i++){
        sum += i;
    }
}

void *dummy_write(void *data){
    if(HYBRID){
        Task *task = (Task*)data;
        struct sched_attr attr = task->get_attr();
        int ret;
        unsigned int flags = 0;

        ret = task->sched_setattr(0, &attr, flags);
        if(ret < 0){
            perror("sched_setattr");
            exit(-1);
        }
    }
    int iter = 10000;

    for(int i = 0; i < iter; i++){
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
    if(HYBRID){
        Task *task = (Task*)data;
        struct sched_attr attr = task->get_attr();
        int ret;
        unsigned int flags = 0;

        ret = task->sched_setattr(0, &attr, flags);
        if(ret < 0){
            perror("sched_setattr");
            exit(-1);
        }
    }
    std::string line;
    int iter = 10000;

    for(int i = 0; i < iter; i++){
        std::fstream dummyfile ("dummytext.txt");
        
        if (dummyfile.is_open())
        {        
            while(std::getline(dummyfile,line)){
                //std::cout << line << '\n';
            }      
            dummyfile.close();
        }
        else{
            std::cout << "Unable to open file";
        }
    }
}

void *dummy_sort(void *data){
    if(HYBRID){
        Task *task = (Task*)data;
        struct sched_attr attr = task->get_attr();
        int ret;
        unsigned int flags = 0;

        ret = task->sched_setattr(0, &attr, flags);
        if(ret < 0){
            perror("sched_setattr");
            exit(-1);
        }
    }
    int iter = 10000;

    int size = 1000;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> dis(0,1000);
    int iarr[size] = {0};

    for(int i = 0; i < iter; i++){
        for(int j = 0; j < size; j++){
            iarr[j] = dis(gen);
        }
        std::sort(iarr,iarr+size);
    }   
}
