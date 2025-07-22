#ifndef __HEADER_GUARD_BINARYSEARCH_TREE__
#define __HEADER_GUARD_BINARYSEARCH_TREE__

#include <stdbool.h>
#include <stdlib.h>
#include "vector_primitive.h"
#include "binarytree.h"

typedef struct BinarySearchTree__TYPE_NAME__ BinarySearchTree__TYPE_NAME__;
typedef struct BinarySearchTree__TYPE_NAME___SPSP_FoundInfo BinarySearchTree__TYPE_NAME___SPSP_FoundInfo;
typedef int __TYPE__;

typedef enum {
	LESS = 0,
	GREATER = 1
} E_BST_ORDER;

struct BinarySearchTree__TYPE_NAME___SPSP_FoundInfo {
	BinaryTree__TYPE_NAME__ * found_bitree_ptr;
	int tree_order;
};

struct BinarySearchTree__TYPE_NAME__
{
	BinaryTree__TYPE_NAME__ 	* m_bt;
	E_BST_ORDER 				m_bst_order;

    size_t        					( * const size)				(BinarySearchTree__TYPE_NAME__ * self_ptr);
    size_t        					( * const max_depth)		(BinarySearchTree__TYPE_NAME__ * self_ptr);
    void 							( * const insert_item) 		(BinarySearchTree__TYPE_NAME__ * self_ptr, __TYPE__ item);
	bool 							( * const find)				(BinarySearchTree__TYPE_NAME__ * self_ptr, __TYPE__ item);
    BinarySearchTree__TYPE_NAME__ *	( * const remove_item) 		(BinarySearchTree__TYPE_NAME__ * self_ptr, __TYPE__ item);
	int 							( * compare )				(__TYPE__ lhs, __TYPE__ rhs);
};

BinarySearchTree__TYPE_NAME__ * 	CreateBinarySearchTree__TYPE_NAME__				(__TYPE__, E_BST_ORDER);
void                        		DestroyBinarySearchTree__TYPE_NAME__			(BinarySearchTree__TYPE_NAME__ * self_ptr);

size_t        						BinarySearchTree__TYPE_NAME___SPSP_Size			(BinarySearchTree__TYPE_NAME__ * self_ptr);
size_t        						BinarySearchTree__TYPE_NAME___SPSP_MaxDepth		(BinarySearchTree__TYPE_NAME__ * self_ptr);
void   								BinarySearchTree__TYPE_NAME___SPSP_InsertItem	(BinarySearchTree__TYPE_NAME__ * self_ptr, __TYPE__ item);
bool 								BinarySearchTree__TYPE_NAME___SPSP_Find			(BinarySearchTree__TYPE_NAME__ * self_ptr, __TYPE__ item);
BinarySearchTree__TYPE_NAME__ * 	BinarySearchTree__TYPE_NAME___SPSP_RemoveItem	(BinarySearchTree__TYPE_NAME__ * self_ptr, __TYPE__ item);

#endif//__HEADER_GUARD_BINARYSEARCH_TREE__
