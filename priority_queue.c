#include <stdio.h>
#include "priority_queue.h"

void initPQ(PriorityQueue* pq) {
    pq->size = 0;
}

void swap(ChangeRequest* a, ChangeRequest* b) {
    ChangeRequest temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue* pq, int index) {
    if (index == 0) return;
    int parent = (index - 1) / 2;
    if (pq->heap[parent].priority > pq->heap[index].priority) {
        swap(&pq->heap[parent], &pq->heap[index]);
        heapifyUp(pq, parent);
    }
}

void enqueue(PriorityQueue* pq, ChangeRequest data) {
    pq->heap[pq->size] = data;
    heapifyUp(pq, pq->size);
    pq->size++;
}

void heapifyDown(PriorityQueue* pq, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < pq->size && pq->heap[left].priority < pq->heap[smallest].priority)
        smallest = left;
    if (right < pq->size && pq->heap[right].priority < pq->heap[smallest].priority)
        smallest = right;

    if (smallest != index) {
        swap(&pq->heap[index], &pq->heap[smallest]);
        heapifyDown(pq, smallest);
    }
}

ChangeRequest dequeue(PriorityQueue* pq) {
    ChangeRequest empty = {0};
    if (pq->size == 0) {
        printf("No requests to process.\n");
        return empty;
    }
    ChangeRequest top = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return top;
}

int isPQEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}
