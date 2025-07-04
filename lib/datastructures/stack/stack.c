#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* CreateStack(int capacity) {
	Stack* temp_stack = (Stack*) malloc(sizeof(Stack));
	Vector* temp_container = CreateVector(capacity);
	temp_stack->m_container = temp_container;
	temp_stack->m_capacity = temp_container->m_capacity;
	temp_stack->m_size = 0;

	temp_stack->size = StackSize;
	temp_stack->capacity = StackCapacity;
	temp_stack->is_empty = StackIsEmpty;
	temp_stack->top = StackTop;
	temp_stack->pop = StackPop;
	temp_stack->push = StackPush;
	return temp_stack;
}

void DestroyStack(struct Stack* self_ptr) {
	DestroyVector(self_ptr->m_container);
	self_ptr->m_container = NULL;

	self_ptr->m_capacity = 0;
	self_ptr->m_size = 0;

	self_ptr->size = NULL;
	self_ptr->capacity = NULL;
	self_ptr->is_empty = NULL;
	self_ptr->top = NULL;
	self_ptr->pop = NULL;
	self_ptr->push = NULL;
	free(self_ptr);
}


int StackSize(struct Stack* self_ptr) {
	return self_ptr->m_size;
}

int StackCapacity(struct Stack* self_ptr) {
	return self_ptr->m_capacity;
}

bool StackIsEmpty(struct Stack* self_ptr) {
	return self_ptr->m_size == 0;
}

int StackTop(struct Stack* self_ptr) {
	Vector* container = self_ptr->m_container;
	int container_size = container->size(container);
	if(container_size == 0) {
		printf("Stack Is Empty\n");
		abort();
	}
	int top_index = container_size -1;
	return container->read_at(container, top_index);
}

int StackPop(struct Stack* self_ptr) {
	Vector* container = self_ptr->m_container;
	int container_size = container->size(container);
	if(container_size == 0) {
		printf("Stack Is Empty\n");
		abort();
	}
	int res = container->pop(container);
	self_ptr->m_size = container->m_size;
	return res;
}

void StackPush(struct Stack* self_ptr, int item) {
	Vector* container = self_ptr->m_container;
	container->push(container, item);
	self_ptr->m_size = container->m_size;
}
