#ifndef __HEADER_GUARD_NEW_VECTOR_PRIMITIVE__
#define __HEADER_GUARD_NEW_VECTOR_PRIMITIVE__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DEFINE_VECTOR_TYPE(TYPE, TYPE_NAME) \
typedef struct Vector##TYPE_NAME Vector##TYPE_NAME; \
\
struct Vector##TYPE_NAME { \
	TYPE * m_array_ptr; \
	size_t m_size; \
	size_t m_capacity; \
 	\
	size_t 		(* const size) 			 		(Vector##TYPE_NAME * self_ptr); \
	size_t 		(* const capacity) 		 		(Vector##TYPE_NAME * self_ptr); \
	bool 		(* const is_empty)		 		(Vector##TYPE_NAME * self_ptr); \
	TYPE * 	(* const at)			 		(Vector##TYPE_NAME * self_ptr, size_t index); \
	void 		(* const insert_with_index) 	(Vector##TYPE_NAME * self_ptr, size_t index, TYPE item); \
	TYPE 	(* const remove_with_index) 	(Vector##TYPE_NAME * self_ptr, size_t index); \
	void 		(* const push_back) 	 		(Vector##TYPE_NAME * self_ptr, TYPE item); \
	TYPE 	(* const pop_back) 		 		(Vector##TYPE_NAME * self_ptr); \
	size_t 		(* const find) 			 		(Vector##TYPE_NAME * self_ptr, TYPE item); \
	size_t		(* const reserve) 		 		(Vector##TYPE_NAME * self_ptr, size_t new_capacity); \
}; \
\
Vector##TYPE_NAME * CreateVector##TYPE_NAME##Default(); \
Vector##TYPE_NAME * CreateVector##TYPE_NAME				(size_t capacity); \
void 				DestroyVector##TYPE_NAME			(Vector##TYPE_NAME * self_ptr); \
\
size_t 				Vector##TYPE_NAME##Size				(Vector##TYPE_NAME * self_ptr); \
size_t 				Vector##TYPE_NAME##Capacity			(Vector##TYPE_NAME * self_ptr); \
bool 				Vector##TYPE_NAME##IsEmpty			(Vector##TYPE_NAME * self_ptr); \
TYPE * 				Vector##TYPE_NAME##At				(Vector##TYPE_NAME * self_ptr, size_t index); \
void 				Vector##TYPE_NAME##Insert			(Vector##TYPE_NAME * self_ptr, size_t index, TYPE item); \
TYPE 				Vector##TYPE_NAME##Remove			(Vector##TYPE_NAME * self_ptr, size_t index); \
void 				Vector##TYPE_NAME##Push				(Vector##TYPE_NAME * self_ptr, TYPE item); \
TYPE 				Vector##TYPE_NAME##Pop				(Vector##TYPE_NAME * self_ptr); \
size_t 				Vector##TYPE_NAME##Find				(Vector##TYPE_NAME * self_ptr, TYPE item); \
size_t				Vector##TYPE_NAME##Reserve			(Vector##TYPE_NAME * self_ptr, size_t new_capacity); \


#define IMPLEMENT_VECTOR_TYPE(TYPE, TYPE_NAME) \
\
const Vector##TYPE_NAME DEFAULT_VECTOR_##TYPE_NAME##_VTABLE_TEMPLATE = { \
	.m_array_ptr 			= NULL, \
	.m_size 				= 0, \
	.m_capacity 			= 0, \
	.size 					= Vector##TYPE_NAME##Size, \
	.capacity 				= Vector##TYPE_NAME##Capacity, \
	.is_empty 				= Vector##TYPE_NAME##IsEmpty, \
	.at 					= Vector##TYPE_NAME##At, \
	.insert_with_index 		= Vector##TYPE_NAME##Insert, \
	.remove_with_index 		= Vector##TYPE_NAME##Remove, \
	.push_back 				= Vector##TYPE_NAME##Push, \
	.pop_back 				= Vector##TYPE_NAME##Pop, \
	.find 					= Vector##TYPE_NAME##Find, \
	.reserve 				= Vector##TYPE_NAME##Reserve, \
}; \
\
Vector##TYPE_NAME * CreateVector##TYPE_NAME (size_t capacity) { \
	Vector##TYPE_NAME * temp_vector = (Vector##TYPE_NAME *)malloc(sizeof(Vector##TYPE_NAME)); \
	if(temp_vector == NULL) { \
		perror("vector memory alloc failed"); \
		abort(); \
	}\
	memcpy(temp_vector, &DEFAULT_VECTOR_##TYPE_NAME##_VTABLE_TEMPLATE, sizeof(Vector##TYPE_NAME)); \
	temp_vector->m_capacity = (capacity < 16) ? 16 : capacity; \
	temp_vector->m_array_ptr = (TYPE *) malloc(sizeof(TYPE) * temp_vector->m_capacity); \
	if(temp_vector->m_array_ptr == NULL) { \
		printf("Memory allocation failed\n"); \
		abort(); \
	}\
	return temp_vector; \
}\
\
Vector##TYPE_NAME * CreateVector##TYPE_NAME##Default() { \
	return CreateVector##TYPE_NAME (16); \
}\
\
void DestroyVector##TYPE_NAME (Vector##TYPE_NAME * self_ptr) { \
	if(self_ptr == NULL || self_ptr->m_array_ptr == NULL) { \
		perror("double free error\n"); \
		abort(); \
	}\
 \
	free(self_ptr->m_array_ptr); \
	free(self_ptr); \
}\
\
size_t  Vector##TYPE_NAME##Size(struct Vector##TYPE_NAME * self_ptr) { \
	if(self_ptr == NULL) { \
		printf("Vector Not Created\n"); \
		abort(); \
	}\
	return self_ptr->m_size; \
}\
\
size_t  Vector##TYPE_NAME##Capacity(struct Vector##TYPE_NAME * self_ptr) { \
	if(self_ptr == NULL) { \
		printf("Vector Not Created\n"); \
		abort(); \
	}\
	return self_ptr->m_capacity; \
}\
\
bool Vector##TYPE_NAME##IsEmpty(struct Vector##TYPE_NAME * self_ptr) { \
	if(self_ptr == NULL) { \
		printf("Vector Not Created\n"); \
		abort(); \
	}\
	return self_ptr->m_size == 0; \
}\
\
TYPE* Vector##TYPE_NAME##At(struct Vector##TYPE_NAME * self_ptr, size_t index) { \
	if(self_ptr == NULL) { \
		printf("Vector Not Created\n"); \
		abort(); \
	}\
	return (self_ptr->m_array_ptr + index); \
}\
\
size_t  Vector##TYPE_NAME##Reserve     (struct Vector##TYPE_NAME * self_ptr, size_t new_capacity) { \
	size_t vector_size = self_ptr->m_size; \
\
	/* \
	malloc을 사용하는 예시 \
	TYPE * new_array_ptr = (TYPE*) malloc(sizeof(TYPE) * new_capacity); \
	realloc : 이미 할당한 공간의 크기를 바꿀 때 realloc 함수를 사용한다. \
	*/ \
	TYPE * new_array_ptr = (TYPE*) realloc(self_ptr->m_array_ptr, sizeof(TYPE) * new_capacity); \
\
	if(new_array_ptr == NULL) { \
        printf("Memory allocation failed\n"); \
        return self_ptr->m_capacity; \
    }\
\
	/* \
	realloc을 사용하면 이렇게 복사할 필요는 없다. \
	for(int i = 0; i < vector_size; i++) { \
			*(new_array_ptr + i) = *(self_ptr->m_array_ptr + i); \
	}\
	free(self_ptr->m_array_ptr); \
	*/ \
\
	self_ptr->m_array_ptr = new_array_ptr; \
	self_ptr->m_capacity = new_capacity; \
	return new_capacity; \
}\
\
void Vector##TYPE_NAME##Insert			(Vector##TYPE_NAME * self_ptr, size_t index, TYPE item) { \
	if(self_ptr == NULL) { \
		printf("Vector Not Created\n"); \
		abort(); \
	}\
	if(self_ptr->m_array_ptr == NULL) { \
		printf("Vector Array Not Initialized\n"); \
		abort(); \
	}\
	if(0 > index || index > self_ptr->m_size) { \
		printf("Index Out of Range\n"); \
		abort(); \
	}\
\
	if(self_ptr->m_capacity <= self_ptr->m_size) { \
		Vector##TYPE_NAME##Reserve(self_ptr, self_ptr->m_size * 2); \
	}\
\
	if(self_ptr->m_size > 0) { \
		size_t end = self_ptr->m_size-1; \
		\
		for(size_t i = end; i >= index; --i) { \
			self_ptr->m_array_ptr[i+1] = self_ptr->m_array_ptr[i]; \
		}\
	}\
\
	self_ptr->m_array_ptr[index] = item; \
	self_ptr->m_size++; \
}\
\
void Vector##TYPE_NAME##Push(struct Vector##TYPE_NAME * self_ptr, TYPE item) { \
	Vector##TYPE_NAME##Insert(self_ptr, self_ptr->m_size, item); \
}\
\
void Vector##TYPE_NAME##Prepend(struct Vector##TYPE_NAME * self_ptr, TYPE item) { \
	Vector##TYPE_NAME##Insert(self_ptr, 0, item); \
}\
\
TYPE  Vector##TYPE_NAME##Remove (struct Vector##TYPE_NAME * self_ptr, size_t index) { \
	if(0 > index || index >= self_ptr->m_size) { \
		printf("Index Out of Range\n"); \
		abort(); \
	}\
