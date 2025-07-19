#ifndef __HEADER_GUARD_COMPLETE_BINARY_TREE_PRIMITIVE__
#define __HEADER_GUARD_COMPLETE_BINARY_TREE_PRIMITIVE__

#include <stdlib.h>
#include <stdbool.h>
#include "vector_primitive.h"
#include "circular_queue_primitive.h"
#include "stack_primitive.h"

#define DEFINE_COMPLETE_BINARYTREE_TYPE(TYPE, TYPE_NAME) \
typedef struct CompleteBinaryTree##TYPE_NAME CompleteBinaryTree##TYPE_NAME; \
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
\
struct CompleteBinaryTree##TYPE_NAME { \
    Vector##TYPE_NAME * m_container; \
    size_t m_size; \
    size_t m_root; \
\
    size_t m_head_idx; \
\
    size_t (* const size) (CompleteBinaryTree##TYPE_NAME * self_ptr); \
    size_t (* const max_depth) (CompleteBinaryTree##TYPE_NAME * self_ptr); \
    void     (* const insert) (CompleteBinaryTree##TYPE_NAME * self_ptr, TYPE item); \
    TYPE      (* const remove) (CompleteBinaryTree##TYPE_NAME * self_ptr); \
    BinaryTree##TYPE_NAME##NodeInfo (* const get_node) (CompleteBinaryTree##TYPE_NAME * self_ptr, size_t cur_idx); \
    BinaryTree##TYPE_NAME##NodeInfo (* const left_child) (CompleteBinaryTree##TYPE_NAME * self_ptr, size_t cur_idx); \
    BinaryTree##TYPE_NAME##NodeInfo (* const right_child) (CompleteBinaryTree##TYPE_NAME * self_ptr, size_t cur_idx); \
}; \
\
CompleteBinaryTree##TYPE_NAME * CreateCompleteBinaryTree##TYPE_NAME(); \
void    DestroyCompleteBinaryTree##TYPE_NAME(CompleteBinaryTree##TYPE_NAME * self_ptr); \
\
size_t     CompleteBinaryTree##TYPE_NAME##Size (CompleteBinaryTree##TYPE_NAME * self_ptr); \
size_t     CompleteBinaryTree##TYPE_NAME##MaxDepth (CompleteBinaryTree##TYPE_NAME * self_ptr); \
void    CompleteBinaryTree##TYPE_NAME##Insert (CompleteBinaryTree##TYPE_NAME * self_ptr, TYPE item); \
TYPE     CompleteBinaryTree##TYPE_NAME##Remove (CompleteBinaryTree##TYPE_NAME * self_ptr); \
\
BinaryTree##TYPE_NAME##NodeInfo CompleteBinaryTree##TYPE_NAME##GetNode (CompleteBinaryTree##TYPE_NAME * self_ptr, size_t cur_idx); \
BinaryTree##TYPE_NAME##NodeInfo CompleteBinaryTree##TYPE_NAME##LeftChild (CompleteBinaryTree##TYPE_NAME * self_ptr, size_t cur_idx); \
BinaryTree##TYPE_NAME##NodeInfo CompleteBinaryTree##TYPE_NAME##RightChild (CompleteBinaryTree##TYPE_NAME * self_ptr, size_t cur_idx); \
\
void CompleteBinaryTree##TYPE_NAME##BFS(const CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t cur_node, void * user_data); \
void CompleteBinaryTree##TYPE_NAME##StackDFSPreorder(const CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t cur_node, void * user_data); \
void CompleteBinaryTree##TYPE_NAME##StackDFSInorder(const CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t cur_node, void * user_data); \
void CompleteBinaryTree##TYPE_NAME##StackDFSPostorder(const CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t cur_node, void * user_data); \
\
void CompleteBinaryTree##TYPE_NAME##RecurseDFSPreorder(const CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t cur_node, void * user_data); \
void CompleteBinaryTree##TYPE_NAME##RecurseDFSInorder(const CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t cur_node, void * user_data); \
void CompleteBinaryTree##TYPE_NAME##RecurseDFSPostorder(const CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t cur_node, void * user_data); \
\
void CompleteBinaryTree##TYPE_NAME##SwapNode(CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t a_node, size_t b_node); \
\
typedef void (*TreeNodeCallback)(const void* node_data, void* user_data); \
\
void GenericTreeLevelOrder(const void * const tree_ptr, void * user_data); \
void GenericTreeBFS(const void * const tree_ptr, void * user_data); \
void GenericTreeDFS(const void * const tree_ptr, TreeNodeCallback order_callback, void * user_data); \

#define IMPLEMENT_COMPLETE_BINARYTREE_TYPE(TYPE, TYPE_NAME) \
static const CompleteBinaryTree##TYPE_NAME DEFAULT_COMPLETE_BINARYTREE_##TYPE_NAME##_VTABLE_TEMPLATE = { \
    .m_container = NULL, \
    .m_size = 0, \
    .m_root = 0, \
    .m_head_idx = 0, \
    .size = CompleteBinaryTree##TYPE_NAME##Size, \
    .max_depth = CompleteBinaryTree##TYPE_NAME##MaxDepth, \
    .get_node = CompleteBinaryTree##TYPE_NAME##GetNode, \
    .left_child = CompleteBinaryTree##TYPE_NAME##LeftChild, \
    .right_child = CompleteBinaryTree##TYPE_NAME##RightChild, \
    .insert = CompleteBinaryTree##TYPE_NAME##Insert, \
    .remove = CompleteBinaryTree##TYPE_NAME##Remove \
}; \
\
static const BinaryTree##TYPE_NAME##NodeInfo WRONG_BINARYTREE_##TYPE_NAME##_NODE_OUT = { \
    .m_idx = 0, \
    .m_data = 0, \
}; \
\
CompleteBinaryTree##TYPE_NAME * CreateCompleteBinaryTree##TYPE_NAME() \
{ \
    CompleteBinaryTree##TYPE_NAME * temp_complete_tree = malloc(sizeof(CompleteBinaryTree##TYPE_NAME)); \
    if(temp_complete_tree == NULL) { \
        perror("tree allocate failed\n"); \
        abort(); \
    } \
    memcpy(temp_complete_tree, &DEFAULT_COMPLETE_BINARYTREE_##TYPE_NAME##_VTABLE_TEMPLATE, sizeof(CompleteBinaryTree##TYPE_NAME)); \
    temp_complete_tree->m_container = CreateVector##TYPE_NAME##Default(); \
    if(temp_complete_tree->m_container == NULL) { \
        perror("vector allocate failed\n"); \
        abort(); \
    } \
    return temp_complete_tree; \
} \
\
void    DestroyCompleteBinaryTree##TYPE_NAME(CompleteBinaryTree##TYPE_NAME * self_ptr) \
{ \
    if(self_ptr == NULL || self_ptr->m_container == NULL) { \
        perror("prevent double free\n"); \
        return; \
    } \
    if(self_ptr->m_container != NULL) { \
        DestroyVector##TYPE_NAME(self_ptr->m_container); \
        self_ptr->m_container = NULL; \
    } \
    if(self_ptr != NULL) { \
        free(self_ptr); \
        self_ptr = NULL; \
    } \
    return; \
} \
\
size_t     CompleteBinaryTree##TYPE_NAME##Size (CompleteBinaryTree##TYPE_NAME * self_ptr) \
{ \
    return self_ptr->m_size; \
} \
\
size_t     CompleteBinaryTree##TYPE_NAME##MaxDepth (CompleteBinaryTree##TYPE_NAME * self_ptr) \
{ \
    int res = 0; int fulls = 1; \
    while(fulls < self_ptr->m_size) { \
        res++; \
        fulls <<= res; \
    } \
    return res; \
} \
\
static void InsertFirst##TYPE_NAME##Item(CompleteBinaryTree##TYPE_NAME * self_ptr, TYPE item) { \
    if(self_ptr == NULL) { \
        perror("CompleteBinaryTree is NULL\n"); \
        abort(); \
    } \
    self_ptr->m_root = 1; \
    Vector##TYPE_NAME * container = self_ptr->m_container; \
    if(container->is_empty(container)) { \
        container->push_back(container, item); \
    } \
    self_ptr->m_size++; \
    self_ptr->m_head_idx = 1; \
} \
\
void    CompleteBinaryTree##TYPE_NAME##Insert (CompleteBinaryTree##TYPE_NAME * self_ptr, TYPE item) \
{ \
    if(self_ptr == NULL) { \
        perror("CompleteBinaryTree is NULL\n"); \
        abort(); \
    } \
    if(self_ptr->m_size == 0) {InsertFirst##TYPE_NAME##Item(self_ptr, item); return;} \
    Vector##TYPE_NAME * container = self_ptr->m_container; \
    container->push_back(container, item); \
    self_ptr->m_size = container->size(container); \
    return; \
} \
\
static TYPE RemoveFinal##TYPE_NAME##Item(CompleteBinaryTree##TYPE_NAME * self_ptr) { \
    if(self_ptr == NULL) { \
        perror("CompleteBinaryTree is NULL\n"); \
        abort(); \
    } \
    if(self_ptr->m_size != 1) { \
        perror("Not Last Item"); \
        abort(); \
    } \
    size_t last_idx = self_ptr->m_size - 1; \
    self_ptr->m_root = 0; \
    Vector##TYPE_NAME * container = self_ptr->m_container; \
    TYPE res = container->remove_with_index(container, last_idx); \
    self_ptr->m_size = 0; \
    self_ptr->m_head_idx = 0; \
    return res; \
} \
\
TYPE     CompleteBinaryTree##TYPE_NAME##Remove (CompleteBinaryTree##TYPE_NAME * self_ptr) \
{ \
    if(self_ptr == NULL) { \
        perror("CompleteBinaryTree is NULL\n"); \
        abort(); \
    } \
    if(self_ptr->m_size == 1) {return RemoveFinal##TYPE_NAME##Item(self_ptr);} \
    Vector##TYPE_NAME * container = self_ptr->m_container; \
	TYPE res = container->remove_with_index(container, self_ptr->m_size - 1); \
    self_ptr->m_size = container->size(container); \
    return res; \
} \
\
BinaryTree##TYPE_NAME##NodeInfo CompleteBinaryTree##TYPE_NAME##GetNode (CompleteBinaryTree##TYPE_NAME * self_ptr, size_t cur_idx) { \
    if(cur_idx <= 0 || self_ptr->m_size < cur_idx) \
        return WRONG_BINARYTREE_##TYPE_NAME##_NODE_OUT; \
	TYPE cur_data = *self_ptr->m_container->at(self_ptr->m_container, cur_idx - 1); \
    return (BinaryTree##TYPE_NAME##NodeInfo) { .m_idx = cur_idx, .m_data = cur_data }; \
} \
\
BinaryTree##TYPE_NAME##NodeInfo CompleteBinaryTree##TYPE_NAME##LeftChild (CompleteBinaryTree##TYPE_NAME * self_ptr, size_t cur_idx) { \
    return self_ptr->get_node(self_ptr, cur_idx * 2); \
} \
\
BinaryTree##TYPE_NAME##NodeInfo CompleteBinaryTree##TYPE_NAME##RightChild (CompleteBinaryTree##TYPE_NAME * self_ptr, size_t cur_idx) { \
    return self_ptr->get_node(self_ptr, cur_idx * 2 + 1); \
} \
\
void CompleteBinaryTree##TYPE_NAME##BFS(const CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t cur_node, void * user_data) \
{ \
    if(self_ptr == NULL) { \
        perror("tree ptr NULL error \n"); \
        abort(); \
    } \
\
    if(!(0 < cur_node  && cur_node < self_ptr->m_size)) { \
        perror("invalid node error \n"); \
        abort(); \
    } \
\
    CircularQueue##TYPE_NAME *  queue_ptr = CreateCircularQueue##TYPE_NAME(self_ptr->m_size); \
    if(queue_ptr == NULL) { \
        perror("queue alloc failed\n"); \
        abort(); \
    } \
\
    Vector##TYPE_NAME * is_visit_ptr = CreateVector##TYPE_NAME(self_ptr->m_size); \
    if(is_visit_ptr == NULL) { \
        perror("vector alloc failed\n"); \
        abort(); \
    } \
\
    CompleteBinaryTree##TYPE_NAME* tree_access_ptr = (CompleteBinaryTree##TYPE_NAME*)self_ptr; \
\
	BinaryTree##TYPE_NAME##TravelInfo * search_data = (BinaryTree##TYPE_NAME##TravelInfo*) user_data; \
\
    queue_ptr->enqueue(queue_ptr, cur_node); \
\
    while(!queue_ptr->is_empty(queue_ptr)) { \
        int cur_idx = queue_ptr->dequeue(queue_ptr); \
\
		if(*is_visit_ptr->at(is_visit_ptr, cur_idx) != 0) \
            continue; \
\
        *(is_visit_ptr->at(is_visit_ptr, cur_idx)) = true; \
\
        BinaryTree##TYPE_NAME##NodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_idx); \
\
        search_data->callback(search_data, node_info.m_data); \
\
        BinaryTree##TYPE_NAME##NodeInfo nxt_left_child = self_ptr->left_child(tree_access_ptr, cur_idx); \
        if(nxt_left_child.m_idx != 0) \
            queue_ptr->enqueue(queue_ptr, nxt_left_child.m_idx); \
\
        BinaryTree##TYPE_NAME##NodeInfo nxt_right_child = self_ptr->right_child(tree_access_ptr, cur_idx); \
        if(nxt_right_child.m_idx != 0) \
            queue_ptr->enqueue(queue_ptr, nxt_right_child.m_idx); \
    } \
\
    DestroyCircularQueue##TYPE_NAME(queue_ptr); \
    DestroyVector##TYPE_NAME(is_visit_ptr); \
} \
\
void CompleteBinaryTree##TYPE_NAME##StackDFSPreorder(const CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t cur_node, void * user_data) { \
    if(self_ptr == NULL) { \
        perror("tree ptr NULL error\n"); \
        abort(); \
    } \
