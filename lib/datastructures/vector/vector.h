#ifndef __HEADER_GUARD_VECTOR__
#define __HEADER_GUARD_VECTOR__

#include <stdbool.h>
#include "sjhdatatype.h"

typedef struct Vector Vector;

struct Vector {
	DATA_TYPE m_element_type;
	size_t m_element_size;

	GENERIC_DATA_TYPE * m_array_ptr;
	size_t m_size;
	size_t m_capacity;

	size_t  (* const size) 	(struct Vector * self_ptr);
	size_t  (* const capacity)	(struct Vector * self_ptr);
	bool (* const is_empty) (struct Vector * self_ptr);
	GENERIC_DATA_TYPE* 	(* const at) 		(struct Vector * self_ptr, int index);
	void (* const push) 	(struct Vector * self_ptr, GENERIC_DATA_TYPE item);
	void (* const insert) 	(struct Vector * self_ptr, int index, GENERIC_DATA_TYPE item);
	void (* const prepend) 	(struct Vector * self_ptr, GENERIC_DATA_TYPE item);
	GENERIC_DATA_TYPE  (* const pop) 		(struct Vector * self_ptr);
	// return index
	int  (* const find) 	(struct Vector * self_ptr, GENERIC_DATA_TYPE item, DATA_COMPARE_FUNCTION compare);
	GENERIC_DATA_TYPE  (* const delete) 	(struct Vector * self_ptr, int index);
	GENERIC_DATA_TYPE  (* const remove) 	(struct Vector * self_ptr, GENERIC_DATA_TYPE item, DATA_COMPARE_FUNCTION compare);
	int  (* const resize) 	(struct Vector * self_ptr, int new_capacity);
};

Vector* 			CreateVectorDefault	(DATA_TYPE element_type, size_t element_size);
Vector* 			CreateVector	(DATA_TYPE element_type, size_t element_size, int capacity);
void 				DestroyVector	(struct Vector * self_ptr, DATA_DESTROY_FUNCTION destroy_function);
size_t  			VectorSize 		(struct Vector * self_ptr);
size_t  			VectorCapacity	(struct Vector * self_ptr);
bool 				VectorIsEmpty	(struct Vector * self_ptr);
GENERIC_DATA_TYPE*  VectorAt 		(struct Vector * self_ptr, int index);
void 				VectorPush 		(struct Vector * self_ptr, GENERIC_DATA_TYPE item);
void 				VectorInsert 	(struct Vector * self_ptr, int index, GENERIC_DATA_TYPE item);
void 				VectorPrepend 	(struct Vector * self_ptr, GENERIC_DATA_TYPE item);
GENERIC_DATA_TYPE  	VectorPop 		(struct Vector * self_ptr);
int  				VectorFind 		(struct Vector * self_ptr, GENERIC_DATA_TYPE item, DATA_COMPARE_FUNCTION compare);
GENERIC_DATA_TYPE   VectorDelete 	(struct Vector * self_ptr, int index);
GENERIC_DATA_TYPE  	VectorRemove 	(struct Vector * self_ptr, GENERIC_DATA_TYPE item,  DATA_COMPARE_FUNCTION compare);
int 				VectorReserveDefault	(struct Vector * self_ptr);
int  				VectorReserve 	(struct Vector * self_ptr, int new_capacity);

#endif//__HEADER_GUARD_VECTOR__
