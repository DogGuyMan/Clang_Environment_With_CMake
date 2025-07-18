#include <errno.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

// 추후에 GENERIC 타입을 담는 녀석과, STACK 전용 타입을 담는 녀석을 만드는것으로 하자
// 일단은 Heap 메모리 자료구조를 만들자.

// memcpy에서 사용되는 디폴트 형식
// 이렇게 하면 "* const <function_name>" 로 된 함수 포인터
static const Vector DEFAULT_VECTOR_VTABLE_TEMPLATE = {
	.m_element_type	= UNDEFINED,
	.m_element_size	= 0,
	.m_array_ptr 	= NULL,
	.m_size 		= 0,
	.m_capacity 	= 0,
	.size 			= VectorSize,
	.capacity 		= VectorCapacity,
	.is_empty 		= VectorIsEmpty,
	.at 			= VectorAt,
	.push 			= VectorPush,
	.insert 		= VectorInsert,
	.prepend 		= VectorPrepend,
	.pop 			= VectorPop,
	.find 			= VectorFind,
	.delete 		= VectorDelete,
	.remove 		= VectorRemove,
	.resize 		= VectorReserve,
};

Vector* CreateVectorDefault(DATA_TYPE element_type, size_t element_size) {
	return CreateVector(element_type, element_size, 16);
}

// new vector<DATA_TYPE>(int capacity); 를 사용하는것과 같은 동작을 하는것을 의도함.
Vector* CreateVector(DATA_TYPE element_type, size_t element_size, int capacity) {
	// Vector 동적할당
	Vector* temp_vector = malloc(sizeof(Vector));

	// 예외 처리
	if(temp_vector == NULL) {
		perror("vector memory alloc failed");
		abort();
	}
	if(0 >= element_type) {
		perror("element_type not defined");
		abort();
	}

	// Vector 템플릿 멤버 치우기
	memcpy(temp_vector, &DEFAULT_VECTOR_VTABLE_TEMPLATE, sizeof(Vector));

	// 벡터가 담을 데이터 타입
	temp_vector->m_element_type = element_type;
	temp_vector->m_element_size = element_size;

	// 미리 동적할당할 캐퍼시티 세팅
	temp_vector->m_capacity = (capacity < 16) ? 16 : capacity;
	temp_vector->m_array_ptr = malloc(sizeof(GENERIC_DATA_TYPE) * temp_vector->m_capacity);

	// 사용하기 전에 메모리 할당은 안한다..
	// free(NULL)을 하는것은 딱히 별 문제가 없다고 한다.
	for(int i = 0; i < temp_vector->m_capacity; i++) {
		temp_vector->m_array_ptr[i] = EMPTY_GENERIC_DATA_TYPE_VTABLE_TEMPLATE;
		temp_vector->m_array_ptr[i].m_type = element_type;
		temp_vector->m_array_ptr[i].m_size = element_size;
	}

	return temp_vector;
}

// delete vector;을 사용하는것과 같은 동작하는것으로 의도함.
void DestroyVector(Vector* self_ptr, DATA_DESTROY_FUNCTION destroy_function) {
	// 예외 처리
	if(self_ptr == NULL || self_ptr->m_array_ptr == NULL) {
		perror("double free error\n");
		abort();
	}

	// 원소 해제
	// 복합 자료형이면, 복합 자료형에 맞는 파괴 함수를 대리로 실행하도록
	// char, short, int라면 그냥 해제
	GENERIC_DATA_TYPE * ith_element;
	for(int i = 0; i < self_ptr->m_size; i++) {
		ith_element = (self_ptr->m_array_ptr + i);
		if(self_ptr->m_element_type >= TYPE_COMPOSITE)
			destroy_function(ith_element->m_generic_data_ptr);
		else
			free(ith_element->m_generic_data_ptr);
	}

	// 배열 해제
	free(self_ptr->m_array_ptr);

	// vector 해제
	free(self_ptr);
}

size_t  VectorSize(struct Vector * self_ptr)
{
	return self_ptr->m_size;
}

size_t  VectorCapacity(struct Vector * self_ptr)
{
	return self_ptr->m_capacity;
}

bool VectorIsEmpty(struct Vector * self_ptr)
{
	return self_ptr->m_size == 0;
}

// 수정 가능
GENERIC_DATA_TYPE* VectorAt(struct Vector * self_ptr, int index)
{
	GENERIC_DATA_TYPE * res = NULL;
	return (self_ptr->m_array_ptr + index);
}

// 벡터 vector.push_back와 같이 동작하는 것을 의도함.
void VectorPush(struct Vector * self_ptr, GENERIC_DATA_TYPE item)
{
	VectorInsert(self_ptr, self_ptr->m_size, item);
}

