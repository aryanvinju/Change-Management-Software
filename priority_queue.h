#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include "change_request.h"
typedef struct{ChangeRequest heap[100];int size;}PriorityQueue;
void initPQ(PriorityQueue* pq);
void enqueue(PriorityQueue* pq, ChangeRequest data);
ChangeRequest dequeue(PriorityQueue* pq);
int isPQEmpty(PriorityQueue* pq);
#endif