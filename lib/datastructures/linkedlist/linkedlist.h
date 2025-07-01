#pragma once

typedef struct  Node Node;
typedef struct  LinkedList LinkedList;

struct Node {
    int data;
    struct Node* right;
    struct Node* left;
};

struct LinkedList {
    Node* startPtr;
    Node* tailPtr;
    Node* headPtr;
    int size;

    void    (*prepend) (struct LinkedList * selfPointer, int data);
    void    (*append) (struct LinkedList * selfPointer, int data);
    int     (*current_data) (struct LinkedList * selfPointer);
    int    (*remove_first) (struct LinkedList * selfPointer);
    int    (*remove_last) (struct LinkedList * selfPointer);
    void    (*clear) (struct LinkedList * selfPointer);
    void    (*foreach) (struct LinkedList * selfPointer);
};

LinkedList* CreateLinkedList();
void 	DestroyLinkedList(LinkedList* self_ptr);
void    LinkedListPrepend(LinkedList * selfPointer, int data);
void    LinkedListAppend(LinkedList * selfPointer, int data);
int     LinkedListCurrentData(LinkedList * selfPointer);
void    LinkedListClear(LinkedList * selfPointer);
void    LinkedListForeach(LinkedList * selfPointer);
int    LinkedListRemoveFirst(LinkedList * selfPointer);
int    LinkedListRemoveLast(LinkedList * selfPointer);
