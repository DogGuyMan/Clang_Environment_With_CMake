#ifndef __HEADER_GUARD_STACK__
#define __HEADER_GUARD_STACK__

#include <stdbool.h>
#include "vector.h"

typedef struct Stack Stack;

struct Stack {
	Vector* m_container;
	int m_size;
	int m_capacity;

	int (*size) (struct Stack * self_ptr);
	int (*capacity) (struct Stack * self_ptr);
	bool (*is_empty) (struct Stack* self_ptr);
	int (*top) (struct Stack* self_ptr);
	int (*pop) (struct Stack* self_ptr);
	void (*push) (struct Stack* self_ptr, int item);
};

Stack* CreateStack(int capacity);
void DestroyStack(struct Stack* self_ptr);
int StackSize(struct Stack* self_ptr);
int StackCapacity(struct Stack* self_ptr);
bool StackIsEmpty(struct Stack* self_ptr);
int StackTop(struct Stack* self_ptr);
int StackPop(struct Stack* self_ptr);
void StackPush(struct Stack* self_ptr, int item);

#endif//__HEADER_GUARD_STACK__
