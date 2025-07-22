#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef __HEADER_GUARD_VECTOR__
#define __HEADER_GUARD_VECTOR__

typedef struct Vector Vector;

struct Vector {
	int * m_array_ptr;
	int m_size;
	int m_capacity;

	int  (* const size) 	(struct Vector * self_ptr);
	int  (* const capacity)	(struct Vector * self_ptr);
	bool (* const is_empty) (struct Vector * self_ptr);
	int  (* const read_at) 	(struct Vector * self_ptr, int index);
	int* (* const at) 		(struct Vector * self_ptr, int index);
	void (* const push) 	(struct Vector * self_ptr, int item);
	void (* const insert) 	(struct Vector * self_ptr, int index, int item);
	void (* const prepend) 	(struct Vector * self_ptr, int item);
	// return index
	int  (* const pop) 		(struct Vector * self_ptr);
	int  (* const find) 	(struct Vector * self_ptr, int item);
	int  (* const delete) 	(struct Vector * self_ptr, int index);
	int  (* const remove) 	(struct Vector * self_ptr, int item);
	int  (* const resize) 	(struct Vector * self_ptr, int new_capacity);
};

Vector* CreateVector	(int capacity);
void 	DestroyVector	(struct Vector * self_ptr);
int  	VectorSize 		(struct Vector * self_ptr);
int  	VectorCapacity	(struct Vector * self_ptr);
bool 	VectorIsEmpty	(struct Vector * self_ptr);
int  	VectorAt 	(struct Vector * self_ptr, int index);
int*  	VectorAt 		(struct Vector * self_ptr, int index);
void 	VectorPush 		(struct Vector * self_ptr, int item);
void 	VectorInsert 	(struct Vector * self_ptr, int index, int item);
void 	VectorPrepend 	(struct Vector * self_ptr, int item);
int  	VectorPop 		(struct Vector * self_ptr);
int  	VectorFind 		(struct Vector * self_ptr, int item);
int  	VectorDelete 	(struct Vector * self_ptr, int index);
int  	VectorRemove 	(struct Vector * self_ptr, int item);
int  	VectorReserve 	(struct Vector * self_ptr, int new_capacity);

#endif//__HEADER_GUARD_VECTOR__

#ifndef __HEADER_GUARD_CIRCULAR_QUEUE__
#define __HEADER_GUARD_CIRCULAR_QUEUE__


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

#endif//__HEADER_GUARD_CIRCULAR_QUEUE__

#ifndef __HEADER_GUARD_STACK__
#define __HEADER_GUARD_STACK__


typedef struct Stack Stack;

struct Stack {
	Vector* m_container;
	int m_size;
	int m_capacity;

	int (*size) (struct Stack * self_ptr);
	int (*capacity) (struct Stack * self_ptr);
	bool (*is_empty) (struct Stack* self_ptr);
	int (*top) (struct Stack* self_ptr);
	int (*pop) (struct Stack* self_ptr);
	void (*push) (struct Stack* self_ptr, int item);
};

Stack* CreateStack(int capacity);
void DestroyStack(struct Stack* self_ptr);
int StackSize(struct Stack* self_ptr);
int StackCapacity(struct Stack* self_ptr);
bool StackIsEmpty(struct Stack* self_ptr);
int StackTop(struct Stack* self_ptr);
int StackPop(struct Stack* self_ptr);
void StackPush(struct Stack* self_ptr, int item);

#endif//__HEADER_GUARD_STACK__

#ifndef __HEADER_GUARD_TREE__
#define __HEADER_GUARD_TREE__


typedef struct BinaryTree BinaryTree;
typedef struct BinaryTreeNode BinaryTreeNode;

struct BinaryTree {
    int m_idx;
    int m_data;
    int m_childs_count;

    BinaryTree * m_left;
    BinaryTree * m_right;
    BinaryTree * m_child_nodes;

    int     ( * const size)         (BinaryTree * self_ptr);
    BinaryTree *  ( * const left_tree)    (BinaryTree * self_ptr);
    BinaryTree *  ( * const right_tree)   (BinaryTree * self_ptr);
    void    ( * const add_left )    (BinaryTree * self_ptr, BinaryTree * sub_tree );
    void    ( * const add_right )   (BinaryTreeNode * self_ptr, BinaryTree * sub_tree );
    BinaryTree *  ( * const remove_left ) (BinaryTreeNode * self_ptr, BinaryTree * sub_tree );
    BinaryTree *  ( * const remove_right )(BinaryTreeNode * self_ptr, BinaryTree * sub_tree );
};

BinaryTree *  CreateTree();
void    DestroyTree(BinaryTree * self_ptr);

typedef struct CompleteBinaryTree CompleteBinaryTree;
typedef struct BinaryTreeNodeInfo BinaryTreeNodeInfo;
typedef struct BinaryTreeTravelInfo BinaryTreeTravelInfo;

struct BinaryTreeNodeInfo {
    const unsigned m_idx;
    const int m_data;
};

