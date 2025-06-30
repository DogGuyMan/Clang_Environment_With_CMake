#include <stdio.h>
#include "vector_demo.h"

int vector_last_item(Vector* vector) {
	int vector_size = vector->size(vector);
	return vector->at(vector, vector_size - 1);	
}

void print_all_vector_items(Vector* vector) {
	printf("print all : ");
	int vector_size = vector->size(vector);
	for(int i = 0; i < vector_size; i++) {
		printf("%d ", vector->at(vector, i));
	}
	printf("\n");
}

int vector_demo()
{
        Vector* vector = CreateVector(5);
        printf("Create Vector\n");
	printf("vector size : %d\n", vector->size(vector));
	
	vector->push(vector, 1);
	printf("Push To Vector %d\n", vector_last_item(vector));
	printf("vector size : %d\n", vector->size(vector));
	
	vector->push(vector, 10);
        printf("Push To Vector %d\n", vector_last_item(vector));
	printf("vector size : %d\n", vector->size(vector));
	
	printf("vector size : %d\n", vector->size(vector));
        print_all_vector_items(vector);
	DestroyVector(vector);
        printf("Destroy Vector\n");
        return 0;
}
