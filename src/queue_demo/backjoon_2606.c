#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdbool.h>
#include <errno.h>

typedef struct Vector Vector;

static struct Vector {
	int * m_array_ptr;
	int m_size;
	int m_capacity;

	int (*size) 	(struct Vector * self_ptr);
	int (*capacity)	(struct Vector * self_ptr);
	bool(*is_empty) (struct Vector * self_ptr);
	int (*at) 	(struct Vector * self_ptr, int index);
	void (*push) 	(struct Vector * self_ptr, int item);
	void (*insert) 	(struct Vector * self_ptr, int index, int item);
	void (*prepend) 	(struct Vector * self_ptr, int item);
	// return index
	int (*pop) 	(struct Vector * self_ptr);
	int (*find) 	(struct Vector * self_ptr, int item);
	int (*delete) 	(struct Vector * self_ptr, int index);
	int (*remove) 	(struct Vector * self_ptr, int item);
	int (*resize) 	(struct Vector * self_ptr, int new_capacity);
};

Vector* CreateVector(int capacity);
void 	DestroyVector(struct Vector * self_ptr);
int  	VectorSize 	(struct Vector * self_ptr);
int  	VectorCapacity	(struct Vector * self_ptr);
bool 	VectorIsEmpty	(struct Vector * self_ptr);
int  	VectorAt 	(struct Vector * self_ptr, int index);
void 	VectorPush 	(struct Vector * self_ptr, int item);
void 	VectorInsert 	(struct Vector * self_ptr, int index, int item);
void 	VectorPrepend 	(struct Vector * self_ptr, int item);
int  	VectorPop 	(struct Vector * self_ptr);
int  	VectorFind 	(struct Vector * self_ptr, int item);
int  	VectorDelete 	(struct Vector * self_ptr, int index);
int  	VectorRemove 	(struct Vector * self_ptr, int item);
int  	VectorReserve 	(struct Vector * self_ptr, int new_capacity);

static Vector* CreateVector(int capacity) {
	Vector* temp_vector = malloc(sizeof(Vector));
	temp_vector->m_array_ptr = NULL;
	if(capacity <= 16) {
		temp_vector->m_array_ptr = malloc(sizeof(int) * 16);
		temp_vector->m_capacity = 16;
	}
	else {
		temp_vector->m_array_ptr = malloc(sizeof(int) * capacity);
		temp_vector->m_capacity = capacity;
	}

	temp_vector->m_size = 0;
	temp_vector->size = VectorSize;
	temp_vector->capacity = VectorCapacity;
	temp_vector->is_empty = VectorIsEmpty;
	temp_vector->at = VectorAt;
	temp_vector->push = VectorPush;
	temp_vector->insert = VectorInsert;
	temp_vector->prepend = VectorPrepend;
	temp_vector->pop = VectorPop;
	temp_vector->find = VectorFind;
	temp_vector->delete = VectorDelete;
	temp_vector->remove = VectorRemove;
	temp_vector->resize = VectorReserve;
	return temp_vector;
}

static void DestroyVector(Vector* self_ptr) {
	free(self_ptr->m_array_ptr);
	self_ptr->m_size = 0;
	self_ptr->m_capacity = 0;

	self_ptr->size = NULL;
	self_ptr->capacity = NULL;
	self_ptr->is_empty = NULL;
	self_ptr->at = NULL;
	self_ptr->push = NULL;
	self_ptr->insert = NULL;
	self_ptr->prepend =  NULL;
	self_ptr->pop = NULL;
	self_ptr->find = NULL;
	self_ptr->delete = NULL;
	self_ptr->remove = NULL;
	self_ptr->resize = NULL;

	free(self_ptr);
}

static int  VectorSize(struct Vector * self_ptr)
{
	return self_ptr->m_size;
}

static int  VectorCapacity(struct Vector * self_ptr)
{
	return self_ptr->m_capacity;
}

static bool VectorIsEmpty(struct Vector * self_ptr)
{
	return self_ptr->m_size == 0;
}

static int  VectorAt(struct Vector * self_ptr, int index)
{
	return *(self_ptr->m_array_ptr + index);
}

static void VectorPush(struct Vector * self_ptr, int item)
{
	if(self_ptr == NULL) {
		printf("Vector Not Created\n");
		abort();
		return;
	}
	if(self_ptr->m_array_ptr == NULL) {
		printf("Vector Array Not Initialized\n");
		abort();
		return;
	}
	if(self_ptr->m_capacity <= self_ptr->m_size) {
		VectorReserve(self_ptr, self_ptr->m_size * 2);
	}
	*(self_ptr->m_array_ptr + self_ptr->m_size) = item;
	self_ptr->m_size++;
	return;
}

static void VectorInsert     (struct Vector * self_ptr, int index, int item){
	if(self_ptr == NULL) {
		printf("Vector Not Created\n");
		abort();
		return;
	}
	if(self_ptr->m_array_ptr == NULL) {
		printf("Vector Array Not Initialized\n");
		abort();
		return;
	}
	if(0 > index || index >= self_ptr->m_size) {
		printf("Index Out of Range\n");
		abort();
		return;
	}
	if(self_ptr->m_capacity <= self_ptr->m_size) {
		VectorReserve(self_ptr, self_ptr->m_size * 2);
	}
	int vector_size = self_ptr->m_size;
	for(int i = vector_size-1; i >= index; --i) {
		self_ptr->m_array_ptr[i+1] = self_ptr->m_array_ptr[i];
	}
	self_ptr->m_array_ptr[index] = item;
	++(self_ptr->m_size);
	return;
}

