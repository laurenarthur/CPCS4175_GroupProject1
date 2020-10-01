#ifndef QUEUE_H
#define QUEUE_H

#include <time.h> 

//Node structure for jobs
typedef struct Node
{
    char *name;
    int jobTime;
    int jobPriority;
    clock_t arrivalTime; //only for FCFS
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *head, *tail;
    unsigned int size;
} Queue;

Queue* initializeQueue();

void enQueue(Node *newNode );
Node* deQueue();
void printQueue();
void print_num_jobs();
void swap_nodes(Node *node1, Node *node2);

void print_turnaround_time();
void print_CPU_time();
void print_waiting_time();

#endif