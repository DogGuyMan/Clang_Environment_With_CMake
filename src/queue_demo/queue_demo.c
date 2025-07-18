#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdbool.h>

#include "queue_demo.h"

Vector * G[1010] = {NULL, };
Queue * queue = NULL;
// CircularQueue * circular_queue = NULL;

bool is_visit[1010] = {0,};
int N = 0, M = 0;

int queue_demo(int argc, char* argv[]) {
	const char* RESOURCE_PATH = strcat(dirname(argv[0]), "/resources/backjoon_2606_input.txt");
	printf("input resource path : %s\n", RESOURCE_PATH);

	FILE* file = fopen(RESOURCE_PATH, "r");
	if(!file) {
		perror("file open failed\n");
		return EXIT_FAILURE;
	}
	printf("Open %s\n", RESOURCE_PATH);

	char line_buffer[256] = {0,};
	if(fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
		line_buffer[strcspn(line_buffer, "\n")] = '\0';
		if(sscanf(line_buffer, "%d", &N) == 1) {
			printf("input format counts %d, input N parsed well %d\n", 1, N);
		}
	}

	if(fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
		line_buffer[strcspn(line_buffer, "\n")] = '\0';
		if(sscanf(line_buffer, "%d", &M) == 1) {
			printf("input format counts %d, input M parsed well %d\n", 1, M);
		}
	}

	for(int i = 1; i <= N; i++) {
		G[i] = CreateVectorDefault(TYPE_INT, sizeof(int));
	}

	for(int i = 1; i <= M; i++) {
		if(fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
			line_buffer[strcspn(line_buffer, "\n")] = '\0';
			int S = -1, E = -1;
			if(sscanf(line_buffer, "%d %d", &S, &E) == 2) {
				printf("input format counts %d, S : %d --> E : %d\n", 2, S, E);
				GENERIC_DATA_TYPE GDs[2] = {
					GenerateDataInt(S),
					GenerateDataInt(E),
				};
				G[S]->push(G[S], GDs[1]);
				G[E]->push(G[E], GDs[0]);
				DestroyGeneric(GDs + 1);
				DestroyGeneric(GDs + 0);
			}
		}
	}

	queue = CreateQueue(TYPE_INT, sizeof(int));
	GENERIC_DATA_TYPE data;

	data = GenerateDataInt(1);
	queue->enqueue(queue, data);
	DestroyGeneric(&data);

	int infected_count = 0;
	while(!queue->is_empty(queue)) {

		data = queue->dequeue(queue);
		int dequeue_res = *((int*)data.m_generic_data_ptr);
		DestroyGeneric(&data);

		if(is_visit[dequeue_res] == true) continue;
		is_visit[dequeue_res] = true;
		printf("infected! %d\n", dequeue_res);
		infected_count++;
		Vector* adj_vec = G[dequeue_res];
		for(int i = 0; i < adj_vec->size(adj_vec); i++) {
			int nxt = *((int*)adj_vec->at(adj_vec, i)->m_generic_data_ptr);
			if(is_visit[nxt]) continue;
			data = GenerateDataInt(nxt);
			queue->enqueue(queue, data);
			DestroyGeneric(&data);
		}
	}

	printf("infected_count %d\n", infected_count -1);

	for(int i = 1; i <= N; i++) {
		DestroyVector(G[i], NULL);
	}
	DestroyQueue(queue);

	return 1;
}

