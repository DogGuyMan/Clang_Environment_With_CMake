#include "tree_printer.h"
#include <math.h>

// 내부 헬퍼 함수 전방 선언
static void print_with_prefix(BinaryTreeInt* node, const char* prefix, bool is_last);
static void print_complete_structure_recursive(CompleteBinaryTreeInt* tree, size_t index);
static void print_complete_with_prefix(CompleteBinaryTreeInt* tree, size_t index,
                                      const char* prefix, bool is_last);

// 캔버스 생성
char** create_canvas(int width, int height) {
    char** canvas = malloc(height * sizeof(char*));
    if (!canvas) return NULL;

    for (int i = 0; i < height; i++) {
        canvas[i] = malloc((width + 1) * sizeof(char));
        if (!canvas[i]) {
            // 메모리 할당 실패 시 정리
            for (int j = 0; j < i; j++) {
                free(canvas[j]);
            }
            free(canvas);
            return NULL;
        }
        // 공백으로 초기화
        memset(canvas[i], ' ', width);
        canvas[i][width] = '\0';
    }
    return canvas;
}

// 캔버스 해제
void free_canvas(char** canvas, int height) {
    if (!canvas) return;
    for (int i = 0; i < height; i++) {
        if (canvas[i]) free(canvas[i]);
    }
    free(canvas);
}

