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
    .m_head_idx = 0,
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
    self_ptr->m_size++;
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
    self_ptr->m_size--;
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
    self_ptr->m_size--;
    return res;
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
        int cur_idx = queue_ptr->dequeue(queue_ptr);
        if(is_visit_ptr->read_at(is_visit_ptr, cur_idx) != 0) {
            continue;
        }
        *(is_visit_ptr->at(is_visit_ptr, cur_idx)) = 1;
        BinaryTreeNodeOut data = self_ptr->get_node(tree_access_ptr, cur_idx);
        if(print_flag == true)
            printf("%d ", data.m_data);
        else
            *(user_data + visit_count++) = data.m_data;

        BinaryTreeNodeOut nxt_left_child = self_ptr->left_child(tree_access_ptr, cur_idx);
        if(nxt_left_child.m_idx != 0)
            queue_ptr->enqueue(queue_ptr, nxt_left_child.m_idx);

        BinaryTreeNodeOut nxt_right_child = self_ptr->right_child(tree_access_ptr, cur_idx);
        if(nxt_right_child.m_idx != 0)
            queue_ptr->enqueue(queue_ptr, nxt_right_child.m_idx);
    }
    if(print_flag == true)
        printf("\n");

    DestroyQueue(queue_ptr);
    DestroyVector(is_visit_ptr);
}

void CompleteBinaryTreeStackDFSPreorder(const CompleteBinaryTree * const self_ptr, int * user_data) {
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

    bool print_flag = false;
    int visit_count = 0;
    if(user_data == NULL)
        print_flag = true;

    CompleteBinaryTree* tree_access_ptr = (CompleteBinaryTree*) self_ptr;
    int root = self_ptr->m_root;
    stack_ptr->push(stack_ptr, root);
    int cur_idx, nxt_idx;
    int LOOP_MAX = 1000;

    while(!stack_ptr->is_empty(stack_ptr)) {
        int cur_idx = stack_ptr->pop(stack_ptr);
        if(is_visit_ptr->read_at(is_visit_ptr, cur_idx) != 0) {
            continue;
        }
        *(is_visit_ptr->at(is_visit_ptr, cur_idx)) = 1;

        BinaryTreeNodeOut data = self_ptr->get_node(tree_access_ptr, cur_idx);
        // printf("index %d, data %d\n", data.m_idx, data.m_data);

        if(print_flag == true)
            printf("%d ", data.m_idx);
        else
            *(user_data + visit_count++) = data.m_data;
        BinaryTreeNodeOut nxt_right_child = self_ptr->right_child(tree_access_ptr, cur_idx);
        // printf("index %d, data %d\n", nxt_right_child.m_idx, nxt_right_child.m_data);
        if(nxt_right_child.m_idx != 0)
            stack_ptr->push(stack_ptr, nxt_right_child.m_idx);

        BinaryTreeNodeOut nxt_left_child = self_ptr->left_child(tree_access_ptr, cur_idx);
        // printf("index %d, data %d\n", nxt_left_child.m_idx, nxt_left_child.m_data);
        if(nxt_left_child.m_idx != 0)
            stack_ptr->push(stack_ptr, nxt_left_child.m_idx);

    }
    if(print_flag == true)
        printf("\n");

    DestroyStack(stack_ptr);
    DestroyVector(is_visit_ptr);
}

