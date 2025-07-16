#ifndef __HEADER_GUARD_STACK__
#define __HEADER_GUARD_STACK__

#include <stdbool.h>
#include "sjhdatatype.h"
#include "vector_primitive.h"

typedef struct Stack Stack;

struct Stack {
	VectorInt* m_container;
	size_t m_size;
	size_t m_capacity;

	size_t (*size) (struct Stack * self_ptr);
	size_t (*capacity) (struct Stack * self_ptr);
	bool (*is_empty) (struct Stack* self_ptr);
	int (*top) (struct Stack* self_ptr);
	int (*pop) (struct Stack* self_ptr);
	void (*push) (struct Stack* self_ptr, int item);
};

Stack* CreateStack(size_t capacity);
void DestroyStack(struct Stack* self_ptr);
size_t StackSize(struct Stack* self_ptr);
size_t StackCapacity(struct Stack* self_ptr);
bool StackIsEmpty(struct Stack* self_ptr);
int StackTop(struct Stack* self_ptr);
int StackPop(struct Stack* self_ptr);
void StackPush(struct Stack* self_ptr, int item);

#endif//__HEADER_GUARD_STACK__