static void VectorPrepend    (struct Vector * self_ptr, int item) {
	self_ptr->insert(self_ptr, 0, item);
	return;
}

static int  VectorPop(struct Vector * self_ptr)
{
	if(self_ptr->m_size == 0) {
		printf("Vector is Empty\n");
		abort();
	}
	--(self_ptr->m_size);
	return  *(self_ptr->m_array_ptr + self_ptr->m_size);
}

static int  VectorFind       (struct Vector * self_ptr, int item) {
	int founded_index = -1;
	for(int i = 0; i < self_ptr->m_size; i++)
	{
		if(*(self_ptr->m_array_ptr + i) == item) {
			founded_index = i;
			break;
		}
	}
	return founded_index;
}

static int  VectorDelete     (struct Vector * self_ptr, int index)
{
	if(0 > index || index >= self_ptr->m_size) {
		printf("Index Out of Range\n");
		abort();
	}
	int deleted_item = self_ptr->m_array_ptr[index];
	for(int i = index; i < self_ptr->m_size-1; i++) {
		self_ptr->m_array_ptr[i] = self_ptr->m_array_ptr[i+1];
	}
	--(self_ptr->m_size);
	return deleted_item;
}

static int  VectorRemove     (struct Vector * self_ptr, int item)
{
	int founded_index = self_ptr->find(self_ptr, item);
	if(founded_index == -1) {
		return - 1;
	}
	return self_ptr->delete(self_ptr, founded_index);
}

static int  VectorReserve     (struct Vector * self_ptr, int new_capacity)
{
	int vector_size = self_ptr->m_size;
	int * new_array_ptr = (int*) malloc(sizeof(int) * new_capacity);
	if(new_array_ptr == NULL) {  // 추가
        printf("Memory allocation failed\n");
        return self_ptr->m_capacity;  // 기존 capacity 반환
    }
	for(int i = 0; i < vector_size; i++) {
		*(new_array_ptr + i) = *(self_ptr->m_array_ptr + i);
	}
	free(self_ptr->m_array_ptr);
	self_ptr->m_array_ptr = new_array_ptr;
	self_ptr->m_capacity = new_capacity;
	return new_capacity;
}

typedef struct CircularQueue CircularQueue;

struct CircularQueue {
	int * m_array_ptr;
	int m_size;
        int m_capacity;
	int m_front_idx;
	int m_rear_idx;

	int (* const size) (struct CircularQueue * self_ptr);
        int (* const capacity) (struct CircularQueue* self_ptr);
        bool (* const is_empty) (struct CircularQueue* self_ptr);
        int (* const front) (struct CircularQueue* self_ptr);
        int (* const dequeue) (struct CircularQueue* self_ptr);
        void (* const enqueue) (struct CircularQueue* self_ptr, int item);
	bool (* const is_full) (struct CircularQueue* self_ptr);
};

CircularQueue* CreateCircularQueue(int capacity);
void DestroyCircularQueue(struct CircularQueue* self_ptr);
int CircularQueueSize (struct CircularQueue * self_ptr);
int CircularQueueCapacity (struct CircularQueue* self_ptr);
bool CircularQueueIsEmpty (struct CircularQueue* self_ptr);
bool CircularQueueIsFull (struct CircularQueue* self_ptr);
int CircularQueueFront (struct CircularQueue* self_ptr);
int CircularQueueDequeue (struct CircularQueue* self_ptr);
void CircularQueueEnqueue (struct CircularQueue* self_ptr, int item);

static const CircularQueue DEFAULT_CIRCULAR_QUEUE_VTABLE_TEMPLATE = {
    .m_array_ptr = NULL,  // must be initialize after memcpy
    .m_size = 0,
    .m_capacity = 0,      // must be initialize after memcpy
    .m_front_idx = -1,
    .m_rear_idx = -1,
    .size = CircularQueueSize,
    .capacity = CircularQueueCapacity,
    .is_empty = CircularQueueIsEmpty,
    .front = CircularQueueFront,
    .dequeue = CircularQueueDequeue,
    .enqueue = CircularQueueEnqueue,
    .is_full = CircularQueueIsFull
};

static CircularQueue* CreateCircularQueue(int capacity){
	if(capacity <= 0) {
		perror("Invalid capacity\n");
		abort();
	}
	CircularQueue * temp_queue = (CircularQueue*) malloc(sizeof(CircularQueue));
	if(temp_queue == NULL) {
		perror("memory allocation failed\n");
		abort();
	}

	memcpy(temp_queue, &DEFAULT_CIRCULAR_QUEUE_VTABLE_TEMPLATE, sizeof(CircularQueue));

	temp_queue->m_array_ptr = (int*) malloc(sizeof(int) * capacity);
	if(temp_queue->m_array_ptr == NULL) {
		perror("memory allocation failed\n");
		abort();
	}
	temp_queue->m_capacity = capacity;
	return temp_queue;
}

