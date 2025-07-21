#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stack_primitive.h>
#include <circular_queue_primitive.h>
#include "tree.h"

static const BinaryTree__TYPE_NAME__ DEFAULT_BINARYTREE___TYPE_NAME__SPSP__VTABLE_TEMPLATE = {
	.m_data = 0,
	.m_size = 0,
	.m_max_depth = 0,
	.m_root = NULL,
	.m_current = NULL,
	.m_parent = NULL,
	.m_left_child = NULL,
	.m_right_child = NULL,

	.size 			= BinaryTree__TYPE_NAME___SPSP_Size,
	.max_depth 		= BinaryTree__TYPE_NAME___SPSP_MaxDepth,
	.left_child 	= BinaryTree__TYPE_NAME___SPSP_LeftChild,
	.right_child 	= BinaryTree__TYPE_NAME___SPSP_RightChild,
	.insert 		= BinaryTree__TYPE_NAME___SPSP_Insert,
	.get 			= BinaryTree__TYPE_NAME___SPSP_Get,
	.remove 		= BinaryTree__TYPE_NAME___SPSP_Remove,
};

BinaryTree__TYPE_NAME__ *                CreateBinaryTree__TYPE_NAME__(__TYPE__ data){
	BinaryTree__TYPE_NAME__ * temp_tree = malloc(sizeof(BinaryTree__TYPE_NAME__));
	if(temp_tree == NULL) {
		perror("바이너리 트리 메모리 할당 실패");
		return NULL;
	}
	memcpy(temp_tree, &DEFAULT_BINARYTREE___TYPE_NAME__SPSP__VTABLE_TEMPLATE, sizeof(BinaryTree__TYPE_NAME__));
	temp_tree->m_root = temp_tree;
	temp_tree->m_current = temp_tree;
	temp_tree->m_parent = NULL;
	temp_tree->m_data = data;
	temp_tree->m_size = 1;
	temp_tree->m_max_depth = 0;
	return temp_tree;
}

void                        DestroyBinaryTree__TYPE_NAME__(BinaryTree__TYPE_NAME__ * self_ptr){
	if(self_ptr == NULL) {
		perror("DestroyBinaryTree__TYPE_NAME__ 실패");
		return;
	}
	// printf("BinaryTree__TYPE_NAME___SPSP_Remove(self_ptr, self_ptr->m_root);");
	if(self_ptr->m_left_child != NULL)
		DestroyBinaryTree__TYPE_NAME__(self_ptr->m_left_child);
	if(self_ptr->m_right_child != NULL)
		DestroyBinaryTree__TYPE_NAME__(self_ptr->m_right_child);
	free(self_ptr);
}

size_t        			BinaryTree__TYPE_NAME___SPSP_Size(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree){
	if(self_ptr == NULL || current_tree == NULL)
	{
		perror("BinaryTreeSize : 인풋이 널임");
		return 0;
	}
	return current_tree->m_size;
}

/*
Start with Parent
*/
static void					BinaryTreeUpdateDepth(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree) {
	if(current_tree == NULL) {
		return;
	}
	if(current_tree->m_left_child == NULL && current_tree->m_right_child == NULL) { return; }

	size_t ldmax = 0, rdmax = 0, child_max = 0;
	if(current_tree->m_left_child != NULL) {
		ldmax = current_tree->m_left_child->m_max_depth;
	}
	if(current_tree->m_right_child != NULL) {
		rdmax = current_tree->m_right_child->m_max_depth;
	}
	child_max = (ldmax < rdmax) ? rdmax : ldmax;

	current_tree->m_max_depth = child_max + 1;

	if(current_tree != self_ptr->m_root) {
		BinaryTreeUpdateDepth(self_ptr, current_tree->m_parent);
	}
	return;
}

/*
Start with Parent
*/
static void					BinaryTreeUpdateSize(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree, size_t added_size) {
	if(current_tree == NULL) return;
	current_tree->m_size = current_tree->m_size + added_size;
	if(current_tree != self_ptr->m_root) {
		BinaryTreeUpdateSize(self_ptr, current_tree->m_parent, added_size);
	}
	return;
}

