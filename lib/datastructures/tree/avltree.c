#include "avltree.h"
#include <string.h>

const AVLTree__TYPE_NAME__ DEFAULT_AVL_TREE_TEMPLATE = {
	.m_bst = NULL,
	.size = AVLTree__TYPE_NAME___SPSP_Size,
	.max_depth = AVLTree__TYPE_NAME___SPSP_MaxDepth,
	.insert_item = AVLTree__TYPE_NAME___SPSP_InsertItem,
	.find = AVLTree__TYPE_NAME___SPSP_Find,
	.remove_item = AVLTree__TYPE_NAME___SPSP_RemoveItem,
};

static inline int BalanceFactorForAVL (BinaryTree__TYPE_NAME__ * cur_bitree) {
	if(cur_bitree == NULL)
		return 0;

	size_t lmxdepth = 0, rmxdepth = 0;

	if(cur_bitree->m_left_child != NULL)
		lmxdepth = cur_bitree->m_left_child->size(cur_bitree->m_left_child, cur_bitree->m_left_child);
	if(cur_bitree->m_right_child != NULL)
		rmxdepth = cur_bitree->m_right_child->size(cur_bitree->m_right_child, cur_bitree->m_right_child);

	return (int)lmxdepth - (int)rmxdepth;
}

AVLTree__TYPE_NAME__ *CreateAVLTree__TYPE_NAME__(E_BST_ORDER bst_order, __TYPE__ init_data)
{
	AVLTree__TYPE_NAME__ * temp_avl = malloc(sizeof(AVLTree__TYPE_NAME__));
	if(temp_avl == NULL) {
		abort();
	}
	memcpy(temp_avl, &DEFAULT_AVL_TREE_TEMPLATE, sizeof(AVLTree__TYPE_NAME__));
	BinarySearchTree__TYPE_NAME__ * dep_bst = CreateBinarySearchTree__TYPE_NAME__(bst_order, init_data);
	if(dep_bst == NULL) {
		abort();
	}

	temp_avl->m_bst = dep_bst;
	temp_avl->m_bst_order = bst_order;

	return temp_avl;
}

void DestroyAVLTree__TYPE_NAME__(AVLTree__TYPE_NAME__ * self_ptr)
{
	if(self_ptr == NULL && self_ptr->m_bst == NULL) {
		return;
	}

	DestroyBinarySearchTree__TYPE_NAME__(self_ptr->m_bst);
	free(self_ptr);
}


size_t AVLTree__TYPE_NAME___SPSP_Size(AVLTree__TYPE_NAME__ *self_ptr)
{
	if(self_ptr == NULL || self_ptr->m_bst == NULL) abort();
	return self_ptr->m_bst->size(self_ptr->m_bst);
}

size_t AVLTree__TYPE_NAME___SPSP_MaxDepth(AVLTree__TYPE_NAME__ *self_ptr)
{
	if(self_ptr == NULL || self_ptr->m_bst == NULL) abort();
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
	if(self_ptr == NULL || self_ptr->m_bst == NULL) abort();
	BinarySearchTree__TYPE_NAME__ * dep_bst = self_ptr->m_bst;
	dep_bst->insert_item(dep_bst, item);

	BinarySearchTree__TYPE_NAME___SPSP_FoundInfo found_info = BinarySearchTree__TYPE_NAME___SPSP_FindProperPosition(
		dep_bst->m_bt, item, dep_bst->compare
	);

	if(!(found_info.found_bitree_ptr != NULL && found_info.tree_order == 0)) {
		return;
	}

	BinaryTree__TYPE_NAME__ * inserted 	= found_info.found_bitree_ptr;
	BinaryTree__TYPE_NAME__ * top_subtree = found_info.found_bitree_ptr->m_parent->m_parent;

	BinaryTree__TYPE_NAME__ * res_proper_res = top_subtree->m_parent;
	E_BINARY_TREE_INSERT_MODE insert_mode;
	if		(res_proper_res->m_left_child == top_subtree)
		insert_mode = LEFT_INSERT_NODE;
	else if (res_proper_res->m_right_child == top_subtree)
		insert_mode = RIGHT_INSERT_NODE;
	else
		abort();

	if(BalanceFactorForAVL(top_subtree) == 0) return;

	BinaryTree__TYPE_NAME__ * balanced_res = NULL;

	if		(BalanceFactorForAVL(top_subtree) > 1) {
		/* L- */
		if(BalanceFactorForAVL(top_subtree->m_left_child) >= 0)
			balanced_res = AVLTree__TYPE_NAME___SPSP_BalanceLL(dep_bst->m_bt->m_root, top_subtree, top_subtree->m_left_child, inserted);
		else
			balanced_res = AVLTree__TYPE_NAME___SPSP_BalanceLR(dep_bst->m_bt->m_root, top_subtree, top_subtree->m_right_child, inserted);
	}
	else if (BalanceFactorForAVL(top_subtree) < 1){
		/* R- */
		if(BalanceFactorForAVL(top_subtree->m_right_child) >= 0)
			balanced_res = AVLTree__TYPE_NAME___SPSP_BalanceRR(dep_bst->m_bt->m_root, top_subtree, top_subtree->m_right_child, inserted);
		else
			balanced_res = AVLTree__TYPE_NAME___SPSP_BalanceRL(dep_bst->m_bt->m_root, top_subtree, top_subtree->m_left_child, inserted);
	}

	res_proper_res->insert(dep_bst->m_bt->m_root, res_proper_res, insert_mode, balanced_res);
}