struct BinaryTreeTravelInfo
{
    int * const m_array_ptr;
    int m_size;
    void (* const callback) (BinaryTreeTravelInfo * self_ptr, int data);
};

struct CompleteBinaryTree {
    Vector * m_container;
    unsigned m_size;
    unsigned m_root;

    unsigned m_head_idx;   // 재귀로 돌리기 위해 사용됨

    unsigned (* const size) (CompleteBinaryTree * self_ptr);
    unsigned (* const max_depth) (CompleteBinaryTree * self_ptr);
    void     (* const insert) (CompleteBinaryTree * self_ptr, int item);
    int      (* const remove) (CompleteBinaryTree * self_ptr);
    BinaryTreeNodeInfo (* const get_node) (CompleteBinaryTree * self_ptr, unsigned cur_idx);
    BinaryTreeNodeInfo (* const left_child) (CompleteBinaryTree * self_ptr, unsigned cur_idx);
    BinaryTreeNodeInfo (* const right_child) (CompleteBinaryTree * self_ptr, unsigned cur_idx);
};

CompleteBinaryTree * CreateCompleteBinaryTree();

void    DestroyCompleteBinaryTree(CompleteBinaryTree * self_ptr);
unsigned     CompleteBinaryTreeSize (CompleteBinaryTree * self_ptr);
unsigned     CompleteBinaryTreeMaxDepth (CompleteBinaryTree * self_ptr);
void    CompleteBinaryTreeInsert (CompleteBinaryTree * self_ptr, int item);
int     CompleteBinaryTreeRemove (CompleteBinaryTree * self_ptr);

BinaryTreeNodeInfo CompleteBinaryTreeGetNode (CompleteBinaryTree * self_ptr, unsigned cur_idx);
BinaryTreeNodeInfo CompleteBinaryTreeLeftChild (CompleteBinaryTree * self_ptr, unsigned cur_idx);
BinaryTreeNodeInfo CompleteBinaryTreeRightChild (CompleteBinaryTree * self_ptr, unsigned cur_idx);

void CompleteBinaryTreeBFS(const CompleteBinaryTree * const self_ptr, unsigned cur_node, void * user_data);
void CompleteBinaryTreeStackDFSPreorder(const CompleteBinaryTree * const self_ptr, unsigned cur_node, void * user_data);
void CompleteBinaryTreeStackDFSInorder(const CompleteBinaryTree * const self_ptr, unsigned cur_node, void * user_data);
void CompleteBinaryTreeStackDFSPostorder(const CompleteBinaryTree * const self_ptr, unsigned cur_node, void * user_data);

void CompleteBinaryTreeRecurseDFSPreorder(const CompleteBinaryTree * const self_ptr, unsigned cur_node, void * user_data);
void CompleteBinaryTreeRecurseDFSInorder(const CompleteBinaryTree * const self_ptr, unsigned cur_node, void * user_data);
void CompleteBinaryTreeRecurseDFSPostorder(const CompleteBinaryTree * const self_ptr, unsigned cur_node, void * user_data);

void CompleteBinaryTreeSwapNode(CompleteBinaryTree * const self_ptr, unsigned a_node, unsigned b_node);

typedef void (*TreeNodeCallback)(const void* node_data, void* user_data);

void GenericTreeDFS(const void * const tree_ptr, TreeNodeCallback order_callback, void * user_data);

#endif//__HEADER_GUARD_TREE__

#ifndef __HEADER_GUARD_PRIORITYQUEUE__
#define __HEADER_GUARD_PRIORITYQUEUE__


typedef struct PriorityQueue PriorityQueue;
typedef int (* CompareFunction)(CompleteBinaryTree * const, int, int);

struct PriorityQueue {
    CompleteBinaryTree * m_container;

    int (* compare)(CompleteBinaryTree * const, int, int);
    unsigned ( * const size )       (PriorityQueue * const self_ptr);
    bool ( * const is_empty )       (PriorityQueue * const self_ptr);
    void ( * const insert )         (PriorityQueue * const self_ptr, int item);
    int ( * const top )             (PriorityQueue * const self_ptr);
    int ( * const pop )             (PriorityQueue * const self_ptr);
    void ( * const sift_up )		(CompleteBinaryTree * const container_ptr, CompareFunction compare, unsigned cur_node);
    void ( * const sift_down)		(CompleteBinaryTree * const container_ptr, CompareFunction compare, unsigned cur_node);
    int ( * const delete )          (PriorityQueue * const self_ptr, int index);
    int ( * const remove )          (PriorityQueue * const self_ptr, int item);
    void ( * const heapify )        (CompleteBinaryTree * const container_ptr, CompareFunction compare, unsigned cur_node);
};

PriorityQueue * CreatePriorityQueue(CompareFunction compare);
// Build Heap in O(n) Complexity : https://leeminju531.tistory.com/33
PriorityQueue * BuildPriorityQueue(PriorityQueue * self_ptr, CompareFunction compare, int * array_ptr, unsigned array_size);
void DestroyPriorityQueue(PriorityQueue * self_ptr);

