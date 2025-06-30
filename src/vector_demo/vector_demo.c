#include <stdio.h>
#include "vector_demo.h"

int vector_demo()
{
        Vector* vector = CreateVector(0);
        printf("Create Vector\n");
        DestroyVector(vector);
        printf("Destroy Vector\n");
}

