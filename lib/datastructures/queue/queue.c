#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* CreateQueue() {
	Queue * temp_queue = (Queue*) malloc(sizeof(Queue));
	LinkedList * temp_linked_list = CreateLinkedList();
	temp_queue->m_container = temp_linked_list;
	temp_queue->m_size = 0;
	temp_queue->m_capacity = 0;

	temp_queue->size = Size;
	temp_queue->capacity = Capacity;
	temp_queue->is_empty = IsEmpty;
	temp_queue->front = Front;
	temp_queue->dequeue = Dequeue;
	temp_queue->enqueue = Enqueue;
	return temp_queue;
}

void DestroyQueue(Queue* self_ptr) {
	LinkedList * container = self_ptr->m_container;
	DestroyLinkedList(container);
	self_ptr->m_container = NULL;
	self_ptr->m_size = 0;
	self_ptr->m_capacity = 0;

	self_ptr->size = NULL;
	self_ptr->capacity = NULL;
	self_ptr->is_empty = NULL;
	self_ptr->front = NULL;
	self_ptr->dequeue = NULL;
	self_ptr->enqueue = NULL;
	free(self_ptr);
}

int Size (struct Queue * self_ptr) {
	return self_ptr->m_size;
}

int Capacity (struct Queue* self_ptr) {
	return self_ptr->m_capacity;
}

bool IsEmpty (struct Queue* self_ptr) {
	return self_ptr->m_size == 0;
}

int Front (struct Queue* self_ptr) {
	LinkedList * container = self_ptr->m_container;
	return container->startPtr->data;
}

int Dequeue (struct Queue* self_ptr) {
	LinkedList * container = self_ptr->m_container;
	int res = container->remove_first(container);
	self_ptr->m_size = container->size;
	return res;
}

void Enqueue (struct Queue* self_ptr, int item) {
	LinkedList * container = self_ptr->m_container;
	container->append(container, item);
	self_ptr->m_size = container->size;
}
