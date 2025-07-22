#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stack_primitive.h>
#include <circular_queue_primitive.h>
#include "complete_binarytree.h"

#define CreateVector__TYPE_NAME___SPSP_Default CreateVectorIntDefault
#define CreateVector__TYPE_NAME__ CreateVectorInt
#define DestroyVector__TYPE_NAME__ DestroyVectorInt

#define CreateCircularQueue__TYPE_NAME__ CreateCircularQueueInt
#define DestroyCircularQueue__TYPE_NAME__ DestroyCircularQueueInt

#define CreateStack__TYPE_NAME__ CreateStackInt
#define DestroyStack__TYPE_NAME__ DestroyStackInt

static const CompleteBinaryTree__TYPE_NAME__ DEFAULT_COMPLETE_BINARYTREE___TYPE_NAME___SPSP__TEMPLATE = {
    .m_container = NULL,
    .m_size = 0,
    .m_root = 0,
    .m_head_idx = 0,
    .size = CompleteBinaryTree__TYPE_NAME___SPSP_Size,
    .max_depth = CompleteBinaryTree__TYPE_NAME___SPSP_MaxDepth,
    .get_node = CompleteBinaryTree__TYPE_NAME___SPSP_GetNode,
    .left_child = CompleteBinaryTree__TYPE_NAME___SPSP_LeftChild,
    .right_child = CompleteBinaryTree__TYPE_NAME___SPSP_RightChild,
    .insert = CompleteBinaryTree__TYPE_NAME___SPSP_Insert,
    .remove = CompleteBinaryTree__TYPE_NAME___SPSP_Remove
};

static const BinaryTree__TYPE_NAME___SPSP_NodeInfo WRONG_BINARYTREE___TYPE_NAME___SPSP__NODE_OUT = {
    .m_idx = 0,
    .m_data = 0,
};

CompleteBinaryTree__TYPE_NAME__ * CreateCompleteBinaryTree__TYPE_NAME__()
{
    CompleteBinaryTree__TYPE_NAME__ * temp_complete_tree = malloc(sizeof(CompleteBinaryTree__TYPE_NAME__));
    if(temp_complete_tree == NULL) {
        perror("tree allocate failed\n");
        abort();
    }
    memcpy(temp_complete_tree, &DEFAULT_COMPLETE_BINARYTREE___TYPE_NAME___SPSP__TEMPLATE, sizeof(CompleteBinaryTree__TYPE_NAME__));
    temp_complete_tree->m_container = CreateVector__TYPE_NAME___SPSP_Default();
    if(temp_complete_tree->m_container == NULL) {
        perror("vector allocate failed\n");
        abort();
    }
    return temp_complete_tree;
}

void    DestroyCompleteBinaryTree__TYPE_NAME__(CompleteBinaryTree__TYPE_NAME__ * self_ptr)
{
    if(self_ptr == NULL || self_ptr->m_container == NULL) {
        perror("prevent double free\n");
        return;
    }
    if(self_ptr->m_container != NULL) {
        DestroyVector__TYPE_NAME__(self_ptr->m_container);
        self_ptr->m_container = NULL;
    }
    if(self_ptr != NULL) {
        free(self_ptr);
        self_ptr = NULL;
    }
    return;
}

size_t     CompleteBinaryTree__TYPE_NAME___SPSP_Size (CompleteBinaryTree__TYPE_NAME__ * self_ptr)
{
    return self_ptr->m_size;
}

size_t     CompleteBinaryTree__TYPE_NAME___SPSP_MaxDepth (CompleteBinaryTree__TYPE_NAME__ * self_ptr)
{
    int res = 0; int fulls = 1;
    while(fulls < self_ptr->m_size) {
        res++;
        fulls <<= res;
    }
    return res;
}

static void InsertFirst__TYPE_NAME___SPSP_Item(CompleteBinaryTree__TYPE_NAME__ * self_ptr, __TYPE__ item) {
    if(self_ptr == NULL) {
        perror("CompleteBinaryTree is NULL\n");
        abort();
    }
    self_ptr->m_root = 1;
    Vector__TYPE_NAME__ * container = self_ptr->m_container;
    if(container->is_empty(container)) {
        container->push_back(container, item);
    }
    self_ptr->m_size++;
    self_ptr->m_head_idx = 1;
}

