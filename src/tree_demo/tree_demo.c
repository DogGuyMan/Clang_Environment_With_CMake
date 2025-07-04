#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdbool.h>
#include <errno.h>
#include "tree_demo.h"

static int bfs_result[100];
static int preorder_result[100];
static int inorder_result[100];
static int postorder_result[100];

static const int inputs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static const int expected_bfs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static const int expected_preorder[] = {1, 2, 4, 8, 9, 5, 10, 3, 6, 7};
static const int expected_inorder[] = {8, 4, 9, 2, 10, 5, 1, 6, 3, 7};
static const int expected_postorder[] = {8, 9, 4, 10, 5, 2, 6, 7, 3, 1};

int complete_binarytree_demo(int argc, char* argv[]) {
    // 5 4
    // 5 2
    // 1 2
    // 3 4
    // 3 1
    CompleteBinaryTree * complete_binarytree = CreateCompleteBinaryTree();
    for(int i = 0; i < 10; i++) {
        complete_binarytree->insert(complete_binarytree, i);
    }
    CompleteBinaryTreeBFS(complete_binarytree, NULL);
    DestroyCompleteBinaryTree(complete_binarytree);
    return 1;
}
