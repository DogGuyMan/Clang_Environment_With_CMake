#include <stdio.h>
#include <stdlib.h>
#include "linkedlist_demo.h"

void print_all_linkedlist_items(LinkedList* lkdlst) {
	int list_size_cache = lkdlst->m_size;
	printf("print %d's elements : ", list_size_cache);
	lkdlst->m_head_node_ptr = lkdlst->m_start_node_ptr;
	for(int i = 0; i < list_size_cache; i++) {
		GENERIC_DATA_TYPE * gd = lkdlst->current_data(lkdlst);
		if(gd != NULL && gd->m_generic_data_ptr != NULL) {
			int * out_data_ptr = (int*)gd->m_generic_data_ptr;
			printf("%d ", *out_data_ptr);
			lkdlst->m_head_node_ptr = lkdlst->m_head_node_ptr->m_right;
		}
	}
	lkdlst->m_head_node_ptr = lkdlst->m_start_node_ptr;
	printf("\n");
}


int linkedlist_demo()
{

	LinkedList* linkedList = CreateLinkedList(TYPE_INT, sizeof(int));


	GENERIC_DATA_TYPE data;

	data = GenerateDataInt(10);

	linkedList->append(linkedList,  data);

	DestroyGeneric(&data);

	data = GenerateDataInt(20);

	linkedList->prepend(linkedList, data);

	DestroyGeneric(&data);

	data = GenerateDataInt(30);


	linkedList->prepend(linkedList, data);

	DestroyGeneric(&data);

	data = GenerateDataInt(40);

	linkedList->prepend(linkedList, data);

	DestroyGeneric(&data);

	print_all_linkedlist_items(linkedList);


	data = linkedList->remove_first(linkedList);

	DestroyGeneric(&data);


	print_all_linkedlist_items(linkedList);

	data = linkedList->remove_last(linkedList);

	DestroyGeneric(&data);

	print_all_linkedlist_items(linkedList);

	data = linkedList->remove_last(linkedList);

	DestroyGeneric(&data);

	print_all_linkedlist_items(linkedList);

	data = linkedList->remove_last(linkedList);

	DestroyGeneric(&data);

	print_all_linkedlist_items(linkedList);

    for(int i = 0; i < 100; i++) {
		data = GenerateDataInt(i);
		linkedList->append(linkedList, data);
		DestroyGeneric(&data);
    }

	print_all_linkedlist_items(linkedList);


	linkedList->clear(linkedList);


	print_all_linkedlist_items(linkedList);


	DestroyLinkedList(linkedList);

    /*
    Leak: 0x122f040f0  size=112  zone: MallocStackLoggingLiteZone_0x102ac0000   malloc in InitLinkedList  C  Project
        Call stack: 0x1805b4274 (dyld) start | 0x102a53708 (Project) main  main.c:8 | 0x102a537a4 (Project) InitLinkedList  linkedlist.c:7 | 0x18076e894 (libsystem_malloc.dylib) _malloc_zone_malloc_instrumented_or_legacy

    Clear은 그저 linkedList의 내용물을 모두 지우는 것이지 linkedList 자체를 지우는 것이 아니다.
    따라서 linkedList를 free해주어야 한다.
    */

    return 1;
}

/*
*/

void ForeachLinkedListChar(LinkedListChar * llc) {
	if(llc->size(llc) == 0) {
		printf("linked list char empty\n");
	}
	llc->m_head_node_ptr = llc->m_start_node_ptr;
	while(llc->m_head_node_ptr != NULL) {
		printf("%c", llc->current_data(llc));
		llc->m_head_node_ptr = llc->m_head_node_ptr->m_right;
	}
	llc->m_head_node_ptr = llc->m_start_node_ptr;
	printf("\n");
}

int linkedlist_primitive_demo()
{
	LinkedListChar * llc = CreateLinkedListChar();

	ForeachLinkedListChar(llc);


	printf("Hello Linked List Experiment\n");

	llc->append(llc, 'H');
	llc->append(llc, 'E');
	llc->append(llc, 'L');
	llc->append(llc, 'L');
	llc->append(llc, 'O');

	ForeachLinkedListChar(llc);

	printf("WORLD Linked List Experiment\n");

	llc->prepend(llc, ' ');

	llc->prepend(llc, 'D');
	llc->prepend(llc, 'L');
	llc->prepend(llc, 'R');
	llc->prepend(llc, 'O');
	llc->prepend(llc, 'W');

	ForeachLinkedListChar(llc);

	for(int i = 0; i < 5; i++) {
		printf("%c\n", llc->remove_last(llc));
	}

	ForeachLinkedListChar(llc);

	for(int i = 0; i < 5; i++) {
		printf("%c\n", llc->remove_first(llc));
	}

	ForeachLinkedListChar(llc);

	printf("cur size : %zu\n", llc->size(llc));
	while(llc->size(llc) != 0) {
		llc->remove_last(llc);
	}
	printf("cur size : %zu\n", llc->size(llc));

	llc->clear(llc);

	DestroyLinkedListChar(llc);

    return 1;
}
