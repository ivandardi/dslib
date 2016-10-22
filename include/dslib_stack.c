#include "dslib_macros.h"
#include <stddef.h>
#include <stdlib.h>

static void DSLIB_FUNCTION(stack, maybe_resize)(DSLIB_TYPE_STACK* this)
{
	if (this->size >= this->capacity) {
		this->capacity *= 1.618;
		this->data = realloc(this->data, this->capacity * sizeof(*this->data));
	}
}

DSLIB_TYPE_STACK DSLIB_FUNCTION(stack, init)()
{
	DSLIB_TYPE_STACK temp;
	temp.size = 0;
	temp.capacity = 8;
	temp.data = malloc(temp.capacity * sizeof(*temp.data));
	return temp;
}

void DSLIB_FUNCTION(stack, destroy)(DSLIB_TYPE_STACK* this)
{
	free(this->data);
}

DSLIB_TYPE* DSLIB_FUNCTION(stack, top)(DSLIB_TYPE_STACK* this)
{
	return this->data + this->size - 1;
}


int DSLIB_FUNCTION(stack, empty)(DSLIB_TYPE_STACK* this)
{
	return this->size == 0;
}

size_t DSLIB_FUNCTION(stack, size)(DSLIB_TYPE_STACK* this)
{
	return this->size;
}

void
DSLIB_FUNCTION(stack, push_ref)(DSLIB_TYPE_STACK* this,
                                      DSLIB_TYPE* value)
{
	this->data[this->size++] = *value;
	DSLIB_FUNCTION(stack, maybe_resize)(this);
}

void
DSLIB_FUNCTION(stack, push)(DSLIB_TYPE_STACK* this, DSLIB_TYPE value)
{
	this->data[this->size++] = value;
	DSLIB_FUNCTION(stack, maybe_resize)(this);
}

void DSLIB_FUNCTION(stack, pop)(DSLIB_TYPE_STACK* this)
{
	--this->size;
}

#undef DSLIB_TYPE