int MaxCompare         (CompleteBinaryTree * const container_ptr, int a_node, int b_node);
int MinCompare         (CompleteBinaryTree * const container_ptr, int a_node, int b_node);
unsigned PriorityQueueSize       (PriorityQueue * const self_ptr);
bool PriorityQueueIsEmpty       (PriorityQueue * const self_ptr);
void PriorityQueueInsert         (PriorityQueue * const self_ptr, int item);
int PriorityQueueTop             (PriorityQueue * const self_ptr);
int PriorityQueuePop             (PriorityQueue * const self_ptr);
int PriorityQueueDelete         (PriorityQueue * const self_ptr, int index);
int PriorityQueueRemove         (PriorityQueue * const self_ptr, int item);
void SiftUp		(CompleteBinaryTree * const container_ptr, CompareFunction compare, unsigned cur_node);
void SiftDown	(CompleteBinaryTree * const container_ptr, CompareFunction compare, unsigned cur_node);
void Heapify        (CompleteBinaryTree * const container_ptr, CompareFunction compare, unsigned cur_node);
#endif//__HEADER_GUARD_PRIORITYQUEUE__


static const Vector DEFAULT_VECTOR_TEMPLATE = {
	.m_array_ptr = NULL,
	.m_size 	= 0,
	.m_capacity = 0,
	.size 		= VectorSize,
	.capacity 	= VectorCapacity,
	.is_empty 	= VectorIsEmpty,
	.read_at 	= VectorAt,
	.at 		= VectorAt,
	.push 		= VectorPush,
	.insert 	= VectorInsert,
	.prepend 	= VectorPrepend,
	.pop 		= VectorPop,
	.find 		= VectorFind,
	.delete 	= VectorDelete,
	.remove 	= VectorRemove,
	.resize 	= VectorReserve,
};

Vector* CreateVector(int capacity) {
	Vector* temp_vector = malloc(sizeof(Vector));
	if(temp_vector == NULL) {
		perror("vector memory alloc failed");
		abort();
	}
	memcpy(temp_vector, &DEFAULT_VECTOR_TEMPLATE, sizeof(Vector));
	if(capacity <= 16) {
		temp_vector->m_array_ptr = malloc(sizeof(int) * 16);
		temp_vector->m_capacity = 16;
	}
	else {
		temp_vector->m_array_ptr = malloc(sizeof(int) * capacity);
		temp_vector->m_capacity = capacity;
	}
	return temp_vector;
}

void DestroyVector(Vector* self_ptr) {
	if(self_ptr == NULL || self_ptr->m_array_ptr == NULL) {
		perror("double free error\n");
		abort();
	}
	if(self_ptr->m_array_ptr != NULL)
		free(self_ptr->m_array_ptr);
	if(self_ptr != NULL)
		free(self_ptr);
}

int  VectorSize(struct Vector * self_ptr)
{
	return self_ptr->m_size;
}

int  VectorCapacity(struct Vector * self_ptr)
{
	return self_ptr->m_capacity;
}

bool VectorIsEmpty(struct Vector * self_ptr)
{
	return self_ptr->m_size == 0;
}

int  VectorAt(struct Vector * self_ptr, int index)
{
	return *(self_ptr->m_array_ptr + index);
}

int* VectorAt(struct Vector * self_ptr, int index)
{
	return (self_ptr->m_array_ptr + index);
}

void VectorPush(struct Vector * self_ptr, int item)
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

