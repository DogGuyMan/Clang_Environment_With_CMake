#ifndef __HEADER_GUARD_CIRCULAR_QUEUE__
#define __HEADER_GUARD_CIRCULAR_QUEUE__

#include <stdbool.h>
#include <sjhdatatype.h>

typedef struct CircularQueue CircularQueue;

struct CircularQueue {
	GENERIC_DATA_TYPE * m_generic_array_ptr;
	int m_size;
    int m_capacity;
	int m_front_idx;
	int m_rear_idx;

	int (* const size) (struct CircularQueue * self_ptr);
    int (* const capacity) (struct CircularQueue* self_ptr);
    bool (* const is_empty) (struct CircularQueue* self_ptr);
    GENERIC_DATA_TYPE (* const front) (struct CircularQueue* self_ptr);
    GENERIC_DATA_TYPE (* const dequeue) (struct CircularQueue* self_ptr);
    void (* const enqueue) (struct CircularQueue* self_ptr, GENERIC_DATA_TYPE item);
	bool (* const is_full) (struct CircularQueue* self_ptr);
};

CircularQueue* CreateCircularQueue(int capacity);
void DestroyCircularQueue(struct CircularQueue* self_ptr);
int CircularQueueSize (struct CircularQueue * self_ptr);
int CircularQueueCapacity (struct CircularQueue* self_ptr);
bool CircularQueueIsEmpty (struct CircularQueue* self_ptr);
bool CircularQueueIsFull (struct CircularQueue* self_ptr);
GENERIC_DATA_TYPE CircularQueueFront (struct CircularQueue* self_ptr);
GENERIC_DATA_TYPE CircularQueueDequeue (struct CircularQueue* self_ptr);
void CircularQueueEnqueue (struct CircularQueue* self_ptr, GENERIC_DATA_TYPE item);

#endif//__HEADER_GUARD_CIRCULAR_QUEUE__
