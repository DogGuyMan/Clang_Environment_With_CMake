#ifndef __HEADER_GUARD_SJH_DATA_TYPE__
#define __HEADER_GUARD_SJH_DATA_TYPE__


/********************************************************************************
* 다음 링크에서 참고함.
* https://github.com/cwchentw/c-type-check/blob/master/test_type_check.c
*********************************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include <complex.h>

// enum이 1바이트만 사용하여 메모리를 절약
#ifdef __GNUC__
    #define PACKED_UNSIGNED_ENUM __attribute__((packed))
#elif defined(_MSC_VER)
    #define PACKED_UNSIGNED_ENUM : unsigned char
#else
    #define PACKED_UNSIGNED_ENUM
#endif

typedef enum PACKED_UNSIGNED_ENUM {
	ERROR 		= 0x00,
	UNDEFINED	= 0x00,

	TYPE_PRIMITIVE = 0x01,
	TYPE_COMPOSITE = 0x20,

	TYPE_BOOL 	= TYPE_PRIMITIVE + 1,
    TYPE_CHAR,
    TYPE_SIGNED_CHAR,
    TYPE_UNSIGNED_CHAR,
    TYPE_SHORT,
    TYPE_INT,
    TYPE_LONG,
    TYPE_LONG_LONG,
    TYPE_UNSIGNED_SHORT,
    TYPE_UNSIGNED_INT,
    TYPE_UNSIGNED_LONG,
    TYPE_UNSIGNED_LONG_LONG,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_LONG_DOUBLE,
    TYPE_FLOAT_COMPLEX,
    TYPE_DOUBLE_COMPLEX,
    TYPE_LONG_DOUBLE_COMPLEX,

    TYPE_POINTER_TO_VOID = TYPE_COMPOSITE + 1,
    TYPE_POINTER_TO_CHAR,
	TYPE_STRING,
	TYPE_NODE,
	TYPE_VECTOR,
	TYPE_MAX 	= 0xFF,
} DATA_TYPE;

typedef struct GENERIC_DATA_TYPE GENERIC_DATA_TYPE;
typedef GENERIC_DATA_TYPE KEY;
typedef int (* DATA_COMPARE_FUNCTION)(const GENERIC_DATA_TYPE * const , const GENERIC_DATA_TYPE * const);
typedef void (* DATA_DESTROY_FUNCTION)(void * data);

/*
* 제네릭을 하면서 생긴 문제는 힙할당 데이터를 다루게 되었기 떄문에
* 트레이드 오프는 있다.
*/
struct GENERIC_DATA_TYPE
{
	DATA_TYPE m_type;
	void * m_generic_data_ptr; // 제네릭 타입을 사용하게 되면서 너무 곤란한 상황이 발생했다.
	size_t m_size;
};

static const GENERIC_DATA_TYPE EMPTY_GENERIC_DATA_TYPE_VTABLE_TEMPLATE = {
	.m_type = UNDEFINED,
	.m_generic_data_ptr = NULL,
	.m_size = 0
};

static const GENERIC_DATA_TYPE ERROR_GENERIC_DATA_TYPE_VTABLE_TEMPLATE = {
	.m_type = ERROR,
	.m_generic_data_ptr = NULL,
	.m_size = 0
};

static GENERIC_DATA_TYPE GenerateData(DATA_TYPE data_type, size_t data_size, void * data) {
	GENERIC_DATA_TYPE res = EMPTY_GENERIC_DATA_TYPE_VTABLE_TEMPLATE;
	res.m_type = data_type;
	res.m_size = data_size;
	res.m_generic_data_ptr = malloc(data_size);
	memcpy(res.m_generic_data_ptr, data, data_size);
	return res;
}

static GENERIC_DATA_TYPE GenerateDataInt(int data) {
	GENERIC_DATA_TYPE res = EMPTY_GENERIC_DATA_TYPE_VTABLE_TEMPLATE;
	res.m_type = TYPE_INT;
	res.m_size = sizeof(int);
	res.m_generic_data_ptr = malloc(res.m_size);
	int * m_int_data_ptr = (int *) res.m_generic_data_ptr;
	*(m_int_data_ptr) = data;
	return res;
}

static bool TryAssignData(GENERIC_DATA_TYPE * lhs, GENERIC_DATA_TYPE* rhs) {
	if(lhs == NULL || rhs == NULL) return false;
	if(lhs->m_type != rhs->m_type) return false;
	if(lhs->m_size != rhs->m_size) return false;

	// 기존 메모리 해제 (이미 할당되어 있다면)
	if(lhs->m_generic_data_ptr != NULL) {
		free(lhs->m_generic_data_ptr);
	}

	lhs->m_generic_data_ptr = malloc(rhs->m_size);
	if(lhs->m_generic_data_ptr == NULL) return false;

	memcpy(lhs->m_generic_data_ptr, rhs->m_generic_data_ptr, rhs->m_size);

	return true;
}

static inline bool TryGetData (GENERIC_DATA_TYPE * self_ptr, DATA_TYPE try_data_type, void ** out_data) {
    if(self_ptr == NULL || out_data == NULL) {
        return false;
    }

    if(self_ptr->m_type == try_data_type) {
        *out_data = self_ptr->m_generic_data_ptr;
        return true;
    }

	*out_data = NULL;
	return false;
}

static inline void ResetGenericData(GENERIC_DATA_TYPE * self_ptr) {
	if(self_ptr == NULL) return;
	free(self_ptr->m_generic_data_ptr);
    self_ptr->m_generic_data_ptr = NULL;
}

static void DestroyGeneric(GENERIC_DATA_TYPE * self_ptr) {
    if(self_ptr == NULL) return;
	ResetGenericData(self_ptr);
    self_ptr->m_type = UNDEFINED;
    self_ptr->m_size = 0;
}

#endif//__HEADER_GUARD_SJH_DATA_TYPE__
