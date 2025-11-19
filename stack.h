#ifndef STACK_H
#define STACK_H
#include "change_request.h"

typedef struct
{
    ChangeRequest arr[100];
    int top;
} Stack;

void initStack(Stack *s);
void push(Stack *s, ChangeRequest data);
ChangeRequest pop(Stack *s);
int isStackEmpty(Stack *s);
void updatePrioritiesStack(Stack *s, int newPriority); // Added function

#endif
