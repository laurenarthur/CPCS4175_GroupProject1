#include <bits/types/locale_t.h>
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

int num;

time_t arrivalT, val = 1;
struct tm* current_time;
struct tm* new_time;


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

        int seconds = {rand() % 20};

        arrivalT = time(NULL);
        current_time = localtime(&arrivalT); //Cant get time to update for each node.
        

        while (tempNode != NULL)
        {
            tempNode->arrivalTime = clock();
            
            snprintf(str_time, 10, "%d", tempNode->jobTime);
            snprintf(str_pri, 5, "%d", tempNode->jobPriority);
            printf("%-15s%-11s%-3s %02d:%02d:%02d\n", tempNode->name, str_time, str_pri, current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
            tempNode = tempNode->next;
            //tempNode -> current_time -> tm_sec+=seconds;

            if(current_time -> tm_sec == 60 || current_time -> tm_sec > 55 ){
                current_time ->tm_min++;
                current_time -> tm_sec = 0;
                current_time -> tm_sec+=seconds;
            }
            else{
                current_time -> tm_sec+=seconds;
            }
            

            
        }
    }
}

void print_num_jobs(){
    printf("Total number of jobs: %d\n", job_queue->size);
}


//Just trying to put place holders right now tell I can figure out how to actually caculate these times 
void print_turnaround_time() {
    //turn around time = waiting_time + burst_time for all processes
    //average = toatl_turn_around_time / number_of_processes

    int proc[] = {job_queue->size};

    int burst_time[0] = {rand() % 20}; //set burst time to random


    int wait_time[0];
    wait_time[0] = 0;

    char str_time[11];


    int tat[0];

    int total_wt = 0, total_tat = 0;

    clock_t newNode = clock();

    for (int i = 1; i < job_queue->size ; i++ ){
        wait_time[i] = burst_time[i - 1] + wait_time[i -1];
        
    }


   for(int j = 0; j < job_queue->size ; j++){
       tat[j] = burst_time[j] + wait_time[j];
   }

   // Calculate total waiting time and total turn
   // around time
   for (int t = 0; t < job_queue->size; t++) {
      total_wt = total_wt + wait_time[t];
      total_tat = total_tat + tat[t];
   }
   clock_t oldNode = clock();
   
   printf("Average turn around time: %.2f\n\n", (float)total_tat / (float)job_queue->size);

   CPUT = (double)(oldNode - newNode) / CLOCKS_PER_SEC;

   printf("Average CPU time: %d\n\n", CPUT + (int)str_time / job_queue->size );

   
   printf("Average waiting time:  %f\n\n", (float)total_wt / (float)job_queue->size);


    //printf("Average turnaround time: %d\n", waitingtime(proc[job_queue->size, n, burst_time, wait_time));
}


//void print_CPU_time(){
    //amount of time from when a request was submitted until the first response is produced 
    //printf("Average CPU time: \n");

    //printf("Average CPU time: %d\n", CPUT);
//}

//void print_waiting_time(){
    //waiting time = total_waiting_time / number_of_processes
    
   //printf("Average waiting time: %d\n", WT);
//}