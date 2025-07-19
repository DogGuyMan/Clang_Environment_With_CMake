#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdbool.h>
#include <queue.h>
#include <errno.h>
#include <complete_binarytree_primitive.h>
#include <tree.h>
#include <vector_primitive.h>

VectorChar * preorder_result;
VectorChar * inorder_result;
VectorChar * postorder_result;

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

void search_callback(BinaryTreeCharTravelInfo * travel_info, char data) {
    if(travel_info->m_array_ptr == preorder_result->m_array_ptr)    {
        preorder_result->push_back(preorder_result, data);
        travel_info->m_size = preorder_result->size(preorder_result);
        return;
    }
    if(travel_info->m_array_ptr == inorder_result->m_array_ptr)     {
        inorder_result->push_back(inorder_result, data);
        travel_info->m_size = inorder_result->size(inorder_result);
        return;
    }
    if(travel_info->m_array_ptr == postorder_result->m_array_ptr)   {
        postorder_result->push_back(postorder_result, data);
        travel_info->m_size = postorder_result->size(postorder_result);
        return;
    }
    *(travel_info->m_array_ptr + travel_info->m_size++) = data;
    printf("%d ", data);
}

void search_tree_recursive(CompleteBinaryTreeChar * complete_binarytree) {
    preorder_result = CreateVectorCharDefault();
    inorder_result = CreateVectorCharDefault();
    postorder_result = CreateVectorCharDefault();

    BinaryTreeCharTravelInfo preorder_search_result = (BinaryTreeCharTravelInfo){
        .m_array_ptr = preorder_result->m_array_ptr,
        .m_size = 0,
        .callback = search_callback
    };
    printf("Recurse Preorder : ");
    CompleteBinaryTreeCharRecurseDFSPreorder(complete_binarytree, complete_binarytree->m_root, (void *) &preorder_search_result);
    for(int i = 0; i < preorder_search_result.m_size; i++) {
        printf("%d ", preorder_search_result.m_array_ptr[i]);
    }
    printf("\n");

    BinaryTreeCharTravelInfo inorder_search_result = (BinaryTreeCharTravelInfo){
        .m_array_ptr = inorder_result->m_array_ptr,
        .m_size = 0,
        .callback = search_callback
    };
    printf("Recurse Inorder : ");
    CompleteBinaryTreeCharRecurseDFSInorder(complete_binarytree, complete_binarytree->m_root, (void*)&inorder_search_result);

    for(int i = 0; i < inorder_search_result.m_size; i++) {
        printf("%d ", inorder_search_result.m_array_ptr[i]);
    }
    printf("\n");

    BinaryTreeCharTravelInfo postorder_search_result = (BinaryTreeCharTravelInfo){
        .m_array_ptr = postorder_result->m_array_ptr,
        .m_size = 0,
        .callback = search_callback
    };

    printf("Recurse Postorder : ");
    CompleteBinaryTreeCharRecurseDFSPostorder(complete_binarytree, complete_binarytree->m_root, (void*)&postorder_search_result);
    for(int i = 0; i < postorder_search_result.m_size; i++) {
        printf("%d ", postorder_search_result.m_array_ptr[i]);
    }
    printf("\n");

    DestroyVectorChar(preorder_result);
    DestroyVectorChar(inorder_result);
    DestroyVectorChar(postorder_result);
}

void swap_test(CompleteBinaryTreeChar * complete_binarytree) {
    int tree_size = (int) complete_binarytree->size(complete_binarytree);
    for(int i = 0; i < tree_size; i++) {
        printf("%d ", *complete_binarytree->m_container->at(complete_binarytree->m_container, i));
    } printf("\n");
    CompleteBinaryTreeCharSwapNode(complete_binarytree, 1, 5);
    for(int i = 0; i < tree_size; i++) {
        printf("%d ", *complete_binarytree->m_container->at(complete_binarytree->m_container, i));
    } printf("\n");
    CompleteBinaryTreeCharSwapNode(complete_binarytree, 2, 6);
    for(int i = 0; i < tree_size; i++) {
        printf("%d ", *complete_binarytree->m_container->at(complete_binarytree->m_container, i));
    } printf("\n");
    CompleteBinaryTreeCharSwapNode(complete_binarytree, 7, 4);
    for(int i = 0; i < tree_size; i++) {
        printf("%d ", *complete_binarytree->m_container->at(complete_binarytree->m_container, i));
    } printf("\n");
}

int complete_binarytree_demo(int argc, char* argv[]) {
    CompleteBinaryTreeChar * complete_binarytree = CreateCompleteBinaryTreeChar();

    for(int i = 1; i <= 10; i++) {
        printf("%d ", i);
        complete_binarytree->insert(complete_binarytree, i);
    }
    printf("\n");

    search_tree_recursive(complete_binarytree);
    // swap_test(complete_binarytree);

    DestroyCompleteBinaryTreeChar(complete_binarytree);
    return 1;
}

int binarytree_demo(int argc, char* argv[]) {
	BinaryTree__TYPE_NAME__ * bitree = CreateBinaryTree__TYPE_NAME__(1);

	printf("BinaryTree__TYPE_NAME___SPSP_BFS(bitree, bitree, NULL);\n");
	BinaryTree__TYPE_NAME___SPSP_BFS(bitree, bitree, NULL);

	bitree->insert(bitree, bitree, LEFT_INSERT_NODE, CreateBinaryTree__TYPE_NAME__(2));
	printf("BinaryTree__TYPE_NAME___SPSP_BFS(bitree, bitree, NULL);\n");
	BinaryTree__TYPE_NAME___SPSP_BFS(bitree, bitree, NULL);

	bitree->insert(bitree, bitree, RIGHT_INSERT_NODE, CreateBinaryTree__TYPE_NAME__(3));
	printf("BinaryTree__TYPE_NAME___SPSP_BFS(bitree, bitree, NULL);\n");
	BinaryTree__TYPE_NAME___SPSP_BFS(bitree, bitree, NULL);

	bitree->insert(bitree, bitree->m_left_child, RIGHT_INSERT_NODE, CreateBinaryTree__TYPE_NAME__(4));
	printf("BinaryTree__TYPE_NAME___SPSP_BFS(bitree, bitree, NULL);\n");
	BinaryTree__TYPE_NAME___SPSP_BFS(bitree, bitree, NULL);

	bitree->insert(bitree, bitree->m_left_child->m_right_child, LEFT_INSERT_NODE, CreateBinaryTree__TYPE_NAME__(5));
	bitree->insert(bitree, bitree->m_left_child->m_right_child, RIGHT_INSERT_NODE, CreateBinaryTree__TYPE_NAME__(6));
	printf("BinaryTree__TYPE_NAME___SPSP_BFS(bitree, bitree, NULL);\n");
	BinaryTree__TYPE_NAME___SPSP_BFS(bitree, bitree, NULL);

	return 1;
}
