struct Task {
    int priority;
    int Arrival_Time;
    int Service_Time;
    int Service_Start_Time;
    int Developer_ID;

};
struct Node {
    struct Task t;
    struct Node *next;
};
struct TaskList {
    struct Node *head;
    struct Node *tail;
    int size;
};
typedef struct TaskList *List;
struct QueueRecord {
    struct Node *front;
    struct Node *rear;
    int size;
};
typedef struct QueueRecord *Queue;

void InsertNode(List l, int pos, struct Task t);

Queue CreateQueue();

void MakeEmptyQueue(Queue);

int compareTasks(struct Task task1, struct Task task2);

List CreateList();

struct Node *Dequeue(Queue q);

int IsEmptyQueue(Queue);

void Enqueue(Queue q, struct Node *t);

void insertionSort(List l);


#ifndef UNTITLED_QUEUE_H
#define UNTITLED_QUEUE_H


#endif //UNTITLED_QUEUE_H




