#include <stdio.h>
#include <string.h>
#include "bst.h"
#include "priority_queue.h"
#include "stack.h"
int main()
{
    Node *root = NULL;
    PriorityQueue pq;
    Stack st;
    int c;
    initPQ(&pq);
    initStack(&st);
    do
    {
        printf("\n1.Add 2.Process 3.Search 4.Display 5.Undo 6.Exit\nChoice:");
        scanf("%d", &c);
        if (c == 1)
        {
            ChangeRequest cr;
            printf("Enter ID:");
            scanf("%d", &cr.id);
            printf("Enter Title:");
            getchar();
            fgets(cr.title, 100, stdin);
            cr.title[strcspn(cr.title, "\n")] = 0;
            printf("Priority:");
            scanf("%d", &cr.priority);
            strcpy(cr.status, "Pending");
            root = insertBST(root, cr);
            enqueue(&pq, cr);
            push(&st, cr);
            printf("Added.\n");
        }
        else if (c == 2)
        {
            if (isPQEmpty(&pq))
                printf("Empty PQ\n");
            else
            {
                ChangeRequest cr = dequeue(&pq);
                printf("Processing #%d:%s\n", cr.id, cr.title);
                Node *n = searchBST(root, cr.id);
                if (n)
                    strcpy(n->data.status, "Approved");
            }
        }
        else if (c == 3)
        {
            int id;
            printf("Enter ID:");
            scanf("%d", &id);
            Node *r = searchBST(root, id);
            if (r)
                printf("Found:%s|P:%d|%s\n", r->data.title, r->data.priority, r->data.status);
            else
                printf("Not found\n");
        }
        else if (c == 4)
        {
            inorderBST(root);
        }
        else if (c == 5)
        {
            if (isStackEmpty(&st))
                printf("No undo\n");
            else
            {
                ChangeRequest u = pop(&st);
                root = deleteBST(root, u.id);
                printf("Undone %d\n", u.id);
            }
        }
    } while (c != 6);
    return 0;
}
