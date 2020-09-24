#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node
{
    char *name;
    int jobTime;
    int jobPriority;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *head, *tail;
    unsigned int size;
} Queue;

Queue* initializeQueue();
// TODO: change to use global queue - jobQueue
void enQueue(Node *newNode );
Node* deQueue();
void printQueue();
void print_num_jobs();
void swap_nodes(Node *node1, Node *node2);

#endif