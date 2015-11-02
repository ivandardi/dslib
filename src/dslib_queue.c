#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "helper/dslib_error.h"
#include "dslib_queue.h"

#define FREE(ptr) do { free((ptr)); (ptr) = NULL; } while(0)

struct QueueNode {
	void* info;
	struct QueueNode* next;
};

struct Queue {
	struct QueueNode* front;
	struct QueueNode* back;
	userFunction queueFree;
	size_t valSize;
	size_t length;
};

Queue dslib_queue_init(size_t size, userFunction free)
{
	dslib_error = DSLIB_SUCCESS;

	Queue temp = malloc(sizeof(*temp));
	if (!temp) {
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return NULL;
	}

	temp->front = NULL;
	temp->back = NULL;
	temp->queueFree = free;
	temp->valSize = size;
	temp->length = 0;
	return temp;
}

size_t dslib_queue_size(const Queue const queue)
{
	assert(queue != NULL);
	return queue->length;
}

int dslib_queue_empty(const Queue const queue)
{
	assert(queue != NULL);
	return (queue->length == 0);
}

void* dslib_queue_front(const Queue const queue)
{
	assert(queue != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (queue->length == 0) {
		dslib_error = DSLIB_EMPTY;
		return NULL;
	}
	return queue->front->info;
}

void* dslib_queue_back(const Queue const queue)
{
	assert(queue != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (queue->length == 0) {
		dslib_error = DSLIB_EMPTY;
		return NULL;
	}
	return queue->back->info;
}

void dslib_queue_push(Queue const queue, const void* const val)
{
	assert(queue != NULL);

	dslib_error = DSLIB_SUCCESS;

	struct QueueNode* newNode = malloc(sizeof(*newNode));
	if (!newNode) {
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return;
	}
	newNode->info = malloc(queue->valSize);
	if (!newNode->info) {
		FREE(newNode);
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return;
	}
	memcpy(newNode->info, val, queue->valSize);

	newNode->next = NULL;
	if (queue->length == 0) {
		queue->back = queue->front = newNode;
	} else {
		queue->back = queue->back->next = newNode;
	}
	queue->length++;
}

void dslib_queue_pop(Queue const queue)
{
	assert(queue != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (queue->length == 0) {
		dslib_error = DSLIB_EMPTY;
		return;
	}

	struct QueueNode* temp = queue->front;
	queue->front = queue->front->next;
	if (queue->front == NULL) {
		queue->back = NULL;
	}
	if (queue->queueFree) {
		queue->queueFree(temp->info);
	}
	FREE(temp->info);
	FREE(temp);
	queue->length--;
}

void dslib_queue_clear(Queue const queue)
{
	assert(queue != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (queue->length == 0) {
		dslib_error = DSLIB_EMPTY;
		return;
	}

	struct QueueNode* temp;
	while (queue->front) {
		temp = queue->front;
		queue->front = queue->front->next;
		if (queue->queueFree) {
			queue->queueFree(temp->info);
		}
		FREE(temp->info);
		FREE(temp);
	}
	free(queue);
}
