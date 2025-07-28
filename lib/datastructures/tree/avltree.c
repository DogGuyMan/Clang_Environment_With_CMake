#include "avltree.h"
#include <math.h>
#include <string.h>

#define DEBUG_PRINT 1

static const AVLTree__TYPE_NAME__ DEFAULT_AVL_TREE_TEMPLATE = {
	.m_bst = NULL,
	.size = AVLTree__TYPE_NAME___SPSP_Size,
	.max_depth = AVLTree__TYPE_NAME___SPSP_MaxDepth,
	.insert_item = AVLTree__TYPE_NAME___SPSP_InsertItem,
	.find = AVLTree__TYPE_NAME___SPSP_Find,
	.remove_item = AVLTree__TYPE_NAME___SPSP_RemoveItem,
};

/*
1 < Res : 오른쪽 비대
0 : 균형됨
Res < -1 : 왼쪽 비대
*/
static inline int BalanceFactor(BinaryTree__TYPE_NAME__ *cur_bitree)
{
	if (cur_bitree == NULL)
		return 0;

	size_t left_height = 0, right_height = 0;

	if (cur_bitree->m_left_child != NULL)
		left_height = cur_bitree->m_left_child->m_max_depth + 1;
	if (cur_bitree->m_right_child != NULL)
		right_height = cur_bitree->m_right_child->m_max_depth + 1;

	return (int)right_height - (int)left_height;
}

static bool IsTreeBalanced(BinaryTree__TYPE_NAME__ *cur_bitree, int prev_balance_factor, AVLTree__TYPE_NAME___SPSP_BalanceInfo *balance_info_ptr)
{

	int cur_balance_factor = BalanceFactor(cur_bitree);
	if (cur_balance_factor >= 2)
	{
		if (balance_info_ptr != NULL)
		{
			balance_info_ptr->unbalanced_bitree_ptr = cur_bitree;
			balance_info_ptr->rotate_mode = (0 <= prev_balance_factor) ? RR : RL;
		}
		return false;
	}
	else if (cur_balance_factor <= -2)
	{
		if (balance_info_ptr != NULL)
		{
			balance_info_ptr->unbalanced_bitree_ptr = cur_bitree;
			balance_info_ptr->rotate_mode = (0 <= prev_balance_factor) ? LR : LL;
		}
		return false;
	}

	if (cur_bitree == cur_bitree->m_root)
		return true;

	return IsTreeBalanced(cur_bitree->m_parent, cur_balance_factor, balance_info_ptr);
}

AVLTree__TYPE_NAME__ *CreateAVLTree__TYPE_NAME__(E_BST_ORDER bst_order, __TYPE__ init_data)
{
	AVLTree__TYPE_NAME__ *temp_avl = malloc(sizeof(AVLTree__TYPE_NAME__));
	if (temp_avl == NULL)
	{
		abort();
	}
	memcpy(temp_avl, &DEFAULT_AVL_TREE_TEMPLATE, sizeof(AVLTree__TYPE_NAME__));
	BinarySearchTree__TYPE_NAME__ *dep_bst = CreateBinarySearchTree__TYPE_NAME__(bst_order, init_data);
	if (dep_bst == NULL)
	{
		abort();
	}

	temp_avl->m_bst = dep_bst;
	temp_avl->m_bst_order = bst_order;

	return temp_avl;
}

void DestroyAVLTree__TYPE_NAME__(AVLTree__TYPE_NAME__ *self_ptr)
{
	if (self_ptr == NULL || self_ptr->m_bst == NULL)
	{
		return;
	}

	DestroyBinarySearchTree__TYPE_NAME__(self_ptr->m_bst);
	free(self_ptr);
}

size_t AVLTree__TYPE_NAME___SPSP_Size(AVLTree__TYPE_NAME__ *self_ptr)
{
	if (self_ptr == NULL || self_ptr->m_bst == NULL)
		abort();
	return self_ptr->m_bst->size(self_ptr->m_bst);
}

