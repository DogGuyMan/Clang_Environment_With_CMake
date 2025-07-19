#ifndef __HEADER_GUARD_TREE__
#define __HEADER_GUARD_TREE__

#include <stdbool.h>
#include <stdlib.h>
#include "sjhdatatype.h"
#include "vector_primitive.h"

typedef enum {
    LEFT_INSERT_NODE    = -1,
    RIGHT_INSERT_NODE   = 1
} BinaryTreeInsertMode;


typedef struct BinaryTree__TYPE_NAME__ BinaryTree__TYPE_NAME__;
typedef int __TYPE__;

struct BinaryTree__TYPE_NAME__ {
    __TYPE__ m_data;
    size_t m_size;
	size_t m_max_depth;
    BinaryTree__TYPE_NAME__ * m_root;
    BinaryTree__TYPE_NAME__ * m_current;
	BinaryTree__TYPE_NAME__ * m_parent;
    BinaryTree__TYPE_NAME__ * m_left_child;
    BinaryTree__TYPE_NAME__ * m_right_child;

    size_t        				( * const size)					(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree);
    size_t        				( * const max_depth)			(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree);
    BinaryTree__TYPE_NAME__ * 	( * const left_child)			(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree);
    BinaryTree__TYPE_NAME__ * 	( * const right_child)			(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree);
    BinaryTree__TYPE_NAME__ *   ( * const insert)           	(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree, BinaryTreeInsertMode insert_mode, BinaryTree__TYPE_NAME__ * insert_tree);
	__TYPE__ 					( * const get)					(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_node);
    // __TYPE__ 				( * const remove)   			(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_node);
};

BinaryTree__TYPE_NAME__ *   CreateBinaryTree__TYPE_NAME__(__TYPE__);
void                        DestroyBinaryTree__TYPE_NAME__(BinaryTree__TYPE_NAME__ * self_ptr);

size_t        				BinaryTree__TYPE_NAME___SPSP_Size(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree);
size_t        				BinaryTree__TYPE_NAME___SPSP_MaxDepth(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree);
BinaryTree__TYPE_NAME__ *   BinaryTree__TYPE_NAME___SPSP_LeftChild(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree);
BinaryTree__TYPE_NAME__ *   BinaryTree__TYPE_NAME___SPSP_RightChild(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree);
BinaryTree__TYPE_NAME__ *   BinaryTree__TYPE_NAME___SPSP_Insert(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree, BinaryTreeInsertMode insert_mode, BinaryTree__TYPE_NAME__ * insert_tree);
__TYPE__ 					BinaryTree__TYPE_NAME___SPSP_Get(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_node);
// BinaryTree__TYPE_NAME__ *	BinaryTree__TYPE_NAME___SPSP_Remove(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_node, BinaryTree__TYPE_NAME__ * parent_tree);

void BinaryTree__TYPE_NAME___SPSP_BFS(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree, void * user_data);
void BinaryTree__TYPE_NAME___SPSP_LevelOrder(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree, void * user_data);
void BinaryTree__TYPE_NAME___SPSP_RecurseDFSPreorder(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree, void * user_data);
void BinaryTree__TYPE_NAME___SPSP_RecurseDFSInorder(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree, void * user_data);
void BinaryTree__TYPE_NAME___SPSP_RecurseDFSPostorder(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree, void * user_data);

#endif//__HEADER_GUARD_TREE__