void VectorInsert     (struct Vector * self_ptr, int index, int item){
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

void VectorPrepend    (struct Vector * self_ptr, int item) {
	self_ptr->insert(self_ptr, 0, item);
	return;
}

int  VectorPop(struct Vector * self_ptr)
{
	if(self_ptr->m_size == 0) {
		printf("Vector is Empty\n");
		abort();
	}
	--(self_ptr->m_size);
	return  *(self_ptr->m_array_ptr + self_ptr->m_size);
}

int  VectorFind       (struct Vector * self_ptr, int item) {
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

int  VectorDelete     (struct Vector * self_ptr, int index)
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

int  VectorRemove     (struct Vector * self_ptr, int item)
{
	int founded_index = self_ptr->find(self_ptr, item);
	if(founded_index == -1) {
		return - 1;
	}
	return self_ptr->delete(self_ptr, founded_index);
}

int  VectorReserve     (struct Vector * self_ptr, int new_capacity)
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


Stack* CreateStack(int capacity) {
	Stack* temp_stack = (Stack*) malloc(sizeof(Stack));
	Vector* temp_container = CreateVector(capacity);
	temp_stack->m_container = temp_container;
	temp_stack->m_capacity = temp_container->m_capacity;
	temp_stack->m_size = 0;

	temp_stack->size = StackSize;
	temp_stack->capacity = StackCapacity;
	temp_stack->is_empty = StackIsEmpty;
	temp_stack->top = StackTop;
	temp_stack->pop = StackPop;
	temp_stack->push = StackPush;
	return temp_stack;
}

void DestroyStack(struct Stack* self_ptr) {
	DestroyVector(self_ptr->m_container);
	self_ptr->m_container = NULL;

	self_ptr->m_capacity = 0;
	self_ptr->m_size = 0;

	self_ptr->size = NULL;
	self_ptr->capacity = NULL;
	self_ptr->is_empty = NULL;
	self_ptr->top = NULL;
	self_ptr->pop = NULL;
	self_ptr->push = NULL;
	free(self_ptr);
}


int StackSize(struct Stack* self_ptr) {
	return self_ptr->m_size;
}

int StackCapacity(struct Stack* self_ptr) {
	return self_ptr->m_capacity;
}

bool StackIsEmpty(struct Stack* self_ptr) {
	return self_ptr->m_size == 0;
}

int StackTop(struct Stack* self_ptr) {
	Vector* container = self_ptr->m_container;
	int container_size = container->size(container);
	if(container_size == 0) {
		printf("Stack Is Empty\n");
		abort();
	}
	int top_index = container_size -1;
	return container->read_at(container, top_index);
}

int StackPop(struct Stack* self_ptr) {
	Vector* container = self_ptr->m_container;
	int container_size = container->size(container);
	if(container_size == 0) {
		printf("Stack Is Empty\n");
		abort();
	}
	int res = container->pop(container);
	self_ptr->m_size = container->m_size;
	return res;
}

void StackPush(struct Stack* self_ptr, int item) {
	Vector* container = self_ptr->m_container;
	container->push(container, item);
	self_ptr->m_size = container->m_size;
}

static const CompleteBinaryTree DEFAULT_COMPLETE_BINARYTREE_TEMPLATE = {
    .m_container = NULL,
    .m_size = 0,
    .m_root = 0,
    .m_head_idx = 0,
    .size = CompleteBinaryTreeSize,
    .max_depth = CompleteBinaryTreeMaxDepth,
    .get_node = CompleteBinaryTreeGetNode,
    .left_child = CompleteBinaryTreeLeftChild,
    .right_child = CompleteBinaryTreeRightChild,
    .insert = CompleteBinaryTreeInsert,
    .remove = CompleteBinaryTreeRemove
};

static const BinaryTreeNodeInfo WRONG_BINARYTREE_NODE_OUT = {
    .m_idx = 0,
    .m_data = 0,
};

CompleteBinaryTree * CreateCompleteBinaryTree()
{
    CompleteBinaryTree * temp_complete_tree = malloc(sizeof(CompleteBinaryTree));
    if(temp_complete_tree == NULL) {
        perror("tree allocate failed\n");
        abort();
    }
    memcpy(temp_complete_tree, &DEFAULT_COMPLETE_BINARYTREE_TEMPLATE, sizeof(CompleteBinaryTree));
    temp_complete_tree->m_container = CreateVector(15);
    if(temp_complete_tree->m_container == NULL) {
        perror("vector allocate failed\n");
        abort();
    }
    return temp_complete_tree;
}

void    DestroyCompleteBinaryTree(CompleteBinaryTree * self_ptr)
{
    if(self_ptr == NULL || self_ptr->m_container == NULL) {
        perror("prevent double free\n");
        return;
    }
    if(self_ptr->m_container != NULL) {
        DestroyVector(self_ptr->m_container);
        self_ptr->m_container = NULL;
    }
    if(self_ptr != NULL) {
        free(self_ptr);
        self_ptr = NULL;
    }
    return;
}

unsigned     CompleteBinaryTreeSize (CompleteBinaryTree * self_ptr)
{
    return self_ptr->m_size;
}

unsigned     CompleteBinaryTreeMaxDepth (CompleteBinaryTree * self_ptr)
{
    int res = 0; int fulls = 1;
    while(fulls < self_ptr->m_size) {
        res++;
        fulls <<= res;
    }
    return res;
}

static void InsertFirstItem(CompleteBinaryTree * self_ptr, int item) {
    if(self_ptr == NULL) {
        perror("CompleteBinaryTree is NULL\n");
        abort();
    }
    self_ptr->m_root = 1;
    Vector * container = self_ptr->m_container;
    if(container->is_empty(container)) {
        container->push(container, item);
    }
    self_ptr->m_size++;
    self_ptr->m_head_idx = 1;
}

void    CompleteBinaryTreeInsert (CompleteBinaryTree * self_ptr, int item)
{
    if(self_ptr == NULL) {
        perror("CompleteBinaryTree is NULL\n");
        abort();
    }
    if(self_ptr->m_size == 0) {InsertFirstItem(self_ptr, item); return;}
    Vector * container = self_ptr->m_container;
    container->push(container, item);
    self_ptr->m_size = container->size(container);
    return;
}

static int RemoveFinalItem(CompleteBinaryTree * self_ptr) {
    if(self_ptr == NULL) {
        perror("CompleteBinaryTree is NULL\n");
        abort();
    }
    if(self_ptr->m_size != 1) {
        perror("Not Last Item");
        abort();
    }
    unsigned last_idx = self_ptr->m_size - 1;
    self_ptr->m_root = 0;
    Vector* container = self_ptr->m_container;
    int res = container->delete(container, last_idx);
    self_ptr->m_size = 0;
    self_ptr->m_head_idx = 0;
    return res;
}

int     CompleteBinaryTreeRemove (CompleteBinaryTree * self_ptr)
{
    if(self_ptr == NULL) {
        perror("CompleteBinaryTree is NULL\n");
        abort();
    }
    if(self_ptr->m_size == 1) {return RemoveFinalItem(self_ptr);}
    Vector * container = self_ptr->m_container;
    int res = container->delete(container, self_ptr->m_size - 1);
    self_ptr->m_size = container->size(container);
    return res;
}

int     CompleteBinaryTreeDelete(CompleteBinaryTree * self_ptr, int item) {
    if(self_ptr == NULL) {
        perror("CompleteBinaryTree is NULL\n");
        abort();
    }
    // find
    Vector * container = self_ptr->m_container;
    int res = container->remove(container, item);
    self_ptr->m_size = container->size(container);
    return res;
}

BinaryTreeNodeInfo CompleteBinaryTreeGetNode (CompleteBinaryTree * self_ptr, unsigned cur_idx) {
    if(cur_idx <= 0 || self_ptr->m_size < cur_idx)
        return WRONG_BINARYTREE_NODE_OUT;
    return (BinaryTreeNodeInfo) {.m_idx = cur_idx, .m_data = self_ptr->m_container->read_at(self_ptr->m_container, cur_idx - 1)};
}

BinaryTreeNodeInfo CompleteBinaryTreeLeftChild (CompleteBinaryTree * self_ptr, unsigned cur_idx) {
    return self_ptr->get_node(self_ptr, cur_idx * 2);
}

BinaryTreeNodeInfo CompleteBinaryTreeRightChild (CompleteBinaryTree * self_ptr, unsigned cur_idx) {
    return self_ptr->get_node(self_ptr, cur_idx * 2 + 1);
}

void CompleteBinaryTreeBFS(const CompleteBinaryTree * const self_ptr, unsigned int cur_node, void * user_data)
{
    if(self_ptr == NULL) {
        perror("tree ptr NULL error \n");
        abort();
    }

    if(!(0 < cur_node  && cur_node < self_ptr->m_size)) {
        perror("invalid node error \n");
        abort();
    }

    CircularQueue *  queue_ptr = CreateCircularQueue(self_ptr->m_size);
    if(queue_ptr == NULL) {
        perror("queue alloc failed\n");
        abort();
    }

    Vector * is_visit_ptr = CreateVector(self_ptr->m_size);
    if(is_visit_ptr == NULL) {
        perror("vector alloc failed\n");
        abort();
    }

    CompleteBinaryTree* tree_access_ptr = (CompleteBinaryTree*)self_ptr;

    bool print_flag = false;
    BinaryTreeTravelInfo * search_data = NULL;
    if(user_data == NULL) print_flag = true;
    else search_data = (BinaryTreeTravelInfo*) user_data; // 🚸 C에서는 언어차원에서 타입 캐스팅에 대한 검증을 할 수 없다.. 이건 좀 어렵네

    queue_ptr->enqueue(queue_ptr, cur_node);

    while(!queue_ptr->is_empty(queue_ptr)) {
        int cur_idx = queue_ptr->dequeue(queue_ptr);
        if(is_visit_ptr->read_at(is_visit_ptr, cur_idx) != 0) {
            continue;
        }
        *(is_visit_ptr->at(is_visit_ptr, cur_idx)) = 1;

        BinaryTreeNodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_idx);

        if(print_flag)
            printf("%d ", node_info.m_idx);
        else
            search_data->callback(search_data, node_info.m_data);

        BinaryTreeNodeInfo nxt_left_child = self_ptr->left_child(tree_access_ptr, cur_idx);
        if(nxt_left_child.m_idx != 0)
            queue_ptr->enqueue(queue_ptr, nxt_left_child.m_idx);

        BinaryTreeNodeInfo nxt_right_child = self_ptr->right_child(tree_access_ptr, cur_idx);
        if(nxt_right_child.m_idx != 0)
            queue_ptr->enqueue(queue_ptr, nxt_right_child.m_idx);
    }
    if(print_flag == true)
        printf("\n");

    DestroyCircularQueue(queue_ptr);
    DestroyVector(is_visit_ptr);
}

void CompleteBinaryTreeStackDFSPreorder(const CompleteBinaryTree * const self_ptr, unsigned int cur_node, void * user_data) {
    if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
        abort();
    }

    if(!(0 < cur_node && cur_node < self_ptr->m_size)) {
        perror("invalid node error \n");
        abort();
    }

    Stack * stack_ptr = CreateStack(self_ptr->m_size);
    if(stack_ptr == NULL) {
        perror("stack alloc failed\n");
        abort();
    }

    Vector * is_visit_ptr = CreateVector(self_ptr->m_size);
    if(is_visit_ptr == NULL) {
        perror("vector alloc failed\n");
        abort();
    }

    if(self_ptr->m_size == 0) {
        perror("tree empty\n");
        return;
    }

    bool print_flag = false;
    BinaryTreeTravelInfo * search_data = NULL;
    if(user_data == NULL) print_flag = true;
    else search_data = (BinaryTreeTravelInfo*) user_data; // 🚸 C에서는 언어차원에서 타입 캐스팅에 대한 검증을 할 수 없다.. 이건 좀 어렵네

    CompleteBinaryTree* tree_access_ptr = (CompleteBinaryTree*) self_ptr;

    stack_ptr->push(stack_ptr, cur_node);
    int cur_idx, nxt_idx;

    while(!stack_ptr->is_empty(stack_ptr)) {
        int cur_idx = stack_ptr->pop(stack_ptr);
        if(is_visit_ptr->read_at(is_visit_ptr, cur_idx) != 0) {
            continue;
        }
        *(is_visit_ptr->at(is_visit_ptr, cur_idx)) = 1;

        BinaryTreeNodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_idx);
        // printf("index %d, data %d\n", data.m_idx, data.m_data);

        if(print_flag)
            printf("%d ", node_info.m_idx);
        else
            search_data->callback(search_data, node_info.m_data);

        BinaryTreeNodeInfo nxt_right_child = self_ptr->right_child(tree_access_ptr, cur_idx);
        // printf("index %d, data %d\n", nxt_right_child.m_idx, nxt_right_child.m_data);
        if(nxt_right_child.m_idx != 0)
            stack_ptr->push(stack_ptr, nxt_right_child.m_idx);

        BinaryTreeNodeInfo nxt_left_child = self_ptr->left_child(tree_access_ptr, cur_idx);
        // printf("index %d, data %d\n", nxt_left_child.m_idx, nxt_left_child.m_data);
        if(nxt_left_child.m_idx != 0)
            stack_ptr->push(stack_ptr, nxt_left_child.m_idx);

    }
    if(print_flag == true)
        printf("\n");

    DestroyStack(stack_ptr);
    DestroyVector(is_visit_ptr);
}

