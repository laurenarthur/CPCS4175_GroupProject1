typedef struct Node{
    char *name;
    int jobTime;
    int jobPriority;
    struct Node *next;
} Node;

typedef struct Queue{
    Node *head, *tail;
} Queue;

Queue *initializeQueue();
void enQueue(Node *newNode);
Node* deQueue();
void printQueue();
void print_number_jobs();
void swap_nodes(Node *node1, Node *node2);