#ifndef __HEADER_GUARD_TREE_PRIMITIVE__
#define __HEADER_GUARD_TREE_PRIMITIVE__

#include <stdlib.h>
#include <stdbool.h>

#define DEFINE_TREE_TYPE(TYPE, TYPE_NAME) \
typedef struct BinaryTree##TYPE_NAME##NodeInfo BinaryTree##TYPE_NAME##NodeInfo; \
typedef struct BinaryTree##TYPE_NAME##TravelInfo BinaryTree##TYPE_NAME##TravelInfo; \
\
struct BinaryTree##TYPE_NAME##NodeInfo { \
    const size_t m_idx; \
    const TYPE m_data; \
}; \
\
struct BinaryTree##TYPE_NAME##TravelInfo \
{ \
    TYPE * const m_array_ptr; \
    int m_size; \
    void (* const callback) (BinaryTree##TYPE_NAME##TravelInfo * self_ptr, TYPE data); \
}; \

DEFINE_TREE_TYPE(int, Int);
DEFINE_TREE_TYPE(float, Float)
DEFINE_TREE_TYPE(double, Double)
DEFINE_TREE_TYPE(long long, LongLong)
DEFINE_TREE_TYPE(char, Char)
DEFINE_TREE_TYPE(short, Short)

#endif//__HEADER_GUARD_TREE_PRIMITIVE__
