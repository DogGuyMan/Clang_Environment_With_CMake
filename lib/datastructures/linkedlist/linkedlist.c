#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

LinkedList* CreateLinkedList() {
    LinkedList* newLinkedList = malloc(sizeof(LinkedList));

    newLinkedList->startPtr = NULL;
    newLinkedList->headPtr = NULL;
    newLinkedList->tailPtr = NULL;
    newLinkedList->size = 0;

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

void LinkedListPrepend(LinkedList * selfPointer, int data) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->startPtr == NULL) { AddNodeFirstTime(selfPointer, data); return;}

    Node* newNode = CreateNode(data);
    Node* startNode = selfPointer->startPtr;

    startNode->left = newNode;
    newNode->right = startNode;

    selfPointer->startPtr = newNode;
    selfPointer->size++;
}

void LinkedListAppend(LinkedList * selfPointer, int data) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->tailPtr == NULL) { AddNodeFirstTime(selfPointer, data); return;}

    Node* newNode = CreateNode(data);
    Node* tailNode = selfPointer->tailPtr;

    tailNode->right = newNode;
    newNode->left = tailNode;

    selfPointer->tailPtr = newNode;
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
    if(selfPointer->size == 0 && selfPointer->headPtr == NULL) {
	return;
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
	return;
    }

    //printf("start data %d\n", selfPointer->startPtr->data);
    //printf("tail data %d\n", selfPointer->tailPtr->data);
    //printf("head data %d\n", selfPointer->headPtr->data);

    selfPointer->headPtr = selfPointer->startPtr;
    //printf("head data %d\n", selfPointer->headPtr->data);

    //printf("is Head ptr NULL %s\n", (selfPointer->headPtr == NULL) ? "YES" : "NO");
    while(selfPointer->headPtr != NULL) {
        printf("%d ", selfPointer->headPtr->data);
        selfPointer->headPtr = selfPointer->headPtr->right;
    }
    selfPointer->headPtr =selfPointer->startPtr;
    printf("\n");
    return;
}

int LinkedListRemoveFinal(LinkedList * selfPointer, Node* free_target) {
	if(selfPointer->size > 1) {
		printf("Not Linked Lists Final Item");
		abort();
	}
	int final_data = free_target->data;
	selfPointer->size = 0;
	free_target->left = NULL;
	free_target->right = NULL;
	free(free_target);

    selfPointer->startPtr = NULL;
	selfPointer->tailPtr = NULL;
	selfPointer->headPtr = NULL;

	return final_data;
}

int LinkedListRemoveFirst(LinkedList * selfPointer) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->startPtr == NULL) {
        printf("size가 0인데 리스트 값을 접근하려고 함\n");
        abort();
    }
    Node * freeTargetNode = selfPointer->startPtr;
    int first_data = freeTargetNode->data;
    if(selfPointer->size == 1) { return LinkedListRemoveFinal(selfPointer, freeTargetNode); }
    selfPointer->startPtr = selfPointer->startPtr->right;
    freeTargetNode->right->left = NULL;
    freeTargetNode->left = NULL;
    freeTargetNode->right = NULL;
    free(freeTargetNode);
    selfPointer->headPtr = selfPointer->startPtr;

    selfPointer->size--;
    return first_data;
}

int LinkedListRemoveLast(LinkedList * selfPointer) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->tailPtr == NULL) {
        printf("size가 0인데 리스트 값을 접근하려고 함\n");
        abort();
    }
    Node * freeTargetNode = selfPointer->tailPtr;
    int last_data = freeTargetNode->data;
    if(selfPointer->size == 1) { return LinkedListRemoveFinal(selfPointer, freeTargetNode); }
    selfPointer->tailPtr = selfPointer->tailPtr->left;
    freeTargetNode->left->right = NULL;
    freeTargetNode->left = NULL;
    freeTargetNode->right = NULL;
    free(freeTargetNode);
    selfPointer->headPtr = selfPointer->tailPtr;
    selfPointer->size--;
    return last_data;
}

void DestroyLinkedList(LinkedList * selfPointer) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    LinkedListClear(selfPointer);
    free(selfPointer);
}