void    CompleteBinaryTree__TYPE_NAME___SPSP_Insert (CompleteBinaryTree__TYPE_NAME__ * self_ptr, __TYPE__ item)
{
    if(self_ptr == NULL) {
        perror("CompleteBinaryTree is NULL\n");
        abort();
    }
    if(self_ptr->m_size == 0) {InsertFirst__TYPE_NAME___SPSP_Item(self_ptr, item); return;}
    Vector__TYPE_NAME__ * container = self_ptr->m_container;
    container->push_back(container, item);
    self_ptr->m_size = container->size(container);
    return;
}

static __TYPE__ RemoveFinal__TYPE_NAME___SPSP_Item(CompleteBinaryTree__TYPE_NAME__ * self_ptr) {
    if(self_ptr == NULL) {
        perror("CompleteBinaryTree is NULL\n");
        abort();
    }
    if(self_ptr->m_size != 1) {
        perror("Not Last Item");
        abort();
    }
    size_t last_idx = self_ptr->m_size - 1;
    self_ptr->m_root = 0;
    Vector__TYPE_NAME__ * container = self_ptr->m_container;
    __TYPE__ res = container->remove_with_index(container, last_idx);
    self_ptr->m_size = 0;
    self_ptr->m_head_idx = 0;
    return res;
}

__TYPE__     CompleteBinaryTree__TYPE_NAME___SPSP_Remove (CompleteBinaryTree__TYPE_NAME__ * self_ptr)
{
    if(self_ptr == NULL) {
        perror("CompleteBinaryTree is NULL\n");
        abort();
    }
    if(self_ptr->m_size == 1) {return RemoveFinal__TYPE_NAME___SPSP_Item(self_ptr);}
    Vector__TYPE_NAME__ * container = self_ptr->m_container;
	__TYPE__ res = container->remove_with_index(container, self_ptr->m_size - 1);
    self_ptr->m_size = container->size(container);
    return res;
}

BinaryTree__TYPE_NAME___SPSP_NodeInfo CompleteBinaryTree__TYPE_NAME___SPSP_GetNode (CompleteBinaryTree__TYPE_NAME__ * self_ptr, size_t cur_idx) {
    if(cur_idx <= 0 || self_ptr->m_size < cur_idx)
        return WRONG_BINARYTREE___TYPE_NAME___SPSP__NODE_OUT;
	__TYPE__ cur_data = *self_ptr->m_container->at(self_ptr->m_container, cur_idx - 1);
    return (BinaryTree__TYPE_NAME___SPSP_NodeInfo) { .m_idx = cur_idx, .m_data = cur_data };
}

BinaryTree__TYPE_NAME___SPSP_NodeInfo CompleteBinaryTree__TYPE_NAME___SPSP_LeftChild (CompleteBinaryTree__TYPE_NAME__ * self_ptr, size_t cur_idx) {
    return self_ptr->get_node(self_ptr, cur_idx * 2);
}

BinaryTree__TYPE_NAME___SPSP_NodeInfo CompleteBinaryTree__TYPE_NAME___SPSP_RightChild (CompleteBinaryTree__TYPE_NAME__ * self_ptr, size_t cur_idx) {
    return self_ptr->get_node(self_ptr, cur_idx * 2 + 1);
}

void CompleteBinaryTree__TYPE_NAME___SPSP_BFS(const CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t cur_node, void * user_data)
{
    if(self_ptr == NULL) {
        perror("tree ptr NULL error \n");
        abort();
    }

    if(!(0 < cur_node  && cur_node < self_ptr->m_size)) {
        perror("invalid node error \n");
        abort();
    }

    CircularQueue__TYPE_NAME__ *  queue_ptr = CreateCircularQueue__TYPE_NAME__(self_ptr->m_size);
    if(queue_ptr == NULL) {
        perror("queue alloc failed\n");
        abort();
    }

    Vector__TYPE_NAME__ * is_visit_ptr = CreateVector__TYPE_NAME__(self_ptr->m_size);
    if(is_visit_ptr == NULL) {
        perror("vector alloc failed\n");
        abort();
    }

    CompleteBinaryTree__TYPE_NAME__* tree_access_ptr = (CompleteBinaryTree__TYPE_NAME__*)self_ptr;

	BinaryTree__TYPE_NAME___SPSP_TravelInfo * search_data = (BinaryTree__TYPE_NAME___SPSP_TravelInfo*) user_data;

    queue_ptr->enqueue(queue_ptr, cur_node);

    while(!queue_ptr->is_empty(queue_ptr)) {
        int cur_idx = queue_ptr->dequeue(queue_ptr);

		if(*is_visit_ptr->at(is_visit_ptr, cur_idx) != 0)
            continue;

        *(is_visit_ptr->at(is_visit_ptr, cur_idx)) = true;

        BinaryTree__TYPE_NAME___SPSP_NodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_idx);

        search_data->callback(search_data, node_info.m_data);

        BinaryTree__TYPE_NAME___SPSP_NodeInfo nxt_left_child = self_ptr->left_child(tree_access_ptr, cur_idx);
        if(nxt_left_child.m_idx != 0)
            queue_ptr->enqueue(queue_ptr, nxt_left_child.m_idx);

        BinaryTree__TYPE_NAME___SPSP_NodeInfo nxt_right_child = self_ptr->right_child(tree_access_ptr, cur_idx);
        if(nxt_right_child.m_idx != 0)
            queue_ptr->enqueue(queue_ptr, nxt_right_child.m_idx);
    }

    DestroyCircularQueue__TYPE_NAME__(queue_ptr);
    DestroyVector__TYPE_NAME__(is_visit_ptr);
}

