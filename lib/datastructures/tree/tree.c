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
    BinaryTreeSearchInfo * search_data = NULL;
    if(user_data == NULL) print_flag = true;
    else search_data = (BinaryTreeSearchInfo*) user_data; // 🚸 C에서는 언어차원에서 타입 캐스팅에 대한 검증을 할 수 없다.. 이건 좀 어렵네

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

    DestroyQueue(queue_ptr);
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
    BinaryTreeSearchInfo * search_data = NULL;
    if(user_data == NULL) print_flag = true;
    else search_data = (BinaryTreeSearchInfo*) user_data; // 🚸 C에서는 언어차원에서 타입 캐스팅에 대한 검증을 할 수 없다.. 이건 좀 어렵네

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
    BinaryTreeSearchInfo * search_data = NULL;
    if(user_data == NULL) print_flag = true;
    else search_data = (BinaryTreeSearchInfo*) user_data; // 🚸 C에서는 언어차원에서 타입 캐스팅에 대한 검증을 할 수 없다.. 이건 좀 어렵네

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
    BinaryTreeSearchInfo * search_data = NULL;
    if(user_data == NULL) print_flag = true;
    else search_data = (BinaryTreeSearchInfo*) user_data; // 🚸 C에서는 언어차원에서 타입 캐스팅에 대한 검증을 할 수 없다.. 이건 좀 어렵네

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
    BinaryTreeSearchInfo * search_data = NULL;
    if(user_data == NULL) print_flag = true;
    else search_data = (BinaryTreeSearchInfo*) user_data; // 🚸 C에서는 언어차원에서 타입 캐스팅에 대한 검증을 할 수 없다.. 이건 좀 어렵네

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
    BinaryTreeSearchInfo * search_data = NULL;
    if(user_data == NULL) print_flag = true;
    else search_data = (BinaryTreeSearchInfo*) user_data; // 🚸 C에서는 언어차원에서 타입 캐스팅에 대한 검증을 할 수 없다.. 이건 좀 어렵네


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
    BinaryTreeSearchInfo * search_data = NULL;
    if(user_data == NULL) print_flag = true;
    else search_data = (BinaryTreeSearchInfo*) user_data; // 🚸 C에서는 언어차원에서 타입 캐스팅에 대한 검증을 할 수 없다.. 이건 좀 어렵네

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
