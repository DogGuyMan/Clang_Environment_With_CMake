#ifndef __HEADER_GUARD_PRIORITYQUEUE__
#define __HEADER_GUARD_PRIORITYQUEUE__

#include <stdbool.h>
#include <tree.h>

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
