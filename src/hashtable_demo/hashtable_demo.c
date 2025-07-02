#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "hashtable_demo.h"

#define STR_MAX_LEN 1000001

// 1,000,000,000,000 시간 터짐.

// char LINE_BUFFER[STR_MAX_LEN] = {0,};
// char T[STR_MAX_LEN] = {0,};
// char P[STR_MAX_LEN] = {0,};

// bool is_dest_out_of_bound(unsigned str_idx) {
//     return str_idx + strlen(P) > strlen(T);
// }

// bool string_matches(unsigned str_idx) {
//     int plen = strlen(P);
//     for(int i = 0; i < plen; i++) {
//         if(T[i+str_idx] != P[i]) return false;
//     }
//     return true;
// }

// int solve_string_match(int argc, char* argv[]) {
//     const char* RESOURCE_PATH = strcat(dirname(argv[0]), "/resources/backjoon_1786_input.txt");
//     printf("RESOURCE DIR : %s\n", RESOURCE_PATH);

//     FILE * file = fopen(RESOURCE_PATH, "r");
//     if(!file) {
//         perror("file open failed");
//         abort();
//     }
//     printf("Open %s\n", RESOURCE_PATH);

//     if(fgets(LINE_BUFFER, sizeof(LINE_BUFFER), file) != NULL) {
//         LINE_BUFFER[strcspn(LINE_BUFFER, "\n")] = '\0';
//         strcpy(T, LINE_BUFFER);
//         if(strlen(T) > 0) {
//             printf("First Line String : %s / len : %lu\n", T, strlen(T));
//         }
//     }

//     if(fgets(LINE_BUFFER, sizeof(LINE_BUFFER), file) != NULL) {
//         LINE_BUFFER[strcspn(LINE_BUFFER, "\n")] = '\0';
//         strcpy(P, LINE_BUFFER);
//         if(strlen(P) > 0) {
//             printf("Second Line String : %s / len : %lu\n", P, strlen(P));
//         }
//     }

//     // StringHashTable * str_hashtable = CreateStringHashTable(1<<20);
//     int end_idx = strlen(T) - strlen(P);
//     int ans = 0;
//     for(int i = 0; i <= end_idx; i++) {
//         if(string_matches(i))
//             ans++;
//     }
//     printf("%d\n", ans);

//     //DestroyStringHashTable(str_hashtable);
//     return 1;
// }

char LINE_BUFFER[101] = {0,};
char ANS_LIST[500050][101] = {0,};

int compare(const void *a, const void *b) {
    return strcmp((const char*)a, (const char*)b);
}


int hashtable_demo(int argc, char* argv[])
{
    int N = 0;
    int M = 0;

    const char* RESOURCE_PATH = strcat(dirname(argv[0]), "/resources/backjoon_1764_input.txt");
    // printf("RESOURCE DIR : %s\n", RESOURCE_PATH);

    FILE * file = fopen(RESOURCE_PATH, "r");
    if(!file) {
        perror("file open failed");
        abort();
    }
    // printf("Open %s\n", RESOURCE_PATH);

    if(fgets(LINE_BUFFER, sizeof(LINE_BUFFER), file) != NULL) {
        LINE_BUFFER[strcspn(LINE_BUFFER, "\n")] = '\0';
        if(sscanf(LINE_BUFFER, "%d %d", &N, &M) == 2) {
            // printf("Not Heard : %d, Not See : %d\n", N, M);
        }
    }

    StringHashTable * str_hashtable = CreateStringHashTable(1000000);
    int count = 0;
    for(int i = 0; i < N; i++) {
        if(fgets(LINE_BUFFER, sizeof(LINE_BUFFER), file) != NULL) {
            LINE_BUFFER[strcspn(LINE_BUFFER, "\n")] = '\0';
            // printf("Not Heard : %s\n", LINE_BUFFER);
            str_hashtable->add(str_hashtable, LINE_BUFFER, 1);
        }
    }

    for(int i = 0; i < M; i++) {
        if(fgets(LINE_BUFFER, sizeof(LINE_BUFFER), file) != NULL) {
            LINE_BUFFER[strcspn(LINE_BUFFER, "\n")] = '\0';
            StringKeyAndValuePair pair = str_hashtable->get(str_hashtable, LINE_BUFFER);
            if(pair.m_value != 0) {
                // printf("See Exsist, %s\n", LINE_BUFFER);
                strcpy(ANS_LIST[count], pair.m_key);
                count++;
            }
        }
    }
    printf("%d\n", count);
    qsort(ANS_LIST, count, sizeof(char) * 101, compare);
    for(int i = 0; i < count; i++) {
        printf("%s\n", ANS_LIST[i]);
    }
    DestroyStringHashTable(str_hashtable);
    return 1;
}
