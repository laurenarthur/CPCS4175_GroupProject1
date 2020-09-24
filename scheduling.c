#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>

#include "queue.h"
#include "scheduling.h"
#include "policies.h"
#include "global.h"

/*
* Prints the policy according to whats selected by the user 
*/
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

/* 
* First Come First Served policy 
*/
int orderFCFS(){

    if(job_queue -> size == 0){
        printf("There are currently no jobs in the queue to order");
        return -1;
    }

    if(job_queue -> size == 1){
        printf("There is currently only 1 job in the queue, reorder not needed!");
        return 0;
    }

    Node *temp_pointer = job_queue -> head; //assigns the current jobQueue as head.
    

    printf("Scheduiling policy is switched to FCFS. All the %d waiting jobs have been rescheduled.\n", job_queue->size);
    policy = FCFS;
    return 0;
}

/* 
* Second Job First policy 
*/

int orderSJF(){

    if(job_queue -> size == 0){
        printf("There are currently no jobs in the queue to order");
    }

    if(job_queue -> size == 1){
        printf("There is currently only 1 job in the queue, reorder not needed!");
        return 0;
    }

    Node *temp_pointer = job_queue -> head; //assigns the current jobQueue as head.


    printf("Scheduiling policy is switched to SJF. All the %d waiting jobs have been rescheduled.\n", job_queue->size);
    policy = FCFS;
    return 0;
}

/* 
* Priority policy 
*/

int orderPriority(){

    if(job_queue -> size == 0){
        printf("There are currently no jobs in the queue to order");
    }

    if(job_queue -> size == 1){
        printf("There is currently only 1 job in the queue, reorder not needed!");
        return 0;
    }

    Node *temp_pointer = job_queue -> head; //assigns the current jobQueue as head.

    printf("Scheduiling policy is switched to Priority. All the %d waiting jobs have been rescheduled.\n", job_queue->size);
    policy = FCFS;
    return 0;
}