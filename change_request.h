#ifndef CHANGE_REQUEST_H
#define CHANGE_REQUEST_H

typedef struct {
    int id;
    char title[100];
    int priority;
    char status[20];
} ChangeRequest;

#endif