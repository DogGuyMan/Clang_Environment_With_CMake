#ifndef __HEADER_GUARD_BINARYTREE_PRIMITIVE__
#define __HEADER_GUARD_BINARYTREE_PRIMITIVE__

#include <stdbool.h>
#include <stdlib.h>
#include "sjhdatatype.h"
#include "sjhaddresstype.h"
#include "vector_primitive.h"
#include "tree.h"

typedef enum {
    LEFT_INSERT_NODE    = -1,
    RIGHT_INSERT_NODE   = 1
} E_BINARY_TREE_INSERT_MODE;

#define DEFINE_BINARYTREE_TYPE(TYPE, TYPE_NAME) \
typedef struct BinaryTree##TYPE_NAME BinaryTree##TYPE_NAME; \
\
struct BinaryTree##TYPE_NAME { \
    TYPE m_data; \
    size_t m_size; \
	size_t m_max_depth; \
    BinaryTree##TYPE_NAME * m_root; \
    BinaryTree##TYPE_NAME * m_current; \
	BinaryTree##TYPE_NAME * m_parent; \
    BinaryTree##TYPE_NAME * m_left_child; \
    BinaryTree##TYPE_NAME * m_right_child; \
\
    size_t        				( * const size)					(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree); \
    size_t        				( * const max_depth)			(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree); \
    BinaryTree##TYPE_NAME * 	( * const left_child)			(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree); \
    BinaryTree##TYPE_NAME * 	( * const right_child)			(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree); \
    BinaryTree##TYPE_NAME *   ( * const insert)           	(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree, E_BINARY_TREE_INSERT_MODE insert_mode, BinaryTree##TYPE_NAME * insert_tree); \
	TYPE 					( * const get)					(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_node); \
    BinaryTree##TYPE_NAME *	( * const remove)   			(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * sub_tree); \
}; \
\
BinaryTree##TYPE_NAME *   CreateBinaryTree##TYPE_NAME(TYPE); \
void                        DestroyBinaryTree##TYPE_NAME(BinaryTree##TYPE_NAME * self_ptr); \
\
size_t        				BinaryTree##TYPE_NAME##Size(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree); \
size_t        				BinaryTree##TYPE_NAME##MaxDepth(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree); \
BinaryTree##TYPE_NAME *   	BinaryTree##TYPE_NAME##LeftChild(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree); \
BinaryTree##TYPE_NAME *   	BinaryTree##TYPE_NAME##RightChild(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree); \
BinaryTree##TYPE_NAME *   	BinaryTree##TYPE_NAME##Insert(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree, E_BINARY_TREE_INSERT_MODE insert_mode, BinaryTree##TYPE_NAME * insert_tree); \
TYPE 						BinaryTree##TYPE_NAME##Get(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_node); \
BinaryTree##TYPE_NAME * 	BinaryTree##TYPE_NAME##Remove(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * sub_tree); \
\
void BinaryTree##TYPE_NAME##BFS(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree, void * user_data); \
void BinaryTree##TYPE_NAME##LevelOrder(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree, void * user_data); \
void BinaryTree##TYPE_NAME##RecurseDFSPreorder(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree, void * user_data); \
void BinaryTree##TYPE_NAME##RecurseDFSInorder(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree, void * user_data); \
void BinaryTree##TYPE_NAME##RecurseDFSPostorder(BinaryTree##TYPE_NAME * self_ptr, BinaryTree##TYPE_NAME * current_tree, void * user_data); \
\
void BinaryTree##TYPE_NAME##DataSwap(BinaryTree##TYPE_NAME *lhs, BinaryTree##TYPE_NAME *rhs); \
void BinaryTree##TYPE_NAME##LeftReconnectSubtree(BinaryTree##TYPE_NAME *parent, BinaryTree##TYPE_NAME *left_subtree); \
void BinaryTree##TYPE_NAME##RightReconnectSubtree(BinaryTree##TYPE_NAME *parent, BinaryTree##TYPE_NAME *right_subtree); \

#define IMPLEMENT_BINARYTREE_TYPE(TYPE, TYPE_NAME) \
\
static const BinaryTree##TYPE_NAME DEFAULT_BINARYTREE_##TYPE_NAME##_TEMPLATE = { \
	.m_data = 0, \
	.m_size = 0, \
	.m_max_depth = 0, \
	.m_root = NULL, \
	.m_current = NULL, \
	.m_parent = NULL, \
	.m_left_child = NULL, \
	.m_right_child = NULL, \