size_t AVLTree__TYPE_NAME___SPSP_MaxDepth(AVLTree__TYPE_NAME__ *self_ptr)
{
	if (self_ptr == NULL || self_ptr->m_bst == NULL)
		abort();
	return self_ptr->m_bst->max_depth(self_ptr->m_bst);
}

/*
Case Condition Rotation

Left-Left(LL)
Node: BF > 1, Left Child: BF >= 0
Right

Right-Right (RR)
Node: BF < -1, Right Child: BF <= 0
Left

Left-Right(LR)
Node: BF > 1, Left Child: BF < 0
Left + Right

Right-Left(RL)
Node: BF < -1, Riaht Child: BF > 0
Right + Left
*/

void AVLTree__TYPE_NAME___SPSP_InsertItem(AVLTree__TYPE_NAME__ *self_ptr, __TYPE__ item)
{
	if (self_ptr == NULL || self_ptr->m_bst == NULL)
		abort();
	BinarySearchTree__TYPE_NAME__ *dep_bst = self_ptr->m_bst;

	dep_bst->insert_item(dep_bst, item);
	if (self_ptr->size(self_ptr) <= 1)
		return;

	BinarySearchTree__TYPE_NAME___SPSP_FoundInfo found_info = BinarySearchTree__TYPE_NAME___SPSP_FindProperPosition(dep_bst->m_bt, item, dep_bst->compare);

	if (!(found_info.found_bitree_ptr != NULL && found_info.tree_order == 0))
	{
		abort();
	}

	AVLTree__TYPE_NAME___SPSP_BalanceInfo balance_info = {
		.rotate_mode = -1,
		.unbalanced_bitree_ptr = NULL};

	bool is_tree_balanced = IsTreeBalanced(found_info.found_bitree_ptr, BalanceFactor(found_info.found_bitree_ptr), &balance_info);

#if DEBUG_PRINT
	printf("is tree balanced : %s\n", ((is_tree_balanced) ? "YES" : "NO"));
#endif

	if (!is_tree_balanced)
	{
		switch (balance_info.rotate_mode)
		{
		case RR: {AVLTree__TYPE_NAME___SPSP_BalanceRR(self_ptr, balance_info.unbalanced_bitree_ptr); break;}
		case RL: {AVLTree__TYPE_NAME___SPSP_BalanceRL(self_ptr, balance_info.unbalanced_bitree_ptr); break;}
		case LR: {AVLTree__TYPE_NAME___SPSP_BalanceLR(self_ptr, balance_info.unbalanced_bitree_ptr); break;}
		case LL: {AVLTree__TYPE_NAME___SPSP_BalanceLL(self_ptr, balance_info.unbalanced_bitree_ptr); break;}
		default:
			break;
		}
	}
}

bool AVLTree__TYPE_NAME___SPSP_Find(AVLTree__TYPE_NAME__ *self_ptr, __TYPE__ item)
{
	if (self_ptr == NULL || self_ptr->m_bst == NULL)
		abort();
	return self_ptr->m_bst->find(self_ptr->m_bst, item);
}

