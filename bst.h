#ifndef BST_H
#define BST_H
#include "change_request.h"

typedef struct Node {
    ChangeRequest data;
    struct Node *left, *right;
} Node;

Node* insertBST(Node* root, ChangeRequest data);
Node* searchBST(Node* root, int id);
Node* deleteBST(Node* root, int id);
void inorderBST(Node* root);
void updatePrioritiesBST(Node* root, int newPriority);
int countNodes(Node* root);
void bstToArray(Node* root, ChangeRequest* arr, int* index);


#endif
