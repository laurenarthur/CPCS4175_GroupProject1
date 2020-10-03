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
    if(policy == 1){
        printf("Scheduling Policy: FCFS.\n");
    }
    else if(policy == 2){
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

    Node *tempPointer = job_queue -> head; //assigns the current jobQueue as head.
    //pthread_mutex_lock(tempPointer); //Locks the jobqueue?

    while(tempPointer != NULL){

        Node *min = tempPointer;
        Node *tempNode = tempPointer -> next;

        while(tempNode != NULL){
            if(min -> arrivalTime > tempNode -> arrivalTime){
                min = tempNode;
            }
            tempNode = tempNode -> next;
        }
            if(tempPointer != min){
                swap_nodes(tempPointer, min);
                tempPointer = tempPointer -> next;
            }
            else{
                tempPointer = tempPointer -> next;
            } 
        }


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

    Node *tempPointer = job_queue -> head; //assigns the current jobQueue as head.
    //pthread_mutex_lock(tempPointer); //Locks the jobqueue?

    while(tempPointer != NULL){

        Node *min = tempPointer;
        Node *tempNode = tempPointer -> next;

        while(tempNode != NULL){
            if(min -> jobTime > tempNode -> jobTime){
                min = tempNode;
            }
            tempNode = tempNode -> next;
        }
            if(tempPointer != min){
                swap_nodes(tempPointer, min);
                tempPointer = tempPointer -> next;
            }
            else{
                tempPointer = tempPointer -> next;
            } 
        }

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

    Node *tempPointer = job_queue -> head; //assigns the current jobQueue as head.

    //pthread_mutex_lock(tempPointer); //Locks the jobqueue?

    while(tempPointer != NULL){

        Node *min = tempPointer;
        Node *tempNode = tempPointer -> next;

        while(tempNode != NULL){
            if(min -> jobPriority > tempNode -> jobPriority){
                min = tempNode;
            }
            tempNode = tempNode -> next;
        }
            if(tempPointer != min){
                swap_nodes(tempPointer, min);
                tempPointer = tempPointer -> next;
            }
            else{
                tempPointer = tempPointer -> next;
            } 
        }

    printf("Scheduiling policy is switched to Priority. All the %d waiting jobs have been rescheduled.\n", job_queue->size);
    policy = FCFS;
    return 0;
}