// 캔버스 출력
void print_canvas(char** canvas, int width, int height) {
    printf("\n");
    for (int i = 0; i < height; i++) {
        // 오른쪽 공백 제거
        int end = width - 1;
        while (end >= 0 && canvas[i][end] == ' ') {
            end--;
        }
        for (int j = 0; j <= end; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 트리의 높이 계산
int calculate_tree_height(BinaryTreeInt* node) {
    if (!node) return 0;

    int left_height = calculate_tree_height(node->m_left_child);
    int right_height = calculate_tree_height(node->m_right_child);

    return 1 + (left_height > right_height ? left_height : right_height);
}

// 트리의 너비 계산 (특정 깊이에서)
int calculate_tree_width(BinaryTreeInt* node, int depth) {
    if (!node || depth < 0) return 0;
    if (depth == 0) return 1;

    return calculate_tree_width(node->m_left_child, depth - 1) +
           calculate_tree_width(node->m_right_child, depth - 1);
}

// 숫자의 자릿수 계산
int get_number_width(int num) {
    if (num == 0) return 1;
    int width = 0;
    if (num < 0) {
        width = 1; // 음수 부호
        num = -num;
    }
    while (num > 0) {
        width++;
        num /= 10;
    }
    return width;
}

// 문자열을 캔버스에 출력
void draw_string_on_canvas(char** canvas, int x, int y, const char* str, int canvas_width, int canvas_height) {
    if (y < 0 || y >= canvas_height) return;

    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (x + i >= 0 && x + i < canvas_width) {
            canvas[y][x + i] = str[i];
        }
    }
}

// 선을 캔버스에 그리기
void draw_line_on_canvas(char** canvas, int x1, int y1, int x2, int y2, char ch, int canvas_width, int canvas_height) {
    if (x1 == x2) {
        // 수직선
        int start_y = y1 < y2 ? y1 : y2;
        int end_y = y1 > y2 ? y1 : y2;
        for (int y = start_y; y <= end_y; y++) {
            if (y >= 0 && y < canvas_height && x1 >= 0 && x1 < canvas_width) {
                canvas[y][x1] = ch;
            }
        }
    } else if (y1 == y2) {
        // 수평선
        int start_x = x1 < x2 ? x1 : x2;
        int end_x = x1 > x2 ? x1 : x2;
        for (int x = start_x; x <= end_x; x++) {
            if (x >= 0 && x < canvas_width && y1 >= 0 && y1 < canvas_height) {
                canvas[y1][x] = ch;
            }
        }
    } else {
        // 대각선
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        int sx = x1 < x2 ? 1 : -1;
        int sy = y1 < y2 ? 1 : -1;
        int err = dx - dy;

        int x = x1, y = y1;
        while (true) {
            if (x >= 0 && x < canvas_width && y >= 0 && y < canvas_height) {
                canvas[y][x] = ch;
            }

            if (x == x2 && y == y2) break;

            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x += sx;
            }
            if (e2 < dx) {
                err += dx;
                y += sy;
            }
        }
    }
}

// 트리를 재귀적으로 캔버스에 그리기
void print_tree_recursive(BinaryTreeInt* node, char** canvas, int width, int height,
                         int x, int y, int h_spacing, int level) {
    if (!node || y >= height) return;

    // 현재 노드 값을 문자열로 변환
    char value_str[20];
    sprintf(value_str, "%d", node->m_data);
    int value_width = strlen(value_str);

    // 노드 값을 중앙에 배치
    int start_x = x - value_width / 2;
    draw_string_on_canvas(canvas, start_x, y, value_str, width, height);

    // 자식 노드들의 위치 계산
    int child_y = y + 2;
    int left_x = x - h_spacing;
    int right_x = x + h_spacing;

    // 왼쪽 자식
    if (node->m_left_child) {
        // 연결선 그리기
        if (child_y < height) {
            // 부모에서 자식으로 가는 선
            draw_line_on_canvas(canvas, x, y + 1, left_x, child_y, '/', width, height);
        }
        print_tree_recursive(node->m_left_child, canvas, width, height,
                           left_x, child_y, h_spacing / 2, level + 1);
    }

    // 오른쪽 자식
    if (node->m_right_child) {
        // 연결선 그리기
        if (child_y < height) {
            // 부모에서 자식으로 가는 선
            draw_line_on_canvas(canvas, x, y + 1, right_x, child_y, '\\', width, height);
        }
        print_tree_recursive(node->m_right_child, canvas, width, height,
                           right_x, child_y, h_spacing / 2, level + 1);
    }
}

// 메인 트리 출력 함수
void print_beautiful_tree(BinaryTreeInt* root) {
    if (!root) {
        printf("Empty tree\n");
        return;
    }

    printf("Tree Structure:\n");
    printf("================\n");

    // 트리 정보 출력
    int tree_height = calculate_tree_height(root);
    printf("Tree Height: %d\n", tree_height);

    // 캔버스 크기 계산
    int max_nodes_at_level = 1;
    for (int i = 0; i < tree_height - 1; i++) {
        max_nodes_at_level *= 2;
    }

    // 각 노드가 최소 3자리 공간을 가지도록 설정
    int canvas_width = max_nodes_at_level * 8;  // 각 노드마다 8문자 공간
    int canvas_height = tree_height * 2;        // 각 레벨마다 2줄

    // 캔버스 생성
    char** canvas = create_canvas(canvas_width, canvas_height);
    if (!canvas) {
        printf("Memory allocation failed\n");
        return;
    }

    // 초기 가로 간격 설정
    int initial_h_spacing = canvas_width / 4;

    // 트리 그리기
    print_tree_recursive(root, canvas, canvas_width, canvas_height,
                        canvas_width / 2, 0, initial_h_spacing, 0);

    // 캔버스 출력
    print_canvas(canvas, canvas_width, canvas_height);

    // 메모리 해제
    free_canvas(canvas, canvas_height);
}

// 간단한 구조 출력
void print_tree_structure(BinaryTreeInt* root) {
    if (!root) {
        printf("(empty)\n");
        return;
    }

    printf("(%d", root->m_data);
    if (root->m_left_child || root->m_right_child) {
        printf(" ");
        if (root->m_left_child) {
            print_tree_structure(root->m_left_child);
        } else {
            printf("()");
        }
        printf(" ");
        if (root->m_right_child) {
            print_tree_structure(root->m_right_child);
        } else {
            printf("()");
        }
    }
    printf(")");
}

// 브랜치와 함께 트리 출력 (세로 방향)
void print_tree_with_branches(BinaryTreeInt* root) {
    if (!root) {
        printf("Empty tree\n");
        return;
    }

    printf("\nTree with branches:\n");
    printf("===================\n");

    print_with_prefix(root, "", true);
    printf("\n");
}

// ========== 완전 이진 트리 출력 함수들 ==========

// 완전 이진 트리의 높이 계산
int calculate_complete_tree_height(CompleteBinaryTreeInt* tree) {
    if (!tree || tree->m_size == 0) return 0;
    return tree->max_depth(tree);
}

// 완전 이진 트리의 특정 인덱스에서 값 가져오기
int get_complete_tree_value(CompleteBinaryTreeInt* tree, size_t index) {
    if (!tree || index > tree->m_size || index == 0) return -1;
    return *tree->m_container->at(tree->m_container, index - 1);
}

// 완전 이진 트리를 재귀적으로 캔버스에 그리기
void print_complete_tree_recursive(CompleteBinaryTreeInt* tree, char** canvas, int width, int height,
                                  size_t node_index, int x, int y, int h_spacing, int level) {
    if (!tree || node_index > tree->m_size || y >= height) return;

    // 현재 노드 값을 문자열로 변환
    int value = get_complete_tree_value(tree, node_index);
    if (value == -1) return;

    char value_str[20];
    sprintf(value_str, "%d", value);
    int value_width = strlen(value_str);

    // 노드 값을 중앙에 배치
    int start_x = x - value_width / 2;
    draw_string_on_canvas(canvas, start_x, y, value_str, width, height);

    // 자식 노드들의 위치 계산
    int child_y = y + 2;
    size_t left_child_index = node_index * 2;
    size_t right_child_index = node_index * 2 + 1;

    // 왼쪽 자식
    if (left_child_index <= tree->m_size) {
        int left_x = x - h_spacing;
        // 연결선 그리기
        if (child_y < height) {
            draw_line_on_canvas(canvas, x, y + 1, left_x, child_y, '/', width, height);
        }
        print_complete_tree_recursive(tree, canvas, width, height,
                                    left_child_index, left_x, child_y, h_spacing / 2, level + 1);
    }

    // 오른쪽 자식
    if (right_child_index <= tree->m_size) {
        int right_x = x + h_spacing;
        // 연결선 그리기
        if (child_y < height) {
            draw_line_on_canvas(canvas, x, y + 1, right_x, child_y, '\\', width, height);
        }
        print_complete_tree_recursive(tree, canvas, width, height,
                                    right_child_index, right_x, child_y, h_spacing / 2, level + 1);
    }
}

// 완전 이진 트리 아름다운 출력
void print_beautiful_complete_tree(CompleteBinaryTreeInt* tree) {
    if (!tree || tree->m_size == 0) {
        printf("Empty complete binary tree\n");
        return;
    }

    printf("Complete Binary Tree Structure:\n");
    printf("===============================\n");

    // 트리 정보 출력
    int tree_height = calculate_complete_tree_height(tree);
    printf("Tree Height: %d\n", tree_height);
    printf("Tree Size: %zu nodes\n", tree->m_size);

    // 캔버스 크기 계산
    int max_nodes_at_level = 1;
    for (int i = 0; i < tree_height - 1; i++) {
        max_nodes_at_level *= 2;
    }

    int canvas_width = max_nodes_at_level * 8;
    int canvas_height = tree_height * 2;

    // 캔버스 생성
    char** canvas = create_canvas(canvas_width, canvas_height);
    if (!canvas) {
        printf("Memory allocation failed\n");
        return;
    }

    // 초기 가로 간격 설정
    int initial_h_spacing = canvas_width / 4;

    // 트리 그리기 (인덱스 1부터 시작)
    print_complete_tree_recursive(tree, canvas, canvas_width, canvas_height,
                                 1, canvas_width / 2, 0, initial_h_spacing, 0);

    // 캔버스 출력
    print_canvas(canvas, canvas_width, canvas_height);

    // 메모리 해제
    free_canvas(canvas, canvas_height);
}

// 완전 이진 트리 구조 출력 (괄호 표기법)
void print_complete_tree_structure(CompleteBinaryTreeInt* tree) {
    if (!tree || tree->m_size == 0) {
        printf("(empty)\n");
        return;
    }

    print_complete_structure_recursive(tree, 1);
    printf("\n");
}

// 완전 이진 트리 브랜치와 함께 출력
void print_complete_tree_with_branches(CompleteBinaryTreeInt* tree) {
    if (!tree || tree->m_size == 0) {
        printf("Empty complete binary tree\n");
        return;
    }

    printf("\nComplete Binary Tree with branches:\n");
    printf("===================================\n");

    print_complete_with_prefix(tree, 1, "", true);
    printf("\n");
}

// ========== 내부 헬퍼 함수 구현 ==========

static void print_with_prefix(BinaryTreeInt* node, const char* prefix, bool is_last) {
    if (!node) return;

    printf("%s", prefix);
    printf("%s", is_last ? "└── " : "├── ");
    printf("%d\n", node->m_data);

    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

    if (node->m_left_child || node->m_right_child) {
        if (node->m_right_child) {
            print_with_prefix(node->m_right_child, new_prefix, !node->m_left_child);
        }
        if (node->m_left_child) {
            print_with_prefix(node->m_left_child, new_prefix, true);
        }
    }
}

static void print_complete_structure_recursive(CompleteBinaryTreeInt* tree, size_t index) {
    if (index > tree->m_size) {
        printf("()");
        return;
    }

    int value = get_complete_tree_value(tree, index);
    printf("(%d", value);

    size_t left_child = index * 2;
    size_t right_child = index * 2 + 1;

    if (left_child <= tree->m_size || right_child <= tree->m_size) {
        printf(" ");
        print_complete_structure_recursive(tree, left_child);
        printf(" ");
        print_complete_structure_recursive(tree, right_child);
    }
    printf(")");
}

static void print_complete_with_prefix(CompleteBinaryTreeInt* tree, size_t index,
                                      const char* prefix, bool is_last) {
    if (index > tree->m_size) return;

    int value = get_complete_tree_value(tree, index);
    printf("%s", prefix);
    printf("%s", is_last ? "└── " : "├── ");
    printf("%d\n", value);

    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

    size_t left_child = index * 2;
    size_t right_child = index * 2 + 1;

    if (left_child <= tree->m_size || right_child <= tree->m_size) {
        if (right_child <= tree->m_size) {
            print_complete_with_prefix(tree, right_child, new_prefix, left_child > tree->m_size);
        }
        if (left_child <= tree->m_size) {
            print_complete_with_prefix(tree, left_child, new_prefix, true);
        }
    }
}
