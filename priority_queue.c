#include <stdio.h>
#include "priority_queue.h"
void initPQ(PriorityQueue* pq){pq->size=0;}
void swap(ChangeRequest*a,ChangeRequest*b){ChangeRequest t=*a;*a=*b;*b=t;}
void heapifyUp(PriorityQueue*pq,int i){if(i==0)return;int p=(i-1)/2;if(pq->heap[p].priority>pq->heap[i].priority){swap(&pq->heap[p],&pq->heap[i]);heapifyUp(pq,p);}}
void enqueue(PriorityQueue*pq,ChangeRequest d){pq->heap[pq->size]=d;heapifyUp(pq,pq->size);pq->size++;}
void heapifyDown(PriorityQueue*pq,int i){int l=2*i+1,r=2*i+2,s=i;if(l<pq->size&&pq->heap[l].priority<pq->heap[s].priority)s=l;if(r<pq->size&&pq->heap[r].priority<pq->heap[s].priority)s=r;if(s!=i){swap(&pq->heap[i],&pq->heap[s]);heapifyDown(pq,s);}}
ChangeRequest dequeue(PriorityQueue*pq){ChangeRequest e={0};if(pq->size==0){printf("No requests.\n");return e;}ChangeRequest top=pq->heap[0];pq->heap[0]=pq->heap[pq->size-1];pq->size--;heapifyDown(pq,0);return top;}
int isPQEmpty(PriorityQueue*pq){return pq->size==0;}