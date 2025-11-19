#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include "change_request.h"

typedef struct
{
    ChangeRequest *heap;
    int size;
    int capacity;
} PriorityQueue;

void initPQ(PriorityQueue *pq, int capacity);
void enqueue(PriorityQueue *pq, ChangeRequest data);
ChangeRequest dequeue(PriorityQueue *pq);
int isPQEmpty(PriorityQueue *pq);
void heapifyDown(PriorityQueue *pq, int i);
void updatePrioritiesPQ(PriorityQueue *pq, int newPriority);
void removeByIdFromPQ(PriorityQueue *pq, int id);

#endif
