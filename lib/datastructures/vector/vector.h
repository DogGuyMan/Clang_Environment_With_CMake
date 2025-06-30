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
int  Size 	(struct Vector * self_ptr);
int  Capacity	(struct Vector * self_ptr);
bool Is_Empty	(struct Vector * self_ptr);
int  At 	(struct Vector * self_ptr, int index);
void Push 	(struct Vector * self_ptr, int item);
void Insert 	(struct Vector * self_ptr, int index, int item);
void Prepend 	(struct Vector * self_ptr, int item);
int  Pop 	(struct Vector * self_ptr);
int  Find 	(struct Vector * self_ptr, int item);
int  Delete 	(struct Vector * self_ptr, int index);
int  Remove 	(struct Vector * self_ptr, int item);
int  Resize 	(struct Vector * self_ptr, int new_capacity);

#endif//__HEADER_GUARD_VECTOR__
