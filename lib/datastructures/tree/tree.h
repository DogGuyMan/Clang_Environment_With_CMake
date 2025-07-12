#ifndef __HEADER_GUARD_TREE__
#define __HEADER_GUARD_TREE__

#include <stdbool.h>
#include <vector.h>

typedef enum {
    LEFT_INSERT_NODE    = -1,
    RIGHT_INSERT_NODE   = 1
} BinaryTreeInsertMode;

/*
*
*
*
*/

typedef struct BinaryTree BinaryTree;
typedef struct BinaryTreeNode BinaryTreeNode;
typedef struct BinaryTreeNodeGenericInfo BinaryTreeNodeGenericInfo;

struct BinaryTreeNodeGenericInfo {
    int m_data;
};

struct BinaryTree {
    int m_data;
    unsigned m_size;
	unsigned m_max_depth;
    BinaryTree * m_root;
    BinaryTree * m_current;
	BinaryTree * m_parent;
    BinaryTree * m_left_child;
    BinaryTree * m_right_child;

    unsigned        ( * const size)					(BinaryTree * self_ptr, BinaryTree * current_tree);
    unsigned        ( * const max_depth)			(BinaryTree * self_ptr, BinaryTree * current_tree);
    BinaryTree * 	( * const left_child)			(BinaryTree * self_ptr, BinaryTree * current_tree);
    BinaryTree * 	( * const right_child)			(BinaryTree * self_ptr, BinaryTree * current_tree);
    BinaryTree *    ( * const insert)           	(BinaryTree * self_ptr, BinaryTree * current_tree, BinaryTreeInsertMode insert_mode, BinaryTree * insert_tree, int data);
	BinaryTreeNodeGenericInfo ( * const get)		(BinaryTree * self_ptr, BinaryTree * current_node);
    BinaryTreeNodeGenericInfo ( * const remove)     (BinaryTree * self_ptr, BinaryTree * current_node);
};

BinaryTree *                CreateBinaryTree();
void                        DestroyBinaryTree(BinaryTree * self_ptr);

unsigned        			BinaryTreeSize(BinaryTree * self_ptr, BinaryTree * current_tree);
unsigned        			BinaryTreeMaxDepth(BinaryTree * self_ptr, BinaryTree * current_tree);
BinaryTree *        		BinaryTreeLeftChild(BinaryTree * self_ptr, BinaryTree * current_tree);
BinaryTree *        		BinaryTreeRightChild(BinaryTree * self_ptr, BinaryTree * current_tree);
BinaryTree *    			BinaryTreeInsert(BinaryTree * self_ptr, BinaryTree * current_tree, BinaryTreeInsertMode insert_mode, BinaryTree * insert_tree, int data);
BinaryTreeNodeGenericInfo 	BinaryTreeGet(BinaryTree * self_ptr, BinaryTree * current_node);
BinaryTreeNodeGenericInfo 	BinaryTreeRemove(BinaryTree * self_ptr, BinaryTree * current_node);

typedef struct CompleteBinaryTree CompleteBinaryTree;
typedef struct BinaryTreeNodeInfo BinaryTreeNodeInfo;
typedef struct BinaryTreeSearchInfo BinaryTreeSearchInfo;

struct BinaryTreeNodeInfo {
    const unsigned m_idx;
    const int m_data;
};

struct BinaryTreeSearchInfo
{
    int * const m_array_ptr;
    int m_size;
    void (* const callback) (BinaryTreeSearchInfo * self_ptr, int data);
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

// Dequeue를 사용해 구현할 수 있다.
void GenericTreeLevelOrder(const void * const tree_ptr, void * user_data);
void GenericTreeBFS(const void * const tree_ptr, void * user_data);
void GenericTreeDFS(const void * const tree_ptr, TreeNodeCallback order_callback, void * user_data);

#endif//__HEADER_GUARD_TREE__