void CompleteBinaryTreeStackDFSInorder(const CompleteBinaryTree * const self_ptr, int * user_data) {
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
    bool print_flag = false;
    int visit_count = 0;
    if(user_data == NULL)
        print_flag = true;

    CompleteBinaryTree* tree_access_ptr = (CompleteBinaryTree*) self_ptr;
    int root = self_ptr->m_root;
    stack_ptr->push(stack_ptr, root);
    int cur_idx, nxt_idx;
    int LOOP_MAX = 1000;

    while(!stack_ptr->is_empty(stack_ptr)) {
        if(--LOOP_MAX <= 0) {perror("INF LOOP ERROR!\n"); abort();}

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
            BinaryTreeNodeOut data = self_ptr->get_node(tree_access_ptr, end_idx);
            if(print_flag == true)
                printf("%d ", data.m_idx);
            else
                *(user_data + visit_count++) = data.m_data;
        }

        nxt_idx = self_ptr->right_child(tree_access_ptr, end_idx).m_idx;
        BinaryTreeNodeOut nxt_item = self_ptr->get_node(tree_access_ptr, nxt_idx);
        // printf("index %d, data %d\n", nxt_item.m_idx, nxt_item.m_data);
        if(nxt_idx != 0 && is_visit_ptr->read_at(is_visit_ptr, nxt_idx) == 0) {
            stack_ptr->push(stack_ptr, nxt_idx);
        }
    }
    DestroyStack(stack_ptr);
    DestroyVector(is_visit_ptr);
}

void CompleteBinaryTreeStackDFSPostorder(const CompleteBinaryTree * const self_ptr, int * user_data) {
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
    bool print_flag = false;
    int visit_count = 0;
    if(user_data == NULL)
        print_flag = true;

    CompleteBinaryTree* tree_access_ptr = (CompleteBinaryTree*) self_ptr;
    int root = self_ptr->m_root;
    stack_ptr->push(stack_ptr, root);
    int cur_idx, nxt_idx;
    int LOOP_MAX = 1000;

    while(!stack_ptr->is_empty(stack_ptr)) {
        if(--LOOP_MAX <= 0) {perror("INF LOOP ERROR!\n"); abort();}

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
            BinaryTreeNodeOut data = self_ptr->get_node(tree_access_ptr, end_idx);
            if(print_flag == true)
                printf("%d\n", data.m_idx);
            else
                *(user_data + visit_count++) = data.m_data;
        }

        if(!stack_ptr->is_empty(stack_ptr)) {
            int nxt_idx = self_ptr->right_child(tree_access_ptr, stack_ptr->top(stack_ptr)).m_idx;
            BinaryTreeNodeOut nxt_item = self_ptr->get_node(tree_access_ptr, nxt_idx);
            if(nxt_idx != 0 && is_visit_ptr->read_at(is_visit_ptr, nxt_idx) == 0) {
                stack_ptr->push(stack_ptr, nxt_idx);
            }
        }
    }
    DestroyStack(stack_ptr);
    DestroyVector(is_visit_ptr);
}

void CompleteBinaryTreeRecurseDFSPreorder(const CompleteBinaryTree * const self_ptr, int * user_data) {
    static unsigned used_data_size = 0;
    int prev_data_size = used_data_size;

    if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
        abort();
    }

    if(self_ptr->m_size == 0) {
        perror("tree empty\n");
        return;
    }
    unsigned prev_root = self_ptr->m_head_idx;

    bool print_flag = false;
    int visit_count = 0;
    if(user_data == NULL)
        print_flag = true;

    CompleteBinaryTree* tree_access_ptr = (CompleteBinaryTree*) self_ptr;

    unsigned cur_root = tree_access_ptr->m_head_idx;
    unsigned nxt_root = 0;
    BinaryTreeNodeOut data = self_ptr->get_node(tree_access_ptr, cur_root);

    if(used_data_size >= self_ptr->m_size) {
        used_data_size = 0;
        tree_access_ptr->m_head_idx = 1;
        return;
    }

    if(print_flag == true)
        printf("%d\n", data.m_idx);
    else
        *(user_data + (used_data_size++)) = data.m_data;

    nxt_root = self_ptr->left_child(tree_access_ptr, cur_root).m_idx;
    if(nxt_root != 0) {
        tree_access_ptr->m_head_idx = nxt_root;
        CompleteBinaryTreeRecurseDFSPreorder(self_ptr, user_data);
    }
    tree_access_ptr->m_head_idx = cur_root;

    nxt_root = self_ptr->right_child(tree_access_ptr, cur_root).m_idx;
    if(nxt_root != 0) {
        tree_access_ptr->m_head_idx = nxt_root;
        CompleteBinaryTreeRecurseDFSPreorder(self_ptr, user_data);
    }
    tree_access_ptr->m_head_idx = cur_root;
    tree_access_ptr->m_head_idx = prev_root;
}

