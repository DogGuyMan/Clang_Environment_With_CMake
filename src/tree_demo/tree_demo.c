#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdbool.h>
#include <queue.h>
#include <errno.h>
#include <tree.h>
#include <vector.h>

Vector * preorder_result;
Vector * inorder_result;
Vector * postorder_result;

/*
        1
      /   \
     2     3
   /  \   /  \
  4    5 6    7
 / \  /
8  9 10
*/
const int inputs[]              = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int expected_bfs[]        = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int expected_preorder[]   = {1, 2, 4, 8, 9, 5, 10, 3, 6, 7};
const int expected_inorder[]    = {8, 4, 9, 2, 10, 5, 1, 6, 3, 7};
const int expected_postorder[]  = {8, 9, 4, 10, 5, 2, 6, 7, 3, 1};

void search_callback(BinaryTreeSearchInfo * search_info, int data) {
    if(search_info->m_array_ptr == preorder_result->m_array_ptr)    {
        preorder_result->push(preorder_result, data);
        search_info->m_size = preorder_result->size(preorder_result);
        return;
    }
    if(search_info->m_array_ptr == inorder_result->m_array_ptr)     {
        inorder_result->push(inorder_result, data);
        search_info->m_size = inorder_result->size(inorder_result);
        return;
    }
    if(search_info->m_array_ptr == postorder_result->m_array_ptr)   {
        postorder_result->push(postorder_result, data);
        search_info->m_size = postorder_result->size(postorder_result);
        return;
    }
    *(search_info->m_array_ptr + search_info->m_size++) = data;
    printf("%d ", data);
}

int complete_binarytree_demo(int argc, char* argv[]) {
    CompleteBinaryTree * complete_binarytree = CreateCompleteBinaryTree();

    for(int i = 1; i <= 10; i++) {
        printf("%d ", i);
        complete_binarytree->insert(complete_binarytree, i);
    }
    printf("\n");

    preorder_result = CreateVector(10);
    inorder_result = CreateVector(10);
    postorder_result = CreateVector(10);

    /// Preorder ///
    BinaryTreeSearchInfo preorder_search_result = (BinaryTreeSearchInfo){
        .m_array_ptr = preorder_result->m_array_ptr,
        .m_size = 0,
        .callback = search_callback
    };

    // printf("Stack Preorder : ");
    // CompleteBinaryTreeStackDFSPreorder(complete_binarytree, preorder_result);
    // for(int i = 0; i < 10; i++) {
    //     printf("%d ", preorder_result[i]);
    // }
    // printf("\n");

    // memset(preorder_result, 0, sizeof(preorder_result));

    printf("Recurse Preorder : ");
    CompleteBinaryTreeRecurseDFSPreorder(complete_binarytree, complete_binarytree->m_root, (void *) &preorder_search_result);
    for(int i = 0; i < preorder_search_result.m_size; i++) {
        printf("%d ", preorder_search_result.m_array_ptr[i]);
    }
    printf("\n");
    // memset(preorder_result, 0, sizeof(preorder_result));

    /// Inorder ///
    // printf("Stack Inorder : ");
    // CompleteBinaryTreeStackDFSInorder(complete_binarytree, inorder_result);

    // for(int i = 0; i < 10; i++) {
    //     printf("%d ", inorder_result[i]);
    // }
    // printf("\n");
    // memset(inorder_result, 0, sizeof(inorder_result));

    BinaryTreeSearchInfo inorder_search_result = (BinaryTreeSearchInfo){
        .m_array_ptr = inorder_result->m_array_ptr,
        .m_size = 0,
        .callback = search_callback
    };
    printf("Recurse Inorder : ");
    CompleteBinaryTreeRecurseDFSInorder(complete_binarytree, complete_binarytree->m_root, (void*)&inorder_search_result);

    for(int i = 0; i < inorder_search_result.m_size; i++) {
        printf("%d ", inorder_search_result.m_array_ptr[i]);
    }
    printf("\n");
    // memset(inorder_result, 0, sizeof(inorder_result));
    // printf("head ptr %d\n", complete_binarytree->m_head_idx);

    /// Postorder ///
    // printf("Stack Postorder : ");
    // CompleteBinaryTreeStackDFSPostorder(complete_binarytree, postorder_result);
    // for(int i = 0; i < 10; i++) {
    //     printf("%d ", postorder_result[i]);
    // }
    // printf("\n");
    // memset(postorder_result, 0, sizeof(postorder_result));

    BinaryTreeSearchInfo postorder_search_result = (BinaryTreeSearchInfo){
        .m_array_ptr = postorder_result->m_array_ptr,
        .m_size = 0,
        .callback = search_callback
    };

    printf("Recurse Postorder : ");
    CompleteBinaryTreeStackDFSPostorder(complete_binarytree, complete_binarytree->m_root, (void*)&postorder_search_result);
    for(int i = 0; i < postorder_search_result.m_size; i++) {
        printf("%d ", postorder_search_result.m_array_ptr[i]);
    }
    printf("\n");
    // memset(postorder_result, 0, sizeof(postorder_result));

    DestroyVector(preorder_result);
    DestroyVector(inorder_result);
    DestroyVector(postorder_result);
    DestroyCompleteBinaryTree(complete_binarytree);
    return 1;
}