size_t        			BinaryTree__TYPE_NAME___SPSP_MaxDepth(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree) {
	return current_tree->m_max_depth;
}

BinaryTree__TYPE_NAME__ *        		BinaryTree__TYPE_NAME___SPSP_LeftChild(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree) {
	return current_tree->m_left_child;
}

BinaryTree__TYPE_NAME__ *        		BinaryTree__TYPE_NAME___SPSP_RightChild(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree) {
	return current_tree->m_right_child;
}


BinaryTree__TYPE_NAME__ *    			BinaryTree__TYPE_NAME___SPSP_Insert(
												BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree,
												BinaryTreeInsertMode insert_mode,
												BinaryTree__TYPE_NAME__ * insert_tree
										) {
	BinaryTree__TYPE_NAME__ * new_tree = NULL;
	if(self_ptr == NULL || current_tree == NULL || insert_tree == NULL)
	{
		perror("BinaryTreeInsert : 인풋이 널임");
		goto INSERT_FAIL;
	}

	new_tree = insert_tree;
	new_tree->m_root = current_tree->m_root;
	new_tree->m_parent = current_tree;

	switch (insert_mode)
	{
		case LEFT_INSERT_NODE : {
			if(current_tree->m_left_child != NULL) {
				perror("BinaryTreeInsert : 좌 자식이 비어 있지 않음");
				goto INSERT_FAIL;
			}
			current_tree->m_left_child = new_tree;
			break;
		}
		case RIGHT_INSERT_NODE : {
			if(current_tree->m_right_child != NULL) {
				perror("BinaryTreeInsert : 우 자식이 비어 있지 않음");
				goto INSERT_FAIL;
			}
			current_tree->m_right_child = new_tree;
			break;
		}
		default: {
			perror("BinaryTreeInsert : 이상한 삽입 모드\n");
			goto INSERT_FAIL;
		}
	}
	BinaryTreeUpdateSize(self_ptr, new_tree->m_parent, new_tree->m_size);	// one start
	BinaryTreeUpdateDepth(self_ptr, new_tree->m_parent); // zero depth

	return new_tree;

INSERT_FAIL :
	return NULL;
}

__TYPE__ 	BinaryTree__TYPE_NAME___SPSP_Get(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree){
	if(self_ptr == NULL || current_tree == NULL)
	{
		perror("BinaryTreeSize : 인풋이 널임");
		abort();
	}
	return current_tree->m_data;
}

BinaryTree__TYPE_NAME__ * BinaryTree__TYPE_NAME___SPSP_Remove(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * sub_tree) {

	if(sub_tree == self_ptr->m_root && sub_tree->m_parent == NULL) {
		perror("자기 자신을 지울수는 없음");
		abort();
	}
	if(self_ptr == NULL || sub_tree == NULL)
	{
		perror("BinaryTreeSize : 인풋이 널임");
		abort();
	}

	/*
	POST Order로 삭제해야 한다.
	*/
	BinaryTree__TYPE_NAME__ * rm_tree = sub_tree;
	BinaryTree__TYPE_NAME__ * parent_tree = sub_tree->m_parent;
	if(rm_tree->m_parent->m_left_child == sub_tree) {
		/*
		Left 삭제
		*/
		if(rm_tree->m_parent->m_right_child != NULL) {
			rm_tree->m_parent->m_max_depth = rm_tree->m_parent->m_right_child->m_max_depth + 1;
		}
		else {
			rm_tree->m_parent->m_max_depth = parent_tree->m_max_depth - (rm_tree->m_max_depth + 1);
		}
		rm_tree->m_parent->m_size = parent_tree->m_size - rm_tree->m_size;
		rm_tree->m_parent->m_left_child = NULL;

		rm_tree->m_parent = NULL;
		rm_tree->m_root = rm_tree;

	}
	else if(rm_tree->m_parent->m_right_child == sub_tree) {
		/*
		right 삭제
		*/
		if(rm_tree->m_parent->m_left_child != NULL) {
			rm_tree->m_parent->m_max_depth = rm_tree->m_parent->m_left_child->m_max_depth + 1;
		}
		else {
			rm_tree->m_parent->m_max_depth = parent_tree->m_max_depth - (rm_tree->m_max_depth + 1);
		}
		rm_tree->m_parent->m_size = parent_tree->m_size - rm_tree->m_size;
		rm_tree->m_parent->m_right_child = NULL;

		rm_tree->m_parent = NULL;
		rm_tree->m_root = rm_tree;
	}
	else {
		abort();
	}

	BinaryTreeUpdateSize(self_ptr, parent_tree->m_parent, -rm_tree->m_size);
	BinaryTreeUpdateDepth(self_ptr, parent_tree->m_parent);

	return rm_tree;
}