void CompleteBinaryTreeStackDFSInorder(const CompleteBinaryTree * const self_ptr, unsigned int cur_node, void * user_data) {
    if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
        abort();
    }

    if(!(0 < cur_node  && cur_node < self_ptr->m_size)) {
        perror("invalid node error \n");
        abort();
    }

    Stack * stack_ptr = CreateStack(self_ptr->m_size);
    if(stack_ptr == NULL) {
        perror("stack alloc failed\n");
        abort();
    }

    Vector * is_visit_ptr = CreateVector(self_ptr->m_size);
    if(is_visit_ptr == NULL) {
        perror("vector alloc failed\n");
        abort();
    }

    if(self_ptr->m_size == 0) {
        perror("tree empty\n");
        return;
    }

    bool print_flag = false;
    BinaryTreeTravelInfo * search_data = NULL;
    if(user_data == NULL) print_flag = true;
    else search_data = (BinaryTreeTravelInfo*) user_data; // 🚸 C에서는 언어차원에서 타입 캐스팅에 대한 검증을 할 수 없다.. 이건 좀 어렵네

    CompleteBinaryTree* tree_access_ptr = (CompleteBinaryTree*) self_ptr;
    stack_ptr->push(stack_ptr, cur_node);
    int cur_idx, nxt_idx;

    while(!stack_ptr->is_empty(stack_ptr)) {

        cur_idx = stack_ptr->top(stack_ptr);
        nxt_idx = self_ptr->left_child(tree_access_ptr, cur_idx).m_idx;
        if(nxt_idx != 0 && is_visit_ptr->read_at(is_visit_ptr, nxt_idx) == 0) {
            while(nxt_idx != 0) {
                if(is_visit_ptr->read_at(is_visit_ptr, nxt_idx) != 0) break;
                stack_ptr->push(stack_ptr, nxt_idx);
                nxt_idx = self_ptr->left_child(tree_access_ptr, nxt_idx).m_idx;
            }
        }

        int end_idx = stack_ptr->pop(stack_ptr);
        if(is_visit_ptr->read_at(is_visit_ptr,end_idx) == 0) {
            *(is_visit_ptr->at(is_visit_ptr, end_idx)) = 1;
            BinaryTreeNodeInfo node_info = self_ptr->get_node(tree_access_ptr, end_idx);

            if(print_flag == true)
                printf("%d ", node_info.m_idx);
            else
                search_data->callback(search_data, node_info.m_data);
        }

        nxt_idx = self_ptr->right_child(tree_access_ptr, end_idx).m_idx;
        BinaryTreeNodeInfo nxt_item = self_ptr->get_node(tree_access_ptr, nxt_idx);
        if(nxt_idx != 0 && is_visit_ptr->read_at(is_visit_ptr, nxt_idx) == 0) {
            stack_ptr->push(stack_ptr, nxt_idx);
        }
    }
    DestroyStack(stack_ptr);
    DestroyVector(is_visit_ptr);
}

