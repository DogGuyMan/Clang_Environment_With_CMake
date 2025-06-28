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
    int maxSize;

    void    (*prepend) (struct LinkedList * selfPointer, int data);
    void    (*append) (struct LinkedList * selfPointer, int data);
    void    (*pop) (struct LinkedList * selfPointer, int data);
    int     (*current_data) (struct LinkedList * selfPointer);
    void    (*remove_first) (struct LinkedList * selfPointer);
    void    (*remove_last) (struct LinkedList * selfPointer);
    void    (*clear) (struct LinkedList * selfPointer);
    void    (*foreach) (struct LinkedList * selfPointer);
};

LinkedList* InitLinkedList(int size);
void    Prepend(LinkedList * selfPointer, int data);
void    Append(LinkedList * selfPointer, int data);
int     CurrentData(LinkedList * selfPointer);
void    Clear(LinkedList * selfPointer);
void    Foreach(LinkedList * selfPointer);
void    RemoveFirst(LinkedList * selfPointer);
void    RemoveLast(LinkedList * selfPointer);
