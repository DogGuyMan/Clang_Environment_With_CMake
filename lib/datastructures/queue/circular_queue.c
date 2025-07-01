#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circular_queue.h"

static const CircularQueue DEFAULT_CIRCULAR_QUEUE_VTABLE_TEMPLATE = {
    .m_array_ptr = NULL,  // must be initialize after memcpy
    .m_size = 0,
    .m_capacity = 0,      // must be initialize after memcpy
    .m_front_idx = -1,
    .m_rear_idx = -1,
    .size = CircularQueueSize,
    .capacity = CircularQueueCapacity,
    .is_empty = CircularQueueIsEmpty,
    .front = CircularQueueFront,
    .dequeue = CircularQueueDequeue,
    .enqueue = CircularQueueEnqueue,
    .is_full = CircularQueueIsFull
};

CircularQueue* CreateCircularQueue(int capacity){
	if(capacity <= 0) {
		perror("Invalid capacity\n");
		abort();
	}
	CircularQueue * temp_queue = (CircularQueue*) malloc(sizeof(CircularQueue));
	if(temp_queue == NULL) {
		perror("memory allocation failed\n");
		abort();
	}

	memcpy(temp_queue, &DEFAULT_CIRCULAR_QUEUE_VTABLE_TEMPLATE, sizeof(CircularQueue));

	temp_queue->m_array_ptr = (int*) malloc(sizeof(int) * capacity);
	if(temp_queue->m_array_ptr == NULL) {
		perror("memory allocation failed\n");
		abort();
	}
	temp_queue->m_capacity = capacity;
	return temp_queue;
}

void DestroyCircularQueue(struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
		return;
	}
	if(self_ptr->m_array_ptr == NULL)
		free(self_ptr->m_array_ptr);

	free(self_ptr);
}

int CircularQueueSize (struct CircularQueue * self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	return 	self_ptr->m_size;
}

int CircularQueueCapacity (struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	return 	self_ptr->m_capacity;
}

bool CircularQueueIsEmpty (struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	return 	self_ptr->m_size <= 0 &&
		self_ptr->m_front_idx == -1 &&
		self_ptr->m_rear_idx == -1;
}

bool CircularQueueIsFull (struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	return 	self_ptr->m_size >= self_ptr->m_capacity;
}

int CircularQueueFront (struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	if (self_ptr->is_empty(self_ptr)) {
        perror("Queue is empty\n");
        abort();
    }
	return *(self_ptr->m_array_ptr + self_ptr->m_front_idx);
}

int CircularQueueDequeueFinal(struct CircularQueue* self_ptr) {
	if(self_ptr->is_empty(self_ptr)) {
		perror("invailed dequeue operation when is empty\n");
		abort();
	}
	if(self_ptr->m_front_idx != self_ptr->m_rear_idx) {
		perror("somting wrong in dequeue operation\n");
		abort();
	}
	int res = *(self_ptr->m_array_ptr + self_ptr->m_front_idx);
	self_ptr->m_front_idx = -1;
	self_ptr->m_rear_idx = -1;
	self_ptr->m_size = 0;
	return res;
}

int CircularQueueDequeue (struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	if(self_ptr->m_capacity <= 0) {
                perror("queue's capacity is zero\n");
                abort();
        }

	if(self_ptr->is_empty(self_ptr)) {
		perror("invailed dequeue operation when is empty\n");
		abort();
	}
	if(self_ptr->m_size == 1) {return CircularQueueDequeueFinal(self_ptr);}
	int res = *(self_ptr->m_array_ptr + self_ptr->m_front_idx);
	self_ptr->m_front_idx += 1;
	self_ptr->m_front_idx = self_ptr->m_front_idx % self_ptr->m_capacity;
	--(self_ptr->m_size);
	return res;
}

void CircularQueueEnqueueFirst(struct CircularQueue* self_ptr, int first_item) {
	if(self_ptr->m_capacity <= 0) {
		perror("queue's capacity is zero\n");
		abort();
	}
	self_ptr->m_front_idx = 0;
	self_ptr->m_rear_idx = 0;
	self_ptr->m_size = 1;
	*(self_ptr->m_array_ptr + 0) = first_item;
}

void CircularQueueEnqueue (struct CircularQueue* self_ptr, int item){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	if(self_ptr->m_capacity <= 0) {
		perror("queue's capacity is zero\n");
		abort();
	}
	if(self_ptr->is_full(self_ptr)) {
		perror("queue's capacity is full\n");
		abort();
	}
	if(self_ptr->m_size == 0) {
		if(self_ptr->m_front_idx < 0 && self_ptr->m_rear_idx < 0) {
			CircularQueueEnqueueFirst(self_ptr, item);
			return;
		}
		else
		{
			perror("expected empty but index value is invalid\n");
			abort();
		}
	}
	self_ptr->m_rear_idx += 1;
	self_ptr->m_rear_idx = self_ptr->m_rear_idx % self_ptr->m_capacity;
	*(self_ptr->m_array_ptr + self_ptr->m_rear_idx) = item;
	++(self_ptr->m_size);
}