void AVLTree__TYPE_NAME___SPSP_RemoveItem(AVLTree__TYPE_NAME__ *self_ptr, __TYPE__ item)
{
	if (self_ptr == NULL || self_ptr->m_bst == NULL)
		abort();

	BinarySearchTree__TYPE_NAME__ * dep_bst = self_ptr->m_bst;

	if (self_ptr->size(self_ptr) <= 1)
		return;

	BinarySearchTree__TYPE_NAME___SPSP_FoundInfo found_info = BinarySearchTree__TYPE_NAME___SPSP_FindProperPosition(dep_bst->m_bt, item, dep_bst->compare);
	if (!(found_info.found_bitree_ptr != NULL && found_info.tree_order == 0))
	{
		abort();
	}

	BinaryTree__TYPE_NAME__ * balance_test_target = NULL;
	if(found_info.found_bitree_ptr->m_parent != NULL) {
		balance_test_target = found_info.found_bitree_ptr->m_parent;
	}
	self_ptr->m_bst->remove_item(self_ptr->m_bst, item);

	if(balance_test_target == NULL) return;

	AVLTree__TYPE_NAME___SPSP_BalanceInfo balance_info = {
		.rotate_mode = -1,
		.unbalanced_bitree_ptr = NULL};

	bool is_tree_balanced = IsTreeBalanced(balance_test_target, BalanceFactor(balance_test_target), &balance_info);

#if DEBUG_PRINT
	printf("is tree balanced : %s\n", ((is_tree_balanced) ? "YES" : "NO"));
#endif

	if (!is_tree_balanced)
	{
		switch (balance_info.rotate_mode)
		{
		case RR: {AVLTree__TYPE_NAME___SPSP_BalanceRR(self_ptr, balance_info.unbalanced_bitree_ptr); break;}
		case RL: {AVLTree__TYPE_NAME___SPSP_BalanceRL(self_ptr, balance_info.unbalanced_bitree_ptr); break;}
		case LR: {AVLTree__TYPE_NAME___SPSP_BalanceLR(self_ptr, balance_info.unbalanced_bitree_ptr); break;}
		case LL: {AVLTree__TYPE_NAME___SPSP_BalanceLL(self_ptr, balance_info.unbalanced_bitree_ptr); break;}
		default:
			break;
		}
	}
}

/*
로컬 변수로 된 포인터를 함수 매개변수를 통해 전달해서
함수를 통해 변환을 원한다면 "포인터의 포인터"를 넘기고
"포인터의 포인터를 역참조"를 하도록 해서
함수 실행 후 값이 변하도록 한다.
*/
static void HandleUnbalanceBinaryTreeParents(
	AVLTree__TYPE_NAME__ *self_ptr,
	BinaryTree__TYPE_NAME__ ** ref_unbalanced_bitree_parent_ptr, BinaryTree__TYPE_NAME__ ** ref_unbalanced_bitree_ptr,
	bool * ref_is_root_bitree, E_BINARY_TREE_INSERT_MODE * ref_unbitree_parent_inserted
) {

	if ((*ref_unbalanced_bitree_ptr) != self_ptr->m_bst->m_bt->m_root)
	{
		*ref_is_root_bitree = false;
		(*ref_unbalanced_bitree_parent_ptr) = (*ref_unbalanced_bitree_ptr)->m_parent;

		if ((*ref_unbalanced_bitree_ptr)->m_parent->m_left_child == (*ref_unbalanced_bitree_ptr))
		{
			*ref_unbitree_parent_inserted = LEFT_INSERT_NODE;
		}
		else if ((*ref_unbalanced_bitree_ptr)->m_parent->m_right_child == (*ref_unbalanced_bitree_ptr))
		{
			*ref_unbitree_parent_inserted = RIGHT_INSERT_NODE;
		}
		else
			abort();

		(*ref_unbalanced_bitree_ptr) = (*ref_unbalanced_bitree_ptr)->m_parent->remove((*ref_unbalanced_bitree_ptr)->m_parent, *ref_unbalanced_bitree_ptr);
	}
}

