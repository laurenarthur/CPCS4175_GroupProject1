#include <stdio.h>
#include <pthread.h>
#include "parser.h"

int main(){
    pthread_t scheduling, dispatching;
    while(1){
        parse();
    }
    return 0;
}