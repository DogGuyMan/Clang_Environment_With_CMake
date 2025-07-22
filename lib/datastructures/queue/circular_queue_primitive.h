#ifndef __HEADER_GUARD_CIRCULAR_QUEUE_PRIMITIVE__
#define __HEADER_GUARD_CIRCULAR_QUEUE_PRIMITIVE__

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sjhdatatype.h>

static const size_t CIRCULAR_QUEUE_INVALID_INDEX = -1;

#define DEFINE_CIRCULAR_QUEUE_TYPE(TYPE, TYPE_NAME) \
typedef struct CircularQueue##TYPE_NAME CircularQueue##TYPE_NAME; \
\
struct CircularQueue##TYPE_NAME { \
	/* \
	* Vector을 사용할 수 없는것은. 가변 배열이 아니라 Fixed Array가 되야 하기 떄문이다. \
	*/ \
	TYPE * m_array_ptr; \
	size_t m_size; \
    size_t m_capacity; \
	size_t m_front_idx; \
	size_t m_rear_idx; \
\
	size_t (* const size) (struct CircularQueue##TYPE_NAME * self_ptr); \
    size_t (* const capacity) (struct CircularQueue##TYPE_NAME * self_ptr); \
    bool (* const is_empty) (struct CircularQueue##TYPE_NAME * self_ptr); \
    TYPE (* const front) (struct CircularQueue##TYPE_NAME * self_ptr); \
    TYPE (* const dequeue) (struct CircularQueue##TYPE_NAME * self_ptr); \
    void (* const enqueue) (struct CircularQueue##TYPE_NAME * self_ptr, TYPE item); \
	bool (* const is_full) (struct CircularQueue##TYPE_NAME * self_ptr); \
}; \
\
CircularQueue##TYPE_NAME * CreateCircularQueue##TYPE_NAME (size_t capacity); \
void DestroyCircularQueue##TYPE_NAME (struct CircularQueue##TYPE_NAME * self_ptr); \
\
size_t CircularQueue##TYPE_NAME##Size (struct CircularQueue##TYPE_NAME * self_ptr); \
size_t CircularQueue##TYPE_NAME##Capacity (struct CircularQueue##TYPE_NAME * self_ptr); \
bool CircularQueue##TYPE_NAME##IsEmpty (struct CircularQueue##TYPE_NAME * self_ptr); \
bool CircularQueue##TYPE_NAME##IsFull (struct CircularQueue##TYPE_NAME * self_ptr); \
TYPE CircularQueue##TYPE_NAME##Front (struct CircularQueue##TYPE_NAME * self_ptr); \
TYPE CircularQueue##TYPE_NAME##Dequeue (struct CircularQueue##TYPE_NAME * self_ptr); \
void CircularQueue##TYPE_NAME##Enqueue (struct CircularQueue##TYPE_NAME * self_ptr, TYPE item); \

#define IMPLEMENT_CIRCULAR_QUEUE_TYPE(TYPE, TYPE_NAME) \
\
static const CircularQueue##TYPE_NAME DEFAULT_CIRCULAR_QUEUE##TYPE_NAME##_TEMPLATE = { \
    .m_array_ptr = NULL,  \
    .m_size = 0, \
    .m_capacity = 0, \
    .m_front_idx = CIRCULAR_QUEUE_INVALID_INDEX, \
    .m_rear_idx = CIRCULAR_QUEUE_INVALID_INDEX, \
    .size = CircularQueue##TYPE_NAME##Size, \
    .capacity = CircularQueue##TYPE_NAME##Capacity, \
    .is_empty = CircularQueue##TYPE_NAME##IsEmpty, \
    .front = CircularQueue##TYPE_NAME##Front, \
    .dequeue = CircularQueue##TYPE_NAME##Dequeue, \
    .enqueue = CircularQueue##TYPE_NAME##Enqueue, \
    .is_full = CircularQueue##TYPE_NAME##IsFull \
}; \
\
CircularQueue##TYPE_NAME * CreateCircularQueue##TYPE_NAME (size_t capacity){ \
	if(capacity <= 0) { \
		perror("Invalid capacity\n"); \
		abort(); \
	} \
	CircularQueue##TYPE_NAME * temp_queue = (CircularQueue##TYPE_NAME *) malloc(sizeof(CircularQueue##TYPE_NAME)); \
	if(temp_queue == NULL) { \
		perror("memory allocation failed\n"); \
		abort(); \
	} \
\
	memcpy(temp_queue, &DEFAULT_CIRCULAR_QUEUE##TYPE_NAME##_TEMPLATE, sizeof(CircularQueue##TYPE_NAME)); \
	temp_queue->m_array_ptr = (TYPE*) malloc(sizeof(TYPE) * capacity); \
	if(temp_queue->m_array_ptr == NULL) { \
		perror("memory allocation failed\n"); \
		abort(); \
	} \
	temp_queue->m_capacity = capacity; \
	return temp_queue; \
} \
\
void DestroyCircularQueue##TYPE_NAME(struct CircularQueue##TYPE_NAME * self_ptr){ \
	if (self_ptr == NULL && self_ptr->m_array_ptr == NULL) { \
	    perror("Queue is NULL\n"); \
		return; \
	} \
	free(self_ptr->m_array_ptr); \
	free(self_ptr); \
} \
\
size_t CircularQueue##TYPE_NAME##Size (struct CircularQueue##TYPE_NAME * self_ptr){ \
	if (self_ptr == NULL) { \
	    perror("Queue is NULL\n"); \
	    abort(); \
	} \
\
	return 	self_ptr->m_size; \
} \
\
size_t CircularQueue##TYPE_NAME##Capacity (struct CircularQueue##TYPE_NAME * self_ptr){ \
	if (self_ptr == NULL) { \
	    perror("Queue is NULL\n"); \
	    abort(); \
	} \
\
	return 	self_ptr->m_capacity; \
} \
\
bool CircularQueue##TYPE_NAME##IsEmpty (struct CircularQueue##TYPE_NAME * self_ptr){ \
	if (self_ptr == NULL) { \
	    perror("Queue is NULL\n"); \
	    abort(); \
	} \
\
	return 	self_ptr->m_size <= 0 && \
		self_ptr->m_front_idx == CIRCULAR_QUEUE_INVALID_INDEX && \
		self_ptr->m_rear_idx == CIRCULAR_QUEUE_INVALID_INDEX; \
} \
\
bool CircularQueue##TYPE_NAME##IsFull (struct CircularQueue##TYPE_NAME * self_ptr){ \
	if (self_ptr == NULL) { \
	    perror("Queue is NULL\n"); \
	    abort(); \
	} \
\
	return 	self_ptr->m_size >= self_ptr->m_capacity; \
} \
\
TYPE CircularQueue##TYPE_NAME##Front (struct CircularQueue##TYPE_NAME * self_ptr){ \
	if (self_ptr == NULL) { \
	    perror("Queue is NULL\n"); \
	    abort(); \
	} \
