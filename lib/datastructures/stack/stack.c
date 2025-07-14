#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* CreateStack(int capacity) {
	Stack* temp_stack = (Stack*) malloc(sizeof(Stack));
	Vector* temp_container = CreateVector(TYPE_INT, capacity);
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
	DestroyVector(self_ptr->m_container, NULL);
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
	int *res = NULL;
	GENERIC_DATA_TYPE read_at_data = container->read_at(container, top_index);
	if(TryGetData(&read_at_data, TYPE_INT, (void*)&res) && res != NULL) {
		return *res;
	}
	abort();
}

int StackPop(struct Stack* self_ptr) {
	Vector* container = self_ptr->m_container;
	int container_size = container->size(container);
	if(container_size == 0) {
		printf("Stack Is Empty\n");
		abort();
	}

	int * out_data = NULL;
	GENERIC_DATA_TYPE gd = container->pop(container);

	if(TryGetData(&gd, TYPE_INT, (void*)&out_data) && out_data != NULL) {
		int res = *out_data;
		DestroyGeneric(&gd);
		self_ptr->m_size = container->m_size;
		return res;
	}
	abort();
}

/*********************************************************************************
위험한 상황임

void StackPush(struct Stack* self_ptr, int item) {
    Vector* container = self_ptr->m_container;
    GENERIC_DATA_TYPE push_data = {
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
	Vector* container = self_ptr->m_container;

	int* heap_item = malloc(sizeof(int));
	*heap_item = item;

	GENERIC_DATA_TYPE push_data = {
		.m_type = TYPE_INT,
		.m_data = heap_item,
		.m_size = sizeof(int)
	};

	container->push(container, push_data);
	self_ptr->m_size = container->m_size;
}
