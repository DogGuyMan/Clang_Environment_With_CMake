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

void print_all_vector_int_items(VectorInt * vi) {
	size_t vsz = vi->size(vi)-1;
	for(int i = 0; i < vsz; i++) {
		printf("%d, ", *(vi->at(vi, i)));
	}
	printf("%d\n", *(vi->at(vi, vsz)));
}

int vector_demo()
{
    Vector* vector = CreateVector(TYPE_INT, sizeof(int), 5);
    printf("Create Vector\n");
	printf("vector size : %zu\n", vector->size(vector));

	GENERIC_DATA_TYPE data;
	data = GenerateDataInt(1);
	vector->push(vector, data);
	DestroyGeneric(&data);

	printf("Push To Vector %d\n", vector_last_item(vector));
	printf("vector size : %zu\n", vector->size(vector));

	data = GenerateDataInt(10);
	vector->push(vector, data);
	DestroyGeneric(&data);

    printf("Push To Vector %d\n", vector_last_item(vector));
	printf("vector size : %zu\n", vector->size(vector));

	printf("All elements: ");
	print_all_vector_items(vector);

	GENERIC_DATA_TYPE rm_data;
	int vector_size_cached = vector->size(vector);
	for(int i = 0; i < vector_size_cached; i++) {
		rm_data = vector->pop(vector);
		printf("pop : %d\n", *(int*)rm_data.m_data);
		DestroyGeneric(&rm_data);
	}
	printf("After Clear Vector: ");
	print_all_vector_items(vector);

	for(int i = 1; i <= 50; i++) {
		data = GenerateDataInt(i);
		vector->push(vector, data);
		DestroyGeneric(&data);
	}
	printf("1~100 Filled Vector:n");
	print_all_vector_items(vector);

	for(int i = 10; i <= 40; i+=2) {
		if(i > vector->size(vector)) continue;
		rm_data = vector->delete(vector, i);
		// printf("rm index %d, delete : %d, size : %zu\n", i, *(int*)rm_data.m_data, vector->size(vector));
		DestroyGeneric(&rm_data);
		// print_all_vector_items(vector);
	}

	printf("10 even to 40 delete Vector: ");
	print_all_vector_items(vector);

	for(int i = 10; i <= 40; i+=2) {
		data = GenerateDataInt(i);
		vector->insert(vector, i, data);
		printf("insert index %d, insert : %d, size : %zu\n", i, *(int*)data.m_data, vector->size(vector));
		print_all_vector_items(vector);
		DestroyGeneric(&data);
	}

	printf("10 even to 40 re add Vector: ");
	print_all_vector_items(vector);

	DestroyVector(vector, NULL);
    printf("Destroy Vector\n\n");

    return 0;
}

int vector_primitive_demo() {
    // int 벡터 생성
    VectorFloat* f_vec = CreateVectorFloatDefault();

    // 데이터 추가
    f_vec->push_back(f_vec, 1.5);
    f_vec->push_back(f_vec, 2.5);
    f_vec->push_back(f_vec, 3.5);

    // 데이터 출력
    printf("Int Vector size: %zu\n", f_vec->size(f_vec));
    for(size_t i = 0; i < f_vec->size(f_vec); i++) {
        float* value = (f_vec->at(f_vec, i));
        if(value != NULL) {
            printf("f_vec[%zu] = %f\n", i, *value);
        }
    }

    // 메모리 해제
    DestroyVectorFloat(f_vec);
	f_vec = NULL;

	VectorInt * i_vec = CreateVectorIntDefault();
	i_vec->push_back(i_vec, -199);
	i_vec->push_back(i_vec, 10);
	i_vec->push_back(i_vec, 100);

	int i_vec_data;
	for(int i = 0; i < i_vec->size(i_vec)-1; i++) {
		i_vec_data = *(i_vec->at(i_vec, i));
		printf("%d, ", i_vec_data);
	}
	printf("%d\n", *(i_vec->at(i_vec, i_vec->size(i_vec)-1)));

	size_t end_size_cache = i_vec->size(i_vec);
	for(int i = 0; i < end_size_cache; i++) {
		i_vec_data = i_vec->pop_back(i_vec);
		printf("pop : %d\n", i_vec_data);
	}

	if(i_vec->is_empty(i_vec)) {
		printf("int vector empty\n");
	}

	for(int i = 1; i <= 50; ++i) {
		i_vec->push_back(i_vec, i);
	}


	printf("1~100 Filled Vector:\n");
	print_all_vector_int_items(i_vec);
	int rm_data;
	for(int i = 10; i <= 40; i+=2) {
		if(i > i_vec->size(i_vec)) continue;
		rm_data = i_vec->remove_with_index(i_vec, i);
		printf("rm index %d, delete : %d, size : %zu\n", i, rm_data, i_vec->size(i_vec));
		print_all_vector_int_items(i_vec);
	}

	printf("10 even to 40 delete I_vec: ");
	print_all_vector_int_items(i_vec);

	for(int i = 10; i <= 40; i+=2) {
		i_vec->insert_with_index(i_vec, i, i);
		printf("insert index %d, insert : %d, size : %zu\n", i, i, i_vec->size(i_vec));
		print_all_vector_int_items(i_vec);
	}
	DestroyVectorInt(i_vec);
	i_vec = NULL;

    return 0;
}
