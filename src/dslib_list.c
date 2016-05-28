#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "helper/dslib_error.h"
#include "dslib_list.h"

#define FREE(ptr) do { free((ptr)); (ptr) = NULL; } while(0)

typedef struct ListNode {
    void* info;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

struct List {
    struct ListNode* front;
    struct ListNode* back;
    userFunction listFree;
    size_t elemSize;
    size_t length;
};

List dslib_list_init(size_t size, userFunction free)
{
    dslib_error = DSLIB_SUCCESS;
    List temp = malloc(sizeof(*temp));
    if (!temp) {
        dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
        return NULL;
    }
    temp->front = NULL;
    temp->back = NULL;
    temp->listFree = free;
    temp->elemSize = size;
    temp->length = 0;
    return temp;
}

int dslib_list_empty(const List const list)
{
    dslib_error = DSLIB_SUCCESS;
    return (list->length == 0);
}

size_t dslib_list_size(const List const list)
{
    dslib_error = DSLIB_SUCCESS;
    return list->length;
}

void* dslib_list_front(const List const list)
{
    dslib_error = DSLIB_SUCCESS;
    if (list->length == 0) {
        dslib_error = DSLIB_EMPTY;
        return NULL;
    }
    return list->front->info;
}

void* dslib_list_back(const List const list)
{
    dslib_error = DSLIB_SUCCESS;
    if (list->length == 0) {
        dslib_error = DSLIB_EMPTY;
        return NULL;
    }
    return list->back->info;
}

ListIterator dslib_list_push_front(List const list, const void* const val)
{
    dslib_error = DSLIB_SUCCESS;
    ListNode* newNode = malloc(sizeof(*newNode));
    if (!newNode) {
        dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
        return NULL;
    }
    newNode->info = malloc(list->elemSize);
    if (!newNode->info) {
        FREE(newNode);
        dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
        return NULL;
    }
    memcpy(newNode->info, val, list->elemSize);
    newNode->next = list->front;
    newNode->prev = NULL;
    if (list->length == 0) {
        list->front = list->back = newNode;
    } else {
        list->front = list->front->prev = newNode;
    }
    ++list->length;
    return list->front;
}

void dslib_list_pop_front(List const list)
{
    dslib_error = DSLIB_SUCCESS;
    if (list->length == 0) {
        dslib_error = DSLIB_EMPTY;
        return;
    }
    ListNode* temp = list->front;
    list->front = list->front->next;
    if (list->front == NULL) {
        list->back = NULL;
    } else {
        list->front->prev = NULL;
    }
    if (list->listFree) {
        list->listFree(temp->info);
    }
    FREE(temp->info);
    FREE(temp);
    --list->length;
}

ListIterator dslib_list_push_back(List const list, const void* const val)
{
    dslib_error = DSLIB_SUCCESS;
    ListNode* newNode = malloc(sizeof(*newNode));
    if (!newNode) {
        dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
        return NULL;
    }
    newNode->info = malloc(list->elemSize);
    if (!newNode->info) {
        FREE(newNode);
        dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
        return NULL;
    }
    memcpy(newNode->info, val, list->elemSize);
    newNode->next = NULL;
    newNode->prev = list->back;
    if (list->length == 0) {
        list->back = list->front = newNode;
    } else {
        list->back = list->back->next = newNode;
    }
    ++list->length;
    return list->back;
}

void dslib_list_pop_back(List const list)
{
    dslib_error = DSLIB_SUCCESS;
    if (list->length == 0) {
        dslib_error = DSLIB_EMPTY;
        return;
    }
    if (list->length == 1) {
        dslib_list_pop_front(list);
        return;
    }
    ListNode* temp = list->back->prev;
    temp->next = NULL;
    if (list->listFree) {
        list->listFree(list->back->info);
    }
    FREE(list->back->info);
    FREE(list->back);
    list->back = temp;
    --list->length;
}

ListIterator dslib_list_insert(List const list, const ListIterator const position, const void* const val)
{
    assert(list != NULL);
    dslib_error = DSLIB_SUCCESS;
    if (position == dslib_list_front(list)) {
        return dslib_list_push_front(list, val);
    }
    if (position == dslib_list_back(list)) {
        return dslib_list_push_back(list, val);
    }
    ListNode* newNode = malloc(sizeof(*newNode));
    if (!newNode) {
        dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
        return NULL;
    }
    newNode->info = malloc(list->elemSize);
    if (!newNode->info) {
        FREE(newNode);
        dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
        return NULL;
    }
    memcpy(newNode->info, val, list->elemSize);
    newNode->next = position;
    newNode->prev = position->prev;
    position->prev->next = newNode;
    position->prev = newNode;
    ++list->length;
    return newNode;
}

ListIterator dslib_list_erase(List const list, const ListIterator const position)
{
    dslib_error = DSLIB_SUCCESS;
    if (list->length == 0) {
        dslib_error = DSLIB_EMPTY;
        return NULL;
    }
    ListNode* next = position->next;
    if (position == list->front) {
        dslib_list_pop_front(list);
    }
    else
    if (position == list->back) {
        dslib_list_pop_back(list);
    }
    else {
        position->prev->next = position->next;
        position->next->prev = position->prev;
        if (list->listFree) {
            list->listFree(position->info);
        }
        FREE(position->info);
        free(position);
        --list->length;
    }
    return next;
}

void dslib_list_clear(List const list)
{
    dslib_error = DSLIB_SUCCESS;
    if (list->length == 0) {
        dslib_error = DSLIB_EMPTY;
        return;
    }
    ListNode* temp;
    while (list->front) {
        temp = list->front;
        list->front = list->front->next;
        if (list->listFree) {
            list->listFree(temp->info);
        }
        FREE(temp->info);
        FREE(temp);
    }
    list->back = NULL;
    list->length = 0;
}

void dslib_list_destroy(List const list)
{
    dslib_error = DSLIB_SUCCESS;
    dslib_list_clear(list);
    free(list);
}

ListIterator dslib_list_iterator_begin(const List const list)
{
    return list->front;
}

ListIterator dslib_list_iterator_end(const List const list)
{
    assert(list != NULL);
    return NULL;
}

ListIterator dslib_list_iterator_increment(ListIterator it)
{
    return it->next;
}

ListIterator dslib_list_iterator_decrement(ListIterator it)
{
    return it->prev;
}

ListIterator dslib_list_iterator_rbegin(const List const list)
{
    return list->back;
}

ListIterator dslib_list_iterator_rend(const List const list)
{
    return NULL;
}

ListIterator dslib_list_iterator_rincrement(ListIterator it)
{
    return it->prev;
}

ListIterator dslib_list_iterator_rdecrement(ListIterator it)
{
    return it->next;
}

void* dslib_list_iterator_dereference(ListIterator it)
{
    return it->info;
}
