#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include "Queue.h"


#define Critical 4
#define High_priority 3
#define Medium 2
#define Normal 1

void parseInput(int *noOfTasks, int *noOfDeveloper, int *maxArrivalTime, int *maxServiceTime);

void reportStatistics(List l, int noOfDeveloper);

List createTaskList(int noOfTasks, int noOfDeveloper, int maxArrivalTime, int maxServiceTime);

void accomplishTask(Queue q, List l, int DeveloperAvailability[], int noOfDeveloper, int currentTime);

void newTask(Queue q, List l, int DeveloperAvailability[], int noOfDeveloper);

Queue initialiseSimulator(List l, int noOfDeveloper, int *DeveloperAvailability);

int main() {
    srand(time(NULL));
    int DeveloperAvailability[0];
    int noOfTasks, noOfDeveloper, maxArrivalTime, maxServiceTime;
    parseInput(&noOfTasks, &noOfDeveloper, &maxArrivalTime, &maxServiceTime);
    List l = createTaskList(noOfTasks, noOfDeveloper, maxArrivalTime, maxServiceTime);
    Queue q = initialiseSimulator(l, noOfDeveloper, DeveloperAvailability);
    accomplishTask(q, l, DeveloperAvailability, noOfDeveloper, 0);
    reportStatistics(l, noOfDeveloper);

    return 0;
}


void parseInput(int *noOfTasks, int *noOfDeveloper, int *maxArrivalTime, int *maxServiceTime) {
    printf("TODO_Simulator:");
    scanf("%d %d %d %d", noOfTasks, noOfDeveloper, maxArrivalTime, maxServiceTime);
}


List createTaskList(int noOfTasks, int noOfDeveloper, int maxArrivalTime, int maxServiceTime) {
    List TaskList = CreateList();
    struct Node *tmpTaskNode;
    for (int i = 0; i < noOfTasks; ++i) {
        tmpTaskNode = (struct Node *) malloc(sizeof(struct Node));
        if (tmpTaskNode == NULL) {
            printf("out of Memory");
        } else {
            struct Task t;
            t.priority = 1 + rand() % 4;
            t.Arrival_Time = 1 + rand() % (maxArrivalTime);
            t.Service_Time = 1 + rand() % (maxServiceTime);
            t.Developer_ID = 0;
            t.Service_Start_Time = 0;


            // check the insert method again
            InsertNode(TaskList, i + 1, t);
        }
    }
    insertionSort(TaskList);
    //DisplayList(TaskList);
    return TaskList;
}


Queue initialiseSimulator(List l, int noOfDeveloper, int *DeveloperAvailability) {
    Queue q = CreateQueue();
    for (int i = 0; i < noOfDeveloper; ++i) {
        DeveloperAvailability[i] = 1;
    }
    newTask(q, l, DeveloperAvailability, noOfDeveloper);
    return q;
}

void newTask(Queue q, List l, int DeveloperAvailability[], int noOfDeveloper) {
    int devNum = 0;
    int i = 0;
    struct Node *tmp = l->head->next;
    if (IsEmptyQueue(q)) {
        while (i != noOfDeveloper) {

            do {
                devNum = rand() % noOfDeveloper;
            } while (DeveloperAvailability[devNum] == 0);

            DeveloperAvailability[devNum] = 0;
            // Update Service start time
            for (int j = 0; j < i; ++j) {
                tmp = tmp->next;
            }
            tmp->t.Developer_ID = devNum;

            i++;
        }
    } else {
        while (tmp != NULL) {
            Enqueue(q, tmp);
            tmp = tmp->next;
        }

    }
}

void accomplishTask(Queue q, List l, int DeveloperAvailability[], int noOfDeveloper, int currentTime) {

    if (!IsEmptyQueue(q)) {

        struct Node *completedTask = Dequeue(q);

        completedTask->t.Service_Start_Time = currentTime;
        int devolperId = completedTask->t.Developer_ID;


        DeveloperAvailability[devolperId] = 0;

        DeveloperAvailability[devolperId] = 1;

        InsertNode(l, l->size + 1, completedTask->t);

        free(completedTask);
    }
}

void reportStatistics(List l, int noOfDeveloper) {
    int criticalCount = 0, highPriorityCount = 0, mediumCount = 0, normalCount = 0;
    int developerCount[noOfDeveloper];
    int completionTime = 0, totalWaitingTime = 0, maxWaitingTime = 0;

    for (int i = 0; i < noOfDeveloper; ++i) {
        developerCount[i] = 0;
    }

    struct Node *currentNode = l->head->next;

    while (currentNode != NULL) {
        switch (currentNode->t.priority) {
            case Critical:
                criticalCount++;
                break;
            case High_priority:
                highPriorityCount++;
                break;
            case Medium:
                mediumCount++;
                break;
            case Normal:
                normalCount++;
                break;
        }

        developerCount[currentNode->t.Developer_ID]++;

        completionTime = currentNode->t.Service_Start_Time + currentNode->t.Service_Time;

        int waitingTime = currentNode->t.Service_Start_Time - currentNode->t.Arrival_Time;
        totalWaitingTime += waitingTime;

        if (waitingTime > maxWaitingTime) {
            maxWaitingTime = waitingTime;
        }

        currentNode = currentNode->next;
    }

    double averageWaitingTime = (double) totalWaitingTime / l->size;

    printf("****************Report*****************\n/n");
    printf("*The number of Developers is: %d\n", noOfDeveloper);
    printf("*The number of Tasks: %d\n", l->size);
    printf("*Number of Tasks for each Label:\n");
    printf(" Critical: %d\n", criticalCount);
    printf(" High priority: %d\n", highPriorityCount);
    printf(" Medium: %d\n", mediumCount);
    printf(" Normal: %d\n", normalCount);
    printf("*Number of Tasks for each Developer:\n");
    for (int i = 0; i < noOfDeveloper; ++i) {
        printf("Developer %d Accomplished: %d\n", i + 1, developerCount[i]);
    }
    printf("*Completion time: %d\n", completionTime);
    printf("*Average time spent in the queue: %.2f\n", averageWaitingTime);
    printf("*Maximum waiting time: %d\n", maxWaitingTime);
}
