#pragma once

/**
 * \file
 *
 * \brief A stack.
 *
 * The dslib stack is based on a singly linked list, only allowing interfacing
 * with the front of the list. Since it's a stack, we call it the top of the
 * stack.
 *
 * The dslib stack has the following time complexity for each of its operations:
 *
 * * push: O(1)
 *
 * * pop: O(1)
 *
 * The dslib stack doesn't provice iterators.
 */

#include "dslib_macros.h"
#include <stddef.h>


#define DSLIB_TYPE_STACK TYPE_EVALUATOR(stack, DSLIB_TYPE)

typedef struct DSLIB_TYPE_STACK
{
	size_t size;
	size_t capacity;
	DSLIB_TYPE* data;
} DSLIB_TYPE_STACK;


DSLIB_TYPE_STACK DSLIB_FUNCTION(stack, init)();

void DSLIB_FUNCTION(stack, destroy)(DSLIB_TYPE_STACK* this);

DSLIB_TYPE* DSLIB_FUNCTION(stack, top)(DSLIB_TYPE_STACK * this);

int DSLIB_FUNCTION(stack, empty)(DSLIB_TYPE_STACK * this);

size_t DSLIB_FUNCTION(stack, size)(DSLIB_TYPE_STACK * this);

void
DSLIB_FUNCTION(stack, push_ref)(DSLIB_TYPE_STACK * this,
                                DSLIB_TYPE * value);
void
DSLIB_FUNCTION(stack, push)(DSLIB_TYPE_STACK * this, DSLIB_TYPE value);

void DSLIB_FUNCTION(stack, pop)(DSLIB_TYPE_STACK * this);

#undef DSLIB_TYPE
