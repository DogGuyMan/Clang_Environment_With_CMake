#ifndef __HEADER_GUARD_QUEUE__
#define __HEADER_GUARD_QUEUE__

#include <stdbool.h>
#include <sjhdatatype.h>
#include "linkedlist.h"

typedef struct Queue Queue;

struct Queue {
	DATA_TYPE data_type;
	size_t data_size;
	LinkedList * m_container;
	size_t m_size;
	size_t m_capacity;

	size_t (*size) (struct Queue * self_ptr);
	size_t (*capacity) (struct Queue* self_ptr);
	bool (*is_empty) (struct Queue* self_ptr);
	GENERIC_DATA_TYPE (*front) (struct Queue* self_ptr);
	GENERIC_DATA_TYPE (*dequeue) (struct Queue* self_ptr);
	void (*enqueue) (struct Queue* self_ptr, GENERIC_DATA_TYPE item);
};

Queue* CreateQueue(DATA_TYPE data_type, size_t data_size);
void DestroyQueue(struct Queue* self_ptr);
size_t Size (struct Queue * self_ptr);
size_t Capacity (struct Queue* self_ptr);
bool IsEmpty (struct Queue* self_ptr);
GENERIC_DATA_TYPE Front (struct Queue* self_ptr);
GENERIC_DATA_TYPE Dequeue (struct Queue* self_ptr);
void Enqueue (struct Queue* self_ptr, GENERIC_DATA_TYPE item);


#endif//__HEADER_GUARD_QUEUE__
