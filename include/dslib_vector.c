#include "dslib_macros.h"
#include <stddef.h>
#include <stdlib.h>

// Iterators

static DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector_iterator, init)(DSLIB_TYPE* value)
{
	DSLIB_TYPE_VECTOR_ITERATOR temp;
	temp.value = value;
	return temp;
}

int
DSLIB_FUNCTION(vector_iterator, not_equal)(DSLIB_TYPE_VECTOR_ITERATOR lhs,
                                           DSLIB_TYPE_VECTOR_ITERATOR rhs)
{
	return lhs.value != rhs.value;
}

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector_iterator, begin)(DSLIB_TYPE_VECTOR* this)
{
	return DSLIB_FUNCTION(vector_iterator, init)(this->data);
}

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector_iterator, end)(DSLIB_TYPE_VECTOR* this)
{
	return DSLIB_FUNCTION(vector_iterator, init)(this->data + this->size);
}

void
DSLIB_FUNCTION(vector_iterator, increment)(DSLIB_TYPE_VECTOR_ITERATOR* this)
{
	++this->value;
}

void
DSLIB_FUNCTION(vector_iterator, decrement)(DSLIB_TYPE_VECTOR_ITERATOR* this)
{
	--this->value;
}

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector_iterator, rbegin)(DSLIB_TYPE_VECTOR* this)
{
	return DSLIB_FUNCTION(vector_iterator, init)(this->data + this->size - 1);
}

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector_iterator, rend)(DSLIB_TYPE_VECTOR* this)
{
	return DSLIB_FUNCTION(vector_iterator, init)(this->data - 1);
}

void
DSLIB_FUNCTION(vector_iterator, rincrement)(DSLIB_TYPE_VECTOR_ITERATOR* this)
{
	--this->value;
}

void
DSLIB_FUNCTION(vector_iterator, rdecrement)(DSLIB_TYPE_VECTOR_ITERATOR* this)
{
	++this->value;
}


// Vector



static void DSLIB_FUNCTION(vector, maybe_resize)(DSLIB_TYPE_VECTOR* this)
{
	if (this->size >= this->capacity) {
		this->capacity *= 1.618;
		this->data = realloc(this->data, this->capacity * sizeof(*this->data));
	}
}

DSLIB_TYPE_VECTOR DSLIB_FUNCTION(vector, init)()
{
	DSLIB_TYPE_VECTOR temp;
	temp.size = 0;
	temp.capacity = 8;
	temp.data = malloc(temp.capacity * sizeof(*temp.data));
	return temp;
}

void DSLIB_FUNCTION(vector, destroy)(DSLIB_TYPE_VECTOR* this)
{
	free(this->data);
}

void DSLIB_FUNCTION(vector, reserve)(DSLIB_TYPE_VECTOR* this, size_t newcap)
{
	if (newcap > this->capacity) {
		this->capacity = newcap;
		this->data = realloc(this->data, this->capacity * sizeof(*this->data));
	}
}

size_t DSLIB_FUNCTION(vector, capacity)(DSLIB_TYPE_VECTOR* this)
{
	return this->capacity;
}

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector, at)(DSLIB_TYPE_VECTOR* this, size_t pos)
{
	return DSLIB_FUNCTION(vector_iterator, init)(this->data + pos);
}

int DSLIB_FUNCTION(vector, empty)(DSLIB_TYPE_VECTOR* this)
{
	return this->size == 0;
}

size_t DSLIB_FUNCTION(vector, size)(DSLIB_TYPE_VECTOR* this)
{
	return this->size;
}

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector, front)(DSLIB_TYPE_VECTOR* this)
{
	return DSLIB_FUNCTION(vector_iterator, init)(this->data);
}

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector, back)(DSLIB_TYPE_VECTOR* this)
{
	return DSLIB_FUNCTION(vector_iterator, init)(this->data + this->size - 1);
}

void
DSLIB_FUNCTION(vector, push_back_ref)(DSLIB_TYPE_VECTOR* this,
                                      DSLIB_TYPE* value)
{
	this->data[this->size++] = *value;
	DSLIB_FUNCTION(vector, maybe_resize)(this);
}

void
DSLIB_FUNCTION(vector, push_back)(DSLIB_TYPE_VECTOR* this, DSLIB_TYPE value)
{
	this->data[this->size++] = value;
	DSLIB_FUNCTION(vector, maybe_resize)(this);
}

void DSLIB_FUNCTION(vector, pop_back)(DSLIB_TYPE_VECTOR* this)
{
	if (this->size) {
		--this->size;
	}
}

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector, insert)(DSLIB_TYPE_VECTOR* this,
                               DSLIB_TYPE_VECTOR_ITERATOR pos,
                               DSLIB_TYPE* value)
{
	size_t i = this->size;
	DSLIB_TYPE* it = this->data + this->size;
	for (; it != pos.value; --it, --i) {
		*it = *(it - 1);
	}
	*it = *value;

	++this->size;
	DSLIB_FUNCTION(vector, maybe_resize)(this);

	return DSLIB_FUNCTION(vector_iterator, init)(this->data + i);
}

DSLIB_TYPE_VECTOR_ITERATOR
DSLIB_FUNCTION(vector, erase)(DSLIB_TYPE_VECTOR* this,
                              DSLIB_TYPE_VECTOR_ITERATOR pos)
{
	if (!this->size) {
		return pos;
	}

	DSLIB_TYPE* ret = pos.value + 1;

	for (; DSLIB_FUNCTION(vector_iterator, not_equal)(pos, DSLIB_FUNCTION(
	vector_iterator, end)(this)); ++pos.value) {
		*pos.value = *(pos.value + 1);
	}

	--this->size;
	return DSLIB_FUNCTION(vector_iterator, init)(ret);
}

void DSLIB_FUNCTION(vector, clear)(DSLIB_TYPE_VECTOR* this)
{
	this->size = 0;
}

#undef DSLIB_TYPE
