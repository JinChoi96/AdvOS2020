#include "include.h"

void msec_work(int msec){
    unsigned int iter = 600000 * msec;
    int sum = 0;
    for(unsigned i = 0; i < iter; i++){
        sum += i;
    }
    return;
}

void dummy_write(){
    return;
}

void dummy_read(){
    return;
}

void traverse_directory(){
    return;
}