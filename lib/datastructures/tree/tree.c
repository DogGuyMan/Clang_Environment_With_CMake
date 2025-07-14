#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stack.h>
#include <queue.h>
#include "tree.h"

static const BinaryTreeNodeGenericInfo EMPTY_NODE_GENERIC_INFO = {
    .m_data = 0
};

static const BinaryTree DEFAULT_BINARYTREE_VTABLE_TEMPLATE = {
	.m_data = 0,
	.m_size = 0,
	.m_max_depth = 0,
	.m_root = NULL,
	.m_current = NULL,
	.m_parent = NULL,
	.m_left_child = NULL,
	.m_right_child = NULL,

	.size = BinaryTreeSize,
	.max_depth = BinaryTreeMaxDepth,
	.left_child = BinaryTreeLeftChild,
	.right_child = BinaryTreeRightChild,
	.insert = BinaryTreeInsert,
	.get = BinaryTreeGet,
	.remove = BinaryTreeRemove,
};

BinaryTree *                CreateBinaryTree(){
	BinaryTree * temp_tree = malloc(sizeof(BinaryTree));
	if(temp_tree == NULL) {
		perror("바이너리 트리 메모리 할당 실패");
		return NULL;
	}
	memcpy(temp_tree, &DEFAULT_BINARYTREE_VTABLE_TEMPLATE, sizeof(BinaryTree));
	return temp_tree;
}

void                        DestroyBinaryTree(BinaryTree * self_ptr){
	if(self_ptr == NULL) {
		perror("DestroyBinaryTree 실패");
		return;
	}
	BinaryTreeRemove(self_ptr, self_ptr->m_root);
	free(self_ptr);
}

unsigned        			BinaryTreeSize(BinaryTree * self_ptr, BinaryTree * current_tree){
	if(self_ptr == NULL || current_tree == NULL)
	{
		perror("BinaryTreeSize : 인풋이 널임");
		return -1;
	}
	return current_tree->m_size;
}

void					BinaryTreeUpdateDepth(BinaryTree * self_ptr, BinaryTree * current_tree) {
	if(current_tree->m_left_child != NULL) {
		current_tree->m_max_depth = current_tree->m_left_child->m_max_depth + 1;
		if(current_tree != self_ptr->m_root) {
			BinaryTreeUpdateDepth(self_ptr, current_tree->m_parent);
		}
	}
	else if(current_tree->m_right_child != NULL) {
		current_tree->m_max_depth = current_tree->m_right_child->m_max_depth + 1;
		if(current_tree != self_ptr->m_root) {
			BinaryTreeUpdateDepth(self_ptr, current_tree->m_parent);
		}
	}
	return;
}

unsigned        			BinaryTreeMaxDepth(BinaryTree * self_ptr, BinaryTree * current_tree) {
	return current_tree->m_max_depth;
}

BinaryTree *        		BinaryTreeLeftChild(BinaryTree * self_ptr, BinaryTree * current_tree) {
	return current_tree->m_left_child;
}

BinaryTree *        		BinaryTreeRightChild(BinaryTree * self_ptr, BinaryTree * current_tree) {
	return current_tree->m_right_child;
}


BinaryTree * BinaryTreeFirstInsert(BinaryTree * self_ptr, int data) {
	if(self_ptr == NULL || self_ptr->m_size > 0) {
		perror("BinaryTreeFirstInsert : 최초 삽입 조건이 아님");
		return NULL;
	}
	self_ptr->m_root = self_ptr;
	self_ptr->m_current = self_ptr;
	self_ptr->m_parent = NULL;
	self_ptr->m_data = data;
	self_ptr->m_size = 1;
	self_ptr->m_max_depth = 1;
	return self_ptr;
}

BinaryTree *    			BinaryTreeInsert(	BinaryTree * self_ptr, BinaryTree * current_tree,
												BinaryTreeInsertMode insert_mode,
												BinaryTree * insert_tree, int data ) {
	BinaryTree * new_tree = NULL;
	if(self_ptr == NULL || current_tree == NULL)
	{
		perror("BinaryTreeInsert : 인풋이 널임");
		goto INSERT_FAIL;
	}

	if(self_ptr->m_size == 0)
	{
		return BinaryTreeFirstInsert(self_ptr, data);
	}

	if(insert_tree == NULL ) {
		new_tree = CreateBinaryTree();
		new_tree->m_data = data;
		new_tree->m_root = current_tree->m_root;
		new_tree->m_parent = current_tree;
		new_tree->m_max_depth = 0;
	}
	else {
		new_tree = insert_tree;
		insert_tree->m_root = current_tree->m_root;
		insert_tree->m_parent = current_tree;
	}

	switch (insert_mode)
	{
		case LEFT_INSERT_NODE : {
			if(current_tree->left_child != NULL) {
				perror("BinaryTreeInsert : 좌 자식이 비어 있지 않음");
				goto INSERT_FAIL;
			}
			current_tree->m_left_child = new_tree;
			break;
		}
		case RIGHT_INSERT_NODE : {
			if(current_tree->right_child != NULL) {
				perror("BinaryTreeInsert : 우 자식이 비어 있지 않음");
				goto INSERT_FAIL;
			}
			current_tree->m_right_child = new_tree;
			break;
		}
		default: {
			perror("BinaryTreeInsert : 이상한 삽입 모드\n");
			goto INSERT_FAIL;
		}
	}
	BinaryTreeUpdateDepth(self_ptr, current_tree);
	self_ptr->m_size++;

	return new_tree;

INSERT_FAIL :
	if(new_tree != NULL && new_tree != insert_tree) {
		DestroyBinaryTree(new_tree);
	}
	return NULL;
}

