#ifndef __HEADER_GUARD_TREE_PRINTER__
#define __HEADER_GUARD_TREE_PRINTER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <binarytree_primitive.h>
#include <complete_binarytree_primitive.h>

// 트리의 노드 위치 정보를 저장하는 구조체
typedef struct TreeNodePosition {
    int x, y;       // 콘솔에서의 위치 (x: 열, y: 행)
    int value;      // 노드의 값
    bool is_left_child;   // 왼쪽 자식인지 여부
    bool is_right_child;  // 오른쪽 자식인지 여부
} TreeNodePosition;

// 트리를 아름답게 출력하는 함수들
void print_beautiful_tree(BinaryTreeInt* root);
void print_tree_structure(BinaryTreeInt* root);
void print_tree_with_branches(BinaryTreeInt* root);

// 완전 이진 트리 출력 함수들
void print_beautiful_complete_tree(CompleteBinaryTreeInt* tree);
void print_complete_tree_structure(CompleteBinaryTreeInt* tree);
void print_complete_tree_with_branches(CompleteBinaryTreeInt* tree);

// 내부 헬퍼 함수들
int calculate_tree_width(BinaryTreeInt* node, int depth);
int calculate_tree_height(BinaryTreeInt* node);
void print_tree_recursive(BinaryTreeInt* node, char** canvas, int width, int height,
                         int x, int y, int h_spacing, int level);
void print_canvas(char** canvas, int width, int height);
char** create_canvas(int width, int height);
void free_canvas(char** canvas, int height);

#endif // __HEADER_GUARD_TREE_PRINTER__
