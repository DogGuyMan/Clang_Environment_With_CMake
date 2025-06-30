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

	temp_vector->size = Size;
	temp_vector->capacity = Capacity;
	temp_vector->is_empty = Is_Empty;
	temp_vector->at = At;
	temp_vector->push = Push;
	temp_vector->insert = Insert;
	temp_vector->prepend = Prepend;
	temp_vector->pop = Pop;
	temp_vector->find = Find;
	temp_vector->delete = Delete;
	temp_vector->remove = Remove;
	temp_vector->resize = Resize;
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

int  Size       (struct Vector * self_ptr) 
{
	return self_ptr->m_size;
}

int  Capacity   (struct Vector * self_ptr) 
{
	return self_ptr->m_capacity; 
}

bool Is_Empty   (struct Vector * self_ptr)
{
	return self_ptr->m_size == 0 && (self_ptr->m_array_ptr + 0) == NULL;
}

int  At         (struct Vector * self_ptr, int index) 
{
	return *(self_ptr->m_array_ptr + index);
}

void Push       (struct Vector * self_ptr, int item) 
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
	// TODO PLEASE APPLY CAPACITY DYNAMICS!!
	if(self_ptr->m_capacity <= self_ptr->m_size) {
		printf("Vector Capacity Full\n");
		abort();
		return;
	}
	// TODO LAST POINTER
	*(self_ptr->m_array_ptr + self_ptr->m_size) = item;
	++self_ptr->m_size;
	return;
}

void Insert     (struct Vector * self_ptr, int index, int item){
	// TODO IMPLEMENT PLEASE
	printf("NOT IMPLEMENTED\n");
	abort();
	return;
}
void Prepend    (struct Vector * self_ptr, int item) {
	// TODO IMPLEMENT PLEASE
	printf("NOT IMPLEMENTED\n");
	abort();
	return;

}

int  Pop        (struct Vector * self_ptr)
{
	int res = *(self_ptr->m_array_ptr + self_ptr->m_size);
	--self_ptr->m_size;
	return res;
}

int  Find       (struct Vector * self_ptr, int item) {
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

int  Delete     (struct Vector * self_ptr, int index)
{
	// TODO IMPLEMENT PLEASE
	printf("NOT IMPLEMENTED\n");
	abort();
	return -1;
}

int  Remove     (struct Vector * self_ptr, int item)
{
	// TODO IMPLEMENT PLEASE
	printf("NOT IMPLEMENTED\n");
	abort();
	return -1;
}

int  Resize     (struct Vector * self_ptr, int new_capacity)
{
	// TODO IMPLEMENT PLEASE
	printf("NOT IMPLEMENTED\n");
	abort();
	return -1;
}


