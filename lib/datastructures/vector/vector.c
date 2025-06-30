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
	temp_vector->resize = VectorResize;
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

int  VectorSize       (struct Vector * self_ptr)
{
	return self_ptr->m_size;
}

int  VectorCapacity   (struct Vector * self_ptr)
{
	return self_ptr->m_capacity;
}

bool VectorIsEmpty   (struct Vector * self_ptr)
{
	return self_ptr->m_size == 0 && (self_ptr->m_array_ptr + 0) == NULL;
}

int  VectorAt         (struct Vector * self_ptr, int index)
{
	return *(self_ptr->m_array_ptr + index);
}

void VectorPush       (struct Vector * self_ptr, int item)
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
	// TODO PLEASE RESIZE
	if(self_ptr->m_capacity <= self_ptr->m_size) {
		printf("Vector Capacity Full\n");
		abort();
		return;
	}
	*(self_ptr->m_array_ptr + self_ptr->m_size) = item;
	self_ptr->m_size++;
	return;
}

void VectorInsert     (struct Vector * self_ptr, int index, int item){
	// TODO IMPLEMENT PLEASE
	printf("NOT IMPLEMENTED\n");
	abort();
	return;
}
void VectorPrepend    (struct Vector * self_ptr, int item) {
	// TODO IMPLEMENT PLEASE
	printf("NOT IMPLEMENTED\n");
	abort();
	return;

}

int  VectorPop        (struct Vector * self_ptr)
{
	int res = *(self_ptr->m_array_ptr + self_ptr->m_size);
	--self_ptr->m_size;
	return res;
}

int  VectorFind       (struct Vector * self_ptr, int item) {
	int finded_index = -1;
	for(int i = 0; i < self_ptr->m_size; i++)
	{
		if(*(self_ptr->m_array_ptr + i) == item) {
			finded_index = i;
			break;
		}
	}
	return finded_index;
}

int  VectorDelete     (struct Vector * self_ptr, int index)
{
	// TODO IMPLEMENT PLEASE
	printf("NOT IMPLEMENTED\n");
	abort();
	return -1;
}

int  VectorRemove     (struct Vector * self_ptr, int item)
{
	// TODO IMPLEMENT PLEASE
	printf("NOT IMPLEMENTED\n");
	abort();
	return -1;
}

int  VectorResize     (struct Vector * self_ptr, int new_capacity)
{
	// TODO IMPLEMENT PLEASE
	printf("NOT IMPLEMENTED\n");
	abort();
	return -1;
}
