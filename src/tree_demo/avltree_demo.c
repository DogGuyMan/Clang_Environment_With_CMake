#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <avltree.h>
#include "tree_printer.h"



// value = 50;
// value = 30;
// value = 20;
// value = 40;
// value = 70;
// value = 60;
// value = 80;

// value = 100
// value = 50
// value = 150
// value = 25
// value = 75
// value = 125
// value = 175
// value = 12
// value = 37
// value = 162
// value = 187

int avl_demo(int argc, char* argv[]) {
    printf("=== AVL Tree Demonstration ===\n\n");

    // 첫 번째 트리 생성 및 출력
	AVLTree__TYPE_NAME__ * avltree = CreateAVLTree__TYPE_NAME__(BST_LESS_ORDER, 80);

	int values1[] = {10,5,70,60,20,40,50,30};
	int num_values1 = sizeof(values1) / sizeof(values1[0]);

	for(int i = 0; i < num_values1; i++) {
		avltree->insert_item(avltree, values1[i]);
		printf("Added %d\n", values1[i]);
		printf("\n--- Beautiful Tree Visualization ---\n");
		print_beautiful_tree(avltree->m_bst->m_bt->m_root);
	}

	for(int i = 0; i < num_values1; i++) {
		avltree->remove_item(avltree, values1[i]);
		printf("Removed %d\n", values1[i]);
		printf("\n--- Beautiful Tree Visualization ---\n");
		print_beautiful_tree(avltree->m_bst->m_bt->m_root);
	}


    printf("Tree Statistics:\n");
    printf("- Size: %zu nodes\n", avltree->size(avltree));
    printf("- Height: %zu levels\n", avltree->max_depth(avltree));

    // 두 번째 트리로 더 복잡한 예제
    printf("\n\n=== Second Example: Larger Tree ===\n");
    printf("Creating tree with values: 100, 50, 150, 25, 75, 125, 175, 12, 37, 162, 187\n");

    AVLTree__TYPE_NAME__ * avltree2 = CreateAVLTree__TYPE_NAME__(BST_GREATER_ORDER, 100);
    int values2[] = {175,  50, 12,  25, 75, 125, 37, 162, 187, 150};
    int num_values2 = sizeof(values2) / sizeof(values2[0]);

    for (int i = 0; i < num_values2; i++) {
        avltree2->insert_item(avltree2, values2[i]);
        printf("Added %d\n", values2[i]);
    }

    printf("\n--- Beautiful Tree Visualization ---\n");
    print_beautiful_tree(avltree2->m_bst->m_bt->m_root);

    printf("--- Tree with Branches ---\n");
    print_tree_with_branches(avltree2->m_bst->m_bt->m_root);

    printf("Tree Statistics:\n");
    printf("- Size: %zu nodes\n", avltree2->size(avltree2));
    printf("- Height: %zu levels\n", avltree2->max_depth(avltree2));

	DestroyAVLTree__TYPE_NAME__(avltree2);

	// 메모리 정리
    DestroyAVLTree__TYPE_NAME__(avltree);

    return 0;
}