void CompleteBinaryTreeRecurseDFSInorder(const CompleteBinaryTree * const self_ptr, int * user_data) {
    static unsigned used_data_size = 0;
    int prev_data_size = used_data_size;

    if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
        abort();
    }

    if(self_ptr->m_size == 0) {
        perror("tree empty\n");
        return;
    }
    unsigned prev_root = self_ptr->m_head_idx;

    bool print_flag = false;
    int visit_count = 0;
    if(user_data == NULL)
        print_flag = true;

    CompleteBinaryTree* tree_access_ptr = (CompleteBinaryTree*) self_ptr;

    unsigned cur_root = tree_access_ptr->m_head_idx;
    unsigned nxt_root = 0;

    if(used_data_size >= self_ptr->m_size) {
        used_data_size = 0;
        tree_access_ptr->m_head_idx = 1;
        return;
    }

    nxt_root = self_ptr->left_child(tree_access_ptr, cur_root).m_idx;
    if(nxt_root != 0) {
        tree_access_ptr->m_head_idx = nxt_root;
        CompleteBinaryTreeRecurseDFSInorder(self_ptr, user_data);
    }
    tree_access_ptr->m_head_idx = cur_root;

    BinaryTreeNodeOut data = self_ptr->get_node(tree_access_ptr, cur_root);
    if(print_flag == true)
        printf("%d\n", data.m_idx);
    else
        *(user_data + (used_data_size++)) = data.m_data;

    nxt_root = self_ptr->right_child(tree_access_ptr, cur_root).m_idx;
    if(nxt_root != 0) {
        tree_access_ptr->m_head_idx = nxt_root;
        CompleteBinaryTreeRecurseDFSInorder(self_ptr, user_data);
    }
    tree_access_ptr->m_head_idx = cur_root;
    tree_access_ptr->m_head_idx = prev_root;
}

void CompleteBinaryTreeRecurseDFSPostorder(const CompleteBinaryTree * const self_ptr, int * user_data) {
    static unsigned used_data_size = 0;
    int prev_data_size = used_data_size;

    if(self_ptr == NULL) {
        perror("tree ptr NULL error\n");
        abort();
    }

    if(self_ptr->m_size == 0) {
        perror("tree empty\n");
        return;
    }
    unsigned prev_root = self_ptr->m_head_idx;

    bool print_flag = false;
    int visit_count = 0;
    if(user_data == NULL)
        print_flag = true;

    CompleteBinaryTree* tree_access_ptr = (CompleteBinaryTree*) self_ptr;

    unsigned cur_root = tree_access_ptr->m_head_idx;
    unsigned nxt_root = 0;

    if(used_data_size >= self_ptr->m_size) {
        used_data_size = 0;
        tree_access_ptr->m_head_idx = 1;
        return;
    }

    nxt_root = self_ptr->left_child(tree_access_ptr, cur_root).m_idx;
    if(nxt_root != 0) {
        tree_access_ptr->m_head_idx = nxt_root;
        CompleteBinaryTreeRecurseDFSPostorder(self_ptr, user_data);
    }
    tree_access_ptr->m_head_idx = cur_root;

    nxt_root = self_ptr->right_child(tree_access_ptr, cur_root).m_idx;
    if(nxt_root != 0) {
        tree_access_ptr->m_head_idx = nxt_root;
        CompleteBinaryTreeRecurseDFSPostorder(self_ptr, user_data);
    }
    tree_access_ptr->m_head_idx = cur_root;
    tree_access_ptr->m_head_idx = prev_root;

    BinaryTreeNodeOut data = self_ptr->get_node(tree_access_ptr, cur_root);
    if(print_flag == true)
        printf("%d\n", data.m_idx);
    else
        *(user_data + (used_data_size++)) = data.m_data;
}