void CompleteBinaryTree__TYPE_NAME___SPSP_StackDFSPreorder(const CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t cur_node, void * user_data) {
    if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
        abort();
    }

    if(!(0 < cur_node && cur_node < self_ptr->m_size)) {
        perror("invalid node error \n");
        abort();
    }

    Stack__TYPE_NAME__ * stack_ptr = CreateStack__TYPE_NAME__(self_ptr->m_size);
    if(stack_ptr == NULL) {
        perror("stack alloc failed\n");
        abort();
    }

    Vector__TYPE_NAME__ * is_visit_ptr = CreateVector__TYPE_NAME__(self_ptr->m_size);
    if(is_visit_ptr == NULL) {
        perror("vector alloc failed\n");
        abort();
    }

    if(self_ptr->m_size == 0) {
        perror("tree empty\n");
        return;
    }


    BinaryTree__TYPE_NAME___SPSP_TravelInfo * search_data = (BinaryTree__TYPE_NAME___SPSP_TravelInfo*) user_data;

    CompleteBinaryTree__TYPE_NAME__* tree_access_ptr = (CompleteBinaryTree__TYPE_NAME__*) self_ptr;

    stack_ptr->push(stack_ptr, cur_node);
    int cur_idx, nxt_idx;

    while(!stack_ptr->is_empty(stack_ptr)) {
        int cur_idx = stack_ptr->pop(stack_ptr);
        if(*is_visit_ptr->at(is_visit_ptr, cur_idx) != 0) continue;
        *(is_visit_ptr->at(is_visit_ptr, cur_idx)) = true;

        BinaryTree__TYPE_NAME___SPSP_NodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_idx);

        search_data->callback(search_data, node_info.m_data);

        BinaryTree__TYPE_NAME___SPSP_NodeInfo nxt_right_child = self_ptr->right_child(tree_access_ptr, cur_idx);

        if(nxt_right_child.m_idx != 0)
            stack_ptr->push(stack_ptr, nxt_right_child.m_idx);

        BinaryTree__TYPE_NAME___SPSP_NodeInfo nxt_left_child = self_ptr->left_child(tree_access_ptr, cur_idx);

        if(nxt_left_child.m_idx != 0)
            stack_ptr->push(stack_ptr, nxt_left_child.m_idx);

    }

    DestroyStack__TYPE_NAME__(stack_ptr);
    DestroyVector__TYPE_NAME__(is_visit_ptr);
}

