#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stack.h>
#include <queue.h>
#include "tree.h"

static const CompleteBinaryTree DEFAULT_COMPLETE_BINARYTREE_VTABLE_TEMPLATE = {
    .m_container = NULL,
    .m_size = 0,
    .m_root = 0,
    .size = CompleteBinaryTreeSize,
    .max_depth = CompleteBinaryTreeMaxDepth,
    .get_node = CompleteBinaryTreeGetNode,
    .left_child = CompleteBinaryTreeLeftChild,
    .right_child = CompleteBinaryTreeRightChild,
    .insert = CompleteBinaryTreeInsert,
    .remove = CompleteBinaryTreeRemove
};

static const BinaryTreeNodeOut WRONG_BINARYTREE_NODE_OUT = {
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
    memcpy(temp_complete_tree, &DEFAULT_COMPLETE_BINARYTREE_VTABLE_TEMPLATE, sizeof(CompleteBinaryTree));
    Vector * temp_container = malloc(sizeof(Vector));
    if(temp_container == NULL) {
        perror("vector allocate failed\n");
        abort();
    }
    temp_container = CreateVector(15);

    temp_complete_tree->m_container = temp_container;
    return temp_complete_tree;
}

void    DestroyCompleteBinaryTree(CompleteBinaryTree * self_ptr)
{
    if(self_ptr == NULL || self_ptr->m_container == NULL) {
        perror("prevent double free\n");
        return;
    }
    if(self_ptr->m_container != NULL) {
        free(self_ptr->m_container);
    }
    if(self_ptr != NULL) {
        free(self_ptr);
    }
    return;
}

size_t     CompleteBinaryTreeSize (CompleteBinaryTree * self_ptr)
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
    Vector* container = self_ptr->m_container;
    return container->delete(container, last_idx);
}

int     CompleteBinaryTreeRemove (CompleteBinaryTree * self_ptr)
{
    if(self_ptr == NULL) {
        perror("CompleteBinaryTree is NULL\n");
        abort();
    }
    if(self_ptr->m_size == 1) {return RemoveFinalItem(self_ptr);}
    Vector * container = self_ptr->m_container;
    return container->delete(container, self_ptr->m_size - 1);
}

BinaryTreeNodeOut CompleteBinaryTreeGetNode (CompleteBinaryTree * self_ptr, unsigned cur_idx) {
    if(cur_idx <= 0 || self_ptr->m_size < cur_idx)
        return WRONG_BINARYTREE_NODE_OUT;
    return (BinaryTreeNodeOut) {.m_idx = cur_idx, .m_data = self_ptr->m_container->read_at(self_ptr->m_container, cur_idx - 1)};
}

BinaryTreeNodeOut CompleteBinaryTreeLeftChild (CompleteBinaryTree * self_ptr, unsigned cur_idx) {
    return self_ptr->get_node(self_ptr, cur_idx * 2);
}

BinaryTreeNodeOut CompleteBinaryTreeRightChild (CompleteBinaryTree * self_ptr, unsigned cur_idx) {
    return self_ptr->get_node(self_ptr, cur_idx * 2 + 1);
}

void CompleteBinaryTreeBFS(const CompleteBinaryTree * const self_ptr, int * user_data)
{
    if(self_ptr == NULL) {
        perror("tree ptr NULL error \n");
        abort();
    }

    Queue *  queue_ptr = CreateQueue();
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
    int visit_count = 0;
    if(user_data == NULL)
        print_flag = true;

    queue_ptr->enqueue(queue_ptr, tree_access_ptr->m_root);

    while(!queue_ptr->is_empty(queue_ptr)) {
        int cur_idx = queue_ptr->dequeue(queue_ptr) - 1;
        if(is_visit_ptr->read_at(is_visit_ptr, cur_idx) != 0) {
            continue;
        }
        *(is_visit_ptr->at(is_visit_ptr, cur_idx)) = 1;
        BinaryTreeNodeOut data = self_ptr->get_node(tree_access_ptr, cur_idx);
        if(print_flag == true)
            printf("%d ", data.m_data);
        else
            *(user_data + visit_count) = data.m_data;

        BinaryTreeNodeOut nxt_left_child = self_ptr->left_child(tree_access_ptr, cur_idx);
        if(nxt_left_child.m_idx != 0)
            queue_ptr->enqueue(queue_ptr, nxt_left_child.m_idx);

        BinaryTreeNodeOut nxt_right_child = self_ptr->right_child(tree_access_ptr, cur_idx);
        if(nxt_right_child.m_idx != 0)
            queue_ptr->enqueue(queue_ptr, nxt_right_child.m_idx);
    }

    DestroyQueue(queue_ptr);
    DestroyVector(is_visit_ptr);
}

void CompleteBinaryTreeDFSPreorder(const CompleteBinaryTree * const self_ptr, int * user_data) {
    if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
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

    int root = self_ptr->m_root;
    stack_ptr->push(stack_ptr, root);

    bool print_flag = false;
    int visit_count = 0;
    if(user_data == NULL)
        print_flag = true;

    CompleteBinaryTree* tree_access_ptr = (CompleteBinaryTree*)self_ptr;

    while(!stack_ptr->is_empty(stack_ptr)) {
        int cur_idx = stack_ptr->top(stack_ptr);
        if(is_visit_ptr->read_at(is_visit_ptr, cur_idx) != 0) {
            continue;
        }
        *(is_visit_ptr->at(is_visit_ptr, cur_idx)) = 1;
        BinaryTreeNodeOut data = self_ptr->get_node(tree_access_ptr, cur_idx);
        if(print_flag == true)
            printf("%d ", data.m_data);
        else
            *(user_data + visit_count) = data.m_data;

        BinaryTreeNodeOut nxt_left_child = self_ptr->left_child(tree_access_ptr, cur_idx);
        if(nxt_left_child.m_idx != 0)
            stack_ptr->push(stack_ptr, nxt_left_child.m_idx);

        BinaryTreeNodeOut nxt_right_child = self_ptr->right_child(tree_access_ptr, cur_idx);
        if(nxt_right_child.m_idx != 0)
            stack_ptr->push(stack_ptr, nxt_right_child.m_idx);
    }

    DestroyStack(stack_ptr);
    DestroyVector(is_visit_ptr);
}

void CompleteBinaryTreeDFSInorder(const CompleteBinaryTree * const self_ptr, int * user_data) {

}

void CompleteBinaryTreeDFSPostorder(const CompleteBinaryTree * const self_ptr, int * user_data) {

}
