#include <stdio.h>
#include "stack.h"
void initStack(Stack *s) 
{
    s->top = -1;
}

void push(Stack *s, ChangeRequest d)
{
    if (s->top == 100)
    {
        printf("Undo stack full!\n");
        return;
    }
    s->arr[++(s->top)] = d;
}

ChangeRequest pop(Stack *s)
{
    ChangeRequest e = {0};
    if (s->top == -1)
    {
        printf("Nothing to undo.\n");
        return e;
    }
    return s->arr[(s->top)--];
}

int isStackEmpty(Stack *s)
{
    return s->top == -1; 
}