\
    if(!(0 < cur_node && cur_node < self_ptr->m_size)) { \
        perror("invalid node error \n"); \
        abort(); \
    } \
\
    Stack##TYPE_NAME * stack_ptr = CreateStack##TYPE_NAME(self_ptr->m_size); \
    if(stack_ptr == NULL) { \
        perror("stack alloc failed\n"); \
        abort(); \
    } \
\
    Vector##TYPE_NAME * is_visit_ptr = CreateVector##TYPE_NAME(self_ptr->m_size); \
    if(is_visit_ptr == NULL) { \
        perror("vector alloc failed\n"); \
        abort(); \
    } \
\
    if(self_ptr->m_size == 0) { \
        perror("tree empty\n"); \
        return; \
    } \
\
 \
    BinaryTree##TYPE_NAME##TravelInfo * search_data = (BinaryTree##TYPE_NAME##TravelInfo*) user_data; \
\
    CompleteBinaryTree##TYPE_NAME* tree_access_ptr = (CompleteBinaryTree##TYPE_NAME*) self_ptr; \
\
    stack_ptr->push(stack_ptr, cur_node); \
    int cur_idx, nxt_idx; \
\
    while(!stack_ptr->is_empty(stack_ptr)) { \
        int cur_idx = stack_ptr->pop(stack_ptr); \
        if(*is_visit_ptr->at(is_visit_ptr, cur_idx) != 0) continue; \
        *(is_visit_ptr->at(is_visit_ptr, cur_idx)) = true; \
\
        BinaryTree##TYPE_NAME##NodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_idx); \
\
        search_data->callback(search_data, node_info.m_data); \
\
        BinaryTree##TYPE_NAME##NodeInfo nxt_right_child = self_ptr->right_child(tree_access_ptr, cur_idx); \
\
        if(nxt_right_child.m_idx != 0) \
            stack_ptr->push(stack_ptr, nxt_right_child.m_idx); \
\
        BinaryTree##TYPE_NAME##NodeInfo nxt_left_child = self_ptr->left_child(tree_access_ptr, cur_idx); \
\
        if(nxt_left_child.m_idx != 0) \
            stack_ptr->push(stack_ptr, nxt_left_child.m_idx); \
\
    } \