void CompleteBinaryTreeStackDFSPostorder(const CompleteBinaryTree * const self_ptr, unsigned int cur_node, void * user_data) {
    if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
        abort();
    }

    if(!(0 < cur_node  && cur_node < self_ptr->m_size)) {
        perror("invalid node error \n");
        abort();
    }

    Stack * stack_ptr = CreateStack(self_ptr->m_size);
    if(stack_ptr == NULL) {
        perror("stack alloc failed\n");
        abort();
    }

    Vector * is_visit_ptr = CreateVector(self_ptr->m_size);
    if(is_visit_ptr == NULL) {
        perror("vector alloc failed\n");
        abort();
    }

    if(self_ptr->m_size == 0) {
        perror("tree empty\n");
        return;
    }

    bool print_flag = false;
    BinaryTreeTravelInfo * search_data = NULL;
    if(user_data == NULL) print_flag = true;
    else search_data = (BinaryTreeTravelInfo*) user_data; // 🚸 C에서는 언어차원에서 타입 캐스팅에 대한 검증을 할 수 없다.. 이건 좀 어렵네

    CompleteBinaryTree* tree_access_ptr = (CompleteBinaryTree*) self_ptr;
    stack_ptr->push(stack_ptr, cur_node);
    int cur_idx, nxt_idx;

    while(!stack_ptr->is_empty(stack_ptr)) {

        cur_idx = stack_ptr->top(stack_ptr);
        nxt_idx = self_ptr->left_child(tree_access_ptr, cur_idx).m_idx;
        if(nxt_idx != 0 && is_visit_ptr->read_at(is_visit_ptr, nxt_idx) == 0) {
            while(nxt_idx != 0) {
                if(is_visit_ptr->read_at(is_visit_ptr, nxt_idx) != 0) break;
                stack_ptr->push(stack_ptr, nxt_idx);
                nxt_idx = self_ptr->left_child(tree_access_ptr, nxt_idx).m_idx;
            }
        }

        int end_idx = stack_ptr->pop(stack_ptr);
        if(is_visit_ptr->read_at(is_visit_ptr,end_idx) == 0) {
            *(is_visit_ptr->at(is_visit_ptr, end_idx)) = 1;
            BinaryTreeNodeInfo node_info = self_ptr->get_node(tree_access_ptr, end_idx);
            if(print_flag == true)
                printf("%d\n", node_info.m_idx);
            else
                search_data->callback(search_data, node_info.m_data);
        }

        if(!stack_ptr->is_empty(stack_ptr)) {
            int nxt_idx = self_ptr->right_child(tree_access_ptr, stack_ptr->top(stack_ptr)).m_idx;
            BinaryTreeNodeInfo nxt_item = self_ptr->get_node(tree_access_ptr, nxt_idx);
            if(nxt_idx != 0 && is_visit_ptr->read_at(is_visit_ptr, nxt_idx) == 0) {
                stack_ptr->push(stack_ptr, nxt_idx);
            }
        }
    }
    DestroyStack(stack_ptr);
    DestroyVector(is_visit_ptr);
}

