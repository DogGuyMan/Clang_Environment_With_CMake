#ifndef __HEADER_GUARD_AVL_TREE__
#define __HEADER_GUARD_AVL_TREE__

#include <stdbool.h>
#include <stdlib.h>
#include "sjhaddresstype.h"
#include "binarysearchtree.h"

typedef struct AVLTree__TYPE_NAME__ AVLTree__TYPE_NAME__;

struct AVLTree__TYPE_NAME__ {
	BinarySearchTree__TYPE_NAME__ * m_bst;
	E_BST_ORDER m_bst_order;

	size_t 	(*const size)(AVLTree__TYPE_NAME__ *self_ptr);
	size_t 	(*const max_depth)(AVLTree__TYPE_NAME__ *self_ptr);
	void 	(*const insert_item)(AVLTree__TYPE_NAME__ *self_ptr, __TYPE__ item);
	bool 	(*const find)(AVLTree__TYPE_NAME__ *self_ptr, __TYPE__ item);
	void 	(*const remove_item)(AVLTree__TYPE_NAME__ *self_ptr, __TYPE__ item);
};

AVLTree__TYPE_NAME__ *	CreateAVLTree__TYPE_NAME__(E_BST_ORDER, __TYPE__);
void 					DestroyAVLTree__TYPE_NAME__(AVLTree__TYPE_NAME__ *);

size_t 	AVLTree__TYPE_NAME___SPSP_Size(AVLTree__TYPE_NAME__ *self_ptr);
size_t 	AVLTree__TYPE_NAME___SPSP_MaxDepth(AVLTree__TYPE_NAME__ *self_ptr);
void 	AVLTree__TYPE_NAME___SPSP_InsertItem(AVLTree__TYPE_NAME__ *self_ptr, __TYPE__ item);
bool 	AVLTree__TYPE_NAME___SPSP_Find(AVLTree__TYPE_NAME__ *self_ptr, __TYPE__ item);
void 	AVLTree__TYPE_NAME___SPSP_RemoveItem(AVLTree__TYPE_NAME__ *self_ptr, __TYPE__ item);

BinaryTree__TYPE_NAME__ * AVLTree__TYPE_NAME___SPSP_BalanceLL(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * A, BinaryTree__TYPE_NAME__ * B, BinaryTree__TYPE_NAME__ * C);
BinaryTree__TYPE_NAME__ * AVLTree__TYPE_NAME___SPSP_BalanceRR(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * A, BinaryTree__TYPE_NAME__ * B, BinaryTree__TYPE_NAME__ * C);
BinaryTree__TYPE_NAME__ * AVLTree__TYPE_NAME___SPSP_BalanceLR(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * A, BinaryTree__TYPE_NAME__ * B, BinaryTree__TYPE_NAME__ * C);
BinaryTree__TYPE_NAME__ * AVLTree__TYPE_NAME___SPSP_BalanceRL(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * A, BinaryTree__TYPE_NAME__ * B, BinaryTree__TYPE_NAME__ * C);

#endif//__HEADER_GUARD_AVL_TREE__
