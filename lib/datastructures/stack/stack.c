#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

const Stack DEFAULT_STACK_VTABLE_TEMPLATE = {
	.m_element_type		= UNDEFINED,
	.m_element_size		= 0,
	.m_container		= NULL,
	.m_size				= 0,
	.m_capacity 		= 0,
	.size				= StackSize,
	.capacity			= StackCapacity,
	.is_empty			= StackIsEmpty,
	.top				= StackTop,
	.pop				= StackPop,
	.push				= StackPush,
};

Stack * CreateStack(DATA_TYPE element_type, size_t element_size, size_t capacity) {
	Stack * temp_stack = (Stack *) malloc(sizeof(Stack));

	if(temp_stack == NULL) {
		perror("vector memory alloc failed");
		abort();
	}
	if(0 >= element_type) {
		perror("element_type not defined");
		abort();
	}

	memcpy(temp_stack, &DEFAULT_STACK_VTABLE_TEMPLATE, sizeof(Stack));

	Vector* temp_container 		= CreateVector(element_type, element_size, capacity);

	temp_stack->m_element_type 	=	element_type;
	temp_stack->m_element_size 	=	element_size;
	temp_stack->m_container 	=	temp_container;
	temp_stack->m_capacity 		=	temp_container->m_capacity;

	return temp_stack;
}

void DestroyStack(struct Stack* self_ptr, DATA_DESTROY_FUNCTION destroy_function) {
	// 예외 처리
	if(self_ptr == NULL || self_ptr->m_container == NULL) {
		perror("double free error\n");
		abort();
	}

	DestroyVector(self_ptr->m_container, destroy_function);
	self_ptr->m_container = NULL;
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

GENERIC_DATA_TYPE StackTop(struct Stack* self_ptr) {
	Vector * container = self_ptr->m_container;
	int container_size = container->size(container);
	if(container_size == 0) {
		printf("Stack Is Empty\n");
		abort();
	}
	int top_index = container_size -1;
	return *(container->at(container, top_index));
}

GENERIC_DATA_TYPE StackPop(struct Stack* self_ptr) {
	Vector * container = self_ptr->m_container;
	size_t container_size = container->size(container);
	if(container_size == 0) {
		printf("Stack Is Empty\n");
		abort();
	}

	GENERIC_DATA_TYPE pop_data = container->pop(container);
	self_ptr->m_size = container->size(container);
	return pop_data;
}

/*********************************************************************************
위험한 상황임

void StackPush(struct Stack* self_ptr, int item) {
    Vector * container = self_ptr->m_container;
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

void StackPush(struct Stack* self_ptr, GENERIC_DATA_TYPE item) {
	Vector * container = self_ptr->m_container;

	container->push(container, item);
	self_ptr->m_size = container->m_size;
}
