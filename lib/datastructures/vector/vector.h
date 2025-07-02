#ifndef __HEADER_GUARD_VECTOR__
#define __HEADER_GUARD_VECTOR__

#include <stdbool.h>

typedef struct Vector Vector;

struct Vector {
	int * m_array_ptr;
	int m_size;
	int m_capacity;

	int (*size) 	(struct Vector * self_ptr);
	int (*capacity)	(struct Vector * self_ptr);
	bool(*is_empty) (struct Vector * self_ptr);
	int (*at) 	(struct Vector * self_ptr, int index);
	void (*push) 	(struct Vector * self_ptr, int item);
	void (*insert) 	(struct Vector * self_ptr, int index, int item);
	void (*prepend) 	(struct Vector * self_ptr, int item);
	// return index
	int (*pop) 	(struct Vector * self_ptr);
	int (*find) 	(struct Vector * self_ptr, int item);
	int (*delete) 	(struct Vector * self_ptr, int index);
	int (*remove) 	(struct Vector * self_ptr, int item);
	int (*resize) 	(struct Vector * self_ptr, int new_capacity);
};

Vector* CreateVector(int capacity);
void 	DestroyVector(struct Vector * self_ptr);
int  	VectorSize 	(struct Vector * self_ptr);
int  	VectorCapacity	(struct Vector * self_ptr);
bool 	VectorIsEmpty	(struct Vector * self_ptr);
int  	VectorAt 	(struct Vector * self_ptr, int index);
void 	VectorPush 	(struct Vector * self_ptr, int item);
void 	VectorInsert 	(struct Vector * self_ptr, int index, int item);
void 	VectorPrepend 	(struct Vector * self_ptr, int item);
int  	VectorPop 	(struct Vector * self_ptr);
int  	VectorFind 	(struct Vector * self_ptr, int item);
int  	VectorDelete 	(struct Vector * self_ptr, int index);
int  	VectorRemove 	(struct Vector * self_ptr, int item);
int  	VectorReserve 	(struct Vector * self_ptr, int new_capacity);

#endif//__HEADER_GUARD_VECTOR__
