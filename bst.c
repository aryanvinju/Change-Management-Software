#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

Node *createNode(ChangeRequest data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *insertBST(Node *root, ChangeRequest data)
{
    if (!root)
        return createNode(data);
    
    if (data.id == root->data.id) {
        return root; // Should be prevented by main.c
    }
    
    if (data.id < root->data.id)
        root->left = insertBST(root->left, data);
    else if (data.id > root->data.id)
        root->right = insertBST(root->right, data);
    
    return root;
}

Node *searchBST(Node *root, int id)
{
    if (!root || root->data.id == id)
        return root;
    if (id < root->data.id)
        return searchBST(root->left, id);
    return searchBST(root->right, id);
}

Node *minValueNode(Node *n)
{
    Node *c = n;
    while (c && c->left)
        c = c->left;
    return c;
}

Node *deleteBST(Node *root, int id)
{
    if (!root)
        return root;
    if (id < root->data.id)
        root->left = deleteBST(root->left, id);
    else if (id > root->data.id)
        root->right = deleteBST(root->right, id);
    else
    {
        if (!root->left)
        {
            Node *t = root->right;
            free(root);
            return t;
        }
        else if (!root->right)
        {
            Node *t = root->left;
            free(root);
            return t;
        }
        Node *t = minValueNode(root->right);
        root->data = t->data;
        root->right = deleteBST(root->right, t->data.id);
    }
    return root;
}

void inorderBST(Node *root)
{
    if (!root)
        return;
    inorderBST(root->left);
    printf("ID:%d | Title:%s | Priority:%d | Status:%s\n", root->data.id, root->data.title, root->data.priority, root->data.status);
    inorderBST(root->right);
}

void updatePrioritiesBST(Node* root, int newPriority) {
    if (!root) 
        return;
    
    if (root->data.priority >= newPriority) {
        root->data.priority++;
    }
    
    updatePrioritiesBST(root->left, newPriority);
    updatePrioritiesBST(root->right, newPriority);
}

int countNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void bstToArray(Node* root, ChangeRequest* arr, int* index) {
    if (root == NULL) {
        return;
    }
    
    bstToArray(root->left, arr, index);
    
    arr[*index] = root->data;
    (*index)++;
    

    bstToArray(root->right, arr, index);
}