\
	if(self_ptr->m_size == 0) { \
		printf("Vector is Empty\n"); \
		abort(); \
	}\
\
	TYPE deleted_item = self_ptr->m_array_ptr[index]; \
\
	for(int i = index; i < self_ptr->m_size-1; i++) { \
		self_ptr->m_array_ptr[i] = self_ptr->m_array_ptr[i+1]; \
	}\
	--(self_ptr->m_size); \
\
	return deleted_item; \
}\
\
TYPE  Vector##TYPE_NAME##Pop(struct Vector##TYPE_NAME * self_ptr) { \
	return  Vector##TYPE_NAME##Remove(self_ptr, self_ptr->m_size-1); \
}\
\
size_t  Vector##TYPE_NAME##Find       (struct Vector##TYPE_NAME * self_ptr, TYPE item) { \
	for(size_t i = 0; i < self_ptr->m_size; i++) { \
		if(self_ptr->m_array_ptr[i] == item) { \
			return (size_t)i; \
		}\
	}\
	abort(); \
}\

DEFINE_VECTOR_TYPE(int, Int)
DEFINE_VECTOR_TYPE(float, Float)
DEFINE_VECTOR_TYPE(double, Double)
DEFINE_VECTOR_TYPE(long long, LongLong)
DEFINE_VECTOR_TYPE(char, Char)
DEFINE_VECTOR_TYPE(short, Short)

#endif//__HEADER_GUARD_NEW_VECTOR_PRIMITIVE__