void CompleteBinaryTreeRecurseDFSPreorder(const CompleteBinaryTree * const self_ptr, unsigned int cur_node, void * user_data) {

    if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
        abort();
    }

    if(!(0 < cur_node  && cur_node <= self_ptr->m_size)) {
        if(cur_node == 0) return;
        perror("invalid node error \n");
        abort();
    }

    if(self_ptr->m_size == 0) {
        perror("tree empty\n");
        return;
    }

    CompleteBinaryTree* tree_access_ptr = (CompleteBinaryTree*) self_ptr;

    bool print_flag = false;
    BinaryTreeTravelInfo * search_data = NULL;
    if(user_data == NULL) print_flag = true;
    else search_data = (BinaryTreeTravelInfo*) user_data; // 🚸 C에서는 언어차원에서 타입 캐스팅에 대한 검증을 할 수 없다.. 이건 좀 어렵네

    BinaryTreeNodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_node);
    if(print_flag == true) printf("%d\n", node_info.m_idx);
    else search_data->callback(search_data, node_info.m_data);

    CompleteBinaryTreeRecurseDFSPreorder(self_ptr, self_ptr->left_child(tree_access_ptr, cur_node).m_idx, search_data);
    CompleteBinaryTreeRecurseDFSPreorder(self_ptr, self_ptr->right_child(tree_access_ptr, cur_node).m_idx, search_data);
}

