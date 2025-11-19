#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

void initPQ(PriorityQueue *pq, int capacity) {
    pq->size = 0;
    pq->capacity = capacity;
    pq->heap = (ChangeRequest *)malloc(capacity * sizeof(ChangeRequest));
    
    if (pq->heap == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for priority queue.\n");
        exit(EXIT_FAILURE);
    }
}

void swap(ChangeRequest *a, ChangeRequest *b)
{
    ChangeRequest t = *a;
    *a = *b;
    *b = t;
}

void heapifyUp(PriorityQueue *pq, int i)
{
    if (i == 0)
        return;
    int p = (i - 1) / 2;
    if (pq->heap[p].priority > pq->heap[i].priority)
    {
        swap(&pq->heap[p], &pq->heap[i]);
        heapifyUp(pq, p);
    }
}

void heapifyDown(PriorityQueue *pq, int i)
{
    int l = 2 * i + 1, r = 2 * i + 2, s = i;
    if (l < pq->size && pq->heap[l].priority < pq->heap[s].priority)
        s = l;
    if (r < pq->size && pq->heap[r].priority < pq->heap[s].priority)
        s = r;
    if (s != i)
    {
        swap(&pq->heap[i], &pq->heap[s]);
        heapifyDown(pq, s);
    }
}

void enqueue(PriorityQueue *pq, ChangeRequest d)
{
    if (pq->size == pq->capacity) {
        printf("Priority queue full!\n");
        return;
    }
    pq->heap[pq->size] = d;
    heapifyUp(pq, pq->size);
    pq->size++;
}

ChangeRequest dequeue(PriorityQueue *pq)
{
    ChangeRequest e = {0}; 
    if (pq->size == 0)
    {
        printf("No requests.\n");
        return e;
    }
    ChangeRequest top = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return top;
}

int isPQEmpty(PriorityQueue *pq) 
{   
    return pq->size == 0; 
}


void rebuildHeap(PriorityQueue *pq) {
    for (int i = (pq->size / 2) - 1; i >= 0; i--) {
        heapifyDown(pq, i);
    }
}

void updatePrioritiesPQ(PriorityQueue *pq, int newPriority) {
    for (int i = 0; i < pq->size; i++) {
        if (pq->heap[i].priority >= newPriority) {
            pq->heap[i].priority++;
        }
    }

    rebuildHeap(pq);
}
void removeByIdFromPQ(PriorityQueue *pq, int id) {
    int i = -1;
    for (i = 0; i < pq->size; i++) {
        if (pq->heap[i].id == id) {
            break; 
        }
    }

    if (i == pq->size) {
        return;
    }

    swap(&pq->heap[i], &pq->heap[pq->size - 1]);
    
    pq->size--;

    int parent = (i - 1) / 2;
    if (i > 0 && pq->heap[i].priority < pq->heap[parent].priority) {
        heapifyUp(pq, i);
    } else {
        heapifyDown(pq, i);
    }
}
