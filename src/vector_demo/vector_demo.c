#include <stdio.h>
#include "vector_demo.h"

int vector_last_item(Vector* vector) {
	int vector_size = vector->size(vector);
	GENERIC_DATA_TYPE * gd = NULL;
	gd = vector->at(vector, vector_size - 1);
	if(gd != NULL) {
		int * out_data = NULL;
		if(TryGetData(gd, TYPE_INT, (void*)&out_data) && out_data != NULL) {
			int res = *(out_data);
			return res;
		}
	}
	abort();
}

void print_all_vector_items(Vector* vector) {
	printf("print all : ");
	int vector_size = vector->size(vector);
	for(int i = 0; i < vector_size; i++) {
		GENERIC_DATA_TYPE * gd = vector->at(vector, i);
		if(gd != NULL && gd->m_data != NULL) {
			int * out_data_ptr = (int*)gd->m_data;
			printf("%d ", *out_data_ptr);
			// DestroyGeneric(gd);  // 이 부분을 제거합니다 - VectorAt은 내부 포인터를 반환하므로
		}
	}
	printf("\n");
}

int vector_demo()
{
    Vector* vector = CreateVector(TYPE_INT, sizeof(int), 5);
    printf("Create Vector\n");
	printf("vector size : %d\n", vector->size(vector));

	GENERIC_DATA_TYPE data;
	data = GenerateDataInt(1);
	vector->push(vector, data);
	DestroyGeneric(&data);

	printf("Push To Vector %d\n", vector_last_item(vector));
	printf("vector size : %d\n", vector->size(vector));

	data = GenerateDataInt(10);
	vector->push(vector, data);
	DestroyGeneric(&data);

    printf("Push To Vector %d\n", vector_last_item(vector));
	printf("vector size : %d\n", vector->size(vector));

	printf("All elements: ");
	print_all_vector_items(vector);

	GENERIC_DATA_TYPE pop_data;
	int vector_size_cached = vector->size(vector);
	for(int i = 0; i < vector_size_cached; i++) {
		pop_data = vector->pop(vector);
		printf("pop : %d\n", *(int*)pop_data.m_data);
		DestroyGeneric(&pop_data);
	}
	printf("After Clear Vector: ");
	print_all_vector_items(vector);

	for(int i = 1; i <= 100; i++) {
		data = GenerateDataInt(i);
		vector->push(vector, data);
		DestroyGeneric(&data);
	}
	printf("1~100 Filled Vector: ");
	print_all_vector_items(vector);

	DestroyVector(vector, NULL);
    printf("Destroy Vector\n");
    return 0;
}
