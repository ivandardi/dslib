#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "helper/dslib_error.h"
#include "dslib_stack.h"

#define FREE(ptr) do { free((ptr)); (ptr) = NULL; } while(0)

struct StackNode {
	void* info;
	struct StackNode* next;
};

struct Stack {
	struct StackNode* top;
	userFunction stackFree;
	size_t valSize;
	size_t length;
};

Stack dslib_stack_init(size_t size, userFunction free)
{
	dslib_error = DSLIB_SUCCESS;

	Stack temp = malloc(sizeof(*temp));
	if (!temp) {
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return NULL;
	}

	temp->top = NULL;
	temp->stackFree = free;
	temp->valSize = size;
	temp->length = 0;
	return temp;
}

size_t dslib_stack_size(const Stack const stack)
{
	assert(stack != NULL);
	return stack->length;
}

int dslib_stack_empty(const Stack const stack)
{
	assert(stack != NULL);
	return (stack->length == 0);
}

void* dslib_stack_top(const Stack const stack)
{
	assert(stack != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (stack->length == 0) {
		dslib_error = DSLIB_EMPTY;
		return NULL;
	}
	return stack->top->info;
}

void dslib_stack_push(Stack const stack, const void* const val)
{
	assert(stack != NULL);

	dslib_error = DSLIB_SUCCESS;

	struct StackNode* newNode = malloc(sizeof(*newNode));
	if (!newNode) {
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return;
	}
	newNode->info = malloc(stack->valSize);
	if (!newNode->info) {
		FREE(newNode);
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return;
	}
	memcpy(newNode->info, val, stack->valSize);

	newNode->next = stack->top;
	stack->top = newNode;
	stack->length++;
}

void dslib_stack_pop(Stack const stack)
{
	assert(stack != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (stack->length == 0) {
		dslib_error = DSLIB_EMPTY;
		return;
	}

	struct StackNode* temp = stack->top;
	stack->top = stack->top->next;
	if (stack->stackFree) {
		stack->stackFree(temp->info);
	}
	FREE(temp->info);
	FREE(temp);
	stack->length--;
}

void dslib_stack_clear(Stack const stack)
{
	assert(stack != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (stack->length == 0) {
		dslib_error = DSLIB_EMPTY;
		return;
	}

	struct StackNode* temp;
	while (stack->top) {
		temp = stack->top;
		stack->top = stack->top->next;
		if (stack->stackFree) {
			stack->stackFree(temp->info);
		}
		FREE(temp->info);
		FREE(temp);
	}
	free(stack);
}
