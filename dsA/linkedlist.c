#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node *link;
};

struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    { // Edge Case: Memory allocation failed
        printf("Memory allocation failed. Node creation aborted.\n");
        return NULL;
    }

    newNode->value = value;
    newNode->link = NULL;
    return newNode;
}

void insertNode(struct Node **head, int value, int nodePosition)
{
    if (head == NULL)
    {
        printf("Invalid operation: head pointer is NULL.\n");
        return;
    }

    struct Node *newNode = createNode(value);

    if (newNode == NULL)
    {
        // Edge Case: Memory allocation failed, so we just return.
        return;
    }

    if (nodePosition == 0)
    {
        newNode->link = *head;
        *head = newNode;
    }
    else
    {
        struct Node *current = *head;
        int i;

        for (i = 0; current != NULL && i < nodePosition - 1; i++)
        {
            current = current->link;
        }

        // If current is NULL, the position was out of bounds
        if (current == NULL)
        {
            printf("Position out of bounds. Insertion failed.\n");
            free(newNode);
        }
        else
        {
            newNode->link = current->link;
            current->link = newNode;
        }
    }
}

void deleteNodeByPosition(struct Node **head, int nodePosition)
{
    // Edge Case: Handle empty list
    if (*head == NULL)
    {
        printf("List is empty. Deletion failed.\n");
        return;
    }

    struct Node *current = *head;

    if (nodePosition == 0)
    {
        *head = current->link;
        free(current);
    }
    else
    {

        for (int i = 0; current != NULL && i < nodePosition - 1; i++)
        {
            current = current->link;
        }

        // Edge Case: Handle invalid position
        if (current == NULL || current->link == NULL)
        {
            printf("Position out of bounds. Deletion failed.\n");
            return;
        }

        struct Node *nodeToDelete = current->link;
        current->link = nodeToDelete->link;

        free(nodeToDelete);
    }
}

void deleteNodeByPointer(struct Node **head, struct Node *nodeToDelete)
{
    // Edge Case: Handle empty list or NULL node to delete
    if (*head == NULL || nodeToDelete == NULL)
    {
        printf("Invalid operation: List is empty or node to delete is NULL.\n");
        return;
    }

    // Edge Case: Handle deletion of the head node
    if (*head == nodeToDelete)
    {
        *head = nodeToDelete->link;
        free(nodeToDelete);
        return;
    }

    struct Node *current = *head;

    while (current != NULL && current->link != nodeToDelete)
    {
        current = current->link;
    }

    // Edge Case: Unlink and free the node if found, else print error
    if (current != NULL && current->link == nodeToDelete)
    {
        current->link = nodeToDelete->link;
        free(nodeToDelete);
    }
    else
    {
        printf("Node to delete not found in the list.\n");
    }
}

void swapNodesByPosition(struct Node **head, int nodePosition1, int nodePosition2)
{
    // Edge Case: If both positions are the same, no swap is needed.
    if (nodePosition1 == nodePosition2)
        return;

    struct Node *prevNode1 = NULL, *prevNode2 = NULL;
    struct Node *node1 = *head, *node2 = *head;

    if (nodePosition1 > nodePosition2)
    {
        int tempPos = nodePosition1;
        nodePosition1 = nodePosition2;
        nodePosition2 = tempPos;
    }

    // Edge Case: If the list is empty (head is NULL), no nodes can be swapped.
    if (*head == NULL)
        return;

    for (int i = 0; i < nodePosition2; i++)
    {
        // Edge Case: If node1 or node2 becomes NULL during traversal, the positions are out of bounds.
        if (i < nodePosition1)
        {
            if (node1 == NULL)
                return;
            prevNode1 = node1;
            node1 = node1->link;
        }
        if (node2 == NULL)
            return;
        prevNode2 = node2;
        node2 = node2->link;
    }

    if (prevNode1 != NULL)
        prevNode1->link = node2;
    else
        *head = node2; // Edge Case: If node1 was the head, update head to node2.

    if (prevNode2 != NULL)
        prevNode2->link = node1;
    else
        *head = node1; // Edge Case: If node2 was the head, update head to node1.

    struct Node *temp = node1->link;
    node1->link = node2->link;
    node2->link = temp;
}

