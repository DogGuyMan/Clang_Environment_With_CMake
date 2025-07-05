#ifndef __HEADER_GUARD_PRIORITYQUEUE__
#define __HEADER_GUARD_PRIORITYQUEUE__

#include <stdbool.h>
#include <tree.h>

typedef struct PriorityQueue PriorityQueue;

struct PriorityQueue {
    CompleteBinaryTree * m_container;

    int ( * const compare)          (PriorityQueue * const self_ptr, int a_node, int b_node);
    unsigned ( * const size )       (PriorityQueue * const self_ptr);
    bool ( * const is_empty )       (PriorityQueue * const self_ptr);
    void ( * const insert )         (PriorityQueue * const self_ptr, int item);
    int ( * const top )             (PriorityQueue * const self_ptr);
    int ( * const pop )             (PriorityQueue * const self_ptr);
    void ( * const sift_up )		(CompleteBinaryTree * const self_ptr, int cur_node);
    void ( * const sift_down)		(CompleteBinaryTree * const self_ptr, int cur_node);
    int ( * const remove )         (PriorityQueue * const self_ptr, int item);
    void ( * const heapfiy )        (CompleteBinaryTree * const container_ptr);
};

int Compare         (PriorityQueue * const self_ptr, int a_node, int b_node);
unsigned Size       (PriorityQueue * const self_ptr);
bool IsEmpty       (PriorityQueue * const self_ptr);
void Insert         (PriorityQueue * const self_ptr, int item);
int Top             (PriorityQueue * const self_ptr);
int Pop             (PriorityQueue * const self_ptr);
int Remove         (PriorityQueue * const self_ptr, int item);
void SiftUp		(CompleteBinaryTree * const self_ptr, int cur_node);
void SiftDown	(CompleteBinaryTree * const self_ptr, int cur_node);
void Heapfiy        (CompleteBinaryTree * const container_ptr);
#endif//__HEADER_GUARD_PRIORITYQUEUE__
