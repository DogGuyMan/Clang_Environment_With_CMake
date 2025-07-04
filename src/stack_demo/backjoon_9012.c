#include <errno.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vector Vector;

static struct Vector
{
	int *m_array_ptr;
	int m_size;
	int m_capacity;
	int (*size)(struct Vector *self_ptr);
	int (*capacity)(struct Vector *self_ptr);
	bool (*is_empty)(struct Vector *self_ptr);
	int (*at)(struct Vector *self_ptr, int index);
	void (*push)(struct Vector *self_ptr, int item);
	void (*insert)(struct Vector *self_ptr, int index, int item);
	void (*prepend)(struct Vector *self_ptr, int item);
	// return index
	int (*pop)(struct Vector *self_ptr);
	int (*find)(struct Vector *self_ptr, int item);
	int (*delete)(struct Vector *self_ptr, int index);
	int (*remove)(struct Vector *self_ptr, int item);
	int (*resize)(struct Vector *self_ptr, int new_capacity);
};

static Vector *CreateVector(int capacity);
void DestroyVector(struct Vector *self_ptr);
int VectorSize(struct Vector *self_ptr);
int VectorCapacity(struct Vector *self_ptr);
bool VectorIsEmpty(struct Vector *self_ptr);
int VectorAt(struct Vector *self_ptr, int index);
void VectorPush(struct Vector *self_ptr, int item);
void VectorInsert(struct Vector *self_ptr, int index, int item);
void VectorPrepend(struct Vector *self_ptr, int item);
int VectorPop(struct Vector *self_ptr);
int VectorFind(struct Vector *self_ptr, int item);
int VectorDelete(struct Vector *self_ptr, int index);
int VectorRemove(struct Vector *self_ptr, int item);
int VectorReserve(struct Vector *self_ptr, int new_capacity);

static Vector *CreateVector(int capacity)
{
	Vector *temp_vector = malloc(sizeof(Vector));
	temp_vector->m_array_ptr = NULL;
	if (capacity <= 16)
	{
		temp_vector->m_array_ptr = malloc(sizeof(int) * 16);
		temp_vector->m_capacity = 16;
	}
	else
	{
		temp_vector->m_array_ptr = malloc(sizeof(int) * capacity);
		temp_vector->m_capacity = capacity;
	}

	temp_vector->m_size = 0;
	temp_vector->size = VectorSize;
	temp_vector->capacity = VectorCapacity;
	temp_vector->is_empty = VectorIsEmpty;
	temp_vector->at = VectorAt;
	temp_vector->push = VectorPush;
	temp_vector->insert = VectorInsert;
	temp_vector->prepend = VectorPrepend;
	temp_vector->pop = VectorPop;
	temp_vector->find = VectorFind;
	temp_vector->delete = VectorDelete;
	temp_vector->remove = VectorRemove;
	temp_vector->resize = VectorReserve;
	return temp_vector;
}

static void DestroyVector(Vector *self_ptr)
{
	free(self_ptr->m_array_ptr);
	self_ptr->m_size = 0;
	self_ptr->m_capacity = 0;

	self_ptr->size = NULL;
	self_ptr->capacity = NULL;
	self_ptr->is_empty = NULL;
	self_ptr->at = NULL;
	self_ptr->push = NULL;
	self_ptr->insert = NULL;
	self_ptr->prepend = NULL;
	self_ptr->pop = NULL;
	self_ptr->find = NULL;
	self_ptr->delete = NULL;
	self_ptr->remove = NULL;
	self_ptr->resize = NULL;

	free(self_ptr);
}

static int VectorSize(struct Vector *self_ptr)
{
	return self_ptr->m_size;
}

static int VectorCapacity(struct Vector *self_ptr)
{
	return self_ptr->m_capacity;
}

static bool VectorIsEmpty(struct Vector *self_ptr)
{
	return self_ptr->m_size == 0;
}

