#ifndef __HEADER_GUARD_STACK__
#define __HEADER_GUARD_STACK__

#include <stdbool.h>
#include "sjhdatatype.h"
#include "vector.h"

typedef struct Stack Stack;

struct Stack {
	DATA_TYPE m_element_type;
	size_t m_element_size;
	Vector* m_container;
	size_t m_size;
	size_t m_capacity;

	size_t (*size) (struct Stack * self_ptr);
	size_t (*capacity) (struct Stack * self_ptr);
	bool (*is_empty) (struct Stack* self_ptr);
	GENERIC_DATA_TYPE (*top) (struct Stack* self_ptr);
	GENERIC_DATA_TYPE (*pop) (struct Stack* self_ptr);
	void (*push) (struct Stack* self_ptr, GENERIC_DATA_TYPE item);
};

Stack * CreateStack(DATA_TYPE element_type, size_t element_size, size_t capacity);
void DestroyStack(struct Stack* self_ptr, DATA_DESTROY_FUNCTION destroy_function);
size_t StackSize(struct Stack* self_ptr);
size_t StackCapacity(struct Stack* self_ptr);
bool StackIsEmpty(struct Stack* self_ptr);
GENERIC_DATA_TYPE StackTop(struct Stack* self_ptr);
GENERIC_DATA_TYPE StackPop(struct Stack* self_ptr);
void StackPush(struct Stack* self_ptr, GENERIC_DATA_TYPE item);

#endif//__HEADER_GUARD_STACK__
