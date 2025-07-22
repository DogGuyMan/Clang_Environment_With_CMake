#include <binarysearchtree.h>
#include "binarysearchtree_demo.h"

static int inputs[] = {55	,30	,91	,18	,77	,59	,83, 60, 61, 62, 63, 64, 65};
static int input_count = 13;

int compare(const void * lhs, const void * rhs) {
	int lhs_int = *(int*)lhs;
	int rhs_int = *(int*)rhs;
	if(lhs_int == rhs_int) return 0;
	if(lhs_int < rhs_int) return -1;
	return 1;
}

int bst_demo() {

	BinarySearchTree__TYPE_NAME__ * less_bst = CreateBinarySearchTree__TYPE_NAME__(BST_LESS_ORDER, inputs[0]);
	BinarySearchTree__TYPE_NAME__ * greater_bst = CreateBinarySearchTree__TYPE_NAME__(BST_GREATER_ORDER, inputs[0]);

	for(int i = 1; i < input_count; i++) {
		less_bst->insert_item(less_bst, inputs[i]);
		greater_bst->insert_item(greater_bst, inputs[i]);
	}

	/*
	cur 0th depth :  			55
	cur 1th depth :  		30 		91
	cur 2th depth :  	18  	77  	-
	cur 3th depth :  -  	59  	83
	*/
	BinaryTreeIntBFS(less_bst->m_bt, less_bst->m_bt, NULL);
	/*
	cur 0th depth :  			55
	cur 1th depth :  		91 		30
	cur 2th depth :  	-  		77 		18
	cur 3th depth :  		83  	59  -  		-
	*/
	// BinaryTreeIntBFS(greater_bst->m_bt, greater_bst->m_bt, NULL);
	qsort(inputs, input_count, sizeof(int), compare);

	printf("sorted inputs : ");
	for(int i = 0; i < input_count; i++) {
		printf(" %d ", inputs[i]);
	}
	printf("\n");

	for(int i = 0; i < input_count; i++) {
		if(less_bst->size(less_bst) <= 1) break;
		printf("less_bst->remove_item(less_bst, %d);\n", inputs[i]);
		less_bst->remove_item(less_bst, inputs[i]);
		BinaryTreeIntBFS(less_bst->m_bt, less_bst->m_bt, NULL);
		greater_bst->remove_item(greater_bst, inputs[i]);
	}

	DestroyBinarySearchTree__TYPE_NAME__(less_bst);
	DestroyBinarySearchTree__TYPE_NAME__(greater_bst);

	return 1;
}