\
    DestroyStack##TYPE_NAME(stack_ptr); \
    DestroyVector##TYPE_NAME(is_visit_ptr); \
} \
\
void CompleteBinaryTree##TYPE_NAME##StackDFSInorder(const CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t cur_node, void * user_data) { \
    if(self_ptr == NULL) { \
        perror("tree ptr NULL error\n"); \
        abort(); \
    } \
\
    if(!(0 < cur_node  && cur_node < self_ptr->m_size)) { \
        perror("invalid node error \n"); \
        abort(); \
    } \
\
    Stack##TYPE_NAME * stack_ptr = CreateStack##TYPE_NAME(self_ptr->m_size); \
    if(stack_ptr == NULL) { \
        perror("stack alloc failed\n"); \
        abort(); \
    } \
\
    Vector##TYPE_NAME * is_visit_ptr = CreateVector##TYPE_NAME(self_ptr->m_size); \
    if(is_visit_ptr == NULL) { \
        perror("vector alloc failed\n"); \
        abort(); \
    } \
\
    if(self_ptr->m_size == 0) { \
        perror("tree empty\n"); \
        return; \
    } \
\
 \
    BinaryTree##TYPE_NAME##TravelInfo * search_data = (BinaryTree##TYPE_NAME##TravelInfo*) user_data; \