bool AVLTree__TYPE_NAME___SPSP_Find(AVLTree__TYPE_NAME__ *self_ptr, __TYPE__ item)
{
	if(self_ptr == NULL || self_ptr->m_bst == NULL) abort();
	return self_ptr->m_bst->find(self_ptr->m_bst, item);
}

void AVLTree__TYPE_NAME___SPSP_RemoveItem(AVLTree__TYPE_NAME__ *self_ptr, __TYPE__ item)
{
	if(self_ptr == NULL || self_ptr->m_bst == NULL) abort();
}

BinaryTree__TYPE_NAME__ * AVLTree__TYPE_NAME___SPSP_BalanceLL(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * A, BinaryTree__TYPE_NAME__ * B, BinaryTree__TYPE_NAME__ * C) {
	BinaryTree__TYPE_NAME__ * balanced_res = NULL;

	A = self_ptr->remove(self_ptr, A);
	B = A->remove(A, B);

	if(B->m_right_child != NULL) {
		BinaryTree__TYPE_NAME__ * rm_b_right = B->remove(B, B->m_right_child);
		A->insert(A, A, LEFT_INSERT_NODE, rm_b_right);
	}
	B->insert(B, B, RIGHT_INSERT_NODE, A);
	balanced_res = B;
	return balanced_res;
}

BinaryTree__TYPE_NAME__ * AVLTree__TYPE_NAME___SPSP_BalanceRR(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * A, BinaryTree__TYPE_NAME__ * B, BinaryTree__TYPE_NAME__ * C) {
	BinaryTree__TYPE_NAME__ * balanced_res = NULL;

	A = self_ptr->remove(self_ptr, A);
	B = A->remove(A, B);

	if(B->m_left_child != NULL) {
		BinaryTree__TYPE_NAME__ * rm_b_left = B->remove(B, B->m_left_child);
		A->insert(A, A, RIGHT_INSERT_NODE, rm_b_left);
	}
	B->insert(B, B, LEFT_INSERT_NODE, A);
	balanced_res = B;
	return balanced_res;
}

BinaryTree__TYPE_NAME__ * AVLTree__TYPE_NAME___SPSP_BalanceLR(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * A, BinaryTree__TYPE_NAME__ * B, BinaryTree__TYPE_NAME__ * C) {
	BinaryTree__TYPE_NAME__ * balanced_res = NULL;
	B = AVLTree__TYPE_NAME___SPSP_BalanceRR(self_ptr, B, C, NULL);
	balanced_res = AVLTree__TYPE_NAME___SPSP_BalanceLL(self_ptr, A, B, NULL);
	return balanced_res;
}

BinaryTree__TYPE_NAME__ * AVLTree__TYPE_NAME___SPSP_BalanceRL(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * A, BinaryTree__TYPE_NAME__ * B, BinaryTree__TYPE_NAME__ * C) {
	BinaryTree__TYPE_NAME__ * balanced_res = NULL;
	B = AVLTree__TYPE_NAME___SPSP_BalanceLL(self_ptr, B, C, NULL);
	balanced_res = AVLTree__TYPE_NAME___SPSP_BalanceRR(self_ptr, A, B, NULL);
	return balanced_res;
}
