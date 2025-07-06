#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "priority_queue.h"

static const PriorityQueue DEFAULT_PRIORITY_QUEUE_VTABLE_TEMPLATE = {
	.m_container = NULL,
	.compare = NULL,
	.size = PriorityQueueSize,
	.is_empty = PriorityQueueIsEmpty,
	.insert = PriorityQueueInsert,
	.delete = PriorityQueueDelete,
	.top = PriorityQueueTop,
	.pop = PriorityQueuePop,
	.sift_up = SiftUp,
	.sift_down = SiftDown,
	.heapify = Heapify
};

PriorityQueue * CreatePriorityQueue(CompareFunction compare)  {
	PriorityQueue * temp_pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
	if(temp_pq == NULL) {
		perror("priority queue memory alloc failed\n");
		abort();
	}
	memcpy(temp_pq, &DEFAULT_PRIORITY_QUEUE_VTABLE_TEMPLATE ,sizeof(PriorityQueue));
	temp_pq->m_container = CreateCompleteBinaryTree();
	if(temp_pq->m_container == NULL) {
		perror("container memory alloc failed\n");
		abort();
	}
	temp_pq->compare = compare;
	if(temp_pq->compare == NULL) {
		temp_pq->compare = MaxCompare;
	}
	return temp_pq;
}

// Build Heap in O(n) Complexity
PriorityQueue * BuildPriorityQueue(PriorityQueue * self_ptr, CompareFunction compare, int * array_ptr, unsigned array_size) {
	if(self_ptr == NULL) {
		self_ptr = CreatePriorityQueue(compare);
	}
	for(int i = 0; i < array_size; i++) {
		self_ptr->m_container->insert(self_ptr->m_container, *(array_ptr + i));
	}
	// int depth = self_ptr->m_container->max_depth(self_ptr->m_container)-1;
	for(int i = array_size; i >= 1; i--) {
		self_ptr->heapify(self_ptr->m_container, compare, i);
	}
	return self_ptr;
}

void DestroyPriorityQueue(PriorityQueue * self_ptr) {
	if(self_ptr == NULL) {
		perror("double free error\n");
		return;
	}
	if(self_ptr->m_container != NULL) {
		DestroyCompleteBinaryTree(self_ptr->m_container);
		self_ptr->m_container = NULL;
	}
	free(self_ptr);
}

int MaxCompare         (CompleteBinaryTree * const container_ptr, int a_node, int b_node){
	CompleteBinaryTree * container = container_ptr;
	BinaryTreeNodeInfo a_node_info = container->get_node(container, a_node);
	BinaryTreeNodeInfo b_node_info = container->get_node(container, b_node);
	// printf("[a node idx : %d, data %d]", a_node_info.m_idx, a_node_info.m_data);
	// printf("[b node idx : %d, data %d] result : %d\n", b_node_info.m_idx, b_node_info.m_data, a_node_info.m_data > b_node_info.m_data);
	if(a_node_info.m_data < b_node_info.m_data) return 1;
	if(a_node_info.m_data > b_node_info.m_data) return -1;
	return 0;
}

int MinCompare         (CompleteBinaryTree * const container_ptr, int a_node, int b_node){
	CompleteBinaryTree * container = container_ptr;
	BinaryTreeNodeInfo a_node_info = container->get_node(container, a_node);
	BinaryTreeNodeInfo b_node_info = container->get_node(container, b_node);
	if(a_node_info.m_data < b_node_info.m_data) return -1;
	if(a_node_info.m_data > b_node_info.m_data) return 1;
	return 0;
}

unsigned PriorityQueueSize       (PriorityQueue * const self_ptr){
	CompleteBinaryTree * container = self_ptr->m_container;
	return container->size(container);
}

bool PriorityQueueIsEmpty       (PriorityQueue * const self_ptr){
	CompleteBinaryTree * container = self_ptr->m_container;
	return container->size(container) == 0;
}

void PriorityQueueInsert         (PriorityQueue * const self_ptr, int item){
	CompleteBinaryTree * container = self_ptr->m_container;
	container->insert(container, item);
	// printf("insert %d, size : %d\n", container->size(container), item);
	self_ptr->sift_up(container, self_ptr->compare, container->size(container));
}

int PriorityQueueTop             (PriorityQueue * const self_ptr){
	CompleteBinaryTree * container = self_ptr->m_container;
	return container->get_node(container, 1).m_data;
}

int PriorityQueuePop             (PriorityQueue * const self_ptr){
	CompleteBinaryTree * container = self_ptr->m_container;
	BinaryTreeNodeInfo top_info = container->get_node(container, 1);
	// printf("[top \"%d\" | index : %d, data : %d ]", 1, top_info.m_idx, top_info.m_data);
	BinaryTreeNodeInfo last_info = container->get_node(container, container->size(container));
	// printf("[last \"%d\" | index : %d, data : %d]\n", container->size(container), last_info.m_idx, last_info.m_data);

	CompleteBinaryTreeSwapNode(container, top_info.m_idx, container->size(container));

	container->remove(container);
	// printf("sift_down start\n");
	self_ptr->sift_down(container, self_ptr->compare, 1);
	return top_info.m_data;
}

