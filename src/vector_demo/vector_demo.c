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

	vector->push(vector, GenerateDataInt(1));
	printf("Push To Vector %d\n", vector_last_item(vector));
	printf("vector size : %d\n", vector->size(vector));

	vector->push(vector, GenerateDataInt(10));
        printf("Push To Vector %d\n", vector_last_item(vector));
	printf("vector size : %d\n", vector->size(vector));

	printf("All elements: ");
	print_all_vector_items(vector);

	DestroyVector(vector, NULL);
    printf("Destroy Vector\n");
        return 0;
}
