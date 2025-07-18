#ifndef __HEADER_GUARD_LINKEDLIST__
#define __HEADER_GUARD_LINKEDLIST__

#include <stdlib.h>
#include <stdbool.h>
#include <sjhdatatype.h>

typedef struct  Node Node;
typedef struct  LinkedList LinkedList;

struct Node {
    GENERIC_DATA_TYPE * data_ptr;
    struct Node* m_right;
    struct Node* m_left;
};

struct LinkedList {
	DATA_TYPE m_data_type;
	size_t m_data_size;
    Node* m_start_node_ptr;
    Node* m_tail_node_ptr;
    Node* m_head_node_ptr;
    int m_size;

    void    (*prepend) (struct LinkedList * selfPointer, GENERIC_DATA_TYPE data);
    void    (*append) (struct LinkedList * selfPointer, GENERIC_DATA_TYPE data);
    GENERIC_DATA_TYPE *     (*current_data) (struct LinkedList * selfPointer);
    GENERIC_DATA_TYPE    (*remove_first) (struct LinkedList * selfPointer);
    GENERIC_DATA_TYPE    (*remove_last) (struct LinkedList * selfPointer);
    void    (*clear) (struct LinkedList * selfPointer);

};

Node * CreateNode(GENERIC_DATA_TYPE data);
void DestroyNode(Node * self_ptr);
LinkedList * CreateLinkedList(DATA_TYPE, size_t);
void 	DestroyLinkedList(LinkedList* self_ptr);

void    LinkedListPrepend(LinkedList * selfPointer, GENERIC_DATA_TYPE data);
void    LinkedListAppend(LinkedList * selfPointer, GENERIC_DATA_TYPE data);
GENERIC_DATA_TYPE *     LinkedListCurrentData(LinkedList * selfPointer);
GENERIC_DATA_TYPE    LinkedListRemoveFirst(LinkedList * selfPointer);
GENERIC_DATA_TYPE    LinkedListRemoveLast(LinkedList * selfPointer);
void    LinkedListClear(LinkedList * selfPointer);

#endif//__HEADER_GUARD_LINKEDLIST__
