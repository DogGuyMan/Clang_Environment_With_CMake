#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

Vector* CreateVector(int capacity) {
	Vector* temp_vector = malloc(sizeof(Vector));
	temp_vector->m_array_ptr = NULL;
	if(capacity != 0) {
		temp_vector->m_array_ptr = malloc(sizeof(int) * capacity);
	}
	temp_vector->m_size = 0;
	temp_vector->m_capacity = capacity;

	temp_vector->size = VectorSize;
	temp_vector->capacity = VectorCapacity;
	temp_vector->is_empty = VectorIsEmpty;
	temp_vector->at = VectorAt;
	temp_vector->push = VectorPush;
	temp_vector->insert = VectorInsert;
	temp_vector->prepend = VectorPrepend;
	temp_vector->pop = VectorPop;
	temp_vector->find = VectorFind;
	temp_vector->delete = VectorDelete;
	temp_vector->remove = VectorRemove;
	temp_vector->resize = VectorReserve;
	return temp_vector;
}

void DestroyVector(Vector* self_ptr) {
	free(self_ptr->m_array_ptr);
	self_ptr->m_size = 0;
	self_ptr->m_capacity = 0;

	self_ptr->size = NULL;
	self_ptr->capacity = NULL;
	self_ptr->is_empty = NULL;
	self_ptr->at = NULL;
	self_ptr->push = NULL;
	self_ptr->insert = NULL;
	self_ptr->prepend =  NULL;
	self_ptr->pop = NULL;
	self_ptr->find = NULL;
	self_ptr->delete = NULL;
	self_ptr->remove = NULL;
	self_ptr->resize = NULL;

	free(self_ptr);
}

int  VectorSize(struct Vector * self_ptr)
{
	return self_ptr->m_size;
}

int  VectorCapacity(struct Vector * self_ptr)
{
	return self_ptr->m_capacity;
}

bool VectorIsEmpty(struct Vector * self_ptr)
{
	return self_ptr->m_size == 0;
}

int  VectorAt(struct Vector * self_ptr, int index)
{
	return *(self_ptr->m_array_ptr + index);
}

void VectorPush(struct Vector * self_ptr, int item)
{
	if(self_ptr == NULL) {
		printf("Vector Not Created\n");
		abort();
		return;
	}
	if(self_ptr->m_array_ptr == NULL) {
		printf("Vector Array Not Initialized\n");
		abort();
		return;
	}
	if(self_ptr->m_capacity <= self_ptr->m_size) {
		VectorReserve(self_ptr, self_ptr->m_size * 2);
	}
	*(self_ptr->m_array_ptr + self_ptr->m_size) = item;
	self_ptr->m_size++;
	return;
}

void VectorInsert     (struct Vector * self_ptr, int index, int item){
	if(self_ptr == NULL) {
		printf("Vector Not Created\n");
		abort();
		return;
	}
	if(self_ptr->m_array_ptr == NULL) {
		printf("Vector Array Not Initialized\n");
		abort();
		return;
	}
	if(0 > index || index >= self_ptr->m_size) {
		printf("Index Out of Range\n");
		abort();
		return;
	}
	if(self_ptr->m_capacity <= self_ptr->m_size) {
		VectorReserve(self_ptr, self_ptr->m_size * 2);
	}
	int vector_size = self_ptr->m_size;
	for(int i = vector_size-1; i >= index; --i) {
		self_ptr->m_array_ptr[i+1] = self_ptr->m_array_ptr[i];
	}
	self_ptr->m_array_ptr[index] = item;
	++(self_ptr->m_size);
	return;
}

void VectorPrepend    (struct Vector * self_ptr, int item) {
	self_ptr->insert(self_ptr, 0, item);
	return;
}

int  VectorPop(struct Vector * self_ptr)
{
	if(self_ptr->m_size == 0) {
		printf("Vector is Empty\n");
		abort();
	}
	--(self_ptr->m_size);
	return  *(self_ptr->m_array_ptr + self_ptr->m_size);
}

int  VectorFind       (struct Vector * self_ptr, int item) {
	int founded_index = -1;
	for(int i = 0; i < self_ptr->m_size; i++)
	{
		if(*(self_ptr->m_array_ptr + i) == item) {
			founded_index = i;
			break;
		}
	}
	return founded_index;
}

int  VectorDelete     (struct Vector * self_ptr, int index)
{
	if(0 > index || index >= self_ptr->m_size) {
		printf("Index Out of Range\n");
		abort();
	}
	int deleted_item = self_ptr->m_array_ptr[index];
	for(int i = index; i < self_ptr->m_size-1; i++) {
		self_ptr->m_array_ptr[i] = self_ptr->m_array_ptr[i+1];
	}
	--(self_ptr->m_size);
	return deleted_item;
}

int  VectorRemove     (struct Vector * self_ptr, int item)
{
	int founded_index = self_ptr->find(self_ptr, item);
	if(founded_index == -1) {
		return - 1;
	}
	return self_ptr->delete(self_ptr, founded_index);
}

int  VectorReserve     (struct Vector * self_ptr, int new_capacity)
{
	int vector_size = self_ptr->m_size;
	int * new_array_ptr = (int*) malloc(sizeof(int) * new_capacity);
	if(new_array_ptr == NULL) {  // 추가
        printf("Memory allocation failed\n");
        return self_ptr->m_capacity;  // 기존 capacity 반환
    }
	for(int i = 0; i < vector_size; i++) {
		*(new_array_ptr + i) = *(self_ptr->m_array_ptr + i);
	}
	free(self_ptr->m_array_ptr);
	self_ptr->m_array_ptr = new_array_ptr;
	self_ptr->m_capacity = new_capacity;
	return new_capacity;
}
