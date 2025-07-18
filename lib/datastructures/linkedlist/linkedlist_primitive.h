#ifndef __HEADER_GUARD_LINKEDLIST_PRIMITIVE__
#define __HEADER_GUARD_LINKEDLIST_PRIMITIVE__

#include <stdlib.h>
#include <stdbool.h>

#define DEFINE_LINKEDLIST_TYPE(TYPE, TYPE_NAME) \
\
typedef struct Node##TYPE_NAME Node##TYPE_NAME; \
typedef struct LinkedList##TYPE_NAME LinkedList##TYPE_NAME; \
\
struct Node##TYPE_NAME  { \
    TYPE m_data; \
    struct Node##TYPE_NAME * m_right; \
    struct Node##TYPE_NAME * m_left; \
}; \
\
struct LinkedList##TYPE_NAME { \
    Node##TYPE_NAME * m_start_node_ptr; \
    Node##TYPE_NAME * m_tail_node_ptr; \
    Node##TYPE_NAME * m_head_node_ptr; \
    size_t m_size; \
\
	size_t 		(* const size)		(struct LinkedList##TYPE_NAME * self_ptr); \
    void    	(* const prepend) (struct LinkedList##TYPE_NAME * self_ptr, TYPE data); \
    void    	(* const append) (struct LinkedList##TYPE_NAME * self_ptr, TYPE data); \
    TYPE		(* const current_data) (struct LinkedList##TYPE_NAME * self_ptr); \
    TYPE    	(* const remove_first) (struct LinkedList##TYPE_NAME * self_ptr); \
    TYPE    	(* const remove_last) (struct LinkedList##TYPE_NAME * self_ptr); \
    void    	(* const clear) (struct LinkedList##TYPE_NAME * self_ptr); \
\
}; \
\
Node##TYPE_NAME * CreateNode##TYPE_NAME (TYPE data); \
LinkedList##TYPE_NAME * CreateLinkedList##TYPE_NAME(); \
void 		DestroyLinkedList##TYPE_NAME(LinkedList##TYPE_NAME * self_ptr); \
\
size_t 		LinkedList##TYPE_NAME##Size (struct LinkedList##TYPE_NAME * self_ptr); \
void    	LinkedList##TYPE_NAME##Prepend(LinkedList##TYPE_NAME * self_ptr, TYPE data); \
void    	LinkedList##TYPE_NAME##Append(LinkedList##TYPE_NAME * self_ptr, TYPE data); \
TYPE    LinkedList##TYPE_NAME##CurrentData(LinkedList##TYPE_NAME * self_ptr); \
void      	LinkedList##TYPE_NAME##Clear(LinkedList##TYPE_NAME * self_ptr); \
TYPE    LinkedList##TYPE_NAME##RemoveFirst(LinkedList##TYPE_NAME * self_ptr); \
TYPE    LinkedList##TYPE_NAME##RemoveLast(LinkedList##TYPE_NAME * self_ptr); \

#define IMPLEMENT_LINKEDLIST_TYPE(TYPE, TYPE_NAME) \
\
const Node##TYPE_NAME EMPTY_NODE_##TYPE_NAME = { \
    .m_data = 0, \
    .m_right = NULL, \
    .m_left = NULL, \
}; \
\
const LinkedList##TYPE_NAME DEFAULT_LINKEDLIST_##TYPE_NAME##VTALBE_TEMPLATE = { \
    .m_start_node_ptr = NULL, \
    .m_tail_node_ptr = NULL, \
    .m_head_node_ptr = NULL, \
    .m_size = 0, \
\
	.size = LinkedList##TYPE_NAME##Size, \
    .prepend = LinkedList##TYPE_NAME##Prepend, \
    .append = LinkedList##TYPE_NAME##Append, \
    .current_data = LinkedList##TYPE_NAME##CurrentData, \
    .remove_first = LinkedList##TYPE_NAME##RemoveFirst, \
    .remove_last = LinkedList##TYPE_NAME##RemoveLast, \
    .clear = LinkedList##TYPE_NAME##Clear, \
}; \
\
Node##TYPE_NAME * CreateNode##TYPE_NAME (TYPE data) { \
    Node##TYPE_NAME * temp_node = malloc(sizeof(Node##TYPE_NAME)); \
	if(temp_node == NULL) { \
		perror("노드 메모리 할당 실패\n"); \
		abort(); \
	} \
	memcpy(temp_node, &EMPTY_NODE_##TYPE_NAME , sizeof(Node##TYPE_NAME)); \
    temp_node->m_data = data; \
    return temp_node; \
} \
\
LinkedList##TYPE_NAME * CreateLinkedList##TYPE_NAME() { \
    LinkedList##TYPE_NAME * temp_linkedlist = malloc(sizeof(LinkedList##TYPE_NAME)); \
	if(temp_linkedlist == NULL) \
	{ \
		perror("링크드 리스트 메모리 할당 실패\n"); \
		abort(); \
	} \
\
	memcpy(temp_linkedlist, &DEFAULT_LINKEDLIST_##TYPE_NAME##VTALBE_TEMPLATE, sizeof(LinkedList##TYPE_NAME)); \
    return temp_linkedlist; \
} \
\
void DestroyLinkedList##TYPE_NAME(LinkedList##TYPE_NAME * self_ptr) { \
    if(self_ptr == NULL) { \
        printf("Linked List Not Initialized\n"); \
        abort(); \
    } \
    LinkedListClear(self_ptr); \
    free(self_ptr); \
} \
\
size_t 		LinkedList##TYPE_NAME##Size (struct LinkedList##TYPE_NAME * self_ptr) { \
	return self_ptr->m_size; \
} \
\
TYPE LinkedList##TYPE_NAME##CurrentData (LinkedList##TYPE_NAME * self_ptr) { \
    if(self_ptr == NULL) { \
        printf("Linked List Not Initialized\n"); \
        abort(); \
    } \
    if(self_ptr->m_head_node_ptr == NULL) { \
        printf("size가 0인데 리스트 값을 접근하려고 함\n"); \
        abort(); \
    } \
    return self_ptr->m_head_node_ptr->m_data; \
} \
\
static void AddNode##TYPE_NAME##FirstTime (LinkedList##TYPE_NAME * self_ptr, TYPE data) { \
    self_ptr->m_head_node_ptr = CreateNode##TYPE_NAME(data); \
    self_ptr->m_start_node_ptr = self_ptr->m_head_node_ptr; \
    self_ptr->m_tail_node_ptr = self_ptr->m_head_node_ptr; \
    self_ptr->m_size = 1; \
} \
\
void LinkedList##TYPE_NAME##Prepend (LinkedList##TYPE_NAME * self_ptr, TYPE data) { \
    if(self_ptr == NULL) { \
        printf("Linked List Not Initialized\n"); \
        abort(); \
    } \
    if(self_ptr->m_start_node_ptr == NULL) { AddNode##TYPE_NAME##FirstTime(self_ptr, data); return;} \
\
    Node##TYPE_NAME * new_node = CreateNode##TYPE_NAME(data); \
    Node##TYPE_NAME * start_node = self_ptr->m_start_node_ptr; \
\
    start_node->m_left = new_node; \
    new_node->m_right = start_node; \
\
    self_ptr->m_start_node_ptr = new_node; \
    self_ptr->m_size++; \
} \
\
void LinkedList##TYPE_NAME##Append (LinkedList##TYPE_NAME * self_ptr, TYPE data) { \
    if(self_ptr == NULL) { \
        printf("Linked List Not Initialized\n"); \
        abort(); \
    } \
    if(self_ptr->m_tail_node_ptr == NULL) { AddNode##TYPE_NAME##FirstTime(self_ptr, data); return;} \
\
    Node##TYPE_NAME * new_node = CreateNode##TYPE_NAME(data); \
    Node##TYPE_NAME * tail_node = self_ptr->m_tail_node_ptr; \
\
    tail_node->m_right = new_node; \
    new_node->m_left = tail_node; \
\
    self_ptr->m_tail_node_ptr = new_node; \
    self_ptr->m_size++; \
} \
\
void LinkedList##TYPE_NAME##Clear (LinkedList##TYPE_NAME * self_ptr) { \
    if(self_ptr == NULL) { \
        printf("Linked List Not Initialized\n"); \
        abort(); \
    } \
    if(self_ptr->m_size == 0 && self_ptr->m_head_node_ptr == NULL) { \
		return; \
    } \
    self_ptr->m_head_node_ptr = self_ptr->m_start_node_ptr; \
    while(self_ptr->m_head_node_ptr != NULL) { \
        LinkedList##TYPE_NAME##RemoveFirst(self_ptr); \
    } \
    self_ptr->m_head_node_ptr = NULL; \
    self_ptr->m_start_node_ptr = NULL; \
    self_ptr->m_tail_node_ptr = NULL; \
	self_ptr->m_size = 0;\
} \
\
static TYPE LinkedList##TYPE_NAME##RemoveFinal (LinkedList##TYPE_NAME * self_ptr, Node##TYPE_NAME * free_target) { \
	if(self_ptr->m_size > 1) { \
		printf("Not Linked Lists Final Item"); \
		abort(); \
	} \
	TYPE final_data = free_target->m_data; \
	free(free_target); \
	\
    self_ptr->m_start_node_ptr = NULL; \
	self_ptr->m_tail_node_ptr = NULL; \
	self_ptr->m_head_node_ptr = NULL; \
	self_ptr->m_size = 0; \
