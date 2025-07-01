#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdbool.h>

#include "queue_demo.h"

Vector * G[1010] = {NULL, };
Queue * queue = NULL;
CircularQueue * circular_queue = NULL;

bool IsVisit[1010] = {0,};
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
		G[i] = CreateVector(0);
	}

	for(int i = 1; i <= M; i++) {
		if(fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
			line_buffer[strcspn(line_buffer, "\n")] = '\0';
			int S = -1, E = -1;
			if(sscanf(line_buffer, "%d %d", &S, &E) == 2) {
				printf("input format counts %d, S : %d --> E : %d\n", 2, S, E);
				G[S]->push(G[S], E);
				G[E]->push(G[E], S);
			}
		}
	}

	queue = CreateQueue();

	queue->enqueue(queue, 1);
	int infected_count = 0;
	while(!queue->is_empty(queue)) {
		int dequeue_res = queue->dequeue(queue);
		if(IsVisit[dequeue_res] == true) continue;
		IsVisit[dequeue_res] = true;
		printf("infected! %d\n", dequeue_res);
		infected_count++;
		Vector* adj_vec = G[dequeue_res];
		for(int i = 0; i < adj_vec->size(adj_vec); i++) {
			int nxt = adj_vec->at(adj_vec, i);
			if(IsVisit[nxt]) continue;
			queue->enqueue(queue, nxt);
		}
	}

	printf("infected_count %d\n", infected_count -1);

	for(int i = 1; i <= N; i++) {
		DestroyVector(G[i]);
	}
	DestroyQueue(queue);

	return 1;
}

int circular_queue_demo(int argc, char* argv[]) {
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
		G[i] = CreateVector(0);
	}

	for(int i = 1; i <= M; i++) {
		if(fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
			line_buffer[strcspn(line_buffer, "\n")] = '\0';
			int S = -1, E = -1;
			if(sscanf(line_buffer, "%d %d", &S, &E) == 2) {
				printf("input format counts %d, S : %d --> E : %d\n", 2, S, E);
				G[S]->push(G[S], E);
				G[E]->push(G[E], S);
			}
		}
	}

	circular_queue = CreateCircularQueue(1010);

	circular_queue->enqueue(circular_queue, 1);
	int infected_count = 0;
	while(!circular_queue->is_empty(circular_queue)) {
		int dequeue_res = circular_queue->dequeue(circular_queue);
		if(IsVisit[dequeue_res] == true) continue;
		IsVisit[dequeue_res] = true;
		printf("infected! %d\n", dequeue_res);
		infected_count++;
		Vector* adj_vec = G[dequeue_res];
		for(int i = 0; i < adj_vec->size(adj_vec); i++) {
			int nxt = adj_vec->at(adj_vec, i);
			if(IsVisit[nxt]) continue;
			circular_queue->enqueue(circular_queue, nxt);
		}
	}

	printf("infected_count %d\n", infected_count -1);

	for(int i = 1; i <= N; i++) {
		DestroyVector(G[i]);
	}
	DestroyCircularQueue(circular_queue);

	return 1;
}
