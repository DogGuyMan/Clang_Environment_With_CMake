#ifndef __HEADER_GUARD_QUEUE__
#define __HEADER_GUARD_QUEUE__

#include <stdbool.h>
#include <linkedlist>

typedef struct Queue Queue;

struct Queue {
	LinkedList* m_container;
	int m_size;
	int m_capacity;

	int (*size) (struct Queue * self_ptr);
	int (*capacity) (struct Queue* self_ptr);
	bool (*is_empty) (struct Queue* self_ptr);
	int (*front) (struct Queue* self_ptr);
	int (*dequeue) (struct Queue* self_ptr);
	void (*enqueue) (struct Queue* self_ptr, int item);
};

Queue* CreateQueue();
void DestroyQueue(struct Queue* self_ptr);
int Size (struct Queue * self_ptr);
int Capacity (struct Queue* self_ptr);
bool IsEmpty (struct Queue* self_ptr);
int Front (struct Queue* self_ptr);
int Dequeue (struct Queue* self_ptr);
void Enqueue (struct Queue* self_ptr, int item);


#endif//__HEADER_GUARD_QUEUE__