int circular_queue_demo(int argc, char* argv[]) {

	bool is_visit[1010] = {0,};
	int N = 0, M = 0;

	const char* RESOURCE_PATH = strcat(dirname(argv[0]), "/resources/backjoon_2606_input.txt");
	printf("input resource path : %s\n", RESOURCE_PATH);

	FILE* file = fopen(RESOURCE_PATH, "r");
	if(!file) {
		perror("file open failed\n");
		return EXIT_FAILURE;
	}
	printf("Open %s\n", RESOURCE_PATH);

	char line_buffer[256] = {0,};
	if(fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
		line_buffer[strcspn(line_buffer, "\n")] = '\0';
		if(sscanf(line_buffer, "%d", &N) == 1) {
			printf("input format counts %d, input N parsed well %d\n", 1, N);
		}
	}

	if(fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
		line_buffer[strcspn(line_buffer, "\n")] = '\0';
		if(sscanf(line_buffer, "%d", &M) == 1) {
			printf("input format counts %d, input M parsed well %d\n", 1, M);
		}
	}

	VectorInt * G[1010] = {NULL, };
	for(int i = 1; i <= N; i++) {
		G[i] = CreateVectorIntDefault();
	}

	for(int i = 1; i <= N; i++) {
		if(fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
			line_buffer[strcspn(line_buffer, "\n")] = '\0';
		}
		int S = -1, E = -1;
		if(sscanf(line_buffer, "%d %d", &S, &E) == 2) {
				printf("input format counts %d, S : %d --> E : %d\n", 2, S, E);
				G[S]->push_back(G[S], E);
				G[E]->push_back(G[E], S);
		}
	}

	CircularQueueInt * cq = CreateCircularQueueInt(1010);
	cq->enqueue(cq, 1);

	int infected_count = 0;
	while(!cq->is_empty(cq)) {
		int dequeue_data = cq->dequeue(cq);
		if(is_visit[dequeue_data] == true) continue;
		is_visit[dequeue_data] = true;
		printf("infected! %d\n", dequeue_data);
		infected_count++;
		VectorInt* adj_vec = G[dequeue_data];
		for(int i = 0; i < adj_vec->size(adj_vec); i++) {
			int nxt = *(adj_vec->at(adj_vec, i));
			if(is_visit[nxt]) continue;
			cq->enqueue(cq, nxt);
		}
	}

	printf("infected_count %d\n", infected_count -1);

	for(int i = 1; i <= N; i++) {
		DestroyVectorInt(G[i]);
	}
	DestroyCircularQueueInt(cq);

	return 1;
}

// static int inputs[]              = {10, 3, 2, 5, 9, 4, 6, 7, 8, 1};
// void swap(int * a, int * b) {
// 	int temp = *a;
// 	*a = *b;
// 	*b = temp;
// }

// void test_pq(const char * HEAP_TYPE, CompareFunction compare) {
// 	PriorityQueue * heap = BuildPriorityQueue(CreatePriorityQueue(compare), compare, inputs, 10);
// 	printf("%s : ", HEAP_TYPE);
// 	for(int i = 1; i <= heap->size(heap); i++) {
// 		printf("%d ", heap->m_container->get_node(heap->m_container, i).m_data);
// 	}
// 	printf("\n");
// 	printf("iterate %s heap : ", HEAP_TYPE);
// 	for(int i = 1; i <= 10; i++) {
// 		printf("%d ", heap->m_container->get_node(heap->m_container, i).m_data);
// 	}
// 	printf("\n");

// 	printf("pop %s heap : \n", HEAP_TYPE);
// 	for(int i = 1; i <= 10; i++) {
// 		printf("pop : %d : ", heap->pop(heap));
// 		for(int i = 1; i <= heap->size(heap); i++) {
// 			printf("%d ", heap->m_container->get_node(heap->m_container, i).m_data);
// 		}
// 		printf("\n");
// 	}
// 	printf("\n");

// 	printf("%s heap currernt size %d\n", HEAP_TYPE, heap->size(heap));
// 	DestroyPriorityQueue(heap);
// }

// void test_remove(const char * HEAP_TYPE, CompareFunction compare) {
// 	PriorityQueue * heap = BuildPriorityQueue(CreatePriorityQueue(compare), compare, inputs, 10);

// 	printf("%s : ", HEAP_TYPE);
// 	for(int i = 1; i <= heap->size(heap); i++) {
// 		printf("%d ", heap->m_container->get_node(heap->m_container, i).m_data);
// 	}
// 	printf("\n");

// 	printf("%s heap currernt size %d\n", HEAP_TYPE, heap->size(heap));
// 	for(int i = 1; i <= 10; i++) {
// 		unsigned del_item = (heap->size(heap)) / 2;
// 		printf("remove : %d : ", heap->delete(heap, del_item));
// 		for(int i = 1; i <= heap->size(heap); i++) {
// 			printf("%d ", heap->m_container->get_node(heap->m_container, i).m_data);
// 		}
// 		printf("\n");
// 	}
// 	printf("%s heap currernt size %d\n", HEAP_TYPE, heap->size(heap));

// 	DestroyPriorityQueue(heap);
// }

// int priority_queue_demo(int argc, char * argv[]) {

// 	// test_pq("max", MaxCompare);
// 	// test_pq("min", MinCompare);
// 	test_remove("max", MaxCompare);
// 	return 0;
// }