void BinaryTree__TYPE_NAME___SPSP_BFS(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree, void * user_data) {
	CircularQueueAddressType * bt_ptr_queue = CreateCircularQueueAddressType(1 << (self_ptr->m_max_depth + 1));

	int depth = 0;
	int size_by_depth = 1;
	BinaryTree__TYPE_NAME__ * head_tree;
	bt_ptr_queue->enqueue(bt_ptr_queue, (uintptr_t)current_tree);

	while(!bt_ptr_queue->is_empty(bt_ptr_queue) && depth <= self_ptr->max_depth(self_ptr, self_ptr)) {
		printf("cur %dth depth : ", depth);
		int new_size_by_depth = 0;

		CircularQueueAddressType * temp_bt_ptr_queue = CreateCircularQueueAddressType(size_by_depth * 2 + 1);
		for(int i = 0; i < size_by_depth; i++) {
			uintptr_t q_front = bt_ptr_queue->dequeue(bt_ptr_queue);

			if(q_front != 0) {
				head_tree = (BinaryTree__TYPE_NAME__ *)q_front;
				printf(" %d ", head_tree->get(self_ptr, head_tree));
			}
			else{
				printf(" - ");
				continue;
			}
			if(head_tree->m_left_child != NULL){
				temp_bt_ptr_queue->enqueue(temp_bt_ptr_queue, (uintptr_t)head_tree->m_left_child);
				new_size_by_depth++;
			}
			else {
				temp_bt_ptr_queue->enqueue(temp_bt_ptr_queue, 0);
				new_size_by_depth++;
			}

			if(head_tree->m_right_child != NULL){

				temp_bt_ptr_queue->enqueue(temp_bt_ptr_queue, (uintptr_t)head_tree->m_right_child);
				new_size_by_depth++;
			}
			else {
				temp_bt_ptr_queue->enqueue(temp_bt_ptr_queue, 0);
				new_size_by_depth++;
			}
		}
		while(!temp_bt_ptr_queue->is_empty(temp_bt_ptr_queue)) {
			bt_ptr_queue->enqueue(bt_ptr_queue, temp_bt_ptr_queue->dequeue(temp_bt_ptr_queue));
		}
		DestroyCircularQueueAddressType(temp_bt_ptr_queue);
		printf("\n");
		size_by_depth = new_size_by_depth;
		depth++;
	}

	DestroyCircularQueueAddressType(bt_ptr_queue);
}

void BinaryTree__TYPE_NAME___SPSP_LevelOrder(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree, void * user_data) {

}

void BinaryTree__TYPE_NAME___SPSP_RecurseDFSPreorder(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree, void * user_data) {

}

void BinaryTree__TYPE_NAME___SPSP_RecurseDFSInorder(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree, void * user_data) {

}

void BinaryTree__TYPE_NAME___SPSP_RecurseDFSPostorder(BinaryTree__TYPE_NAME__ * self_ptr, BinaryTree__TYPE_NAME__ * current_tree, void * user_data) {

}