\
	return final_data; \
} \
\
TYPE LinkedList##TYPE_NAME##RemoveFirst (LinkedList##TYPE_NAME * self_ptr) { \
    if(self_ptr == NULL) { \
        printf("Linked List Not Initialized\n"); \
        abort(); \
    } \
    if(self_ptr->m_start_node_ptr == NULL) { \
        printf("size가 0인데 리스트 값을 접근하려고 함\n"); \
        abort(); \
    } \
    Node##TYPE_NAME * free_target_node = self_ptr->m_start_node_ptr; \
    TYPE first_data = free_target_node->m_data; \
    if(self_ptr->m_size == 1) { return LinkedList##TYPE_NAME##RemoveFinal(self_ptr, free_target_node); } \
    self_ptr->m_start_node_ptr = self_ptr->m_start_node_ptr->m_right; \
    free_target_node->m_right->m_left = NULL; \
    free_target_node->m_left = NULL; \
    free_target_node->m_right = NULL; \
\
	free(free_target_node); \
    self_ptr->m_head_node_ptr = self_ptr->m_start_node_ptr; \
    self_ptr->m_size--; \
    return first_data; \
} \
\
TYPE LinkedList##TYPE_NAME##RemoveLast (LinkedList##TYPE_NAME * self_ptr) { \
    if(self_ptr == NULL) { \
        printf("Linked List Not Initialized\n"); \
        abort(); \
    } \
    if(self_ptr->m_tail_node_ptr == NULL) { \
        printf("size가 0인데 리스트 값을 접근하려고 함\n"); \
        abort(); \
    } \
    Node##TYPE_NAME * free_target_node = self_ptr->m_tail_node_ptr; \
    TYPE last_data = free_target_node->m_data; \
    if(self_ptr->m_size == 1) { return LinkedList##TYPE_NAME##RemoveFinal(self_ptr, free_target_node); } \
    self_ptr->m_tail_node_ptr = self_ptr->m_tail_node_ptr->m_left; \
    free_target_node->m_left->m_right = NULL; \
    free_target_node->m_left = NULL; \
    free_target_node->m_right = NULL; \
    free(free_target_node); \
    self_ptr->m_head_node_ptr = self_ptr->m_tail_node_ptr; \
    self_ptr->m_size--; \
    return last_data; \
} \

DEFINE_LINKEDLIST_TYPE(int, Int)
DEFINE_LINKEDLIST_TYPE(float, Float)
DEFINE_LINKEDLIST_TYPE(double, Double)
DEFINE_LINKEDLIST_TYPE(long long, LongLong)
DEFINE_LINKEDLIST_TYPE(char, Char)
DEFINE_LINKEDLIST_TYPE(short, Short)

#endif//__HEADER_GUARD_LINKEDLIST__
