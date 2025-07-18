#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

Node * CreateNode(GENERIC_DATA_TYPE data) {
    Node * newNode = malloc(sizeof(Node));

	if(newNode == NULL) {
		perror("노드 메모리 할당 실패\n");
		abort();
	}

	newNode->data_ptr = malloc(sizeof(GENERIC_DATA_TYPE));
	*(newNode->data_ptr) = (GENERIC_DATA_TYPE) {
		.m_type = data.m_type,
		.m_generic_data_ptr = NULL,
		.m_size = data.m_size,
	};
	newNode->data_ptr->m_generic_data_ptr = malloc(data.m_size);
	memcpy(newNode->data_ptr->m_generic_data_ptr, data.m_generic_data_ptr, data.m_size);

	newNode->m_left = NULL;
	newNode->m_right = NULL;

	return newNode;
}

void DestroyNode(Node * self_ptr) {
	if(self_ptr == NULL && self_ptr->data_ptr == NULL) {
		perror("노드 더블 프리 에러");
		abort();
	}
	DestroyGeneric(self_ptr->data_ptr);
	free(self_ptr->data_ptr);
	self_ptr->m_left = NULL;
    self_ptr->m_right = NULL;
    free(self_ptr);
}

LinkedList * CreateLinkedList(DATA_TYPE data_type, size_t data_size) {
    LinkedList * newLinkedList = malloc(sizeof(LinkedList));

	if(newLinkedList == NULL) {
		perror("링크드 리스트 메모리 할당 실패\n");
		abort();
	}

	newLinkedList->m_data_type = data_type;
	newLinkedList->m_data_size = data_size;
    newLinkedList->m_start_node_ptr = NULL;
    newLinkedList->m_head_node_ptr = NULL;
    newLinkedList->m_tail_node_ptr = NULL;
    newLinkedList->m_size = 0;

    newLinkedList->append = LinkedListAppend;
    newLinkedList->prepend = LinkedListPrepend;
    newLinkedList->current_data = LinkedListCurrentData;
    newLinkedList->remove_first = LinkedListRemoveFirst;
    newLinkedList->remove_last = LinkedListRemoveLast;
    newLinkedList->clear = LinkedListClear;

    return newLinkedList;
}

void AddNodeFirstTime(LinkedList * selfPointer, GENERIC_DATA_TYPE data) {
	selfPointer->m_head_node_ptr = CreateNode(data);
    selfPointer->m_start_node_ptr = selfPointer->m_head_node_ptr;
    selfPointer->m_tail_node_ptr = selfPointer->m_head_node_ptr;
    selfPointer->m_size = 1;
}

void LinkedListPrepend(LinkedList * selfPointer, GENERIC_DATA_TYPE data) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->m_start_node_ptr == NULL) { AddNodeFirstTime(selfPointer, data); return;}

    Node * newNode = CreateNode(data);
    Node * startNode = selfPointer->m_start_node_ptr;

    startNode->m_left = newNode;
    newNode->m_right = startNode;

    selfPointer->m_start_node_ptr = newNode;
    selfPointer->m_size++;
}

void LinkedListAppend(LinkedList * selfPointer, GENERIC_DATA_TYPE data) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->m_tail_node_ptr == NULL) {
		AddNodeFirstTime(selfPointer, data);
		return;
	}

    Node * newNode = CreateNode(data);
    Node * tailNode = selfPointer->m_tail_node_ptr;

    tailNode->m_right = newNode;
    newNode->m_left = tailNode;

    selfPointer->m_tail_node_ptr = newNode;
    selfPointer->m_size++;
}

GENERIC_DATA_TYPE * LinkedListCurrentData(LinkedList * selfPointer) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->m_head_node_ptr == NULL) {
        printf("size가 0인데 리스트 값을 접근하려고 함\n");
        abort();
    }
    return selfPointer->m_head_node_ptr->data_ptr;
}

