#include "binarysearchtree.h"
#include <errno.h>
#include <string.h>

#define BinaryTree__TYPE_NAME___SPSP_LeftReconnectSubtree BinaryTreeIntLeftReconnectSubtree
#define BinaryTree__TYPE_NAME___SPSP_RightReconnectSubtree BinaryTreeIntRightReconnectSubtree
#define BinaryTree__TYPE_NAME___SPSP_DataSwap BinaryTreeIntDataSwap
#define CreateBinaryTree__TYPE_NAME__ CreateBinaryTreeInt
#define DestroyBinaryTree__TYPE_NAME__ DestroyBinaryTreeInt

const BinarySearchTree__TYPE_NAME__ DEFAULT_BST_TEMPLATE = {
	.m_bt = NULL,
	.m_bst_order = BST_LESS_ORDER,
	.size = BinarySearchTree__TYPE_NAME___SPSP_Size,
	.max_depth = BinarySearchTree__TYPE_NAME___SPSP_MaxDepth,
	.insert_item = BinarySearchTree__TYPE_NAME___SPSP_InsertItem,
	.find = BinarySearchTree__TYPE_NAME___SPSP_Find,
	.remove_item = BinarySearchTree__TYPE_NAME___SPSP_RemoveItem,
};

static int BinarySearchTree__TYPE_NAME___SPSP_LessCompare(__TYPE__ lhs, __TYPE__ rhs)
{
	if (lhs > rhs)
		return -1;
	if (lhs < rhs)
		return 1;
	return 0;
}

static int BinarySearchTree__TYPE_NAME___SPSP_GreaterCompare(__TYPE__ lhs, __TYPE__ rhs)
{
	if (lhs > rhs)
		return 1;
	if (lhs < rhs)
		return -1;
	return 0;
}

const BinarySearchTree__TYPE_NAME___SPSP_FoundInfo ERROR_PROPER_POSITION_INFO_TEMPLATE = {
	.found_bitree_ptr = NULL,
	.tree_order = 0};

BinarySearchTree__TYPE_NAME__ *CreateBinarySearchTree__TYPE_NAME__(E_BST_ORDER bst_order, __TYPE__ item)
{
	BinarySearchTree__TYPE_NAME__ *temp_bst = (BinarySearchTree__TYPE_NAME__ *)malloc(sizeof(BinarySearchTree__TYPE_NAME__));
	if (temp_bst == NULL)
	{
		perror("bst 메모리 할당 실패");
		abort();
	}
	memcpy(temp_bst, &DEFAULT_BST_TEMPLATE, sizeof(BinarySearchTree__TYPE_NAME__));
	BinaryTree__TYPE_NAME__ *temp_bitree = CreateBinaryTree__TYPE_NAME__(item);
	if (temp_bitree == NULL)
	{
		perror("binary tree 메모리 할당 실패");
		abort();
	}

	temp_bst->m_bt = temp_bitree;
	temp_bst->m_bst_order = bst_order;

	if (temp_bst->m_bst_order == BST_LESS_ORDER)
		temp_bst->compare = BinarySearchTree__TYPE_NAME___SPSP_LessCompare;
	else if (temp_bst->m_bst_order == BST_GREATER_ORDER)
		temp_bst->compare = BinarySearchTree__TYPE_NAME___SPSP_GreaterCompare;
	else
	{
		DestroyBinarySearchTree__TYPE_NAME__(temp_bst);
		abort();
	}

	return temp_bst;
}

void DestroyBinarySearchTree__TYPE_NAME__(BinarySearchTree__TYPE_NAME__ *self_ptr)
{
	if (self_ptr == NULL || self_ptr->m_bt == NULL)
	{
		perror("BST 더블 프레 에러");
		return;
	}
	DestroyBinaryTree__TYPE_NAME__(self_ptr->m_bt->m_root);
	free(self_ptr);
}

size_t BinarySearchTree__TYPE_NAME___SPSP_Size(BinarySearchTree__TYPE_NAME__ *self_ptr)
{
	if (self_ptr == NULL || self_ptr->m_bt == NULL)
		return 0;
	return self_ptr->m_bt->m_size;
}