void AVLTree__TYPE_NAME___SPSP_BalanceLL(AVLTree__TYPE_NAME__ *self_ptr, BinaryTree__TYPE_NAME__ *unbalanced_bitree_ptr)
{
	bool is_root_bitree = true;
	BinaryTree__TYPE_NAME__ * unbalanced_bitree_parent_ptr = NULL;
	E_BINARY_TREE_INSERT_MODE unbitree_parent_inserted = 0;

	HandleUnbalanceBinaryTreeParents(self_ptr, &unbalanced_bitree_parent_ptr, &unbalanced_bitree_ptr,
		&is_root_bitree, &unbitree_parent_inserted);

	BinaryTree__TYPE_NAME__ *left_subtree = unbalanced_bitree_ptr->remove(unbalanced_bitree_ptr, unbalanced_bitree_ptr->m_left_child);

	BinaryTree__TYPE_NAME__ *left_right_subtree = NULL;
	if (left_subtree->m_right_child != NULL)
	{
		left_right_subtree = left_subtree->remove(left_subtree, left_subtree->m_right_child);
		unbalanced_bitree_ptr->insert(
			unbalanced_bitree_ptr, unbalanced_bitree_ptr,
			LEFT_INSERT_NODE, left_right_subtree);
	}
	left_subtree->insert(left_subtree, left_subtree,
						 RIGHT_INSERT_NODE, unbalanced_bitree_ptr);

	if (is_root_bitree)
		self_ptr->m_bst->m_bt = left_subtree->m_root;
	else
	{
		unbalanced_bitree_parent_ptr->insert(unbalanced_bitree_parent_ptr, unbalanced_bitree_parent_ptr,
								unbitree_parent_inserted, left_subtree);
	}
}

void AVLTree__TYPE_NAME___SPSP_BalanceRR(AVLTree__TYPE_NAME__ *self_ptr, BinaryTree__TYPE_NAME__ *unbalanced_bitree_ptr)
{
	bool is_root_bitree = true;
	BinaryTree__TYPE_NAME__ * unbalanced_bitree_parent_ptr = NULL;
	E_BINARY_TREE_INSERT_MODE unbitree_parent_inserted = 0;

	HandleUnbalanceBinaryTreeParents(self_ptr, &unbalanced_bitree_parent_ptr, &unbalanced_bitree_ptr,
		&is_root_bitree, &unbitree_parent_inserted);

	BinaryTree__TYPE_NAME__ *right_subtree = unbalanced_bitree_ptr->remove(unbalanced_bitree_ptr,
																		   unbalanced_bitree_ptr->m_right_child);

	BinaryTree__TYPE_NAME__ *right_left_subtree = NULL;
	if (right_subtree->m_left_child != NULL)
	{
		right_left_subtree = right_subtree->remove(right_subtree, right_subtree->m_left_child);
		unbalanced_bitree_ptr->insert(
			unbalanced_bitree_ptr, unbalanced_bitree_ptr,
			RIGHT_INSERT_NODE, right_left_subtree);
	}
	right_subtree->insert(right_subtree, right_subtree,
						  LEFT_INSERT_NODE, unbalanced_bitree_ptr);

	if (is_root_bitree)
		self_ptr->m_bst->m_bt = right_subtree->m_root;
	else
	{
		unbalanced_bitree_parent_ptr->insert(unbalanced_bitree_parent_ptr, unbalanced_bitree_parent_ptr,
											 unbitree_parent_inserted, right_subtree);
	}

}

void AVLTree__TYPE_NAME___SPSP_BalanceLR(AVLTree__TYPE_NAME__ *self_ptr, BinaryTree__TYPE_NAME__ * unbalanced_bitree_ptr)
{
	AVLTree__TYPE_NAME___SPSP_BalanceRR(self_ptr, unbalanced_bitree_ptr->m_left_child);
	AVLTree__TYPE_NAME___SPSP_BalanceLL(self_ptr, unbalanced_bitree_ptr);
}

void AVLTree__TYPE_NAME___SPSP_BalanceRL(AVLTree__TYPE_NAME__ *self_ptr, BinaryTree__TYPE_NAME__ * unbalanced_bitree_ptr)
{
	AVLTree__TYPE_NAME___SPSP_BalanceLL(self_ptr, unbalanced_bitree_ptr->m_right_child);
	AVLTree__TYPE_NAME___SPSP_BalanceRR(self_ptr, unbalanced_bitree_ptr);
}