BinaryTreeNodeGenericInfo 	BinaryTreeGet(BinaryTree * self_ptr, BinaryTree * current_tree){
	if(self_ptr == NULL || current_tree == NULL)
	{
		perror("BinaryTreeSize : 인풋이 널임");
		return EMPTY_NODE_GENERIC_INFO;
	}
	BinaryTreeNodeGenericInfo res;
	res.m_data = self_ptr->m_data;
	return res;
}

BinaryTreeNodeGenericInfo 	BinaryTreeRemove(BinaryTree * self_ptr, BinaryTree * current_tree){
	if(self_ptr == NULL || current_tree == NULL)
	{
		perror("BinaryTreeSize : 인풋이 널임");
		return EMPTY_NODE_GENERIC_INFO;
	}

	// POST Order로 삭제해야 한다.
	if(current_tree->m_left_child != NULL)
		BinaryTreeRemove(self_ptr, current_tree->m_left_child);
	if(current_tree->m_right_child != NULL)
		BinaryTreeRemove(self_ptr, current_tree->m_right_child);

	BinaryTreeNodeGenericInfo res;
	res.m_data = self_ptr->m_data;

	if(current_tree->m_left_child == NULL && current_tree->m_right_child == NULL) {
		if(current_tree != current_tree->m_root) {
			if(current_tree->m_parent->m_right_child == current_tree)
				current_tree->m_parent->m_right_child = NULL;
			else if (current_tree->m_parent->m_left_child == current_tree)
				current_tree->m_parent->m_left_child = NULL;
		}

		free(current_tree);
	}

	return res;
}

void BinaryTreeBFS(BinaryTree * self_ptr, BinaryTree * current_tree, void * user_data) {

}

void BinaryTreeLevelOrder(BinaryTree * self_ptr, BinaryTree * current_tree, void * user_data) {

}

void BinaryTreeRecurseDFSPreorder(BinaryTree * self_ptr, BinaryTree * current_tree, void * user_data) {

}

void BinaryTreeRecurseDFSInorder(BinaryTree * self_ptr, BinaryTree * current_tree, void * user_data) {

}

void BinaryTreeRecurseDFSPostorder(BinaryTree * self_ptr, BinaryTree * current_tree, void * user_data) {

}


/*
*
*
*
*/

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
    temp_complete_tree->m_container = CreateVector(TYPE_INT, 15);
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
        DestroyVector(self_ptr->m_container, NULL);
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
	GENERIC_DATA_TYPE push_data = {
		.m_type = TYPE_INT,
		.m_data = &item,
		.m_size = sizeof(int),
	};
    if(container->is_empty(container)) {
        container->push(container, push_data);
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
	GENERIC_DATA_TYPE push_data = {
		.m_type = TYPE_INT,
		.m_data = &item,
		.m_size = sizeof(int),
	};
    container->push(container, push_data);
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
    int res = *((int*)container->delete(container, last_idx).m_data);
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
	int res = *((int*)container->delete(container, self_ptr->m_size - 1).m_data);
    self_ptr->m_size = container->size(container);
    return res;
}

static int IntCompareFunction(const GENERIC_DATA_TYPE lhs, const GENERIC_DATA_TYPE rhs) {
	int lhs_data = *((int *) lhs.m_data);
	int rhs_data = *((int *) rhs.m_data);
	return (lhs_data == rhs_data) ? 0 : ((lhs_data < rhs_data) ? 1 : -1 );
}

int     CompleteBinaryTreeDelete(CompleteBinaryTree * self_ptr, int item) {
    if(self_ptr == NULL) {
        perror("CompleteBinaryTree is NULL\n");
        abort();
    }
    // find
    Vector * container = self_ptr->m_container;
	GENERIC_DATA_TYPE delete_data = {
		.m_type = TYPE_INT,
		.m_data = &item,
		.m_size = sizeof(int),
	};
    int res = *((int*)container->remove(container, delete_data, IntCompareFunction).m_data);
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
