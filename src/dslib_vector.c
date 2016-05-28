#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "helper/dslib_error.h"
#include "dslib_vector.h"

#define FREE(ptr) do { free((ptr)); (ptr) = NULL; } while(0)

struct Vector {
    size_t elemSize;
    size_t length;
    size_t capacity;
    userFunction listFree;
    void** vec;
};

static void dslib_vector_internal_maybe_resize(Vector vector)
{
    if (vector->length == vector->capacity) {
        vector->capacity *= 2;
        vector->vec = realloc(vector->vec, vector->capacity);
    }
    else
    if (vector->length < vector->capacity / 4) {
        vector->capacity /= 2;
        vector->vec = realloc(vector->vec, vector->capacity);
    }
}

Vector dslib_vector_init(size_t size, userFunction free)
{
    dslib_error = DSLIB_SUCCESS;
    Vector temp = malloc(sizeof(*temp));
    if (!temp) {
        dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
        return NULL;
    }
    temp->elemSize = size;
    temp->length = 0;
    temp->capacity = 0;
    temp->listFree = free;
    vec = NULL;
    return temp;
}

void dslib_vector_destroy(Vector const vector);

void dslib_vector_reserve(Vector const vector, size_t new_cap)
{
    if (new_cap <= vector->capacity) {
        return;
    }
    vector->capacity = new_cap;
    vector->vec
}

size_t dslib_vector_capacity(const Vector const vector);

void* dslib_vector_at(const Vector const vector, size_t pos);

int dslib_vector_empty(const Vector const vector);

size_t dslib_vector_size(const Vector const vector);

void* dslib_vector_front(const Vector const vector);

void* dslib_vector_back(const Vector const vector);

VectorIterator dslib_vector_push_back(Vector const vector, const void* const val);

void dslib_vector_pop_back(Vector const vector);

VectorIterator dslib_vector_insert(Vector const vector, const VectorIterator const position, const void* const val);

VectorIterator dslib_vector_erase(Vector const vector, const VectorIterator const position);

void dslib_vector_clear(Vector const vector);

VectorIterator dslib_vector_iterator_begin(const Vector const vector);

VectorIterator dslib_vector_iterator_end(const Vector const vector);

VectorIterator dslib_vector_iterator_increment(VectorIterator it);

VectorIterator dslib_vector_iterator_decrement(VectorIterator it);

VectorIterator dslib_vector_iterator_rbegin(const Vector const vector);

VectorIterator dslib_vector_iterator_rend(const Vector const vector);

VectorIterator dslib_vector_iterator_rincrement(VectorIterator it);

VectorIterator dslib_vector_iterator_rdecrement(VectorIterator it);

void* dslib_vector_iterator_dereference(VectorIterator it);
