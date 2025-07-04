#ifndef __HEADER_GUARD_HEAP__
#define __HEADER_GUARD_HEAP__

#include <stdbool.h>
#include <vector.h>

typedef struct Heap Heap;

struct Heap {
    Vector m_container;
    int m_size;
    int m_capacity;
};

#endif//__HEADER_GUARD_HEAP__