void LinkedListClear(LinkedList * selfPointer) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->m_size == 0 && selfPointer->m_head_node_ptr == NULL) {
		return;
    }
    selfPointer->m_head_node_ptr = selfPointer->m_start_node_ptr;
	GENERIC_DATA_TYPE rm_target;
    while(selfPointer->m_head_node_ptr != NULL) {
        rm_target = LinkedListRemoveFirst(selfPointer);
		DestroyGeneric(&rm_target);
    }
    selfPointer->m_head_node_ptr = NULL;
    selfPointer->m_start_node_ptr = NULL;
    selfPointer->m_tail_node_ptr = NULL;
	selfPointer->m_size = 0;
}

GENERIC_DATA_TYPE LinkedListRemoveFinal(LinkedList * selfPointer, Node * free_target) {
	if(selfPointer->m_size > 1) {
		printf("Not Linked Lists Final Item");
		abort();
	}
	GENERIC_DATA_TYPE final_data = (GENERIC_DATA_TYPE) {
		.m_type = free_target->data_ptr->m_type,
		.m_generic_data_ptr = NULL,
		.m_size = free_target->data_ptr->m_size,
	};
	if(TryAssignData(&final_data, free_target->data_ptr)) {
		DestroyNode(free_target);
		selfPointer->m_head_node_ptr = NULL;
    	selfPointer->m_start_node_ptr = NULL;
    	selfPointer->m_tail_node_ptr = NULL;
		selfPointer->m_size = 0;
		return final_data;
	}
	return ERROR_GENERIC_DATA_TYPE_VTABLE_TEMPLATE;
}

GENERIC_DATA_TYPE LinkedListRemoveFirst(LinkedList * selfPointer) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->m_start_node_ptr == NULL) {
        printf("size가 0인데 리스트 값을 접근하려고 함\n");
        abort();
    }
    Node * freeTargetNode = selfPointer->m_start_node_ptr;
    if(selfPointer->m_size == 1) {
		return LinkedListRemoveFinal(selfPointer, freeTargetNode);
	}
	selfPointer->m_start_node_ptr = selfPointer->m_start_node_ptr->m_right;
	freeTargetNode->m_right->m_left = NULL;
    GENERIC_DATA_TYPE first_data = (GENERIC_DATA_TYPE) {
		.m_type = freeTargetNode->data_ptr->m_type,
		.m_generic_data_ptr = NULL,
		.m_size = freeTargetNode->data_ptr->m_size,
	};
	if(TryAssignData(&first_data, freeTargetNode->data_ptr)) {
		DestroyNode(freeTargetNode);
		selfPointer->m_head_node_ptr = selfPointer->m_start_node_ptr;
		selfPointer->m_size--;
		return first_data;
	}
	return ERROR_GENERIC_DATA_TYPE_VTABLE_TEMPLATE;
}

GENERIC_DATA_TYPE LinkedListRemoveLast(LinkedList * selfPointer) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    if(selfPointer->m_tail_node_ptr == NULL) {
        printf("size가 0인데 리스트 값을 접근하려고 함\n");
        abort();
    }
    Node * freeTargetNode = selfPointer->m_tail_node_ptr;
	if(selfPointer->m_size == 1) {
		return LinkedListRemoveFinal(selfPointer, freeTargetNode);
	}
	selfPointer->m_tail_node_ptr = selfPointer->m_tail_node_ptr->m_left;
	freeTargetNode->m_left->m_right = NULL;
    GENERIC_DATA_TYPE last_data = (GENERIC_DATA_TYPE) {
		.m_type = freeTargetNode->data_ptr->m_type,
		.m_generic_data_ptr = NULL,
		.m_size = freeTargetNode->data_ptr->m_size,
	};
	if(TryAssignData(&last_data, freeTargetNode->data_ptr)) {
		DestroyNode(freeTargetNode);
		selfPointer->m_head_node_ptr = selfPointer->m_tail_node_ptr;
		selfPointer->m_size--;
		return last_data;
	}
	return ERROR_GENERIC_DATA_TYPE_VTABLE_TEMPLATE;
}

void DestroyLinkedList(LinkedList * selfPointer) {
    if(selfPointer == NULL) {
        printf("Linked List Not Initialized\n");
        abort();
    }
    LinkedListClear(selfPointer);
    free(selfPointer);
}
