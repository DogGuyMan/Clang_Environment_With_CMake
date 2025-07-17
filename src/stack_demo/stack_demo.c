#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdbool.h>
#include "stack_demo.h"

bool solve(Stack * stack, const char* bracket_line, int str_len)
{
	for(int i = 0; i < str_len; i++) {
		switch(bracket_line[i])
		{
			case '(' : {
						char data = '(';
						GENERIC_DATA_TYPE gd = GenerateData(TYPE_CHAR, sizeof(char), (void*)&data);
						stack->push(stack, gd);
						DestroyGeneric(&gd);
						break;
				   }
			case ')' : {
						if(stack->m_size <= 0) {
							return false;
					   	}
						GENERIC_DATA_TYPE pop_data;
						pop_data = stack->pop(stack);
						DestroyGeneric(&pop_data);
					   	break;
				   	}
			default  : {
					  break;
				   }
		}
	}
	bool empty_flag = stack->is_empty(stack);
	return empty_flag;
}

bool solve_with_primitive(StackChar* stack, const char* bracket_line, int str_len)
{
	for(int i = 0; i < str_len; i++) {
		switch(bracket_line[i])
		{
			case '(' : {
					   stack->push(stack, '(');
					   break;
				   }
			case ')' : {
					   if(stack->m_size <= 0) {
						return false;
					   }
					   stack->pop(stack);
					   break;
				   }
			default  : {
					  break;
				   }
		}
	}
	bool empty_flag = stack->is_empty(stack);
	return empty_flag;
}

int stack_demo(int argc, char* argv[])
{
	const char* RESOURCE_PATH = strcat(dirname(argv[0]), "/resources/backjoon_9012_input.txt");
	printf("input resource path :  %s\n", RESOURCE_PATH);

	FILE* file = fopen(RESOURCE_PATH, "r");
	if(!file) {
		perror("file open failed\n");
		return EXIT_FAILURE;
	}
	printf("Open %s\n", RESOURCE_PATH);

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
		//printf("get line strings\n");
		char line_str[55];
		int str_len = 0;
		if(sscanf(line_buffer, "%s", line_str) == 1)
		{
			str_len = strlen(line_str);
			printf("%dth parsed line %s \n", line_num, line_str);
		}
		line_num++;
		Stack* stack = CreateStack(TYPE_CHAR, sizeof(char), str_len);
		if(solve(stack, line_str, str_len))	printf("YES\n");
		else								printf("NO\n");

		DestroyStack(stack, NULL);
	}
	return 1;
}

int stack_primitive_demo(int argc, char* argv[])
{
	//printf("current directory structure \n");
	//system("find . -maxdepth 2 -type d");
	const char* RESOURCE_PATH = strcat(dirname(argv[0]), "/resources/backjoon_9012_input.txt");

	printf("input resource path :  %s\n", RESOURCE_PATH);

	FILE* file = fopen(RESOURCE_PATH, "r");
	if(!file) {
		perror("file open failed\n");
		return EXIT_FAILURE;
	}
	printf("Open %s\n", RESOURCE_PATH);

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
		//printf("get line strings\n");
		char line_str[55];
		int str_len = 0;
		if(sscanf(line_buffer, "%s", line_str) == 1)
		{
			str_len = strlen(line_str);
			printf("%dth parsed line %s \n", line_num, line_str);
		}
		else
		{
			//printf("fail parse line\n");
		}
		line_num++;
		StackChar* stack = CreateStackChar(str_len);
		if(solve_with_primitive(stack, line_str, str_len)) {
			printf("YES\n");
		}
		else
			printf("NO\n");
		//printf("line num %d\n", line_num);
		//printf("str length %d\n", str_len);
		DestroyStackChar(stack);
	}
	return 0;
}