static int VectorAt(struct Vector *self_ptr, int index)
{
	return *(self_ptr->m_array_ptr + index);
}

static void VectorPush(struct Vector *self_ptr, int item)
{
	if (self_ptr == NULL)
	{
		printf("Vector Not Created\n");
		abort();
		return;
	}
	if (self_ptr->m_array_ptr == NULL)
	{
		printf("Vector Array Not Initialized\n");
		abort();
		return;
	}
	if (self_ptr->m_capacity <= self_ptr->m_size)
	{
		VectorReserve(self_ptr, self_ptr->m_size * 2);
	}
	*(self_ptr->m_array_ptr + self_ptr->m_size) = item;
	self_ptr->m_size++;
	return;
}

static void VectorInsert(struct Vector *self_ptr, int index, int item)
{
	if (self_ptr == NULL)
	{
		printf("Vector Not Created\n");
		abort();
		return;
	}
	if (self_ptr->m_array_ptr == NULL)
	{
		printf("Vector Array Not Initialized\n");
		abort();
		return;
	}
	if (0 > index || index >= self_ptr->m_size)
	{
		printf("Index Out of Range\n");
		abort();
		return;
	}
	if (self_ptr->m_capacity <= self_ptr->m_size)
	{
		VectorReserve(self_ptr, self_ptr->m_size * 2);
	}
	int vector_size = self_ptr->m_size;
	for (int i = vector_size - 1; i >= index; --i)
	{
		self_ptr->m_array_ptr[i + 1] = self_ptr->m_array_ptr[i];
	}
	self_ptr->m_array_ptr[index] = item;
	++(self_ptr->m_size);
	return;
}

static void VectorPrepend(struct Vector *self_ptr, int item)
{
	self_ptr->insert(self_ptr, 0, item);
	return;
}

static int VectorPop(struct Vector *self_ptr)
{
	if (self_ptr->m_size == 0)
	{
		printf("Vector is Empty\n");
		abort();
	}
	--(self_ptr->m_size);
	return *(self_ptr->m_array_ptr + self_ptr->m_size);
}

int VectorFind(struct Vector *self_ptr, int item)
{
	int founded_index = -1;
	for (int i = 0; i < self_ptr->m_size; i++)
	{
		if (*(self_ptr->m_array_ptr + i) == item)
		{
			founded_index = i;
			break;
		}
	}
	return founded_index;
}

static int VectorDelete(struct Vector *self_ptr, int index)
{
	if (0 > index || index >= self_ptr->m_size)
	{
		printf("Index Out of Range\n");
		abort();
	}
	int deleted_item = self_ptr->m_array_ptr[index];
	for (int i = index; i < self_ptr->m_size - 1; i++)
	{
		self_ptr->m_array_ptr[i] = self_ptr->m_array_ptr[i + 1];
	}
	--(self_ptr->m_size);
	return deleted_item;
}

static int VectorRemove(struct Vector *self_ptr, int item)
{
	int founded_index = self_ptr->find(self_ptr, item);
	if (founded_index == -1)
	{
		return -1;
	}
	return self_ptr->delete(self_ptr, founded_index);
}

static int VectorReserve(struct Vector *self_ptr, int new_capacity)
{
	int vector_size = self_ptr->m_size;
	int *new_array_ptr = (int *)malloc(sizeof(int) * new_capacity);
	if (new_array_ptr == NULL)
	{ // 추가
		printf("Memory allocation failed\n");
		return self_ptr->m_capacity; // 기존 capacity 반환
	}
	for (int i = 0; i < vector_size; i++)
	{
		*(new_array_ptr + i) = *(self_ptr->m_array_ptr + i);
	}
	free(self_ptr->m_array_ptr);
	self_ptr->m_array_ptr = new_array_ptr;
	self_ptr->m_capacity = new_capacity;
	return new_capacity;
}

typedef struct Stack Stack;

