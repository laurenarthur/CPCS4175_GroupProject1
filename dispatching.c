#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>

#include "queue.h"

int run_job_process(){
    
    //Process that waits tell user quits out of the program 
    pid_t child_running = fork();

    //creating  something to pull execution time out of queue to display 

    if(child_running<0){
        printf("Failed\n");
        exit(1);
    }

    if(child_running==0){
        //simulate a job running 
        execv("./process");
    }

    int statusOfjob;
    wait(&statusOfjob);

    if(statusOfjob ==0 ){
        printf("Parent: It Worked\n");
    }
    else if (statusOfjob == 1 ){
        printf("Terminate with error\n");
    }
}