\
	.size = BinaryTree##TYPE_NAME##Size, \
	.max_depth = BinaryTree##TYPE_NAME##MaxDepth, \
	.left_child = BinaryTree##TYPE_NAME##LeftChild, \
	.right_child = BinaryTree##TYPE_NAME##RightChild, \
	.insert = BinaryTree##TYPE_NAME##Insert, \
	.get = BinaryTree##TYPE_NAME##Get, \
	.remove = BinaryTree##TYPE_NAME##Remove, \
}; \
\
/* \
Start with Parent \
*/ \
static void BottomUpBinaryTreeUpdateDepth( \
	BinaryTree##TYPE_NAME *self_ptr, BinaryTree##TYPE_NAME *current_tree) \
{ \
	if (current_tree == NULL) \
	{ \
		return; \
	} \
	if (current_tree->m_left_child == NULL && current_tree->m_right_child == NULL) \
	{ \
		return; \
	} \
\
	size_t ldmax = 0, rdmax = 0, child_max = 0; \
	if (current_tree->m_left_child != NULL) \
	{ \
		ldmax = current_tree->m_left_child->m_max_depth; \
	} \
	if (current_tree->m_right_child != NULL) \
	{ \
		rdmax = current_tree->m_right_child->m_max_depth; \
	} \
	child_max = (ldmax < rdmax) ? rdmax : ldmax; \
\
	current_tree->m_max_depth = child_max + 1; \
\
	if (current_tree != self_ptr->m_root) \
	{ \
		BottomUpBinaryTreeUpdateDepth(self_ptr, current_tree->m_parent); \
	} \
	return; \
} \
\
/* \
Start with Parent \
*/ \
static void BottomUpBinaryTreeUpdateSize( \
	BinaryTree##TYPE_NAME *self_ptr, BinaryTree##TYPE_NAME *current_tree) \
{ \
	if (current_tree == NULL) \
		return; \
	current_tree->m_size = 1; \
	if(current_tree->m_left_child != NULL) \
		current_tree->m_size += current_tree->m_left_child->m_size; \
	if(current_tree->m_right_child != NULL) \
		current_tree->m_size += current_tree->m_right_child->m_size; \
\
	if (current_tree != self_ptr->m_root) \
	{ \
		BottomUpBinaryTreeUpdateSize(self_ptr, current_tree->m_parent); \
	} \
	return; \
} \
\
void BinaryTree##TYPE_NAME##DataSwap( \
	BinaryTree##TYPE_NAME *lhs, BinaryTree##TYPE_NAME *rhs) \
{ \
	if (lhs == NULL || rhs == NULL) \
		abort(); \
	TYPE tval = lhs->get(lhs, lhs); \
	lhs->m_data = rhs->m_data; \
	rhs->m_data = tval; \
} \
\
void BinaryTree##TYPE_NAME##LeftReconnectSubtree( \
	BinaryTree##TYPE_NAME *parent, BinaryTree##TYPE_NAME *left_subtree) \
{ \
	if (parent == NULL || left_subtree == NULL) abort(); \
\
	BinaryTree##TYPE_NAME *rm_subtree = parent->m_left_child; \
	rm_subtree->m_parent = NULL; \
	rm_subtree->m_root = rm_subtree; \
	rm_subtree->m_current = rm_subtree; \
	parent->m_left_child = NULL; \
	if (left_subtree->m_parent->m_left_child == left_subtree) \
	{ \
		left_subtree->m_parent->m_left_child = NULL; \
	} \
	else if (left_subtree->m_parent->m_right_child == left_subtree) \
	{ \
		left_subtree->m_parent->m_right_child = NULL; \
	} \
	else \
		abort(); \
	DestroyBinaryTree##TYPE_NAME(rm_subtree); \
	parent->insert(parent->m_root, parent, LEFT_INSERT_NODE, left_subtree); \
} \
\
void BinaryTree##TYPE_NAME##RightReconnectSubtree( \
	BinaryTree##TYPE_NAME *parent, BinaryTree##TYPE_NAME *right_subtree) \
{ \
	if (parent == NULL || right_subtree == NULL) abort(); \
\
	BinaryTree##TYPE_NAME *rm_subtree = parent->m_right_child; \
	rm_subtree->m_parent = NULL; \
	rm_subtree->m_root = rm_subtree; \
	rm_subtree->m_current = rm_subtree; \
	parent->m_right_child = NULL; \
	if (right_subtree->m_parent->m_left_child == right_subtree) \
	{ \
		right_subtree->m_parent->m_left_child = NULL; \
	} \
	else if (right_subtree->m_parent->m_right_child == right_subtree) \
	{ \
		right_subtree->m_parent->m_right_child = NULL; \
	} \
	else abort(); \
	DestroyBinaryTree##TYPE_NAME(rm_subtree); \
	parent->insert(parent->m_root, parent, RIGHT_INSERT_NODE, right_subtree); \
} \
\
BinaryTree##TYPE_NAME *CreateBinaryTree##TYPE_NAME(TYPE data) \
{ \
	BinaryTree##TYPE_NAME *temp_tree = malloc(sizeof(BinaryTree##TYPE_NAME)); \
	if (temp_tree == NULL) \
	{ \
		perror("바이너리 트리 메모리 할당 실패"); \
		return NULL; \
	} \
	memcpy(temp_tree, &DEFAULT_BINARYTREE_##TYPE_NAME##_TEMPLATE, sizeof(BinaryTree##TYPE_NAME)); \
	temp_tree->m_root = temp_tree; \
	temp_tree->m_current = temp_tree; \
	temp_tree->m_parent = NULL; \
	temp_tree->m_data = data; \
	temp_tree->m_size = 1; \
	temp_tree->m_max_depth = 0; \
	return temp_tree; \
} \
\
void DestroyBinaryTree##TYPE_NAME(BinaryTree##TYPE_NAME *self_ptr) \
{ \
	if (self_ptr == NULL) \
	{ \
		perror("DestroyBinaryTree##TYPE_NAME 실패"); \
		return; \
	} \
	if (self_ptr->m_left_child != NULL) \
		DestroyBinaryTree##TYPE_NAME(self_ptr->m_left_child); \
	if (self_ptr->m_right_child != NULL) \
		DestroyBinaryTree##TYPE_NAME(self_ptr->m_right_child); \
	free(self_ptr); \
} \
\
size_t BinaryTree##TYPE_NAME##Size( \
	BinaryTree##TYPE_NAME *self_ptr, BinaryTree##TYPE_NAME *current_tree) \
{ \
	if (self_ptr == NULL || current_tree == NULL) \
	{ \
		perror("BinaryTreeSize : 인풋이 널임"); \
		return 0; \
	} \
	return current_tree->m_size; \
} \
\
size_t BinaryTree##TYPE_NAME##MaxDepth( \
	BinaryTree##TYPE_NAME *self_ptr, BinaryTree##TYPE_NAME *current_tree) \
{ \
	return current_tree->m_max_depth; \
} \
\
BinaryTree##TYPE_NAME *BinaryTree##TYPE_NAME##LeftChild( \
	BinaryTree##TYPE_NAME *self_ptr, BinaryTree##TYPE_NAME *current_tree) \
{ \
	return current_tree->m_left_child; \
} \
\
BinaryTree##TYPE_NAME *BinaryTree##TYPE_NAME##RightChild( \
	BinaryTree##TYPE_NAME *self_ptr, BinaryTree##TYPE_NAME *current_tree) \
{ \
	return current_tree->m_right_child; \
} \
\
BinaryTree##TYPE_NAME *BinaryTree##TYPE_NAME##Insert( \
	BinaryTree##TYPE_NAME *self_ptr, BinaryTree##TYPE_NAME *current_tree, \
	E_BINARY_TREE_INSERT_MODE insert_mode, BinaryTree##TYPE_NAME *insert_tree) \
{ \
	BinaryTree##TYPE_NAME *new_tree = NULL; \
	if (self_ptr == NULL || current_tree == NULL || insert_tree == NULL) \
	{ \
		perror("BinaryTreeInsert : 인풋이 널임"); \
		goto INSERT_FAIL; \
	} \
\
	new_tree = insert_tree; \
	new_tree->m_root = current_tree->m_root; \
	new_tree->m_parent = current_tree; \
\
	switch (insert_mode) \
	{ \
	case LEFT_INSERT_NODE: \
	{ \
		if (current_tree->m_left_child != NULL) \
		{ \
			perror("BinaryTreeInsert : 좌 자식이 비어 있지 않음"); \
			goto INSERT_FAIL; \
		} \
		current_tree->m_left_child = new_tree; \
		break; \
	} \
	case RIGHT_INSERT_NODE: \
	{ \
		if (current_tree->m_right_child != NULL) \
		{ \
			perror("BinaryTreeInsert : 우 자식이 비어 있지 않음"); \
			goto INSERT_FAIL; \
		} \
		current_tree->m_right_child = new_tree; \
		break; \
	} \
	default: \
	{ \
		perror("BinaryTreeInsert : 이상한 삽입 모드\n"); \
		goto INSERT_FAIL; \
	} \
	} \
	/* \
	one start \
	*/ \
	BottomUpBinaryTreeUpdateSize(self_ptr, new_tree->m_parent); \
	/* \
	zero depth \
	*/ \
	BottomUpBinaryTreeUpdateDepth(self_ptr, new_tree->m_parent); \
\
	return new_tree; \
\
INSERT_FAIL: \
	return NULL; \
} \
\
TYPE BinaryTree##TYPE_NAME##Get( \
	BinaryTree##TYPE_NAME *self_ptr, BinaryTree##TYPE_NAME *current_tree) \
{ \
	if (self_ptr == NULL || current_tree == NULL) \
	{ \
		perror("BinaryTreeSize : 인풋이 널임"); \
		abort(); \
	} \
	return current_tree->m_data; \
} \
\
BinaryTree##TYPE_NAME *BinaryTree##TYPE_NAME##Remove( \
	BinaryTree##TYPE_NAME *self_ptr, BinaryTree##TYPE_NAME *sub_tree) \
{ \
\
	if (sub_tree == self_ptr->m_root && sub_tree->m_parent == NULL) \
	{ \
		perror("자기 자신을 지울수는 없음"); \
		abort(); \
	} \
	if (self_ptr == NULL || sub_tree == NULL) \
	{ \
		perror("BinaryTreeSize : 인풋이 널임"); \
		abort(); \
	} \
\
	/* \
	POST Order로 삭제해야 한다. \
	*/ \
	BinaryTree##TYPE_NAME *rm_tree = sub_tree; \
	BinaryTree##TYPE_NAME *parent_tree = sub_tree->m_parent; \
	if (rm_tree->m_parent->m_left_child == sub_tree) \
	{ \
		/* \
		Left 삭제 \
		*/ \
		if (rm_tree->m_parent->m_right_child != NULL) \
		{ \
			rm_tree->m_parent->m_max_depth = rm_tree->m_parent->m_right_child->m_max_depth + 1; \
		} \
		else \
		{ \
			rm_tree->m_parent->m_max_depth = parent_tree->m_max_depth - (rm_tree->m_max_depth + 1); \
		} \
		rm_tree->m_parent->m_size = parent_tree->m_size - rm_tree->m_size; \
		rm_tree->m_parent->m_left_child = NULL; \
\
		rm_tree->m_parent = NULL; \
		rm_tree->m_root = rm_tree; \
	} \
	else if (rm_tree->m_parent->m_right_child == sub_tree) \
	{ \
		/* \
		right 삭제 \
		*/ \
		if (rm_tree->m_parent->m_left_child != NULL) \
		{ \
			rm_tree->m_parent->m_max_depth = rm_tree->m_parent->m_left_child->m_max_depth + 1; \
		} \
		else \
		{ \
			rm_tree->m_parent->m_max_depth = parent_tree->m_max_depth - (rm_tree->m_max_depth + 1); \
		} \
		rm_tree->m_parent->m_size = parent_tree->m_size - rm_tree->m_size; \
		rm_tree->m_parent->m_right_child = NULL; \
\
		rm_tree->m_parent = NULL; \
		rm_tree->m_root = rm_tree; \
	} \
	else \
	{ \
		abort(); \
	} \
\
	BottomUpBinaryTreeUpdateSize(self_ptr, parent_tree->m_parent); \
	BottomUpBinaryTreeUpdateDepth(self_ptr, parent_tree->m_parent); \
\
	return rm_tree; \
} \
\
void BinaryTree##TYPE_NAME##BFS( \
	BinaryTree##TYPE_NAME *self_ptr, BinaryTree##TYPE_NAME *current_tree, void *user_data) \
{ \
	CircularQueueAddressType *bt_ptr_queue = CreateCircularQueueAddressType(1 << (self_ptr->m_max_depth + 1)); \
\
	int depth = 0; \
	int size_by_depth = 1; \
	BinaryTree##TYPE_NAME *head_tree; \
	bt_ptr_queue->enqueue(bt_ptr_queue, (uintptr_t)current_tree); \
\
	while (!bt_ptr_queue->is_empty(bt_ptr_queue) && depth <= self_ptr->max_depth(self_ptr, self_ptr)) \
	{ \
		printf("cur %dth depth : ", depth); \
		int new_size_by_depth = 0; \
\
		CircularQueueAddressType *temp_bt_ptr_queue = CreateCircularQueueAddressType(size_by_depth * 2 + 1); \
		for (int i = 0; i < size_by_depth; i++) \
		{ \
			uintptr_t q_front = bt_ptr_queue->dequeue(bt_ptr_queue); \
\
			if (q_front != 0) \
			{ \
				head_tree = (BinaryTree##TYPE_NAME *)q_front; \
				printf(" %d ", head_tree->get(self_ptr, head_tree)); \
			} \
			else \
			{ \
				printf(" - "); \
				continue; \
			} \
			if (head_tree->m_left_child != NULL) \
			{ \
				temp_bt_ptr_queue->enqueue(temp_bt_ptr_queue, (uintptr_t)head_tree->m_left_child); \
				new_size_by_depth++; \
			} \
			else \
			{ \
				temp_bt_ptr_queue->enqueue(temp_bt_ptr_queue, 0); \
				new_size_by_depth++; \
			} \
\
			if (head_tree->m_right_child != NULL) \
			{ \
\
				temp_bt_ptr_queue->enqueue(temp_bt_ptr_queue, (uintptr_t)head_tree->m_right_child); \
				new_size_by_depth++; \
			} \
			else \
			{ \
				temp_bt_ptr_queue->enqueue(temp_bt_ptr_queue, 0); \
				new_size_by_depth++; \
			} \
		} \
		while (!temp_bt_ptr_queue->is_empty(temp_bt_ptr_queue)) \
		{ \
			bt_ptr_queue->enqueue(bt_ptr_queue, temp_bt_ptr_queue->dequeue(temp_bt_ptr_queue)); \
		} \
		DestroyCircularQueueAddressType(temp_bt_ptr_queue); \
		printf("\n"); \
		size_by_depth = new_size_by_depth; \
		depth++; \
	} \
\
	DestroyCircularQueueAddressType(bt_ptr_queue); \
} \
\
void BinaryTree##TYPE_NAME##LevelOrder( \
	BinaryTree##TYPE_NAME *self_ptr, BinaryTree##TYPE_NAME *current_tree, void *user_data) \
{ \
} \
\
void BinaryTree##TYPE_NAME##RecurseDFSPreorder( \
	BinaryTree##TYPE_NAME *self_ptr, BinaryTree##TYPE_NAME *current_tree, void *user_data) \
{ \
} \
\
void BinaryTree##TYPE_NAME##RecurseDFSInorder( \
	BinaryTree##TYPE_NAME *self_ptr, BinaryTree##TYPE_NAME *current_tree, void *user_data) \
{ \
} \
\
void BinaryTree##TYPE_NAME##RecurseDFSPostorder( \
	BinaryTree##TYPE_NAME *self_ptr, BinaryTree##TYPE_NAME *current_tree, void *user_data) \
{ \
} \

DEFINE_BINARYTREE_TYPE(int, Int)
// DEFINE_BINARYTREE_TYPE(float, Float)
// DEFINE_BINARYTREE_TYPE(double, Double)
// DEFINE_BINARYTREE_TYPE(long long, LongLong)
// DEFINE_BINARYTREE_TYPE(char, Char)
// DEFINE_BINARYTREE_TYPE(short, Short)

#endif//__HEADER_GUARD_BINARYTREE_PRIMITIVE__