void CompleteBinaryTreeRecurseDFSInorder(const CompleteBinaryTree * const self_ptr, unsigned int cur_node, void * user_data) {

    if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
        abort();
    }

    if(!(0 < cur_node  && cur_node <= self_ptr->m_size)) {
        if(cur_node == 0) return;
        perror("invalid node error \n");
        abort();
    }

    if(self_ptr->m_size == 0) {
        perror("tree empty\n");
        return;
    }

    CompleteBinaryTree* tree_access_ptr = (CompleteBinaryTree*) self_ptr;

    bool print_flag = false;
    BinaryTreeTravelInfo * search_data = NULL;
    if(user_data == NULL) print_flag = true;
    else search_data = (BinaryTreeTravelInfo*) user_data; // 🚸 C에서는 언어차원에서 타입 캐스팅에 대한 검증을 할 수 없다.. 이건 좀 어렵네


    CompleteBinaryTreeRecurseDFSInorder(self_ptr, self_ptr->left_child(tree_access_ptr, cur_node).m_idx , search_data);
    BinaryTreeNodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_node);
    if(print_flag == true) printf("%d\n", node_info.m_idx);
    else search_data->callback(search_data, node_info.m_data);
    CompleteBinaryTreeRecurseDFSInorder(self_ptr, self_ptr->right_child(tree_access_ptr, cur_node).m_idx, search_data);
}

void CompleteBinaryTreeRecurseDFSPostorder(const CompleteBinaryTree * const self_ptr, unsigned int cur_node, void * user_data) {

    if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
        abort();
    }

    if(!(0 < cur_node  && cur_node <= self_ptr->m_size)) {
        if(cur_node == 0) return;
        perror("invalid node error \n");
        abort();
    }

    if(self_ptr->m_size == 0) {
        perror("tree empty\n");
        return;
    }

    CompleteBinaryTree* tree_access_ptr = (CompleteBinaryTree*) self_ptr;

    bool print_flag = false;
    BinaryTreeTravelInfo * search_data = NULL;
    if(user_data == NULL) print_flag = true;
    else search_data = (BinaryTreeTravelInfo*) user_data; // 🚸 C에서는 언어차원에서 타입 캐스팅에 대한 검증을 할 수 없다.. 이건 좀 어렵네

    CompleteBinaryTreeRecurseDFSPostorder(self_ptr, self_ptr->left_child(tree_access_ptr, cur_node).m_idx, search_data);
    CompleteBinaryTreeRecurseDFSPostorder(self_ptr, self_ptr->right_child(tree_access_ptr, cur_node).m_idx, search_data);
    BinaryTreeNodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_node);
    if(print_flag == true) printf("%d\n", node_info.m_idx);
    else search_data->callback(search_data, node_info.m_data);

}

void CompleteBinaryTreeSwapNode(CompleteBinaryTree * const self_ptr, unsigned a_node, unsigned b_node) {
        if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
        abort();
    }

    if(self_ptr->m_size == 0) {
        perror("tree empty\n");
        return;
    }
    BinaryTreeNodeInfo a_node_info = self_ptr->get_node(self_ptr, a_node);
    BinaryTreeNodeInfo b_node_info = self_ptr->get_node(self_ptr, b_node);
    *(self_ptr->m_container->at(self_ptr->m_container, a_node-1)) = b_node_info.m_data;
    *(self_ptr->m_container->at(self_ptr->m_container, b_node-1)) = a_node_info.m_data;
}


static const PriorityQueue DEFAULT_PRIORITY_QUEUE_TEMPLATE = {
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
	memcpy(temp_pq, &DEFAULT_PRIORITY_QUEUE_TEMPLATE ,sizeof(PriorityQueue));
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
	int last_internal_node = self_ptr->size(self_ptr) / 2;
	for(int i = last_internal_node; i >= 1; i--) {
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
	if(a_node_info.m_data <= b_node_info.m_data) return 1;
	if(a_node_info.m_data > b_node_info.m_data) return -1;
	return 0;
}

int MinCompare         (CompleteBinaryTree * const container_ptr, int a_node, int b_node){
	CompleteBinaryTree * container = container_ptr;
	BinaryTreeNodeInfo a_node_info = container->get_node(container, a_node);
	BinaryTreeNodeInfo b_node_info = container->get_node(container, b_node);
	if(a_node_info.m_data <= b_node_info.m_data) return -1;
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

PriorityQueue * pq;

int N;
int main() {
    pq = CreatePriorityQueue(MinCompare);
    scanf("%d", &N);

    if(N <= 1) {
        printf("0\n");
        DestroyPriorityQueue(pq);
        return 0;
    }

    for(int i = 0 ; i < N; i++) {
        int c;
        scanf("%d", &c);
        pq->insert(pq, c);
    }
    char trash; scanf("%c", &trash);

    long long res = 0;
    while(pq->size(pq) > 1) {
        int f = pq->pop(pq);
        int s = pq->pop(pq);
        res += (f + s);
        pq->insert(pq, (f + s));
    }
    printf("%lld\n", res);
    DestroyPriorityQueue(pq);
    return 0;
}
