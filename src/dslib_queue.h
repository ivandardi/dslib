#ifndef DSLIB_QUEUE_H_INCLUDED
#define DSLIB_QUEUE_H_INCLUDED

/**
 * \file
 *
 * \brief A queue.
 *
 * The dslib queue is based on a singly linked list, allowing popping from the
 * start of the list and pushing to the back of the list.
 *
 * The dslib queue has the following time complexity for each of its operations:
 *
 * * push: O(1)
 *
 * * pop: O(1)
 *
 * The dslib queue doesn't provice iterators.
 */

#include "helper/dslib_typedefs.h"

/**
 * \brief Initializes a queue.
 *
 * \param size Size of the elements of the queue in bytes. Use sizeof(type) as
 *        the argument.
 * \param free Pointer to a function that takes a void* parameter and returns
 *        void. It's used in case the queue contains malloc'd pointers so that
 *        it doesn't leak memory. If the types used don't contain malloc'd
 *        pointers, this can be passed as NULL.
 * \return An initialized queue.
 *
 * \sa dslib_queue_clear()
 */
Queue dslib_queue_init(size_t size, userFunction free);

/**
 * \brief Returns whether the queue is empty (whether its size is 0).
 *
 * \param queue The queue.
 * \return 1 if the length of the queue is 0,
 *         0 otherwise.
 *
 * \sa dslib_queue_clear(), dslib_queue_size()
 */
int dslib_queue_empty(const Queue const queue);

/**
 * \brief Returns the number of elements in the queue.
 *
 * \param queue The queue.
 * \return The number of elements in the queue.
 *
 * \sa dslib_queue_empty()
 */
size_t dslib_queue_size(const Queue const queue);

/**
 * \brief Returns a pointer to the first element in the queue.
 *
 * Calling this function on an empty queue returns a NULL pointer.
 *
 * \param queue The queue.
 * \return A void pointer to the info of the first element in the queue.
 *
 * \sa dslib_queue_back(), dslib_iterator_begin(), dslib_queue_pop()
 */
void* dslib_queue_front(const Queue const queue);

/**
 * \brief Returns a pointer to the last element in the queue.
 *
 * Calling this function on an empty queue returns a NULL pointer.
 *
 * \param queue The queue.
 * \return A void pointer to the info of the last element in the queue.
 *
 * \sa dslib_queue_front(), dslib_iterator_end(), dslib_queue_push()
 */
void* dslib_queue_back(const Queue const queue);

/**
 * \brief Inserts a new element at the end of the queue, after its current last
 *        element. The content of val is copied to the inserted element.
 *
 * \param queue The queue.
 * \param val Value to be copied to the inserted element.
 *
 * \sa dslib_queue_pop(), dslib_queue_size()
 */
void dslib_queue_push(Queue const queue, const void* const val);

/**
 * \brief Removes the first element in the queue container, effectively reducing
 *        its size by one.
 *
 * \param queue The queue.
 *
 * \sa dslib_queue_push(), dslib_queue_empty()
 */
void dslib_queue_pop(Queue const queue);

/**
 * \brief Removes all elements from the queue (which are destroyed), and then
 *        destroys the queue itself.
 *
 * \param queue The queue.
 *
 * \sa dslib_queue_pop(), dslib_queue_empty()
 */
void dslib_queue_clear(Queue const queue);

#endif /* DSLIB_QUEUE_H_INCLUDED */
