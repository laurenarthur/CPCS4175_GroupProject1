#include <stdio.h>
#include <pthread.h>
#include "parser.h"
#include "global.h"

int main(){
    pthread_t scheduling, dispatching;
    while(1){
        parse();
    }
    return 0;
}