size_t BinarySearchTree__TYPE_NAME___SPSP_MaxDepth(BinarySearchTree__TYPE_NAME__ *self_ptr)
{
	if (self_ptr == NULL || self_ptr->m_bt == NULL)
		return 0;
	return self_ptr->m_bt->m_max_depth;
}

static BinarySearchTree__TYPE_NAME___SPSP_FoundInfo FindProperPosition(
	BinaryTree__TYPE_NAME__ *current_tree, __TYPE__ item,
	int (*compare)(__TYPE__ lhs, __TYPE__ rhs))
{
	if (current_tree == NULL)
		return ERROR_PROPER_POSITION_INFO_TEMPLATE;
	__TYPE__ current_item = current_tree->get(current_tree->m_root, current_tree);
	if (compare(current_item, item) == -1)
	{
		if (current_tree->m_left_child == NULL)
		{
			return (BinarySearchTree__TYPE_NAME___SPSP_FoundInfo){.found_bitree_ptr = current_tree, .tree_order = LEFT_INSERT_NODE};
		}
		return FindProperPosition(current_tree->m_left_child, item, compare);
	}
	else if (compare(current_item, item) == 1)
	{
		if (current_tree->m_right_child == NULL)
		{
			return (BinarySearchTree__TYPE_NAME___SPSP_FoundInfo){.found_bitree_ptr = current_tree, .tree_order = RIGHT_INSERT_NODE};
		}
		return FindProperPosition(current_tree->m_right_child, item, compare);
	}
	return (BinarySearchTree__TYPE_NAME___SPSP_FoundInfo){.found_bitree_ptr = current_tree, .tree_order = 0};
}

void BinarySearchTree__TYPE_NAME___SPSP_InsertItem(BinarySearchTree__TYPE_NAME__ *self_ptr, __TYPE__ item)
{
	if (self_ptr == NULL || self_ptr->m_bt == NULL)
	{
		perror("인풋이 널임\n");
		abort();
	}

	BinarySearchTree__TYPE_NAME___SPSP_FoundInfo ppinfo = FindProperPosition(self_ptr->m_bt, item, self_ptr->compare);
	if (ppinfo.found_bitree_ptr == NULL)
		return;

	E_BINARY_TREE_INSERT_MODE insert_mode = 0;
	if (ppinfo.tree_order == -1)
		insert_mode = LEFT_INSERT_NODE;
	else if (ppinfo.tree_order == 1)
		insert_mode = RIGHT_INSERT_NODE;
	else
		return;

	BinaryTree__TYPE_NAME__ *new_tree = CreateBinaryTree__TYPE_NAME__(item);
	BinaryTree__TYPE_NAME__ *bitree_root = self_ptr->m_bt->m_root;
	bitree_root->insert(bitree_root, ppinfo.found_bitree_ptr, insert_mode, new_tree);
}

bool BinarySearchTree__TYPE_NAME___SPSP_Find(BinarySearchTree__TYPE_NAME__ *self_ptr, __TYPE__ item)
{
	if (self_ptr == NULL || self_ptr->m_bt == NULL)
	{
		perror("인풋이 널임\n");
		abort();
	}

	BinarySearchTree__TYPE_NAME___SPSP_FoundInfo ppinfo = FindProperPosition(self_ptr->m_bt, item, self_ptr->compare);
	return (ppinfo.found_bitree_ptr != NULL && ppinfo.tree_order == 0);
}

static void SelectRightSide(BinarySearchTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * rm_bitree) {
	BinaryTree__TYPE_NAME__ *near_bitree = rm_bitree->m_right_child;
	while (near_bitree->m_left_child != NULL)
	{
		near_bitree = near_bitree->m_left_child;
	}
	BinaryTree__TYPE_NAME___SPSP_DataSwap(near_bitree, rm_bitree);
	rm_bitree = near_bitree;
	if (rm_bitree->m_right_child != NULL)
	{
		BinaryTree__TYPE_NAME__ *reconnect_parent_bitree_ptr = rm_bitree->m_parent;
		BinaryTree__TYPE_NAME__ *reconnect_subtree_ptr = rm_bitree->m_right_child;
		// 리커넥트를 해야함. 리커넥트 하면 알아서 지워짐
		if (self_ptr->compare(reconnect_parent_bitree_ptr->m_data, reconnect_subtree_ptr->m_data) == -1)
			BinaryTree__TYPE_NAME___SPSP_LeftReconnectSubtree(reconnect_parent_bitree_ptr, reconnect_subtree_ptr);
		else
		{
			BinaryTree__TYPE_NAME___SPSP_RightReconnectSubtree(reconnect_parent_bitree_ptr, reconnect_subtree_ptr);
		}
	}
	else
	{
		DestroyBinaryTreeInt(self_ptr->m_bt->m_root->remove(self_ptr->m_bt->m_root, rm_bitree));
	}
	return;
}