\
	if (self_ptr->is_empty(self_ptr)) { \
        perror("Queue is empty\n"); \
        abort(); \
    } \
\
	return *(self_ptr->m_array_ptr + self_ptr->m_front_idx); \
} \
\
TYPE CircularQueue##TYPE_NAME##DequeueFinal(struct CircularQueue##TYPE_NAME * self_ptr) { \
	if(self_ptr->is_empty(self_ptr)) { \
		perror("invailed dequeue operation when is empty\n"); \
		abort(); \
	} \
	if(self_ptr->m_front_idx != self_ptr->m_rear_idx) { \
		perror("somting wrong in dequeue operation\n"); \
		abort(); \
	} \
	TYPE res = *(self_ptr->m_array_ptr + self_ptr->m_front_idx); \
\
	self_ptr->m_front_idx = CIRCULAR_QUEUE_INVALID_INDEX; \
	self_ptr->m_rear_idx = CIRCULAR_QUEUE_INVALID_INDEX; \
	self_ptr->m_size = 0; \
	return res; \
} \
\
TYPE CircularQueue##TYPE_NAME##Dequeue (struct CircularQueue##TYPE_NAME * self_ptr){ \
	if (self_ptr == NULL) { \
	    perror("Queue is NULL\n"); \
	    abort(); \
	} \
\
	if(self_ptr->m_capacity <= 0) { \
		perror("queue's capacity is zero\n"); \
		abort(); \
	} \
\
	if(self_ptr->is_empty(self_ptr)) { \
		perror("invailed dequeue operation when is empty\n"); \
		abort(); \
	} \
	if(self_ptr->m_size == 1) {return CircularQueue##TYPE_NAME##DequeueFinal(self_ptr);} \
	TYPE res = *(self_ptr->m_array_ptr + self_ptr->m_front_idx); \
\
	self_ptr->m_front_idx += 1; \
	self_ptr->m_front_idx = self_ptr->m_front_idx % self_ptr->m_capacity; \
	--(self_ptr->m_size); \
	return res; \
} \
\
void CircularQueue##TYPE_NAME##EnqueueFirst(struct CircularQueue##TYPE_NAME * self_ptr, TYPE first_item) { \
	if(self_ptr->m_capacity <= 0) { \
		perror("queue's capacity is zero\n"); \
		abort(); \
	} \
\
	self_ptr->m_front_idx = 0; \
	self_ptr->m_rear_idx = 0; \
	self_ptr->m_size = 1; \
	*(self_ptr->m_array_ptr + 0) = first_item; \
} \
\
void CircularQueue##TYPE_NAME##Enqueue (struct CircularQueue##TYPE_NAME * self_ptr, TYPE item){ \
	if (self_ptr == NULL) { \
	    perror("Queue is NULL\n"); \
	    abort(); \
	} \
\
	if(self_ptr->m_capacity <= 0) { \
		perror("queue's capacity is zero\n"); \
		abort(); \
	} \
	if(self_ptr->is_full(self_ptr)) { \
		perror("queue's capacity is full\n"); \
		abort(); \
	} \
\
	if(self_ptr->m_size == 0) { \
		if(self_ptr->m_front_idx == CIRCULAR_QUEUE_INVALID_INDEX && self_ptr->m_rear_idx == CIRCULAR_QUEUE_INVALID_INDEX) { \
			CircularQueue##TYPE_NAME##EnqueueFirst(self_ptr, item); \
			return; \
		} \
		else \
		{ \
			perror("expected empty but index value is invalid\n"); \
			abort(); \
		} \
	} \
	self_ptr->m_rear_idx += 1; \
	self_ptr->m_rear_idx = self_ptr->m_rear_idx % self_ptr->m_capacity; \
	*(self_ptr->m_array_ptr + self_ptr->m_rear_idx) = item; \
	++(self_ptr->m_size); \
} \

DEFINE_CIRCULAR_QUEUE_TYPE(int, Int)
DEFINE_CIRCULAR_QUEUE_TYPE(float, Float)
DEFINE_CIRCULAR_QUEUE_TYPE(double, Double)
DEFINE_CIRCULAR_QUEUE_TYPE(long long, LongLong)
DEFINE_CIRCULAR_QUEUE_TYPE(char, Char)
DEFINE_CIRCULAR_QUEUE_TYPE(short, Short)
DEFINE_CIRCULAR_QUEUE_TYPE(uintptr_t, AddressType)

#endif//__HEADER_GUARD_CIRCULAR_QUEUE_PRIMITIVE__
