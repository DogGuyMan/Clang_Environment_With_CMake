#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

LinkedList* InitLinkedList(int size) {
    LinkedList* newLinkedList = malloc(sizeof(LinkedList));

    newLinkedList->startPtr = NULL;
    newLinkedList->headPtr = NULL;
    newLinkedList->tailPtr = NULL;
    newLinkedList->size = 0;
    newLinkedList->maxSize = size;

    newLinkedList->append = LinkedListAppend;
    newLinkedList->prepend = LinkedListPrepend;
    newLinkedList->current_data = LinkedListCurrentData;
    newLinkedList->remove_first = LinkedListRemoveFirst;
    newLinkedList->remove_last = LinkedListRemoveLast;
    newLinkedList->clear = LinkedListClear;
    newLinkedList->foreach = LinkedListForeach;

    return newLinkedList;
}

Node* CreateNode(int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void AddNodeFirstTime(LinkedList * selfPointer, int data) {
    selfPointer->headPtr = CreateNode(data);
    selfPointer->startPtr = selfPointer->headPtr;
    selfPointer->tailPtr = selfPointer->headPtr;
    selfPointer->size = 1;
}

void LinkedListAppend(LinkedList * selfPointer, int data) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->size >= selfPointer->maxSize) {
        printf("Linked List Capacity FULL\n");
        abort();
    }
    if(selfPointer->startPtr == NULL) { AddNodeFirstTime(selfPointer, data); return;}

    Node* newNode = CreateNode(data);
    Node* startNode = selfPointer->startPtr;

    startNode->left = newNode;
    newNode->right = startNode;

    selfPointer->headPtr = newNode;
    selfPointer->startPtr = selfPointer->headPtr;
    selfPointer->size++;
}
void LinkedListPrepend(LinkedList * selfPointer, int data) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->size >= selfPointer->maxSize) {
        printf("Linked List Capacity FULL\n");
        abort();
    }
    if(selfPointer->tailPtr == NULL) { AddNodeFirstTime(selfPointer, data); return;}

    Node* newNode = CreateNode(data);
    Node* tailNode = selfPointer->tailPtr;

    tailNode->right = newNode;
    newNode->left = tailNode;

    selfPointer->headPtr = newNode;
    selfPointer->tailPtr = selfPointer->headPtr;
    selfPointer->size++;
}

int LinkedListCurrentData(LinkedList * selfPointer) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->headPtr == NULL) {
        printf("size가 0인데 리스트 값을 접근하려고 함\n");
        abort();
    }
    return selfPointer->headPtr->data;
}

void LinkedListClear(LinkedList * selfPointer) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->headPtr == NULL) {
        printf("size가 0인데 리스트 값을 접근하려고 함\n");
        abort();
    }
    selfPointer->headPtr = selfPointer->startPtr;
    while(selfPointer->headPtr != NULL) {
        LinkedListRemoveFirst(selfPointer);
    }
    selfPointer->headPtr = NULL;
    selfPointer->startPtr = NULL;
    selfPointer->tailPtr = NULL;
}

void LinkedListForeach(LinkedList * selfPointer) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->headPtr == NULL) {
        printf("size가 0인데 리스트 값을 접근하려고 함\n");
        abort();
    }

    selfPointer->headPtr = selfPointer->startPtr;
    while(selfPointer->headPtr != NULL) {
        printf("%d ", selfPointer->headPtr->data);
        selfPointer->headPtr = selfPointer->headPtr->right;
    }
    selfPointer->headPtr =selfPointer->startPtr;
    printf("\n");
    return;
}

void LinkedListRemoveFirst(LinkedList * selfPointer) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->startPtr == NULL) {
        printf("size가 0인데 리스트 값을 접근하려고 함\n");
        abort();
    }
    Node * freeTargetNode = selfPointer->startPtr;
    printf("RemoveNodeData %d\n", freeTargetNode->data );
    selfPointer->startPtr = selfPointer->startPtr->right;
    freeTargetNode->data = 0;
    freeTargetNode->left = NULL;
    freeTargetNode->right = NULL;
    free(freeTargetNode);
    selfPointer->headPtr = selfPointer->startPtr;
    selfPointer->size--;
}

void LinkedListRemoveLast(LinkedList * selfPointer) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->tailPtr == NULL) {
        printf("size가 0인데 리스트 값을 접근하려고 함\n");
        abort();
    }
    selfPointer->headPtr = selfPointer->tailPtr;
    Node * freeTargetNode = selfPointer->tailPtr;
    selfPointer->tailPtr = selfPointer->tailPtr->left;
    freeTargetNode->data = 0;
    freeTargetNode->left = NULL;
    freeTargetNode->right = NULL;
    free(freeTargetNode);
    selfPointer->size--;
}

void DestroyLinkedList(LinkedList * selfPointer) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    LinkedListClear(selfPointer);
    free(selfPointer);
}
