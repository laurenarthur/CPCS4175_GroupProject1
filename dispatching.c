#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>

int run_job_process(){
    
    //Process that waits tell user quits out of the program 
    pid_t child_running = fork();

    if(child_running<0){
        printf("Failed");
        exit(1);
    }

    if(child_running==0){
        execv("./process");
    }
}