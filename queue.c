#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>  

#include "queue.h"
#include "global.h"

//placeholders to print out 
int TAT = 0.0;
int CPUT = 0.0;
int WT= 0.0;

//Initializes a queue and returns it 
Queue* initializeQueue(){
    Queue *queue = (Queue*) malloc(sizeof(Queue));
    queue->head = queue->tail = NULL;
    queue->size = 0;
    return queue;
}

void enQueue(Node *newNode){
    newNode->arrivalTime = clock();

    //empty queue = set head and tail to new node 
    if(job_queue->size == 0){
        job_queue->head = job_queue->tail = newNode;
        job_queue->tail->next = NULL;
        job_queue->size++;
    }
    else{
        //adding node to queue move tail to end 
        job_queue->tail->next = newNode;
        job_queue->tail = job_queue->tail->next;
        job_queue->tail->next = NULL;
        job_queue->size++;
    }
}

Node* deQueue(){
    if(job_queue->size == 0){
        return NULL; 
    }

    Node *removedNode;
    removedNode = job_queue->head;
    job_queue->head = job_queue->head->next;
    job_queue->size--;
    return removedNode; 
}

void copy_node(Node *destination, Node *source){
    destination->name  = (char*) malloc(strlen(source->name) + 1);
    strcpy(destination->name, source->name);
    destination->arrivalTime = source->arrivalTime;
    destination->jobPriority = source->jobPriority;
    destination->jobTime = source->jobTime;
}

void swap_nodes(Node *node1, Node *node2){
    Node *tempNode = (Node *) malloc(sizeof(Node)); // holding temporary inforamtion in memory 
    copy_node(tempNode, node1);
    copy_node(node1, node2);
    copy_node(node2, tempNode);

    free(tempNode);
}

void printQueue(){
    if(job_queue->size == 0){
        printf("There are not jobs pending or running.\n");
    }
    else {
        printf("Name        CPU_Time   Pri   Ariival_Time   Progress\n");
        Node *tempNode = job_queue->head;
        char str_time[11];
        char str_pri[6];
        while (tempNode != NULL)
        {
            snprintf(str_time, 10, "%d", tempNode->jobTime);
            snprintf(str_pri, 5, "%d", tempNode->jobPriority);
            printf("%-15s%-11s%-3s\n", tempNode->name, str_time, str_pri);
            tempNode = tempNode->next;
        }
    }
}

void print_num_jobs(){
    printf("Total number of jobs: %d\n", job_queue->size);
}

//Just trying to put place holders right now tell I can figure out how to actually caculate these times 
void print_turnaround_time(){
    //turn around time = waiting_time + burst_time for all processes
    //average = toatl_turn_around_time / number_of_processes
    printf("Average turnaround time: %d\n", TAT);
}

void print_CPU_time(){
    //amount of time from when a request was submitted until the first response is produced 
    printf("Average CPU time: %d\n", CPUT);
}

void print_waiting_time(){
    //waiting time = total_waiting_time / number_of_processes
    printf("Average waiting time: %d\n", WT);
}