void swapNodesByPointer(struct Node **head, struct Node *node1, struct Node *node2)
{
    // Edge Case: If the nodes to swap are the same, no action is needed.
    if (node1 == node2)
        return;

    struct Node *prevNode1 = NULL, *prevNode2 = NULL;
    struct Node *current = *head;

    // Edge Case: If the list is empty (head is NULL), no nodes can be swapped.
    if (*head == NULL || node1 == NULL || node2 == NULL)
        return;

    // Find the previous nodes of node1 and node2
    while (current != NULL && (prevNode1 == NULL || prevNode2 == NULL))
    {
        if (current->link == node1)
            prevNode1 = current;
        if (current->link == node2)
            prevNode2 = current;
        current = current->link;
    }

    // Edge Case: If one of the nodes is not found in the list, return without swapping.
    if (node1 == NULL || node2 == NULL)
        return;

    // Adjust the previous node links to point to the new nodes
    if (prevNode1 != NULL)
        prevNode1->link = node2;
    else
        *head = node2; // If node1 was the head, update head to node2.

    if (prevNode2 != NULL)
        prevNode2->link = node1;
    else
        *head = node1; // If node2 was the head, update head to node1.

    // Swap the links of node1 and node2
    struct Node *temp = node1->link;
    node1->link = node2->link;
    node2->link = temp;
}

void reverseList(struct Node **head)
{
    struct Node *prev = NULL;
    struct Node *current = *head;
    struct Node *next = NULL;

    // Edge Case: If the list is empty (head is NULL), simply return as there is nothing to reverse.
    if (*head == NULL)
        return;

    while (current != NULL)
    {
        next = current->link;
        current->link = prev;
        prev = current;
        current = next;
    }

    *head = prev;
}

void sortList(struct Node **head)
{
    struct Node *end = NULL;
    struct Node *current;
    struct Node *next;
    int swapped;

    // Edge Case: If the list is empty or has only one node, no sorting is needed.
    if (*head == NULL || (*head)->link == NULL)
        return;

    do
    {
        swapped = 0;
        current = *head;

        while (current->link != end)
        {
            next = current->link;

            if (current->value > next->value)
            {
                swapNodesByPointer(head, current, next);
                swapped = 1;
            }
            else
            {
                current = current->link;
            }
        }

        end = current;
    } while (swapped);
}

void mergeList(struct Node **node1, struct Node **node2)
{
    // Edge Case: If the first list (node1) is empty, set head of node1 to node2 and return.
    if (*node1 == NULL)
    {
        *node1 = *node2;
        return;
    }

    // Edge Case: If the second list (node2) is empty, there's nothing to merge, so return.
    if (*node2 == NULL)
    {
        return;
    }

    struct Node *current = *node1;

    while (current->link != NULL)
    {
        current = current->link;
    }

    current->link = *node2;

    // Edge Case: After merging, node2's head should no longer point to the old list
    *node2 = NULL;
}

void deleteList(struct Node **head)
{
    struct Node *temp;

    // Edge Case: If the list is already empty (head is NULL), there’s nothing to delete.
    if (*head == NULL)
        return;

    while (*head != NULL)
    {
        temp = *head;
        free(temp);
    }

    // Edge Case: After deletion, ensure the head pointer is set to NULL
    *head = NULL;
}

void printList(struct Node *head)
{
    // Edge Case: If the list is empty, indicate this by printing a message.
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    while (head != NULL)
    {
        printf("%d", head->value);
        if (head->link != NULL)
        {
            printf(" -> ");
        }
        head = head->link;
    }
    printf("\n");
}

void countList(struct Node *head)
{
    int count = 0;

    // Edge Case: If the list is empty, count will remain 0, and this will be handled naturally.
    while (head != NULL)
    {
        count++;
        head = head->link;
    }
    printf("Number of Nodes: %d\n", count);
}

int main()
{
    struct Node *node1 = NULL;

    insertNode(node1, 10, 0);
    insertNode(node1, 60, 0);
    insertNode(node1, 30, 0);
    insertNode(node1, 20, 0);
    insertNode(node1, 40, 0);
    insertNode(node1, 50, 0);
    insertNode(node1, 5, 0);
    sortList(&node1);
    printList(node1);

    struct Node *node2 = NULL;
    insertNode(&node2, 1, 0);
    insertNode(&node2, 6, 0);
    insertNode(&node2, 3, 0);
    printList(node2);
    mergeList(&node1, &node2);

    printList(node1);
    sortList(&node1);
    printList(node1);

    deleteList(&node1);
    printf("\n");
    return 0;
}