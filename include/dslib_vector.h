#pragma once

/**
 * \file
 *
 * \brief A vector.
 *
 * The dslib vector is a dinamically sized array. It automatically resizes
 * itself.
 *
 */

#include "dslib_macros.h"
#include <stddef.h>


#define DSLIB_TYPE_VECTOR TYPE_EVALUATOR(vector, DSLIB_TYPE)

#define DSLIB_TYPE_VECTOR_ITERATOR TYPE_EVALUATOR(vector_iterator, DSLIB_TYPE)

#define DSLIB_FOREACH_VECTOR(it, ds, type) for(it = dslib_vector_iterator_## type ##_begin(&ds); dslib_vector_iterator_## type ##_not_equal(it, dslib_vector_iterator_## type ##_end(&v)); dslib_vector_iterator_## type ##_increment(&it))

typedef struct DSLIB_TYPE_VECTOR
{
	size_t size;
	size_t capacity;
	DSLIB_TYPE* data;
} DSLIB_TYPE_VECTOR;

typedef struct DSLIB_TYPE_VECTOR_ITERATOR
{
	DSLIB_TYPE* value;
} DSLIB_TYPE_VECTOR_ITERATOR;

// Iterators

int
DSLIB_FUNCTION(vector_iterator, not_equal)(DSLIB_TYPE_VECTOR_ITERATOR lhs,
                                           DSLIB_TYPE_VECTOR_ITERATOR rhs);

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector_iterator, begin)(DSLIB_TYPE_VECTOR* this);

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector_iterator, end)(DSLIB_TYPE_VECTOR* this);

void
DSLIB_FUNCTION(vector_iterator, increment)(DSLIB_TYPE_VECTOR_ITERATOR* this);

void
DSLIB_FUNCTION(vector_iterator, decrement)(DSLIB_TYPE_VECTOR_ITERATOR* this);

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector_iterator, rbegin)(DSLIB_TYPE_VECTOR* this);

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector_iterator, rend)(DSLIB_TYPE_VECTOR* this);

void
DSLIB_FUNCTION(vector_iterator, rincrement)(DSLIB_TYPE_VECTOR_ITERATOR* this);

void
DSLIB_FUNCTION(vector_iterator, rdecrement)(DSLIB_TYPE_VECTOR_ITERATOR* this);


// Vector


DSLIB_TYPE_VECTOR DSLIB_FUNCTION(vector, init)();

void DSLIB_FUNCTION(vector, destroy)(DSLIB_TYPE_VECTOR* this);

void DSLIB_FUNCTION(vector, reserve)(DSLIB_TYPE_VECTOR* this, size_t newcap);

size_t DSLIB_FUNCTION(vector, capacity)(DSLIB_TYPE_VECTOR* this);

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector, at)(DSLIB_TYPE_VECTOR* this, size_t pos);

int DSLIB_FUNCTION(vector, empty)(DSLIB_TYPE_VECTOR* this);

size_t DSLIB_FUNCTION(vector, size)(DSLIB_TYPE_VECTOR* this);

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector, front)(DSLIB_TYPE_VECTOR* this);

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector, back)(DSLIB_TYPE_VECTOR* this);

void
DSLIB_FUNCTION(vector, push_back_ref)(DSLIB_TYPE_VECTOR* this,
                                      DSLIB_TYPE* value);

void
DSLIB_FUNCTION(vector, push_back)(DSLIB_TYPE_VECTOR* this,
                                  DSLIB_TYPE value);

void DSLIB_FUNCTION(vector, pop_back)(DSLIB_TYPE_VECTOR* this);

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector, insert)(DSLIB_TYPE_VECTOR* this,
                               DSLIB_TYPE_VECTOR_ITERATOR pos,
                               DSLIB_TYPE* value);

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector, erase)(DSLIB_TYPE_VECTOR* this,
                              DSLIB_TYPE_VECTOR_ITERATOR pos);

void DSLIB_FUNCTION(vector, clear)(DSLIB_TYPE_VECTOR* this);

#undef DSLIB_TYPE
