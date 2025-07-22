#ifndef __HEADER_GUARD_COMPLETE_BINARY_TREE__
#define __HEADER_GUARD_COMPLETE_BINARY_TREE__

#include <stdbool.h>
#include "sjhdatatype.h"
#include "vector_primitive.h"
#include "circular_queue_primitive.h"
#include "stack_primitive.h"
#include "tree.h"


typedef struct CompleteBinaryTree__TYPE_NAME__ CompleteBinaryTree__TYPE_NAME__;
typedef VectorInt Vector__TYPE_NAME__;
typedef CircularQueueInt CircularQueue__TYPE_NAME__;
typedef StackInt Stack__TYPE_NAME__;
typedef int __TYPE__;
DEFINE_TREE_TYPE(__TYPE__, __TYPE_NAME___SPSP_);

struct CompleteBinaryTree__TYPE_NAME__ {
    Vector__TYPE_NAME__ * m_container;
    size_t m_size;
    size_t m_root;

    size_t m_head_idx;   // 재귀로 돌리기 위해 사용됨

    size_t (* const size) (CompleteBinaryTree__TYPE_NAME__ * self_ptr);
    size_t (* const max_depth) (CompleteBinaryTree__TYPE_NAME__ * self_ptr);
    void     (* const insert) (CompleteBinaryTree__TYPE_NAME__ * self_ptr, __TYPE__ item);
    __TYPE__      (* const remove) (CompleteBinaryTree__TYPE_NAME__ * self_ptr);
    BinaryTree__TYPE_NAME___SPSP_NodeInfo (* const get_node) (CompleteBinaryTree__TYPE_NAME__ * self_ptr, size_t cur_idx);
    BinaryTree__TYPE_NAME___SPSP_NodeInfo (* const left_child) (CompleteBinaryTree__TYPE_NAME__ * self_ptr, size_t cur_idx);
    BinaryTree__TYPE_NAME___SPSP_NodeInfo (* const right_child) (CompleteBinaryTree__TYPE_NAME__ * self_ptr, size_t cur_idx);
};

CompleteBinaryTree__TYPE_NAME__ * CreateCompleteBinaryTree__TYPE_NAME__();
void    DestroyCompleteBinaryTree__TYPE_NAME__(CompleteBinaryTree__TYPE_NAME__ * self_ptr);

size_t     CompleteBinaryTree__TYPE_NAME___SPSP_Size (CompleteBinaryTree__TYPE_NAME__ * self_ptr);
size_t     CompleteBinaryTree__TYPE_NAME___SPSP_MaxDepth (CompleteBinaryTree__TYPE_NAME__ * self_ptr);
void    CompleteBinaryTree__TYPE_NAME___SPSP_Insert (CompleteBinaryTree__TYPE_NAME__ * self_ptr, __TYPE__ item);
__TYPE__     CompleteBinaryTree__TYPE_NAME___SPSP_Remove (CompleteBinaryTree__TYPE_NAME__ * self_ptr);

BinaryTree__TYPE_NAME___SPSP_NodeInfo CompleteBinaryTree__TYPE_NAME___SPSP_GetNode (CompleteBinaryTree__TYPE_NAME__ * self_ptr, size_t cur_idx);
BinaryTree__TYPE_NAME___SPSP_NodeInfo CompleteBinaryTree__TYPE_NAME___SPSP_LeftChild (CompleteBinaryTree__TYPE_NAME__ * self_ptr, size_t cur_idx);
BinaryTree__TYPE_NAME___SPSP_NodeInfo CompleteBinaryTree__TYPE_NAME___SPSP_RightChild (CompleteBinaryTree__TYPE_NAME__ * self_ptr, size_t cur_idx);


void CompleteBinaryTree__TYPE_NAME___SPSP_BFS(const CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t cur_node, void * user_data);
void CompleteBinaryTree__TYPE_NAME___SPSP_StackDFSPreorder(const CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t cur_node, void * user_data);
void CompleteBinaryTree__TYPE_NAME___SPSP_StackDFSInorder(const CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t cur_node, void * user_data);
void CompleteBinaryTree__TYPE_NAME___SPSP_StackDFSPostorder(const CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t cur_node, void * user_data);

void CompleteBinaryTree__TYPE_NAME___SPSP_RecurseDFSPreorder(const CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t cur_node, void * user_data);
void CompleteBinaryTree__TYPE_NAME___SPSP_RecurseDFSInorder(const CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t cur_node, void * user_data);
void CompleteBinaryTree__TYPE_NAME___SPSP_RecurseDFSPostorder(const CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t cur_node, void * user_data);

void CompleteBinaryTree__TYPE_NAME___SPSP_SwapNode(CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t a_node, size_t b_node);

typedef void (*TreeNodeCallback)(const void* node_data, void* user_data);

// Dequeue를 사용해 구현할 수 있다.
void GenericTreeLevelOrder(const void * const tree_ptr, void * user_data);
void GenericTreeBFS(const void * const tree_ptr, void * user_data);
void GenericTreeDFS(const void * const tree_ptr, TreeNodeCallback order_callback, void * user_data);

#endif//#define __HEADER_GUARD_COMPLETE_BINARY_TREE__
