#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* CreateStack(size_t capacity) {
	Stack* temp_stack = (Stack*) malloc(sizeof(Stack));
	VectorInt* temp_container = CreateVectorInt(capacity);
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
	DestroyVectorInt(self_ptr->m_container);
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

size_t StackSize(struct Stack* self_ptr) {
	return self_ptr->m_size;
}

size_t StackCapacity(struct Stack* self_ptr) {
	return self_ptr->m_capacity;
}

bool StackIsEmpty(struct Stack* self_ptr) {
	return self_ptr->m_size == 0;
}

int StackTop(struct Stack* self_ptr) {
	VectorInt* container = self_ptr->m_container;
	int container_size = container->size(container);
	if(container_size == 0) {
		printf("Stack Is Empty\n");
		abort();
	}
	int top_index = container_size -1;
	return *(container->at(container, top_index));
}

int StackPop(struct Stack* self_ptr) {
	VectorInt* container = self_ptr->m_container;
	size_t container_size = container->size(container);
	if(container_size == 0) {
		printf("Stack Is Empty\n");
		abort();
	}

	int pop_data = container->pop_back(container);
	self_ptr->m_size = container->size(container);
	return pop_data;
}

/*********************************************************************************
위험한 상황임

void StackPush(struct Stack* self_ptr, int item) {
    VectorInt* container = self_ptr->m_container;
    int push_data = {
        .m_type = TYPE_INT,
        .m_data = &item  // ❌ 매개변수의 주소를 저장!
    };

    container->push(container, push_data);
    self_ptr->m_size = container->m_size;
}  // ⚠️ 함수 종료 시 item 매개변수 소멸!

// 사용 예시
int main() {
    Stack* stack = CreateStack(10);

    // Push 시점
    stack->push(stack, 42);  // item = 42의 주소를 저장
    // StackPush 함수 종료 → item 매개변수 소멸

    // Pop 시점 (위험!)
    int result = stack->pop(stack);  // 소멸된 메모리 참조!
    printf("Result: %d\n", result);  // 쓰레기 값 또는 크래시

    return 0;
}

*********************************************************************************/
void StackPush(struct Stack* self_ptr, int item) {
	VectorInt* container = self_ptr->m_container;

	container->push_back(container, item);
	self_ptr->m_size = container->m_size;
}
