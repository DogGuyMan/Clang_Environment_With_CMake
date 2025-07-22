#include <errno.h>
#include <string.h>
#include "binarysearchtree.h"

const BinarySearchTree__TYPE_NAME__ DEFAULT_BST_TEMPLATE = {
	.m_bt 			= 	NULL,
	.m_bst_order	= 	LESS,
	.size 			=	BinarySearchTree__TYPE_NAME___SPSP_Size,
    .max_depth 		= 	BinarySearchTree__TYPE_NAME___SPSP_MaxDepth,
    .insert_item	= 	BinarySearchTree__TYPE_NAME___SPSP_InsertItem,
	.find 			= 	BinarySearchTree__TYPE_NAME___SPSP_Find,
    .remove_item	= 	BinarySearchTree__TYPE_NAME___SPSP_RemoveItem,
};

static int BinarySearchTree__TYPE_NAME___SPSP_LessCompare(__TYPE__ lhs, __TYPE__ rhs) {
	if(lhs == rhs) 	return 	0;
	if(lhs > rhs) 	return 	-1;
	if(lhs < rhs) 	return 	1;
}

static int BinarySearchTree__TYPE_NAME___SPSP_GreaterCompare(__TYPE__ lhs, __TYPE__ rhs) {
	if(lhs == rhs) 	return 	0;
	if(lhs > rhs) 	return 	1;
	if(lhs < rhs) 	return 	-1;
}

const BinarySearchTree__TYPE_NAME___SPSP_FoundInfo ERROR_PROPER_POSITION_INFO_TEMPLATE = {
	.found_bitree_ptr = NULL,
	.tree_order = 0
};

BinarySearchTree__TYPE_NAME__ * 	CreateBinarySearchTree__TYPE_NAME__				(E_BST_ORDER bst_order, __TYPE__ item) {
	BinarySearchTree__TYPE_NAME__ * temp_bst = (BinarySearchTree__TYPE_NAME__ * ) malloc(sizeof(BinarySearchTree__TYPE_NAME__));
	if(temp_bst == NULL) {
		perror("bst 메모리 할당 실패");
		abort();
	}
	memcpy(temp_bst, &DEFAULT_BST_TEMPLATE, sizeof(BinarySearchTree__TYPE_NAME__));
	BinaryTree__TYPE_NAME__ * temp_bitree = CreateBinaryTree__TYPE_NAME__(item);
	if(temp_bitree == NULL) {
		perror("binary tree 메모리 할당 실패");
		abort();
	}

	temp_bst->m_bt = temp_bitree;
	temp_bst->m_bst_order = bst_order;

	if(temp_bst->m_bst_order == LESS)
		temp_bst->compare = BinarySearchTree__TYPE_NAME___SPSP_LessCompare;
	else if (temp_bst->m_bst_order == GREATER)
		temp_bst->compare = BinarySearchTree__TYPE_NAME___SPSP_GreaterCompare;
	else {
		DestroyBinarySearchTree__TYPE_NAME__(temp_bst);
		abort();
	}

	return temp_bst;
}

void                        		DestroyBinarySearchTree__TYPE_NAME__			(BinarySearchTree__TYPE_NAME__ * self_ptr) {
	if(self_ptr == NULL || self_ptr->m_bt == NULL) {
		perror("BST 더블 프레 에러");
		return;
	}
	DestroyBinaryTree__TYPE_NAME__(self_ptr->m_bt->m_root);
	free(self_ptr);
}


size_t        						BinarySearchTree__TYPE_NAME___SPSP_Size			(BinarySearchTree__TYPE_NAME__ * self_ptr) {
	if(self_ptr == NULL || self_ptr->m_bt == NULL)
		return 0;
	return self_ptr->m_bt->m_size;
}

size_t        						BinarySearchTree__TYPE_NAME___SPSP_MaxDepth		(BinarySearchTree__TYPE_NAME__ * self_ptr) {
	if(self_ptr == NULL || self_ptr->m_bt == NULL)
		return 0;
	return self_ptr->m_bt->m_max_depth;
}

static BinarySearchTree__TYPE_NAME___SPSP_FoundInfo FindProperPosition(BinaryTree__TYPE_NAME__ * current_tree, __TYPE__ item, int (* compare) (__TYPE__ lhs, __TYPE__ rhs) ) {
	if(current_tree == NULL)
		return ERROR_PROPER_POSITION_INFO_TEMPLATE;
	__TYPE__ current_item = current_tree->get(current_tree->m_root, current_tree);
	if		(compare(current_item, item) == -1) {
		if(current_tree->m_left_child == NULL) {
			return (BinarySearchTree__TYPE_NAME___SPSP_FoundInfo) {.found_bitree_ptr = current_tree, .tree_order = LEFT_INSERT_NODE };
		}
		return FindProperPosition(current_tree->m_left_child, item, compare);
	}
	else if (compare(current_item, item) == 1) {
		if(current_tree->m_right_child == NULL) {
			return (BinarySearchTree__TYPE_NAME___SPSP_FoundInfo) {.found_bitree_ptr = current_tree, .tree_order = RIGHT_INSERT_NODE };
		}
		return FindProperPosition(current_tree->m_right_child, item, compare);
	}
	return (BinarySearchTree__TYPE_NAME___SPSP_FoundInfo) {.found_bitree_ptr = current_tree, .tree_order = 0 };
}

void   								BinarySearchTree__TYPE_NAME___SPSP_InsertItem	(BinarySearchTree__TYPE_NAME__ * self_ptr, __TYPE__ item) {
	if(self_ptr == NULL || self_ptr->m_bt == NULL) {
		perror("인풋이 널임\n");
		abort();
	}

	BinarySearchTree__TYPE_NAME___SPSP_FoundInfo ppinfo = FindProperPosition(self_ptr->m_bt, self_ptr->m_bst_order, item);
	if(ppinfo.found_bitree_ptr == NULL)
		return;

	E_BINARY_TREE_INSERT_MODE insert_mode = 0;
	if		(ppinfo.tree_order == -1)
		insert_mode = LEFT_INSERT_NODE;
	else if (ppinfo.tree_order == 1)
		insert_mode = RIGHT_INSERT_NODE;
	else
		return;

	BinaryTree__TYPE_NAME__ * new_tree = CreateBinaryTree__TYPE_NAME__(item);
	BinaryTree__TYPE_NAME__ * bitree_root = self_ptr->m_bt->m_root;
	bitree_root->insert(bitree_root, ppinfo.found_bitree_ptr, insert_mode, new_tree);
}

bool 	BinarySearchTree__TYPE_NAME___SPSP_Find			(BinarySearchTree__TYPE_NAME__ * self_ptr, __TYPE__ item) {
	if(self_ptr == NULL || self_ptr->m_bt == NULL) {
		perror("인풋이 널임\n");
		abort();
	}

	BinarySearchTree__TYPE_NAME___SPSP_FoundInfo ppinfo = FindProperPosition(self_ptr->m_bt, self_ptr->m_bst_order, item);
	return (ppinfo.found_bitree_ptr != NULL && ppinfo.tree_order == 0);
}

BinarySearchTree__TYPE_NAME__ * 	BinarySearchTree__TYPE_NAME___SPSP_RemoveItem	(BinarySearchTree__TYPE_NAME__ * self_ptr, __TYPE__ item) {
	if(self_ptr == NULL || self_ptr->m_bt == NULL) {
		perror("인풋이 널임\n");
		abort();
	}

}