\
    CompleteBinaryTree##TYPE_NAME* tree_access_ptr = (CompleteBinaryTree##TYPE_NAME*) self_ptr; \
    stack_ptr->push(stack_ptr, cur_node); \
    int cur_idx, nxt_idx; \
\
    while(!stack_ptr->is_empty(stack_ptr)) { \
\
        cur_idx = stack_ptr->top(stack_ptr); \
        nxt_idx = self_ptr->left_child(tree_access_ptr, cur_idx).m_idx; \
        if(nxt_idx != 0 && *is_visit_ptr->at(is_visit_ptr, nxt_idx) == 0) { \
            while(nxt_idx != 0) { \
                if(*is_visit_ptr->at(is_visit_ptr, nxt_idx) != 0) break; \
                stack_ptr->push(stack_ptr, nxt_idx); \
                nxt_idx = self_ptr->left_child(tree_access_ptr, nxt_idx).m_idx; \
            } \
        } \
\
        int end_idx = stack_ptr->pop(stack_ptr); \
        if(*is_visit_ptr->at(is_visit_ptr,end_idx) == 0) { \
            *(is_visit_ptr->at(is_visit_ptr, end_idx)) = true; \
            BinaryTree##TYPE_NAME##NodeInfo node_info = self_ptr->get_node(tree_access_ptr, end_idx); \
\
            search_data->callback(search_data, node_info.m_data); \
        } \
\
        nxt_idx = self_ptr->right_child(tree_access_ptr, end_idx).m_idx; \
        BinaryTree##TYPE_NAME##NodeInfo nxt_item = self_ptr->get_node(tree_access_ptr, nxt_idx); \
        if(nxt_idx != 0 && *is_visit_ptr->at(is_visit_ptr, nxt_idx) == 0) { \
            stack_ptr->push(stack_ptr, nxt_idx); \
        } \
    } \
    DestroyStack##TYPE_NAME(stack_ptr); \
    DestroyVector##TYPE_NAME(is_visit_ptr); \
} \
\
void CompleteBinaryTree##TYPE_NAME##StackDFSPostorder(const CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t cur_node, void * user_data) { \
    if(self_ptr == NULL) { \
        perror("tree ptr NULL error\n"); \
        abort(); \
    } \
