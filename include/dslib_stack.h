#ifndef DSLIB_STACK_H_INCLUDED
#define DSLIB_STACK_H_INCLUDED

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

#include "helper/dslib_typedefs.h"

/**
 * \brief Initializes a stack.
 *
 * \param size Size of the elements of the stack in bytes. Use sizeof(type) as
 *        the argument.
 * \param free Pointer to a function that takes a void* parameter and returns
 *        void. It's used in case the stack contains malloc'd pointers so that
 *        it doesn't leak memory. If the types used don't contain malloc'd
 *        pointers, this can be passed as NULL.
 * \return An initialized stack.
 *
 * \sa dslib_stack_clear()
 */
Stack dslib_stack_init(size_t size, userFunction free);

/**
 * \brief Returns whether the stack is empty (whether its size is 0).
 *
 * \param stack The stack.
 * \return 1 if the stack is empty, 0 otherwise.
 *
 * \sa dslib_stack_clear(), dslib_stack_size()
 */
int dslib_stack_empty(const Stack const stack);

/**
 * \brief Returns the number of elements in the stack.
 *
 * \param stack The stack.
 * \return The number of elements in the stack.
 *
 * \sa dslib_stack_empty()
 */
size_t dslib_stack_size(const Stack const stack);

/**
 * \brief Returns a pointer to the first element in the stack.
 *
 * Unlike dslib_iterator_begin(), which returns an iterator to this same
 * element, this function returns a direct pointer to the element info.
 * Calling this function on an empty stack returns a NULL pointer.
 *
 * \param stack The stack.
 * \return A void pointer to the info of the first element in the stack.
 *
 * \sa dslib_stack_push(), dslib_stack_pop()
 */
void* dslib_stack_top(const Stack const stack);

/**
 * \brief Inserts a new element at the beginning of the stack, right before its
 *        current first element. The content of val is copied to the inserted
 *        element.
 *
 * \param stack The stack.
 * \param val Value to be copied to the inserted element.
 *
 * \sa dslib_stack_pop(), dslib_stack_size()
 */
void dslib_stack_push(Stack const stack, const void* const val);

/**
 * \brief Removes the first element in the stack container, effectively reducing
 *        its size by one.
 *
 * \param stack The stack.
 *
 * \sa dslib_stack_push(), dslib_stack_empty()
 */
void dslib_stack_pop(Stack const stack);

/**
 * \brief Removes all elements from the stack (which are destroyed), and then
 *        destroys the stack itself.
 *
 * \param stack The stack.
 *
 * \sa dslib_stack_pop(), dslib_stack_empty()
 */
void dslib_stack_clear(Stack const stack);

#endif /* DSLIB_STACK_H_INCLUDED */
