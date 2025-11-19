#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "bst.h"
#include "priority_queue.h"
#include "stack.h"

int compareByPriority(const void *a, const void *b)
{
    ChangeRequest *crA = (ChangeRequest *)a;
    ChangeRequest *crB = (ChangeRequest *)b;
    return (crA->priority - crB->priority);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(int argc, char *argv[])
{
    Node *root = NULL;
    PriorityQueue pq;
    Stack st;
    int c;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <max_queue_size>\n", argv[0]);
        return 1; 
    }

    int max_heap_size = atoi(argv[1]);
    if (max_heap_size <= 0) {
        fprintf(stderr, "Error: Max queue size must be a positive number.\n");
        return 1;
    }
    
    printf("   Welcome to the Change Request Manager\n");
    printf("Setting max queue size to %d\n", max_heap_size);

    initPQ(&pq, max_heap_size);
    initStack(&st);
    do
    {
        printf("\n--- Main Menu ---\n");
        printf("1. Add New Change Request\n");
        printf("2. Process Highest Priority Request\n");
        printf("3. Search for Request by ID\n");
        printf("4. Display All Requests (by Priority)\n");
        printf("5. Display All Requests (by ID)\n");
        printf("6. Undo Last 'Add' Action\n");
        printf("7. Exit\n");
        printf("Please enter your choice (1-7): ");

        if (scanf("%d", &c) != 1) {
            printf("Error: Please enter a number between 1 and 7.\n");
            clearInputBuffer();
            c = 0; 
            continue; 
        }
        clearInputBuffer(); 

        if (c == 1)
        {
            printf("\n== 1. Add New Change Request ==\n");
            ChangeRequest cr;
            printf("Enter a unique numeric ID: ");
            
            if (scanf("%d", &cr.id) != 1) {
                printf("Error: ID must be a number.\n");
                clearInputBuffer();
                continue;
            }
            clearInputBuffer(); 

            if (searchBST(root, cr.id) != NULL)
            {
                printf("Error: ID %d already exists. Cannot add.\n", cr.id);
                continue;
            }

            printf("Enter Title: ");
            fgets(cr.title, 100, stdin);
            cr.title[strcspn(cr.title, "\n")] = 0;

            printf("Enter Priority (lower number = higher priority): ");
            if (scanf("%d", &cr.priority) != 1) {
                printf("Error: Priority must be a number.\n");
                clearInputBuffer();
                continue;
            }
            clearInputBuffer(); 

            updatePrioritiesBST(root, cr.priority);
            updatePrioritiesPQ(&pq, cr.priority);
            updatePrioritiesStack(&st, cr.priority);

            strcpy(cr.status, "Pending");
            root = insertBST(root, cr);
            enqueue(&pq, cr);
            push(&st, cr);
            
            printf("\nSuccess: Request #%d ('%s') added with priority %d.\n", cr.id, cr.title, cr.priority);
        }
        else if (c == 2)
        {
            printf("\n== 2. Process Highest Priority Request ==\n");
            if (isPQEmpty(&pq))
                printf("No pending requests to process.\n");
            else
            {
                ChangeRequest cr = dequeue(&pq);
                printf("Processing highest priority request:\n");
                printf("   ID: %d | Title: %s | Priority: %d\n", cr.id, cr.title, cr.priority);
                Node *n = searchBST(root, cr.id);
                if (n)
                    strcpy(n->data.status, "Approved");
            }
        }
        else if (c == 3)
        {
            printf("\n== 3. Search for Request by ID ==\n");
            int id;
            printf("Enter Request ID to search for: ");
            
            if (scanf("%d", &id) != 1) {
                printf("Error: ID must be a number.\n");
                clearInputBuffer();
                continue;
            }
            clearInputBuffer(); 
            
            Node *r = searchBST(root, id);
            if (r)
            {
                printf("Request Found:\n");
                printf("   ID:       %d\n", r->data.id);
                printf("   Title:    %s\n", r->data.title);
                printf("   Priority: %d\n", r->data.priority);
                printf("   Status:   %s\n", r->data.status);
            }
            else
                printf("Error: Request with ID %d not found.\n", id);

        }
        else if (c == 4)
        {
            printf("\n== 4. Display All Requests (Sorted by Priority) ==\n");
            int nodeCount = countNodes(root);
            if (nodeCount == 0)
            {
                printf("No requests found in the system.\n");
                continue; 
            }

            ChangeRequest *tempArray = (ChangeRequest *)malloc(nodeCount * sizeof(ChangeRequest));
            if (tempArray == NULL)
            {
                printf("Error: Memory allocation failed.\n");
                continue; 
            }

            int index = 0;
            bstToArray(root, tempArray, &index);

            qsort(tempArray, nodeCount, sizeof(ChangeRequest), compareByPriority);

            printf("------------------------------------------------------------------\n");
            printf("PRI | ID  | STATUS   | TITLE\n");
            printf("------------------------------------------------------------------\n");
            for (int i = 0; i < nodeCount; i++)
            {
                printf("%-3d | %-3d | %-8s | %s\n",
                       tempArray[i].priority, tempArray[i].id,
                       tempArray[i].status, tempArray[i].title);
            }
            printf("------------------------------------------------------------------\n");

            free(tempArray);
        }
        else if (c == 5)
        {
            printf("\n== 5. Display All Requests (Sorted by ID) ==\n");
            int nodeCount = countNodes(root);
            if (nodeCount == 0)
            {
                printf("No requests found in the system.\n");
            }
            else
            {
                printf("--------------------------------------------------\n");
                inorderBST(root);
                printf("--------------------------------------------------\n");
            }
        }
        else if (c == 6)
        {
            printf("\n== 6. Undo Last 'Add' Action ==\n");
            if (isStackEmpty(&st))
                printf("Undo stack is empty. Nothing to undo.\n");
            else
            {
                ChangeRequest u = pop(&st);
                root = deleteBST(root, u.id);
                removeByIdFromPQ(&pq, u.id);
                printf("Success: Last added request (#%d) has been undone and removed.\n", u.id);
            }
        }
        else if (c == 7)
        {
            printf("\nThank you for using the Change Request Manager. Goodbye!\n");
        }
        else
        {
            printf("Error: Invalid choice. Please enter a number between 1 and 7.\n");
        }
    } while (c != 7);

    free(pq.heap);
    
    return 0;
}
