#ifndef __HEADER_GUARD_TREE__
#define __HEADER_GUARD_TREE__

#include <stdbool.h>
#include <vector.h>

typedef enum {
    LEFT_INSERT_NODE    = -1,
    RIGHT_INSERT_NODE   = 1
} BinaryTreeInsertMode;

typedef void    * KEY;
typedef int     *(KEY_COMPARE_FUNCTION)(const KEY, const KEY);

typedef struct BinaryTree BinaryTree;
typedef struct BinaryTreeNode BinaryTreeNode;
typedef struct BinaryTreeNodeGenericInfo BinaryTreeNodeGenericInfo;

struct BinaryTreeNodeGenericInfo {
    KEY m_key;
    void * m_data;
};

struct BinaryTreeNode {
    KEY m_key;
    void * m_data;
    BinaryTreeNode * m_left_child;
    BinaryTreeNode * m_right_child;
    BinaryTreeNode * m_left_sibling;
    BinaryTreeNode * m_right_sibling;
};

struct BinaryTree {
    unsigned m_size;
    BinaryTreeNode * m_root;
    BinaryTreeNode * m_current;

    unsigned            ( * const size)             (BinaryTree * self_ptr);
    BinaryTreeNode *    ( * const insert)           (BinaryTree * self_ptr, BinaryTreeNode * current_node, BinaryTreeInsertMode insert_mode, KEY key, void *data);
    BinaryTreeNode *    ( * const find)             (BinaryTree * self_ptr, BinaryTreeNode * current_node, KEY key);
    BinaryTreeNodeGenericInfo ( * const remove)     (BinaryTree * self_ptr, BinaryTreeNode * current_node);
};

BinaryTreeNode *            CreateBinaryTreeNode();
void                        DestroyBinaryTreeNode(BinaryTreeNode * self_ptr);
BinaryTree *                CreateBinaryTree();
void                        DestroyBinaryTree(BinaryTree * self_ptr);
unsigned                    BinaryTreeSize(BinaryTreeNode * self_ptr);
BinaryTreeNode *            BinaryTreeInsertNode(BinaryTree * self_ptr, BinaryTreeNode * current_node, BinaryTreeInsertMode insert_mode, KEY key, void *data);
BinaryTreeNode *            BinaryTreeFindNode(BinaryTree * self_ptr,   BinaryTreeNode * current_node, KEY key);
BinaryTreeNodeGenericInfo   BinaryTreeRemoveNode(BinaryTree * self_ptr, BinaryTreeNode * current_node);

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