static void SelectLeftSide(BinarySearchTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * rm_bitree) {
	BinaryTree__TYPE_NAME__ *near_bitree = rm_bitree->m_left_child;
	while (near_bitree->m_right_child != NULL)
	{
		near_bitree = near_bitree->m_right_child;
	}
	BinaryTree__TYPE_NAME___SPSP_DataSwap(near_bitree, rm_bitree);
	rm_bitree = near_bitree;
	if (rm_bitree->m_left_child != NULL)
	{
		BinaryTree__TYPE_NAME__ *reconnect_parent_bitree_ptr = rm_bitree->m_parent;
		BinaryTree__TYPE_NAME__ *reconnect_subtree_ptr = rm_bitree->m_left_child;
		// 리커넥트를 해야함. 리커넥트 하면 알아서 지워짐
		if (self_ptr->compare(reconnect_parent_bitree_ptr->m_data, reconnect_subtree_ptr->m_data) == -1)
			BinaryTree__TYPE_NAME___SPSP_LeftReconnectSubtree(reconnect_parent_bitree_ptr, reconnect_subtree_ptr);
		else
		{
			BinaryTree__TYPE_NAME___SPSP_RightReconnectSubtree(reconnect_parent_bitree_ptr, reconnect_subtree_ptr);
		}
	}
	else
	{
		DestroyBinaryTreeInt(self_ptr->m_bt->m_root->remove(self_ptr->m_bt->m_root, rm_bitree));
	}
}

void BinarySearchTree__TYPE_NAME___SPSP_RemoveItem(BinarySearchTree__TYPE_NAME__ *self_ptr, __TYPE__ item)
{
	if (self_ptr == NULL || self_ptr->m_bt == NULL)
	{
		perror("인풋이 널임\n");
		abort();
	}
	BinaryTree__TYPE_NAME__ *root_bitree = self_ptr->m_bt->m_root;
	BinarySearchTree__TYPE_NAME___SPSP_FoundInfo ppinfo = FindProperPosition(self_ptr->m_bt, item, self_ptr->compare);
	if (!(ppinfo.found_bitree_ptr != NULL && ppinfo.tree_order == 0))
	{
		perror("item에 해당하는 요소 없음");
		return;
	}
	BinaryTree__TYPE_NAME__ *founded_rm_bitree_ptr = ppinfo.found_bitree_ptr;

	if (founded_rm_bitree_ptr->m_right_child == NULL && founded_rm_bitree_ptr->m_left_child == NULL)
	{
		/* 자식이 아예 없을떄 */
		DestroyBinaryTreeInt(root_bitree->remove(root_bitree, founded_rm_bitree_ptr));
	}
	else if (founded_rm_bitree_ptr->m_left_child == NULL)
	{
		/* 한쪽만 있을떄 우측 */
		SelectRightSide(self_ptr, founded_rm_bitree_ptr);
	}
	else if (founded_rm_bitree_ptr->m_right_child == NULL)
	{
		/* 한쪽만 있을떄 좌측 */
		SelectLeftSide(self_ptr, founded_rm_bitree_ptr);
	}
	else {
		/*
		양쪽에 모두 자식이 있을 떄
		SelectRightSide VS SelectLeftSide 어떤걸 해도 상관은 없다.
		*/
		SelectLeftSide(self_ptr, founded_rm_bitree_ptr); /* SelectRightSide(self_ptr, founded_rm_bitree_ptr); */
	}

}
