#ifndef __HEADER_GUARD_SJH_DATA_TYPE__
#define __HEADER_GUARD_SJH_DATA_TYPE__

#include <stdlib.h>
#include <stdbool.h>

typedef enum {
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_STRING,
	TYPE_NODE,
} DATA_TYPE;

typedef struct GENERIC_DATA_TYPE GENERIC_DATA_TYPE;
typedef GENERIC_DATA_TYPE KEY;
typedef int (* DATA_COMPARE_FUNCTION)(const GENERIC_DATA_TYPE, const GENERIC_DATA_TYPE);

struct GENERIC_DATA_TYPE
{
	DATA_TYPE m_type;
	void * m_data;
};

static bool TryGetData (GENERIC_DATA_TYPE * self_ptr, DATA_TYPE try_data_type, void * out_data) {
    if(self_ptr == NULL) {
        if(out_data != NULL) {
            out_data = NULL;
        }
        return false;
    }

    if(self_ptr->m_type == try_data_type) {
        out_data = self_ptr->m_data;
        return true;
    }

	out_data = NULL;
	return false;
}

#endif//__HEADER_GUARD_SJH_DATA_TYPE__