void CompleteBinaryTree__TYPE_NAME___SPSP_StackDFSInorder(const CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t cur_node, void * user_data) {
    if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
        abort();
    }

    if(!(0 < cur_node  && cur_node < self_ptr->m_size)) {
        perror("invalid node error \n");
        abort();
    }

    StackInt * stack_ptr = CreateStack__TYPE_NAME__(self_ptr->m_size);
    if(stack_ptr == NULL) {
        perror("stack alloc failed\n");
        abort();
    }

    Vector__TYPE_NAME__ * is_visit_ptr = CreateVector__TYPE_NAME__(self_ptr->m_size);
    if(is_visit_ptr == NULL) {
        perror("vector alloc failed\n");
        abort();
    }

    if(self_ptr->m_size == 0) {
        perror("tree empty\n");
        return;
    }


    BinaryTree__TYPE_NAME___SPSP_TravelInfo * search_data = (BinaryTree__TYPE_NAME___SPSP_TravelInfo*) user_data;

    CompleteBinaryTree__TYPE_NAME__* tree_access_ptr = (CompleteBinaryTree__TYPE_NAME__*) self_ptr;
    stack_ptr->push(stack_ptr, cur_node);
    int cur_idx, nxt_idx;

    while(!stack_ptr->is_empty(stack_ptr)) {

        cur_idx = stack_ptr->top(stack_ptr);
        nxt_idx = self_ptr->left_child(tree_access_ptr, cur_idx).m_idx;
        if(nxt_idx != 0 && *is_visit_ptr->at(is_visit_ptr, nxt_idx) == 0) {
            while(nxt_idx != 0) {
                if(*is_visit_ptr->at(is_visit_ptr, nxt_idx) != 0) break;
                stack_ptr->push(stack_ptr, nxt_idx);
                nxt_idx = self_ptr->left_child(tree_access_ptr, nxt_idx).m_idx;
            }
        }

        int end_idx = stack_ptr->pop(stack_ptr);
        if(*is_visit_ptr->at(is_visit_ptr,end_idx) == 0) {
            *(is_visit_ptr->at(is_visit_ptr, end_idx)) = true;
            BinaryTree__TYPE_NAME___SPSP_NodeInfo node_info = self_ptr->get_node(tree_access_ptr, end_idx);

            search_data->callback(search_data, node_info.m_data);
        }

        nxt_idx = self_ptr->right_child(tree_access_ptr, end_idx).m_idx;
        BinaryTree__TYPE_NAME___SPSP_NodeInfo nxt_item = self_ptr->get_node(tree_access_ptr, nxt_idx);
        if(nxt_idx != 0 && *is_visit_ptr->at(is_visit_ptr, nxt_idx) == 0) {
            stack_ptr->push(stack_ptr, nxt_idx);
        }
    }
    DestroyStack__TYPE_NAME__(stack_ptr);
    DestroyVector__TYPE_NAME__(is_visit_ptr);
}

void CompleteBinaryTree__TYPE_NAME___SPSP_StackDFSPostorder(const CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t cur_node, void * user_data) {
    if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
        abort();
    }

    if(!(0 < cur_node  && cur_node < self_ptr->m_size)) {
        perror("invalid node error \n");
        abort();
    }

    StackInt * stack_ptr = CreateStack__TYPE_NAME__(self_ptr->m_size);
    if(stack_ptr == NULL) {
        perror("stack alloc failed\n");
        abort();
    }

    Vector__TYPE_NAME__ * is_visit_ptr = CreateVector__TYPE_NAME__(self_ptr->m_size);
    if(is_visit_ptr == NULL) {
        perror("vector alloc failed\n");
        abort();
    }

    if(self_ptr->m_size == 0) {
        perror("tree empty\n");
        return;
    }


    BinaryTree__TYPE_NAME___SPSP_TravelInfo * search_data = (BinaryTree__TYPE_NAME___SPSP_TravelInfo*) user_data;

    CompleteBinaryTree__TYPE_NAME__* tree_access_ptr = (CompleteBinaryTree__TYPE_NAME__*) self_ptr;
    stack_ptr->push(stack_ptr, cur_node);
    int cur_idx, nxt_idx;

    while(!stack_ptr->is_empty(stack_ptr)) {

        cur_idx = stack_ptr->top(stack_ptr);
        nxt_idx = self_ptr->left_child(tree_access_ptr, cur_idx).m_idx;
        if(nxt_idx != 0 && *is_visit_ptr->at(is_visit_ptr, nxt_idx) == 0) {
            while(nxt_idx != 0) {
                if(*is_visit_ptr->at(is_visit_ptr, nxt_idx) != 0) break;
                stack_ptr->push(stack_ptr, nxt_idx);
                nxt_idx = self_ptr->left_child(tree_access_ptr, nxt_idx).m_idx;
            }
        }

        int end_idx = stack_ptr->pop(stack_ptr);
        if(*is_visit_ptr->at(is_visit_ptr,end_idx) == 0) {
            *(is_visit_ptr->at(is_visit_ptr, end_idx)) = true;
            BinaryTree__TYPE_NAME___SPSP_NodeInfo node_info = self_ptr->get_node(tree_access_ptr, end_idx);

			search_data->callback(search_data, node_info.m_data);
        }

        if(!stack_ptr->is_empty(stack_ptr)) {
            int nxt_idx = self_ptr->right_child(tree_access_ptr, stack_ptr->top(stack_ptr)).m_idx;
            BinaryTree__TYPE_NAME___SPSP_NodeInfo nxt_item = self_ptr->get_node(tree_access_ptr, nxt_idx);
            if(nxt_idx != 0 && *is_visit_ptr->at(is_visit_ptr, nxt_idx) == 0) {
                stack_ptr->push(stack_ptr, nxt_idx);
            }
        }
    }
    DestroyStack__TYPE_NAME__(stack_ptr);
    DestroyVector__TYPE_NAME__(is_visit_ptr);
}

