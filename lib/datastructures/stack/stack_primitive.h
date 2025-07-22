#ifndef __HEADER_GUARD_STACK_PRIMITIVE__
#define __HEADER_GUARD_STACK_PRIMITIVE__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector_primitive.h"

#define DEFINE_STACK_TYPE(TYPE, TYPE_NAME) \
typedef struct Stack##TYPE_NAME Stack##TYPE_NAME; \
\
struct Stack##TYPE_NAME { \
	Vector##TYPE_NAME * m_container; \
	size_t m_size; \
	size_t m_capacity; \
\
	size_t	( * const size) 		(struct Stack##TYPE_NAME * self_ptr); \
	size_t	( * const capacity) 	(struct Stack##TYPE_NAME * self_ptr); \
	bool	( * const is_empty) 	(struct Stack##TYPE_NAME * self_ptr); \
	TYPE	( * const top) 			(struct Stack##TYPE_NAME * self_ptr); \
	TYPE	( * const pop) 			(struct Stack##TYPE_NAME * self_ptr); \
	void	( * const push) 		(struct Stack##TYPE_NAME * self_ptr, TYPE item); \
}; \
\
Stack##TYPE_NAME * 	CreateStack##TYPE_NAME(size_t capacity); \
void 				DestroyStack##TYPE_NAME(struct Stack##TYPE_NAME * self_ptr); \
\
size_t 				Stack##TYPE_NAME##Size(struct Stack##TYPE_NAME * self_ptr);\
size_t 				Stack##TYPE_NAME##Capacity(struct Stack##TYPE_NAME * self_ptr);\
bool 				Stack##TYPE_NAME##IsEmpty(struct Stack##TYPE_NAME * self_ptr);\
TYPE 				Stack##TYPE_NAME##Top(struct Stack##TYPE_NAME * self_ptr);\
TYPE 				Stack##TYPE_NAME##Pop(struct Stack##TYPE_NAME * self_ptr);\
void 				Stack##TYPE_NAME##Push(struct Stack##TYPE_NAME * self_ptr, TYPE item);\

#define IMPLEMENT_STACK_TYPE(TYPE, TYPE_NAME) \
\
const Stack##TYPE_NAME DEFAULT_STACK_##TYPE_NAME##_TEMPLATE = { \
	.m_container		= NULL, \
	.m_size				= 0, \
	.m_capacity 		= 0, \
	.size				= Stack##TYPE_NAME##Size, \
	.capacity			= Stack##TYPE_NAME##Capacity, \
	.is_empty			= Stack##TYPE_NAME##IsEmpty, \
	.top				= Stack##TYPE_NAME##Top, \
	.pop				= Stack##TYPE_NAME##Pop, \
	.push				= Stack##TYPE_NAME##Push, \
}; \
\
Stack##TYPE_NAME * CreateStack##TYPE_NAME(size_t capacity) { \
	Stack##TYPE_NAME * temp_stack = (Stack##TYPE_NAME *) malloc(sizeof(Stack##TYPE_NAME)); \
	if(temp_stack == NULL) { \
		perror("stack memory alloc failed"); \
		abort(); \
	}\
	memcpy(temp_stack, &DEFAULT_STACK_##TYPE_NAME##_TEMPLATE, sizeof(Stack##TYPE_NAME)); \
	Vector##TYPE_NAME* temp_container = CreateVector##TYPE_NAME(capacity); \
	temp_stack->m_container = temp_container; \
	temp_stack->m_capacity = temp_container->m_capacity; \
	return temp_stack;\
}\
\
void DestroyStack##TYPE_NAME(struct Stack##TYPE_NAME * self_ptr) { \
	DestroyVector##TYPE_NAME(self_ptr->m_container); \
	self_ptr->m_container = NULL; \
	free(self_ptr); \
} \
\
size_t Stack##TYPE_NAME##Size(struct Stack##TYPE_NAME * self_ptr) { \
	return self_ptr->m_size; \
}\
size_t Stack##TYPE_NAME##Capacity(struct Stack##TYPE_NAME * self_ptr) {\
	return self_ptr->m_capacity;\
}\
bool Stack##TYPE_NAME##IsEmpty(struct Stack##TYPE_NAME * self_ptr) {\
	return self_ptr->m_size == 0;\
}\
TYPE Stack##TYPE_NAME##Top(struct Stack##TYPE_NAME * self_ptr) {\
	Vector##TYPE_NAME * container = self_ptr->m_container;\
	TYPE container_size = container->size(container);\
	if(container_size == 0) {\
		printf("Stack Is Empty\n");\
		abort();\
	}\
	TYPE top_index = container_size -1;\
	return *(container->at(container, top_index));\
}\
\
TYPE Stack##TYPE_NAME##Pop(struct Stack##TYPE_NAME * self_ptr) {\
	Vector##TYPE_NAME * container = self_ptr->m_container;\
	size_t container_size = container->size(container);\
	if(container_size == 0) {\
		printf("Stack Is Empty\n");\
		abort();\
	}\
\
	TYPE pop_data = container->pop_back(container);\
	self_ptr->m_size = container->size(container);\
	return pop_data;\
}\
\
void Stack##TYPE_NAME##Push(struct Stack##TYPE_NAME * self_ptr, TYPE item) {\
	Vector##TYPE_NAME * container = self_ptr->m_container;\
	container->push_back(container, item);\
	self_ptr->m_size = container->m_size;\
}\

DEFINE_STACK_TYPE(int, Int)
DEFINE_STACK_TYPE(short, Short);
DEFINE_STACK_TYPE(float, Float)
DEFINE_STACK_TYPE(double, Double)
DEFINE_STACK_TYPE(long long, LongLong)
DEFINE_STACK_TYPE(char, Char)
DEFINE_STACK_TYPE(uintptr_t, AddressType)

#endif//__HEADER_GUARD_STACK__
