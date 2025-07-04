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
typedef struct BinaryTreeNodeOut BinaryTreeNodeOut;

struct BinaryTreeNodeOut {
    const unsigned m_idx;
    const int m_data;
};

struct CompleteBinaryTree {
    Vector * m_container;
    size_t m_size;
    unsigned m_root;

    size_t (* const size) (CompleteBinaryTree * self_ptr);
    unsigned (* const max_depth) (CompleteBinaryTree * self_ptr);
    void     (* const insert) (CompleteBinaryTree * self_ptr, int item);
    int      (* const remove) (CompleteBinaryTree * self_ptr);
    BinaryTreeNodeOut (* const get_node) (CompleteBinaryTree * self_ptr, unsigned cur_idx);
    BinaryTreeNodeOut (* const left_child) (CompleteBinaryTree * self_ptr, unsigned cur_idx);
    BinaryTreeNodeOut (* const right_child) (CompleteBinaryTree * self_ptr, unsigned cur_idx);
};

CompleteBinaryTree * CreateCompleteBinaryTree();
void    DestroyCompleteBinaryTree(CompleteBinaryTree * self_ptr);
size_t     CompleteBinaryTreeSize (CompleteBinaryTree * self_ptr);
unsigned     CompleteBinaryTreeMaxDepth (CompleteBinaryTree * self_ptr);
void    CompleteBinaryTreeInsert (CompleteBinaryTree * self_ptr, int item);
int     CompleteBinaryTreeRemove (CompleteBinaryTree * self_ptr);
BinaryTreeNodeOut CompleteBinaryTreeGetNode (CompleteBinaryTree * self_ptr, unsigned cur_idx);
BinaryTreeNodeOut CompleteBinaryTreeLeftChild (CompleteBinaryTree * self_ptr, unsigned cur_idx);
BinaryTreeNodeOut CompleteBinaryTreeRightChild (CompleteBinaryTree * self_ptr, unsigned cur_idx);
#endif//__HEADER_GUARD_TREE__