int PriorityQueueDelete         (PriorityQueue * const self_ptr, int index){
	printf("REMOVE \n");
	CompleteBinaryTree * container = self_ptr->m_container;
	BinaryTreeNodeInfo del_node = container->get_node(container, index);
	CompleteBinaryTreeSwapNode(container, index, container->size(container));
	container->remove(container);
	self_ptr->heapify(container, self_ptr->compare, index);
	return del_node.m_data;
}

int PriorityQueueRemove         (PriorityQueue * const self_ptr, int item){
	printf("REMOVE \n");
	CompleteBinaryTree * container = self_ptr->m_container;
	unsigned find_idx = 0;
	find_idx = (container->m_container->find(container->m_container, item) + 1);
	if(find_idx == 0) {abort();}
	int last_idx = container->size(container);
	CompleteBinaryTreeSwapNode(container, find_idx, last_idx);
	container->remove(container);
	self_ptr->heapify(container, self_ptr->compare, find_idx);
	return item;
}

void SiftUp          (CompleteBinaryTree * const container_ptr, CompareFunction compare, unsigned cur_node){
	if(compare == NULL) {
		perror("compare function not initialized\n");
		abort();
	}
	unsigned par_node = cur_node / 2;
        if(par_node == 0) return;
	if(compare(container_ptr, cur_node, par_node) == -1) {
		CompleteBinaryTreeSwapNode(container_ptr, cur_node, par_node);
		SiftUp(container_ptr, compare, par_node);
	}
}

void SiftDown        (CompleteBinaryTree * const container_ptr, CompareFunction compare, unsigned cur_node){
	if(compare == NULL) {
		perror("compare function not initialized\n");
		abort();
	}
	BinaryTreeNodeInfo left_node = container_ptr->left_child(container_ptr, cur_node);
    BinaryTreeNodeInfo right_node = container_ptr->right_child(container_ptr, cur_node);
	// printf("[left node idx : %d, data %d]", left_node.m_idx, left_node.m_data);
	// printf("[right node idx : %d, data %d]\n", right_node.m_idx, right_node.m_data);
	if(left_node.m_idx == 0 && right_node.m_idx == 0) return;
	if(left_node.m_idx == 0 || right_node.m_idx == 0) {
		if(left_node.m_idx == 0 && compare(container_ptr, cur_node, right_node.m_idx) == 1) {
			CompleteBinaryTreeSwapNode(container_ptr, cur_node, right_node.m_idx);
			SiftDown(container_ptr, compare, (unsigned) right_node.m_idx);
		}
		else if (right_node.m_idx == 0 && compare(container_ptr, cur_node, left_node.m_idx) == 1) {
			CompleteBinaryTreeSwapNode(container_ptr, cur_node, left_node.m_idx);
			SiftDown(container_ptr, compare, (unsigned) left_node.m_idx);
		}
	}
	else {
		// printf("both left right exists\n");
		if(compare(container_ptr, left_node.m_idx, right_node.m_idx) == 1 && compare(container_ptr, cur_node, right_node.m_idx) == 1) {
			// printf("swap with right\n");
			CompleteBinaryTreeSwapNode(container_ptr, cur_node, right_node.m_idx);
			SiftDown(container_ptr, compare, (unsigned) right_node.m_idx);
		}
		else if (compare(container_ptr, left_node.m_idx, right_node.m_idx) == -1 && compare(container_ptr, cur_node, left_node.m_idx) == 1){
			// printf("swap with left\n");
			CompleteBinaryTreeSwapNode(container_ptr, cur_node, left_node.m_idx);
			SiftDown(container_ptr, compare, (unsigned) left_node.m_idx);
		}
	}
}

void Heapify (CompleteBinaryTree * const container_ptr, CompareFunction compare, unsigned cur_node){
   if(container_ptr == NULL) {
        perror("Container is NULL\n");
        abort();
    }

	if(compare == NULL) {
		perror("compare function not initialized\n");
		abort();
	}
	unsigned container_size = container_ptr->size(container_ptr);

    // 범위 검증
    if(cur_node == 0 || cur_node > container_size) {
        return;  // 유효하지 않은 노드
    }

	BinaryTreeNodeInfo left_node = container_ptr->left_child(container_ptr, cur_node);
    BinaryTreeNodeInfo right_node = container_ptr->right_child(container_ptr, cur_node);
	 // 애초에 좌측 노드가 없으면 자식 노드가 없는거가 명확함
	if(left_node.m_idx == 0) return;
	unsigned swap_node = left_node.m_idx;

	if(right_node.m_idx != 0 && compare(container_ptr, left_node.m_idx, right_node.m_idx) == 1) {
		swap_node = right_node.m_idx;
	}
	if(compare(container_ptr, cur_node, swap_node) == 1){
		CompleteBinaryTreeSwapNode(container_ptr, cur_node, swap_node);
		Heapify(container_ptr, compare, swap_node);
	}
}