\
    if(!(0 < cur_node  && cur_node < self_ptr->m_size)) { \
        perror("invalid node error \n"); \
        abort(); \
    } \
\
    Stack##TYPE_NAME * stack_ptr = CreateStack##TYPE_NAME(self_ptr->m_size); \
    if(stack_ptr == NULL) { \
        perror("stack alloc failed\n"); \
        abort(); \
    } \
\
    Vector##TYPE_NAME * is_visit_ptr = CreateVector##TYPE_NAME(self_ptr->m_size); \
    if(is_visit_ptr == NULL) { \
        perror("vector alloc failed\n"); \
        abort(); \
    } \
\
    if(self_ptr->m_size == 0) { \
        perror("tree empty\n"); \
        return; \
    } \
\
 \
    BinaryTree##TYPE_NAME##TravelInfo * search_data = (BinaryTree##TYPE_NAME##TravelInfo*) user_data; \
\
    CompleteBinaryTree##TYPE_NAME* tree_access_ptr = (CompleteBinaryTree##TYPE_NAME*) self_ptr; \
    stack_ptr->push(stack_ptr, cur_node); \
    int cur_idx, nxt_idx; \
\
    while(!stack_ptr->is_empty(stack_ptr)) { \
\
        cur_idx = stack_ptr->top(stack_ptr); \
        nxt_idx = self_ptr->left_child(tree_access_ptr, cur_idx).m_idx; \
        if(nxt_idx != 0 && *is_visit_ptr->at(is_visit_ptr, nxt_idx) == 0) { \
            while(nxt_idx != 0) { \
                if(*is_visit_ptr->at(is_visit_ptr, nxt_idx) != 0) break; \
                stack_ptr->push(stack_ptr, nxt_idx); \
                nxt_idx = self_ptr->left_child(tree_access_ptr, nxt_idx).m_idx; \
            } \
        } \
\
        int end_idx = stack_ptr->pop(stack_ptr); \
        if(*is_visit_ptr->at(is_visit_ptr,end_idx) == 0) { \
            *(is_visit_ptr->at(is_visit_ptr, end_idx)) = true; \
            BinaryTree##TYPE_NAME##NodeInfo node_info = self_ptr->get_node(tree_access_ptr, end_idx); \
\
			search_data->callback(search_data, node_info.m_data); \
        } \
\
        if(!stack_ptr->is_empty(stack_ptr)) { \
            int nxt_idx = self_ptr->right_child(tree_access_ptr, stack_ptr->top(stack_ptr)).m_idx; \
            BinaryTree##TYPE_NAME##NodeInfo nxt_item = self_ptr->get_node(tree_access_ptr, nxt_idx); \
            if(nxt_idx != 0 && *is_visit_ptr->at(is_visit_ptr, nxt_idx) == 0) { \
                stack_ptr->push(stack_ptr, nxt_idx); \
            } \
        } \
    } \
    DestroyStack##TYPE_NAME(stack_ptr); \
    DestroyVector##TYPE_NAME(is_visit_ptr); \
} \
\
void CompleteBinaryTree##TYPE_NAME##RecurseDFSPreorder(const CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t cur_node, void * user_data) { \
\
    if(self_ptr == NULL) { \
        perror("tree ptr NULL error\n"); \
        abort(); \
    } \
