#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_demo.h"

char * strs[1010];

int stack_demo()
{
	FILE* file = fopen("input.txt", "r");
	if(!file) {
		perror("file open failed\n");
		return EXIT_FAILURE;
	}
	
	char line_buffer[256];
	int count = 0;
	if(fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
		if(sscanf(line_buffer, "%d", &count) == 1) {
			printf("input line counts %d\n", count);
		}
	}

	int line_num = 0;
	while(fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
		line_buffer[strcspn(line_buffer, "\n")] = '\0';
		if(sscanf(line_buffer, "%s", strs[line_num]) == 1) {
			printf("%dth parsed line %s \n", line_num, strs[line_num]);
		}
	}
	return 0;
}