static void DestroyCircularQueue(struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
		return;
	}
	if(self_ptr->m_array_ptr != NULL)
		free(self_ptr->m_array_ptr);

	free(self_ptr);
}

static int CircularQueueSize (struct CircularQueue * self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	return 	self_ptr->m_size;
}

static int CircularQueueCapacity (struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	return 	self_ptr->m_capacity;
}

static bool CircularQueueIsEmpty (struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	return 	self_ptr->m_size <= 0 &&
		self_ptr->m_front_idx == -1 &&
		self_ptr->m_rear_idx == -1;
}

static bool CircularQueueIsFull (struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	return 	self_ptr->m_size >= self_ptr->m_capacity;
}

static int CircularQueueFront (struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	if (self_ptr->is_empty(self_ptr)) {
        perror("Queue is empty\n");
        abort();
    }
	return *(self_ptr->m_array_ptr + self_ptr->m_front_idx);
}

static int CircularQueueDequeueFinal(struct CircularQueue* self_ptr) {
	if(self_ptr->is_empty(self_ptr)) {
		perror("invailed dequeue operation when is empty\n");
		abort();
	}
	if(self_ptr->m_front_idx != self_ptr->m_rear_idx) {
		perror("somting wrong in dequeue operation\n");
		abort();
	}
	int res = *(self_ptr->m_array_ptr + self_ptr->m_front_idx);
	self_ptr->m_front_idx = -1;
	self_ptr->m_rear_idx = -1;
	self_ptr->m_size = 0;
	return res;
}

static int CircularQueueDequeue (struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	if(self_ptr->m_capacity <= 0) {
                perror("queue's capacity is zero\n");
                abort();
        }

	if(self_ptr->is_empty(self_ptr)) {
		perror("invailed dequeue operation when is empty\n");
		abort();
	}
	if(self_ptr->m_size == 1) {return CircularQueueDequeueFinal(self_ptr);}
	int res = *(self_ptr->m_array_ptr + self_ptr->m_front_idx);
	self_ptr->m_front_idx += 1;
	self_ptr->m_front_idx = self_ptr->m_front_idx % self_ptr->m_capacity;
	--(self_ptr->m_size);
	return res;
}

static void CircularQueueEnqueueFirst(struct CircularQueue* self_ptr, int first_item) {
	if(self_ptr->m_capacity <= 0) {
		perror("queue's capacity is zero\n");
		abort();
	}
	self_ptr->m_front_idx = 0;
	self_ptr->m_rear_idx = 0;
	self_ptr->m_size = 1;
	*(self_ptr->m_array_ptr + 0) = first_item;
}

static void CircularQueueEnqueue (struct CircularQueue* self_ptr, int item){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	if(self_ptr->m_capacity <= 0) {
		perror("queue's capacity is zero\n");
		abort();
	}
	if(self_ptr->is_full(self_ptr)) {
		perror("queue's capacity is full\n");
		abort();
	}
	if(self_ptr->m_size == 0) {
		if(self_ptr->m_front_idx < 0 && self_ptr->m_rear_idx < 0) {
			CircularQueueEnqueueFirst(self_ptr, item);
			return;
		}
		else
		{
			perror("expected empty but index value is invalid\n");
			abort();
		}
	}
	self_ptr->m_rear_idx += 1;
	self_ptr->m_rear_idx = self_ptr->m_rear_idx % self_ptr->m_capacity;
	*(self_ptr->m_array_ptr + self_ptr->m_rear_idx) = item;
	++(self_ptr->m_size);
}

Vector * G[1010] = {NULL, };
CircularQueue * circular_queue = NULL;

bool IsVisit[1010] = {0,};
int N = 0, M = 0;


int main(int argc, char* argv[]) {

    scanf("%d\n%d", &N, &M);

	for(int i = 1; i <= N; i++) {
		G[i] = CreateVector(0);
	}

	for(int i = 1; i <= M; i++) {
        int S = -1, E = -1;
        scanf("%d %d", &S, &E);
        G[S]->push(G[S], E);
        G[E]->push(G[E], S);
	}

	circular_queue = CreateCircularQueue(1010);

	circular_queue->enqueue(circular_queue, 1);
	int infected_count = 0;
	while(!circular_queue->is_empty(circular_queue)) {
		int dequeue_res = circular_queue->dequeue(circular_queue);
		if(IsVisit[dequeue_res] == true) continue;
		IsVisit[dequeue_res] = true;
		infected_count++;
		Vector* adj_vec = G[dequeue_res];
		for(int i = 0; i < adj_vec->size(adj_vec); i++) {
			int nxt = adj_vec->at(adj_vec, i);
			if(IsVisit[nxt]) continue;
			circular_queue->enqueue(circular_queue, nxt);
		}
	}

	printf("%d\n", infected_count -1);

	for(int i = 1; i <= N; i++) {
		DestroyVector(G[i]);
	}
	DestroyCircularQueue(circular_queue);

	return 0;
}