\
    if(!(0 < cur_node  && cur_node <= self_ptr->m_size)) { \
        if(cur_node == 0) return; \
        perror("invalid node error \n"); \
        abort(); \
    } \
\
    if(self_ptr->m_size == 0) { \
        perror("tree empty\n"); \
        return; \
    } \
\
    CompleteBinaryTree##TYPE_NAME* tree_access_ptr = (CompleteBinaryTree##TYPE_NAME*) self_ptr; \
\
 \
    BinaryTree##TYPE_NAME##TravelInfo * search_data = (BinaryTree##TYPE_NAME##TravelInfo*) user_data; \
\
    BinaryTree##TYPE_NAME##NodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_node); \
    search_data->callback(search_data, node_info.m_data); \
    CompleteBinaryTree##TYPE_NAME##RecurseDFSPreorder(self_ptr, self_ptr->left_child(tree_access_ptr, cur_node).m_idx, search_data); \
    CompleteBinaryTree##TYPE_NAME##RecurseDFSPreorder(self_ptr, self_ptr->right_child(tree_access_ptr, cur_node).m_idx, search_data); \
} \
\
void CompleteBinaryTree##TYPE_NAME##RecurseDFSInorder(const CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t cur_node, void * user_data) { \
\
    if(self_ptr == NULL) { \
        perror("tree ptr NULL error\n"); \
        abort(); \
    } \
