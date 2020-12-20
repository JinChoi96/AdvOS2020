#include "dummywl.h"

void *dummy_work(void *data){
    Task *task = (Task*)data;
    struct sched_attr attr = task->get_attr();
    int ret;
    unsigned int flags = 0;

    ret = task->sched_setattr(0, &attr, flags);
    if(ret < 0){
        perror("sched_setattr");
        exit(-1);
    }

    // iter * k(=6)
    int iter = 500000000;
    int sum = 0;

    auto start = std::chrono::high_resolution_clock::now();  

    for(int k = 0 ; k < 6; k++){  
        for(unsigned i = 0; i < iter; i++){
            sum += i;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds elapsedNS = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);    
    std::cout<<"time 1: "<< elapsedNS.count()<<" ms\n";    

}


void *dummy_write(void *data){
    Task *task = (Task*)data;
    struct sched_attr attr = task->get_attr();
    int ret;
    unsigned int flags = 0;

    ret = task->sched_setattr(0, &attr, flags);
    if(ret < 0){
        perror("sched_setattr");
        exit(-1);
    }

    int iter = 1000000;

    auto start = std::chrono::high_resolution_clock::now();
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
    auto end = std::chrono::high_resolution_clock::now();   
    std::chrono::milliseconds elapsedNS = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);    
    std::cout<<"time 2: "<< elapsedNS.count()<<" ms\n"; 

}

void *dummy_read(void *data){
    Task *task = (Task*)data;
    struct sched_attr attr = task->get_attr();
    int ret;
    unsigned int flags = 0;

    ret = task->sched_setattr(0, &attr, flags);
    if(ret < 0){
        perror("sched_setattr");
        exit(-1);
    }

    std::string line;
    int iter = 1000000;

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < iter; i++){
        std::fstream dummyfile ("dummytext.txt");
        
        if (dummyfile.is_open())
        {        
            while(std::getline(dummyfile,line)){
                // std::cout << line << '\n';
            }      
            dummyfile.close();
        }
        else{
            std::cout << "Unable to open file";
        }
    }
    auto end = std::chrono::high_resolution_clock::now();   
    std::chrono::milliseconds elapsedNS = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);    
    std::cout<<"time 3: "<< elapsedNS.count()<<" ms\n"; 

}

void *dummy_sort(void *data){
    Task *task = (Task*)data;
    struct sched_attr attr = task->get_attr();
    int ret;
    unsigned int flags = 0;

    ret = task->sched_setattr(0, &attr, flags);
    if(ret < 0){
        perror("sched_setattr");
        exit(-1);
    }

    int iter = 30000;

    int size = 1000;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> dis(0,1000);
    int iarr[size] = {0};

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < iter; i++){
        for(int j = 0; j < size; j++){
            iarr[j] = dis(gen);
        }
        std::sort(iarr,iarr+size);
    }  
    auto end = std::chrono::high_resolution_clock::now();    
    std::chrono::milliseconds elapsedNS = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);    
    std::cout<<"time 4: "<< elapsedNS.count()<<" ms\n";
 
}