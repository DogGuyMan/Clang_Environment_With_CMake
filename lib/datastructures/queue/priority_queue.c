#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include "priority_queue.h"

int Compare         (PriorityQueue * const self_ptr, int a_node, int b_node){
	CompleteBinaryTree * container = self_ptr->m_container;
	BinaryTreeNodeInfo a_node_info = container->get_node(container, a_node);
	BinaryTreeNodeInfo b_node_info = container->get_node(container, b_node);
	if(a_node_info.m_data == b_node_info.m_data) return 0;
	if(a_node_info.m_data > b_node_info.m_data) return -1;
	if(a_node_info.m_data < b_node_info.m_data) return 1;
	abort();
}

unsigned Size       (PriorityQueue * const self_ptr){
	CompleteBinaryTree * container = self_ptr->m_container;
	return container->size(container); 
}

bool IsEmpty       (PriorityQueue * const self_ptr){
	CompleteBinaryTree * container = self_ptr->m_container;
	return container->size(container) == 0;
}

void Insert         (PriorityQueue * const self_ptr, int item){
	CompleteBinaryTree * container = self_ptr->m_container;
	container->insert(container, item);
	self_ptr->sift_up(container, container->size(container));
}

int Top             (PriorityQueue * const self_ptr){
	CompleteBinaryTree * container = self_ptr->m_container;
	return container->get_node(container, 1).m_data;
}

int Pop             (PriorityQueue * const self_ptr){
	CompleteBinaryTree * container = self_ptr->m_container;
	BinaryTreeNodeInfo top_info = container->get_node(container, 1);
	CompleteBinaryTreeSwapNode(container, top_info.m_idx, container->size(container)); 
	container->remove(container);
	self_ptr->sift_down(container, 1);
	return top_info.m_data;
}

int Remove         (PriorityQueue * const self_ptr, int item){
	CompleteBinaryTree * container = self_ptr->m_container;
	unsigned find_idx = container->m_container->find(container->m_container, item);
	CompleteBinaryTreeSwapNode(container, find_idx + 1, container->size(container));
	container->remove(container);
	self_ptr->heapfiy(container);
	return item;
}

void SiftUp          (CompleteBinaryTree * const self_ptr,int cur_node){

}

void SiftDown        (CompleteBinaryTree * const self_ptr,int cur_node){

}

void Heapfiy        (CompleteBinaryTree * const container_ptr){

}