// 중간에 요소 삽입
void VectorInsert     (struct Vector * self_ptr, int index, GENERIC_DATA_TYPE item){
	// 예외 처리
	if(item.m_type != self_ptr->m_element_type) {
		printf("Vector Element Not Matched\n");
		return;
	}
	if(self_ptr == NULL) {
		printf("Vector Not Created\n");
		abort();
	}
	if(self_ptr->m_array_ptr == NULL) {
		printf("Vector Array Not Initialized\n");
		abort();
	}
	if(item.m_type != self_ptr->m_element_type) {
		printf("Vector Element Not Matched\n");
		return;
	}

	if(self_ptr->m_capacity <= self_ptr->m_size) {
		VectorReserveDefault(self_ptr);
	}

	size_t vector_size = self_ptr->m_size;

	for(int i = vector_size-1; i >= index; --i) {
		self_ptr->m_array_ptr[i+1] = self_ptr->m_array_ptr[i];
	}

	GENERIC_DATA_TYPE cpy_item = {
		.m_type = self_ptr->m_element_type,
		.m_generic_data_ptr = NULL,
		.m_size = self_ptr->m_element_size
	};
	if(TryAssignData(&cpy_item, &item)) {
		self_ptr->m_array_ptr[index] = cpy_item;
		++(self_ptr->m_size);
	}

	return;
}

void VectorPrepend    (struct Vector * self_ptr, GENERIC_DATA_TYPE item) {
	VectorInsert(self_ptr, 0, item);
}

// 마지막 위치에서 원소 없엠
// 그런데 이제야 왜 Pop에 값 리턴이 없었는가 이해가 되는게..
// 이렇게 되면 메모리 해제가 너무 좀 어려워 지게 되는것 같다.
GENERIC_DATA_TYPE  VectorPop(struct Vector * self_ptr)
{
	return VectorDelete(self_ptr, self_ptr->m_size-1);
}

int  VectorFind       (struct Vector * self_ptr, GENERIC_DATA_TYPE item, DATA_COMPARE_FUNCTION compare) {
	int founded_index = -1;
	for(int i = 0; i < self_ptr->m_size; i++)
	{
		if(compare((self_ptr->m_array_ptr + i), &item) == 0) {
			founded_index = i;
			break;
		}
	}
	return founded_index;
}

GENERIC_DATA_TYPE  VectorDelete     (struct Vector * self_ptr, int index)
{

	if(0 > index || index >= self_ptr->m_size) {
		printf("Index Out of Range\n");
		abort();
	}
	if(self_ptr->m_size == 0) {
		printf("Vector is Empty\n");
		abort();
	}

	// 삭제할 요소를 복사하여 반환
	GENERIC_DATA_TYPE res = EMPTY_GENERIC_DATA_TYPE_VTABLE_TEMPLATE;
	GENERIC_DATA_TYPE * element_to_delete = self_ptr->m_array_ptr + index;
	res.m_type = element_to_delete->m_type;
	res.m_size = element_to_delete->m_size;
	TryAssignData(&res, element_to_delete);

	// 원소 해제
	ResetGenericData(element_to_delete);

	// 배열 요소들 이동
	for(int i = index; i < self_ptr->m_size-1; i++) {
		self_ptr->m_array_ptr[i] = self_ptr->m_array_ptr[i+1];
	}
	--(self_ptr->m_size);

	return res;
}

GENERIC_DATA_TYPE  VectorRemove     (struct Vector * self_ptr, GENERIC_DATA_TYPE item, DATA_COMPARE_FUNCTION compare)
{
	int founded_index = self_ptr->find(self_ptr, item, compare);
	if(founded_index == -1) {
		return ERROR_GENERIC_DATA_TYPE_VTABLE_TEMPLATE;
	}
	return VectorDelete(self_ptr, founded_index);
}

int 	VectorReserveDefault(struct Vector * self_ptr) {
	return VectorReserve(self_ptr, self_ptr->m_capacity * 2);
}

int  	VectorReserve     (struct Vector * self_ptr, int new_capacity)
{
	int vector_size = self_ptr->m_size;
	GENERIC_DATA_TYPE * new_array_ptr = (GENERIC_DATA_TYPE*) malloc(sizeof(GENERIC_DATA_TYPE) * new_capacity);
	if(new_array_ptr == NULL) {  // 추가
        printf("Memory allocation failed\n");
        return self_ptr->m_capacity;  // 기존 capacity 반환
    }

	self_ptr->m_capacity = new_capacity;
	for(int i = 0; i < new_capacity; i++) {
		new_array_ptr[i] = EMPTY_GENERIC_DATA_TYPE_VTABLE_TEMPLATE;
		new_array_ptr[i].m_type = self_ptr->m_element_type;
		new_array_ptr[i].m_size = self_ptr->m_element_size;
		if(i < self_ptr->m_size) {
			if(!TryAssignData(new_array_ptr + i, self_ptr->m_array_ptr + i)) {
				printf("Assign Failed At %d\n", i);
				abort();
			}
			DestroyGeneric(self_ptr->m_array_ptr + i);
		}
	}

	/*****************************************
	❌❌ 이렇게 순서르 만들먼 절대 안된다!!!!!!!!!!
	기껏 배열 만들어 놓고 할당 해제를 해?

	self_ptr->m_array_ptr = new_array_ptr;
	free(self_ptr->m_array_ptr);
	*****************************************/

	free(self_ptr->m_array_ptr);
	self_ptr->m_array_ptr = new_array_ptr;

	return new_capacity;
}
