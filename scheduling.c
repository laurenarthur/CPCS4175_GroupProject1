#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>

#include "queue.h"
#include "scheduling.h"
#include "policies.h"
#include "global.h"

void print_policy(){
    if(policy == FCFS){
        printf("Scheduling Policy: FCFS.\n");
    }
    else if(policy == SJF){
        printf("Scheduling Policy: SJF.\n");
    }
    else{
        printf("Scheduling Policy: Priority.\n");
    }
}

int orderFCFS(){

    printf("Scheduiling policy is switched to FCFS. All the %d waiting jobs have been rescheduled.\n", job_queue->size);
    policy = FCFS;
    return 0;
}

int orderSJF(){

     printf("Scheduiling policy is switched to SJF. All the %d waiting jobs have been rescheduled.\n", job_queue->size);
    policy = FCFS;
    return 0;
}

int orderPriority(){

     printf("Scheduiling policy is switched to Priority. All the %d waiting jobs have been rescheduled.\n", job_queue->size);
    policy = FCFS;
    return 0;
}