\
    if(!(0 < cur_node  && cur_node <= self_ptr->m_size)) { \
        if(cur_node == 0) return; \
        perror("invalid node error \n"); \
        abort(); \
    } \
\
    if(self_ptr->m_size == 0) { \
        perror("tree empty\n"); \
        return; \
    } \
\
    CompleteBinaryTree##TYPE_NAME* tree_access_ptr = (CompleteBinaryTree##TYPE_NAME*) self_ptr; \
\
    BinaryTree##TYPE_NAME##TravelInfo * search_data = (BinaryTree##TYPE_NAME##TravelInfo*) user_data; \
\
    CompleteBinaryTree##TYPE_NAME##RecurseDFSInorder(self_ptr, self_ptr->left_child(tree_access_ptr, cur_node).m_idx , search_data); \
    BinaryTree##TYPE_NAME##NodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_node); \
    search_data->callback(search_data, node_info.m_data); \
    CompleteBinaryTree##TYPE_NAME##RecurseDFSInorder(self_ptr, self_ptr->right_child(tree_access_ptr, cur_node).m_idx, search_data); \
} \
\
void CompleteBinaryTree##TYPE_NAME##RecurseDFSPostorder(const CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t cur_node, void * user_data) { \
\
    if(self_ptr == NULL) { \
        perror("tree ptr NULL error\n"); \
        abort(); \
    } \
\
    if(!(0 < cur_node  && cur_node <= self_ptr->m_size)) { \
        if(cur_node == 0) return; \
        perror("invalid node error \n"); \
        abort(); \
    } \
\
    if(self_ptr->m_size == 0) { \
        perror("tree empty\n"); \
        return; \
    } \
\
    CompleteBinaryTree##TYPE_NAME* tree_access_ptr = (CompleteBinaryTree##TYPE_NAME*) self_ptr; \
\
 \
    BinaryTree##TYPE_NAME##TravelInfo * search_data = (BinaryTree##TYPE_NAME##TravelInfo*) user_data; \
\
    CompleteBinaryTree##TYPE_NAME##RecurseDFSPostorder(self_ptr, self_ptr->left_child(tree_access_ptr, cur_node).m_idx, search_data); \
    CompleteBinaryTree##TYPE_NAME##RecurseDFSPostorder(self_ptr, self_ptr->right_child(tree_access_ptr, cur_node).m_idx, search_data); \
    BinaryTree##TYPE_NAME##NodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_node); \
    search_data->callback(search_data, node_info.m_data); \
\
} \
\
void CompleteBinaryTree##TYPE_NAME##SwapNode(CompleteBinaryTree##TYPE_NAME * const self_ptr, size_t a_node, size_t b_node) { \
        if(self_ptr == NULL) { \
        perror("tree ptr NULL error\n"); \
        abort(); \
    } \
\
    if(self_ptr->m_size == 0) { \
        perror("tree empty\n"); \
        return; \
    } \
    BinaryTree##TYPE_NAME##NodeInfo a_node_info = self_ptr->get_node(self_ptr, a_node); \
    BinaryTree##TYPE_NAME##NodeInfo b_node_info = self_ptr->get_node(self_ptr, b_node); \
    *(self_ptr->m_container->at(self_ptr->m_container, a_node-1)) = b_node_info.m_data; \
    *(self_ptr->m_container->at(self_ptr->m_container, b_node-1)) = a_node_info.m_data; \
} \

DEFINE_COMPLETE_BINARYTREE_TYPE(int, Int);
DEFINE_COMPLETE_BINARYTREE_TYPE(float, Float)
DEFINE_COMPLETE_BINARYTREE_TYPE(double, Double)
DEFINE_COMPLETE_BINARYTREE_TYPE(long long, LongLong)
DEFINE_COMPLETE_BINARYTREE_TYPE(char, Char)
DEFINE_COMPLETE_BINARYTREE_TYPE(short, Short)


#endif//#define __HEADER_GUARD_COMPLETE_BINARY_TREE__
