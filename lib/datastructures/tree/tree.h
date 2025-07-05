#ifndef __HEADER_GUARD_TREE__
#define __HEADER_GUARD_TREE__

#include <stdbool.h>
#include <vector.h>

typedef struct Tree Tree;
typedef struct TreeNode TreeNode;

struct Tree {
    int m_idx;
    int m_data;
    int m_childs_count;

    Tree * m_left;
    Tree * m_right;
    Tree * m_child_nodes;

    int     ( * const size)         (Tree * self_ptr);
    Tree *  ( * const left_tree)    (Tree * self_ptr);
    Tree *  ( * const right_tree)   (Tree * self_ptr);
    void    ( * const add_left )    (Tree * self_ptr, Tree * sub_tree );
    void    ( * const add_right )   (TreeNode * self_ptr, Tree * sub_tree );
    Tree *  ( * const remove_left ) (TreeNode * self_ptr, Tree * sub_tree );
    Tree *  ( * const remove_right )(TreeNode * self_ptr, Tree * sub_tree );
};

Tree *  CreateTree();
void    DestroyTree(Tree * self_ptr);

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

void GenericTreeDFS(const void * const tree_ptr, TreeNodeCallback order_callback, void * user_data);

#endif//__HEADER_GUARD_TREE__