void CompleteBinaryTree__TYPE_NAME___SPSP_RecurseDFSPreorder(const CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t cur_node, void * user_data) {

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

    CompleteBinaryTree__TYPE_NAME__* tree_access_ptr = (CompleteBinaryTree__TYPE_NAME__*) self_ptr;


    BinaryTree__TYPE_NAME___SPSP_TravelInfo * search_data = (BinaryTree__TYPE_NAME___SPSP_TravelInfo*) user_data;

    BinaryTree__TYPE_NAME___SPSP_NodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_node);
    search_data->callback(search_data, node_info.m_data);
    CompleteBinaryTree__TYPE_NAME___SPSP_RecurseDFSPreorder(self_ptr, self_ptr->left_child(tree_access_ptr, cur_node).m_idx, search_data);
    CompleteBinaryTree__TYPE_NAME___SPSP_RecurseDFSPreorder(self_ptr, self_ptr->right_child(tree_access_ptr, cur_node).m_idx, search_data);
}

void CompleteBinaryTree__TYPE_NAME___SPSP_RecurseDFSInorder(const CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t cur_node, void * user_data) {

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

    CompleteBinaryTree__TYPE_NAME__* tree_access_ptr = (CompleteBinaryTree__TYPE_NAME__*) self_ptr;

    BinaryTree__TYPE_NAME___SPSP_TravelInfo * search_data = (BinaryTree__TYPE_NAME___SPSP_TravelInfo*) user_data;

    CompleteBinaryTree__TYPE_NAME___SPSP_RecurseDFSInorder(self_ptr, self_ptr->left_child(tree_access_ptr, cur_node).m_idx , search_data);
    BinaryTree__TYPE_NAME___SPSP_NodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_node);
    search_data->callback(search_data, node_info.m_data);
    CompleteBinaryTree__TYPE_NAME___SPSP_RecurseDFSInorder(self_ptr, self_ptr->right_child(tree_access_ptr, cur_node).m_idx, search_data);
}

void CompleteBinaryTree__TYPE_NAME___SPSP_RecurseDFSPostorder(const CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t cur_node, void * user_data) {

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

    CompleteBinaryTree__TYPE_NAME__* tree_access_ptr = (CompleteBinaryTree__TYPE_NAME__*) self_ptr;


    BinaryTree__TYPE_NAME___SPSP_TravelInfo * search_data = (BinaryTree__TYPE_NAME___SPSP_TravelInfo*) user_data;

    CompleteBinaryTree__TYPE_NAME___SPSP_RecurseDFSPostorder(self_ptr, self_ptr->left_child(tree_access_ptr, cur_node).m_idx, search_data);
    CompleteBinaryTree__TYPE_NAME___SPSP_RecurseDFSPostorder(self_ptr, self_ptr->right_child(tree_access_ptr, cur_node).m_idx, search_data);
    BinaryTree__TYPE_NAME___SPSP_NodeInfo node_info = self_ptr->get_node(tree_access_ptr, cur_node);
    search_data->callback(search_data, node_info.m_data);

}

void CompleteBinaryTree__TYPE_NAME___SPSP_SwapNode(CompleteBinaryTree__TYPE_NAME__ * const self_ptr, size_t a_node, size_t b_node) {
        if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
        abort();
    }

    if(self_ptr->m_size == 0) {
        perror("tree empty\n");
        return;
    }
    BinaryTree__TYPE_NAME___SPSP_NodeInfo a_node_info = self_ptr->get_node(self_ptr, a_node);
    BinaryTree__TYPE_NAME___SPSP_NodeInfo b_node_info = self_ptr->get_node(self_ptr, b_node);
    *(self_ptr->m_container->at(self_ptr->m_container, a_node-1)) = b_node_info.m_data;
    *(self_ptr->m_container->at(self_ptr->m_container, b_node-1)) = a_node_info.m_data;
}
