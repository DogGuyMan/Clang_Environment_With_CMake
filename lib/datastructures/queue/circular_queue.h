#ifndef __HEADER_GUARD_CIRCULAR_QUEUE__
#define __HEADER_GUARD_CIRCULAR_QUEUE__

#include <stdbool.h>

typedef struct CircularQueue CircularQueue;

struct CircularQueue {
	int * m_array_ptr;
	int m_size;
        int m_capacity;
	int m_front_idx;
	int m_rear_idx;

	const int (*size) (struct CircularQueue * self_ptr);
        const int (*capacity) (struct CircularQueue* self_ptr);
        const bool (*is_empty) (struct CircularQueue* self_ptr);
        const int (*front) (struct CircularQueue* self_ptr);
        const int (*dequeue) (struct CircularQueue* self_ptr);
        const void (*enqueue) (struct CircularQueue* self_ptr, int item);
	const bool (*is_full) (struct CircularQueue* self_ptr);
};

CircularQueue* CreateCircularQueue(int capacity);
void DestroyCircularQueue(struct CircularQueue* self_ptr);
int CircularQueueSize (struct CircularQueue * self_ptr);
int CircularQueueCapacity (struct CircularQueue* self_ptr);
bool CircularQueueIsEmpty (struct CircularQueue* self_ptr);
bool CircularQueueIsFull (struct CircularQueue* self_ptr);
int CircularQueueFront (struct CircularQueue* self_ptr);
int CircularQueueDequeue (struct CircularQueue* self_ptr);
void CircularQueueEnqueue (struct CircularQueue* self_ptr, int item);

#endif//__HEADER_GUARD_CIRCULAR_QUEUE__