static struct Stack
{
	Vector *m_container;
	int m_size;
	int m_capacity;
	int (*size)(struct Stack *self_ptr);
	int (*capacity)(struct Stack *self_ptr);
	bool (*is_empty)(struct Stack *self_ptr);
	int (*top)(struct Stack *self_ptr);
	int (*pop)(struct Stack *self_ptr);
	void (*push)(struct Stack *self_ptr, int item);
};

static Stack *CreateStack(int capacity);
static void DestroyStack(struct Stack *self_ptr);
static int StackSize(struct Stack *self_ptr);
static int StackCapacity(struct Stack *self_ptr);
static bool StackIsEmpty(struct Stack *self_ptr);
static int StackTop(struct Stack *self_ptr);
static int StackPop(struct Stack *self_ptr);
static void StackPush(struct Stack *self_ptr, int item);

static Stack *CreateStack(int capacity)
{
	Stack *temp_stack = (Stack *)malloc(sizeof(Stack));
	Vector *temp_container = CreateVector(capacity);
	temp_stack->m_container = temp_container;
	temp_stack->m_capacity = temp_container->m_capacity;
	temp_stack->m_size = 0;
	temp_stack->size = StackSize;
	temp_stack->capacity = StackCapacity;
	temp_stack->is_empty = StackIsEmpty;
	temp_stack->top = StackTop;
	temp_stack->pop = StackPop;
	temp_stack->push = StackPush;
	return temp_stack;
}

static void DestroyStack(struct Stack *self_ptr)
{
	DestroyVector(self_ptr->m_container);
	self_ptr->m_container = NULL;
	self_ptr->m_capacity = 0;
	self_ptr->m_size = 0;
	self_ptr->size = NULL;
	self_ptr->capacity = NULL;
	self_ptr->is_empty = NULL;
	self_ptr->top = NULL;
	self_ptr->pop = NULL;
	self_ptr->push = NULL;
	free(self_ptr);
}

static int StackSize(struct Stack *self_ptr)
{
	return self_ptr->m_size;
}

static int StackCapacity(struct Stack *self_ptr)
{
	return self_ptr->m_capacity;
}

static bool StackIsEmpty(struct Stack *self_ptr)
{
	return self_ptr->m_size == 0;
}

static int StackTop(struct Stack *self_ptr)
{
	Vector *container = self_ptr->m_container;
	int container_size = container->size(container);
	if (container_size == 0)
	{
		printf("Stack Is Empty\n");
		abort();
	}
	int top_index = container_size - 1;
	return container->at(container, top_index);
}

static int StackPop(struct Stack *self_ptr)
{
	Vector *container = self_ptr->m_container;
	int container_size = container->size(container);
	if (container_size == 0)
	{
		printf("Stack Is Empty\n");
		abort();
	}
	int res = container->pop(container);
	self_ptr->m_size = container->m_size;
	return res;
}

static void StackPush(struct Stack *self_ptr, int item)
{
	Vector *container = self_ptr->m_container;
	container->push(container, item);
	self_ptr->m_size = container->m_size;
}

bool solve(Stack *stack, const char *bracket_line, int str_len)
{
	for (int i = 0; i < str_len; i++)
	{
		switch (bracket_line[i])
		{
		case '(':
		{
			stack->push(stack, '(');
			break;
		}
		case ')':
		{
			if (stack->m_size <= 0)
			{
				return false;
			}
			stack->pop(stack);
			break;
		}
		default:
		{
			break;
		}
		}
	}
	bool empty_flag = stack->is_empty(stack);
	return empty_flag;
}

int main()
{
	int N = 0;
	scanf("%d", &N);

	char line_str[55];

	for (int i = 0; i < N; i++)
	{
		int str_len = 0;
		scanf("%s", line_str);
		str_len = strlen(line_str);
		Stack *stack = CreateStack(str_len);
		bool res = solve(stack, line_str, str_len);
		printf("%s\n", (res) ? "YES" : "NO");
		DestroyStack(stack);
	}
	return 0;
}
