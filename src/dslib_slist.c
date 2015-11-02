#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "helper/dslib_error.h"
#include "dslib_slist.h"

#define FREE(ptr) do { free((ptr)); (ptr) = NULL; } while(0)

typedef struct SListNode {
	void* info;
	struct SListNode* next;
} SListNode;

struct SList {
	struct SListNode* front;
	struct SListNode* back;
	userFunction slistFree;
	size_t valSize;
	size_t length;
};

SList dslib_slist_init(size_t size, userFunction free)
{
	dslib_error = DSLIB_SUCCESS;

	SList temp = malloc(sizeof(*temp));
	if (!temp) {
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return NULL;
	}

	temp->front = NULL;
	temp->back = NULL;
	temp->slistFree = free;
	temp->valSize = size;
	temp->length = 0;
	return temp;
}

int dslib_slist_empty(const SList const slist)
{
	assert(slist != NULL);
	return (slist->length == 0);
}

size_t dslib_slist_size(const SList const slist)
{
	assert(slist != NULL);
	return slist->length;
}

void* dslib_slist_front(const SList const slist)
{
	assert(slist != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (slist->length == 0) {
		dslib_error = DSLIB_EMPTY;
		return NULL;
	}
	return slist->front->info;
}

void* dslib_slist_back(const SList const slist)
{
	assert(slist != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (slist->length == 0) {
		dslib_error = DSLIB_EMPTY;
		return NULL;
	}
	return slist->back->info;
}

void dslib_slist_push_front(SList const slist, const void* const val)
{
	assert(slist != NULL);

	dslib_error = DSLIB_SUCCESS;

	SListNode* newNode = malloc(sizeof(*newNode));
	if (!newNode) {
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return;
	}
	newNode->info = malloc(slist->valSize);
	if (!newNode->info) {
		FREE(newNode);
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return;
	}
	memcpy(newNode->info, val, slist->valSize);

	newNode->next = slist->front;
	if (slist->length == 0) {
		slist->back = newNode;
	}
	slist->front = newNode;
	slist->length++;
}

void dslib_slist_pop_front(SList const slist)
{
	assert(slist != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (slist->length == 0) {
		dslib_error = DSLIB_EMPTY;
		return;
	}

	SListNode* temp = slist->front;
	slist->front = slist->front->next;
	if (slist->front == NULL) {
		slist->back = NULL;
	}
	if (slist->slistFree) {
		slist->slistFree(temp->info);
	}
	FREE(temp->info);
	FREE(temp);
	slist->length--;
}

void dslib_slist_push_back(SList const slist, const void* const val)
{
	assert(slist != NULL);

	dslib_error = DSLIB_SUCCESS;

	SListNode* newNode = malloc(sizeof(*newNode));
	if (!newNode) {
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return;
	}
	newNode->info = malloc(slist->valSize);
	if (!newNode->info) {
		FREE(newNode);
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return;
	}
	memcpy(newNode->info, val, slist->valSize);

	newNode->next = NULL;
	if (slist->length == 0) {
		slist->back = slist->front = newNode;
	} else {
		slist->back = slist->back->next = newNode;
	}
	slist->length++;
}

void dslib_slist_pop_back(SList const slist)
{
	assert(slist != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (slist->length == 0) {
		dslib_error = DSLIB_EMPTY;
		return;
	}
	if (slist->length == 1) {
		dslib_slist_pop_front(slist);
		return;
	}

	SListIterator prev;
	dslib_slist_foreach(prev, slist) {
		if (prev->next == dslib_slist_iterator_end(slist)) {
			break;
		}
	}

	prev->next = NULL;
	if (slist->slistFree) {
		slist->slistFree(slist->back->info);
	}
	FREE(slist->back->info);
	FREE(slist->back);
	slist->back = prev;
	slist->length--;
}

SListIterator dslib_slist_insert(SList const slist, const SListIterator const position, const void* const val)
{
	assert(slist != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (position == dslib_slist_front(slist)) {
		dslib_slist_push_front(slist, val);
		return dslib_slist_iterator_begin(slist);
	}
	if (position == dslib_slist_back(slist)) {
		dslib_slist_push_back(slist, val);
		return dslib_slist_iterator_end(slist);;
	}

	SListNode* newNode = malloc(sizeof(*newNode));
	if (!newNode) {
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return NULL;
	}
	newNode->info = malloc(slist->valSize);
	if (!newNode->info) {
		FREE(newNode);
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return NULL;
	}
	memcpy(newNode->info, val, slist->valSize);

	int wasFound = 0;
	SListIterator prev;
	dslib_slist_foreach(prev, slist) {
		if (prev->next == position) {
			wasFound = 1;
			break;
		}
	}
	if (!wasFound) {
		FREE(newNode->info);
		FREE(newNode);
		dslib_error = DSLIB_ELEMENT_NOT_FOUND;
		return NULL;
	}

	newNode->next = position;
	prev->next = newNode;
	slist->length++;
	return newNode;
}

SListIterator dslib_slist_erase(SList const slist, const SListIterator const position)
{
	assert(slist != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (slist->length == 0) {
		dslib_error = DSLIB_EMPTY;
		return NULL;
	}
	if (position == dslib_slist_front(slist)) {
		dslib_slist_pop_front(slist);
		return dslib_slist_iterator_begin(slist);
	}
	if (position == dslib_slist_back(slist)) {
		dslib_slist_pop_back(slist);
		return dslib_slist_iterator_end(slist);
	}

	int wasFound = 0;
	SListIterator prev;
	dslib_slist_foreach(prev, slist) {
		if (prev->next == position) {
			wasFound = 1;
			break;
		}
	}
	if (!wasFound) {
		dslib_error = DSLIB_ELEMENT_NOT_FOUND;
		return NULL;
	}

	prev->next = prev->next->next;
	if (slist->slistFree) {
		slist->slistFree(position->info);
	}
	FREE(position->info);
	free(position);
	slist->length--;
	return prev->next->next;
}

void dslib_slist_clear(SList const slist)
{
	assert(slist != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (slist->length == 0) {
		dslib_error = DSLIB_EMPTY;
		return;
	}

	struct SListNode* temp;
	while (slist->front) {
		temp = slist->front;
		slist->front = slist->front->next;
		if (slist->slistFree) {
			slist->slistFree(temp->info);
		}
		FREE(temp->info);
		FREE(temp);
	}
	free(slist);
}

SListIterator dslib_slist_iterator_begin(const SList const slist)
{
	assert(slist != NULL);
	return slist->front;
}

SListIterator dslib_slist_iterator_end(const SList const slist)
{
	assert(slist != NULL);
	return slist->back->next;
}

void dslib_slist_iterator_increment(SListIterator* it)
{
	*it = (*it)->next;
}

void* dslib_slist_iterator_dereference(SListIterator it)
{
	return it->info;
}

