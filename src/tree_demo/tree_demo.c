#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdbool.h>
#include <errno.h>
#include "tree_demo.h"

int bfs_result[10];
int preorder_result[10];
int inorder_result[10];
int postorder_result[10];

const int inputs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int expected_bfs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int expected_preorder[] = {1, 2, 4, 8, 9, 5, 10, 3, 6, 7};
const int expected_inorder[] = {8, 4, 9, 2, 10, 5, 1, 6, 3, 7};
const int expected_postorder[] = {8, 9, 4, 10, 5, 2, 6, 7, 3, 1};

/*
        1
      /   \
     2     3
   /  \   /  \
  4    5 6    7
 / \  /
8  9 10
*/
int complete_binarytree_demo(int argc, char* argv[]) {
    CompleteBinaryTree * complete_binarytree = CreateCompleteBinaryTree();

    for(int i = 1; i <= 10; i++) {
        printf("%d ", i);
        complete_binarytree->insert(complete_binarytree, i);
    }
    printf("\n");

    /// Preorder ///
    printf("Stack Preorder : ");
    CompleteBinaryTreeStackDFSPreorder(complete_binarytree, preorder_result);
    for(int i = 0; i < 10; i++) {
        printf("%d ", preorder_result[i]);
    }
    printf("\n");

    memset(preorder_result, 0, sizeof(preorder_result));

    printf("Recurse Preorder : ");
    CompleteBinaryTreeRecurseDFSPreorder(complete_binarytree, preorder_result);
    for(int i = 0; i < 10; i++) {
        printf("%d ", preorder_result[i]);
    }
    printf("\n");
    printf("head ptr %d\n", complete_binarytree->m_head_idx);

    memset(preorder_result, 0, sizeof(preorder_result));

    /// Inorder ///
    printf("Stack Inorder : ");
    CompleteBinaryTreeStackDFSInorder(complete_binarytree, inorder_result);

    for(int i = 0; i < 10; i++) {
        printf("%d ", inorder_result[i]);
    }
    printf("\n");
    memset(inorder_result, 0, sizeof(inorder_result));

    printf("Recurse Inorder : ");
    CompleteBinaryTreeRecurseDFSInorder(complete_binarytree, inorder_result);

    for(int i = 0; i < 10; i++) {
        printf("%d ", inorder_result[i]);
    }
    printf("\n");
    memset(inorder_result, 0, sizeof(inorder_result));
    printf("head ptr %d\n", complete_binarytree->m_head_idx);

    /// Postorder ///
    printf("Stack Postorder : ");
    CompleteBinaryTreeStackDFSPostorder(complete_binarytree, postorder_result);
    for(int i = 0; i < 10; i++) {
        printf("%d ", postorder_result[i]);
    }
    printf("\n");
    memset(postorder_result, 0, sizeof(postorder_result));

    printf("Recurse Postorder : ");
    CompleteBinaryTreeStackDFSPostorder(complete_binarytree, postorder_result);
    for(int i = 0; i < 10; i++) {
        printf("%d ", postorder_result[i]);
    }
    printf("\n");
    memset(postorder_result, 0, sizeof(postorder_result));

    DestroyCompleteBinaryTree(complete_binarytree);
    return 1;
}
