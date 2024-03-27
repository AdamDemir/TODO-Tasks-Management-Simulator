#include "Queue.h"
#include <stdio.h>
#include <malloc.h>

Queue CreateQueue() {
    Queue q;


    q = (Queue) malloc(sizeof(struct QueueRecord));
    if (q == NULL)
        printf("Out of memory space\n");
    else
        MakeEmptyQueue(q);
    return q;
}

void MakeEmptyQueue(Queue q) {
    q->size = 0;
    q->front = (struct Node *) malloc(sizeof(struct Node));
    if (q->front == NULL)
        printf("Out of memory space\n");
    else {
        q->front->next = NULL;
        q->rear = q->front;
    }
}

void MakeEmptyList(List l) {
    l->head = (struct Node *) malloc(sizeof(struct Node));
    if (l->head == NULL) {
        printf("Out of memory space\n");
        exit(1);
    } else {
        l->head->next = NULL;
        l->tail = l->head;
        l->size = 0;
    }
}

int isEmptyList(List l) {
    return (l->size == 0);
}


int ListSize(List l) {
    return l->size;
}

List CreateList() {
    List l;
    l = (List) malloc(sizeof(struct TaskList));
    if (l == NULL) {
        printf("Out of Memory\n");
        exit(1);
    } else {
        MakeEmptyList(l);
    }
    return l;
}

void InsertNode(List l, int pos, struct Task t) {
    struct Node *InsertNode = (struct Node *) malloc(sizeof(struct Node));
    if (InsertNode == NULL) {
        printf("Out of Memory\n");
        exit(1);
    } else {
        InsertNode->t = t;
        InsertNode->next = NULL;
        if (pos > l->size)
            pos = l->size + 1;
        if (pos == (l->size + 1)) {
            l->tail->next = InsertNode;
            l->tail = InsertNode;
        } else {
            struct Node *tmpNode = l->head;
            if (tmpNode == NULL) {
                printf("Out of Memory\n");
                exit(1);
            }
            for (int i = 0; i < pos - 1; ++i) {
                tmpNode = tmpNode->next;
            }
            InsertNode->next = tmpNode->next;
            tmpNode->next = InsertNode;

        }
        l->size++;
    }
    insertionSort(l);
}


int IsEmptyQueue(Queue q) {
    return (q->size == 0);
}


void Enqueue(Queue q, struct Node *t) {


    struct Node *current = q->front;
    struct Node *previous = NULL;

    while (current != NULL && compareTasks(current->t, t->t) < 0) {
        previous = current;
        current = current->next;
    }


    if (previous == NULL) {

        t->next = q->front;
        q->front = t;
    } else {

        previous->next = t;
        t->next = current;
    }

}

int compareTasks(struct Task task1, struct Task task2) {
    if (task1.priority != task2.priority) {
        return task2.priority - task1.priority;
    } else {
        return task1.Arrival_Time - task2.Arrival_Time;
    }
}


struct Node *Dequeue(Queue q) {
    struct Node *DeleteNode = q->front;
    q->front = DeleteNode->next;

    q->size--;
    if (IsEmptyQueue(q)) {
        q->rear = NULL;
    }
    struct Node *tmp = DeleteNode;
    free(DeleteNode);
    return tmp;

}


void DisplayList(List l) {
    struct Node *current = l->head->next;
    while (current != NULL) {
        printf("Arrival Time: %d, Service Time: %d, Priority: %d, Developer ID: %d, Service Start Time: %d\n",
               current->t.Arrival_Time, current->t.Service_Time, current->t.priority, current->t.Developer_ID,
               current->t.Service_Start_Time);
        current = current->next;
    }

}

void insertionSort(List l) {
    if (l->head->next == NULL || l->head->next->next == NULL) {

        return;
    }

    struct Node *sorted = NULL;
    struct Node *min = l->head->next;

    while (min != NULL) {
        struct Node *next = min->next;

        if (sorted == NULL || sorted->t.Arrival_Time >= min->t.Arrival_Time) {

            min->next = sorted;
            sorted = min;
        } else {

            struct Node *temp = sorted;
            while (temp->next != NULL && temp->next->t.Arrival_Time < min->t.Arrival_Time) {
                temp = temp->next;
            }
            min->next = temp->next;
            temp->next = min;
        }

        min = next;
    }

    l->head->next = sorted;
}
