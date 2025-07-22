#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdbool.h>
#include <errno.h>
#include <stdbool.h>

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

static const CircularQueue DEFAULT_CIRCULAR_QUEUE_TEMPLATE = {
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

CircularQueue* CreateCircularQueue(int capacity){
	if(capacity <= 0) {
		perror("Invalid capacity\n");
		abort();
	}
	CircularQueue * temp_queue = (CircularQueue*) malloc(sizeof(CircularQueue));
	if(temp_queue == NULL) {
		perror("memory allocation failed\n");
		abort();
	}

	memcpy(temp_queue, &DEFAULT_CIRCULAR_QUEUE_TEMPLATE, sizeof(CircularQueue));

	temp_queue->m_array_ptr = (int*) malloc(sizeof(int) * capacity);
	if(temp_queue->m_array_ptr == NULL) {
		perror("memory allocation failed\n");
		abort();
	}
	temp_queue->m_capacity = capacity;
	return temp_queue;
}

void DestroyCircularQueue(struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
		return;
	}
	if(self_ptr->m_array_ptr != NULL)
		free(self_ptr->m_array_ptr);

	free(self_ptr);
}

int CircularQueueSize (struct CircularQueue * self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	return 	self_ptr->m_size;
}

int CircularQueueCapacity (struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	return 	self_ptr->m_capacity;
}

bool CircularQueueIsEmpty (struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	return 	self_ptr->m_size <= 0 &&
		self_ptr->m_front_idx == -1 &&
		self_ptr->m_rear_idx == -1;
}

bool CircularQueueIsFull (struct CircularQueue* self_ptr){
	if (self_ptr == NULL) {
	    perror("Queue is NULL\n");
	    abort();
	}

	return 	self_ptr->m_size >= self_ptr->m_capacity;
}

int CircularQueueFront (struct CircularQueue* self_ptr){
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

int CircularQueueDequeueFinal(struct CircularQueue* self_ptr) {
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

int CircularQueueDequeue (struct CircularQueue* self_ptr){
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

void CircularQueueEnqueueFirst(struct CircularQueue* self_ptr, int first_item) {
	if(self_ptr->m_capacity <= 0) {
		perror("queue's capacity is zero\n");
		abort();
	}
	self_ptr->m_front_idx = 0;
	self_ptr->m_rear_idx = 0;
	self_ptr->m_size = 1;
	*(self_ptr->m_array_ptr + 0) = first_item;
}

void CircularQueueEnqueue (struct CircularQueue* self_ptr, int item){
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

static int NODE_ARRAY[2020] = {0,};
static int K = 0;
int main(int argc, char* argv[]) {
    scanf("%d", &K);
    int node_cnt = (1 << K) - 1;
    for(int i = 0; i < node_cnt; i++) {
        scanf("%d", &NODE_ARRAY[i]);
    }
    char trash;
    scanf("%c", &trash);
    CircularQueue * queue = CreateCircularQueue(2020);
    int depth_cnt = 2;
    int root = ((1 << K) / depth_cnt) - 1;
    queue->enqueue(queue, root);
    while(!queue->is_empty(queue)) {
        int queue_size_cache = queue->m_size;
        depth_cnt = depth_cnt << 1;
        int mv = (((1 << K) / depth_cnt));
        if(mv == 0) break;
        for(int i = 0; i < queue_size_cache; i++) {
            int mid = queue->dequeue(queue);
            printf("%d ", NODE_ARRAY[mid]);
            queue->enqueue(queue, mid - mv);
            queue->enqueue(queue, mid + mv);
        }
        printf("\n");
    }
    while(!queue->is_empty(queue)) {
        printf("%d ", NODE_ARRAY[queue->dequeue(queue)]);
    }
    printf("\n");
    return 0;
}
