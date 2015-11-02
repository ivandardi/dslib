#ifndef DSLIB_SLIST_H_INCLUDED
#define DSLIB_SLIST_H_INCLUDED

/**
 * \file
 *
 * \brief A singly linked list.
 *
 * The dslib slist is a singly linked list, i.e. elements can only point to the
 * next element, but not the previous one. Because of that, the slist has the
 * following time complexity:
 *
 * * push_front: O(1)
 *
 * * pop_front: O(1)
 *
 * * push_back: O(1)
 *
 * * pop_back: O(n)
 *
 * * insert: O(n)
 *
 * * remove: O(n)
 *
 * The dslib slist provides forward iterators only.
 */

#include "helper/dslib_typedefs.h"

/**
 * \brief Initializes a singly-linked slist (slist).
 *
 * \param size Size of the elements of the slist in bytes. Use sizeof(type) as
 *        the argument.
 * \param free Pointer to a function that takes a void* parameter and returns
 *        void. It's used in case the slist contains malloc'd pointers so that
 *        it doesn't leak memory. If the types used don't contain malloc'd
 *        pointers, this can be passed as NULL.
 * \return An initialized slist.
 *
 * \sa dslib_slist_clear()
 */
SList dslib_slist_init(size_t size, userFunction free);

/**
 * \brief Returns whether the slist is empty (whether its size is 0).
 *
 * \param slist The slist.
 * \return 1 if the length of the slist is 0,
 *         0 otherwise.
 *
 * \sa dslib_slist_clear(), dslib_slist_erase(), dslib_slist_size()
 */
int dslib_slist_empty(const SList const slist);

/**
 * \brief Returns the number of elements in the slist.
 *
 * \param slist The slist.
 * \return The number of elements in the slist.
 *
 * \sa dslib_slist_empty()
 */
size_t dslib_slist_size(const SList const slist);

/**
 * \brief Returns a pointer to the first element in the slist.
 *
 * Unlike dslib_slist_iterator_begin(), which returns an iterator to this same
 * element, this function returns a direct pointer to the element info.
 * Calling this function on an empty slist returns a NULL pointer.
 *
 * \param slist The slist.
 * \return A void pointer to the info of the first element in the slist.
 *
 * \sa dslib_slist_back(), dslib_slist_iterator_begin(),
 * dslib_slist_push_front(), dslib_slist_pop_front()
 */
void* dslib_slist_front(const SList const slist);

/**
 * \brief Returns a pointer to the last element in the slist.
 *
 * Unlike dslib_slist_iterator_end(), which returns an iterator just past this
 * element, this function returns a direct pointer to the element info.
 * Calling this function on an empty slist returns a NULL pointer.
 *
 * \param slist The slist.
 * \return A void pointer to the info of the last element in the slist.
 *
 * \sa dslib_slist_front(), dslib_slist_iterator_end(), dslib_slist_push_back(),
 *     dslib_slist_pop_back()
 */
void* dslib_slist_back(const SList const slist);

/**
 * \brief Inserts a new element at the beginning of the slist, right before its
 *        current first element. The content of val is copied to the inserted
 *        element.
 *
 * \param slist The slist.
 * \param val Value to be copied to the inserted element.
 *
 * \sa dslib_slist_push_back(), dslib_slist_pop_front(), dslib_slist_insert()
 */
void dslib_slist_push_front(SList const slist, const void* const val);

/**
 * \brief Removes the first element in the slist container, effectively reducing
 *        its size by one.
 *
 * \param slist The slist.
 *
 * \sa dslib_slist_pop_back(), dslib_slist_push_front(), dslib_slist_erase()
 */
void dslib_slist_pop_front(SList const slist);

/**
 * \brief Inserts a new element at the end of the slist, after its current last
 *        element. The content of val is copied to the inserted element.
 *
 * \param slist The slist.
 * \param val Value to be copied to the inserted element.
 *
 * \sa dslib_slist_push_front(), dslib_slist_pop_back(), dslib_slist_insert()
 */
void dslib_slist_push_back(SList const slist, const void* const val);

/**
 * \brief Removes the last element in the slist container, effectively reducing
 *        its size by one.
 *
 * \param slist The slist.
 *
 * \sa dslib_slist_pop_front(), dslib_slist_push_back(), dslib_slist_erase()
 */
void dslib_slist_pop_back(SList const slist);

/**
 * \brief Inserts a new element before the element at the specified position.
 *
 * \param slist The slist.
 * \param position Position in the slist where the new element is inserted. It
 *        is an iterator obtained using the iterator functions.
 * \param val Value to be copied to the inserted elements.
 * \return An iterator that points to the inserted element.
 *
 * \sa dslib_slist_push_back(), dslib_slist_push_front(), dslib_slist_erase()
 */
SListIterator dslib_slist_insert(SList const slist, const SListIterator const position, const void* const val);

/**
 * \brief Removes a single element from the slist at the specified position.
 *
 * \param slist The slist.
 * \param position Iterator pointing to the element to be removed.
 * \return An iterator pointing to the element that followed the last element
 *         erased by the function call. This is the slist end if the operation
 *         erased the last element in the slist.
 *
 * \sa dslib_slist_pop_back(), dslib_slist_pop_front(), dslib_slist_insert()
 */
SListIterator dslib_slist_erase(SList const slist, const SListIterator const position);

/**
 * \brief Removes all elements from the slist (which are destroyed), and then
 *        destroys the slist itself.
 *
 * \param slist The slist.
 *
 * \sa dslib_slist_erase(), dslib_slist_pop_back(), dslib_slist_pop_front(),
 *     dslib_slist_empty()
 */
void dslib_slist_clear(SList const slist);

/**
 * \brief Returns an iterator pointing to the first element in the slist.
 *
 * If the slist is empty, the returned iterator value shall not be
 * dereferenced.
 *
 * \param slist The slist.
 * \return An iterator to the beginning of the slist.
 */
SListIterator dslib_slist_iterator_begin(const SList const slist);

/**
 * \brief Returns an iterator referring to the past-the-end element in the
 *        slist.
 *
 * The past-the-end element is the theoretical element that would follow the
 * last element in the slist. It does not point to any element, and thus
 * shall not be dereferenced.
 *
 * If the slist is empty, this function returns the same as
 * dslib_slist_iterator_begin().
 *
 * \param list The list.
 * \return An iterator pointing to the past-the-end element of the list.
 */
SListIterator dslib_slist_iterator_end(const SList const slist);

/**
 * \brief Increments the iterator.
 *
 * \param it The iterator.
 */
void dslib_slist_iterator_increment(SListIterator* it);

/**
 * \brief Dereferences the iterator.
 *
 * \param it The iterator.
 */
void* dslib_slist_iterator_dereference(SListIterator it);

#define dslib_slist_foreach(it,list) for ((it) = dslib_slist_iterator_begin((list)); (it) != dslib_slist_iterator_end((list)); dslib_slist_iterator_increment(&(it)))

#endif /* DSLIB_SLIST_H_INCLUDED */
