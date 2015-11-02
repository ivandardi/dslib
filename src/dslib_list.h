#ifndef DSLIB_LIST_H_INCLUDED
#define DSLIB_LIST_H_INCLUDED

/**
 * \file
 *
 * \brief A doubly linked list.
 *
 * The dslib list is a doubly linked list, i.e. elements point to the next
 * element as well as the previous one. Because of that, the list has the
 * following time complexity:
 *
 * * push_front: O(1)
 *
 * * pop_front: O(1)
 *
 * * push_back: O(1)
 *
 * * pop_back: O(1)
 *
 * * insert: O(1)
 *
 * * remove: O(1)
 *
 * The dslib list provides both forward and backwards iterators. That means its
 * possible to traverse it both ways: from start to end, and from end to start.
 */

#include "helper/dslib_typedefs.h"

/**
 * \brief Initializes a doubly-linked list (list).
 *
 * \param size Size of the elements of the list in bytes. Use sizeof(type) as
 *        the argument.
 * \param free Pointer to a function that takes a void* parameter and returns
 *        void. It's used in case the list contains malloc'd pointers so that
 *        it doesn't leak memory. If the types used don't contain malloc'd
 *        pointers, this can be passed as NULL.
 * \return An initialized list.
 *
 * \sa dslib_list_clear()
 */
List dslib_list_init(size_t size, userFunction free);

/**
 * \brief Returns whether the list is empty (whether its size is 0).
 *
 * \param list The list.
 * \return 1 if the list is empty, 0 otherwise.
 *
 * \sa dslib_list_clear(), dslib_list_erase(), dslib_list_size()
 */
int dslib_list_empty(const List const list);

/**
 * \brief Returns the number of elements in the list.
 *
 * \param list The list.
 * \return The number of elements in the list.
 *
 * \sa dslib_list_empty()
 */
size_t dslib_list_size(const List const list);

/**
 * \brief Returns a pointer to the first element in the list.
 *
 * Unlike dslib_list_iterator_begin(), which returns an iterator to this same
 * element, this function returns a direct pointer to the element info.
 * Calling this function on an empty list returns a NULL pointer.
 *
 * \param list The list.
 * \return A void pointer to the info of the first element in the list.
 *
 * \sa dslib_list_back(), dslib_list_iterator_begin(), dslib_list_push_front(),
 *     dslib_list_pop_front()
 */
void* dslib_list_front(const List const list);

/**
 * \brief Returns a pointer to the last element in the list.
 *
 * Unlike dslib_list_iterator_end(), which returns an iterator just past this
 * element, this function returns a direct pointer to the element info.
 * Calling this function on an empty list returns a NULL pointer.
 *
 * \param list The list.
 * \return A void pointer to the info of the last element in the list.
 *
 * \sa dslib_list_front(), dslib_list_iterator_end(), dslib_list_push_back(),
 *     dslib_list_pop_back()
 */
void* dslib_list_back(const List const list);

/**
 * \brief Inserts a new element at the beginning of the list, right before its
 *        current first element. The content of val is copied to the inserted
 *        element.
 *
 * \param list The list.
 * \param val Value to be copied to the inserted element.
 *
 * \sa dslib_list_push_back(), dslib_list_pop_front(), dslib_list_insert()
 */
void dslib_list_push_front(List const list, const void* const val);

/**
 * \brief Removes the first element in the list list, effectively reducing
 *        its size by one.
 *
 * \param list The list.
 *
 * \sa dslib_list_pop_back(), dslib_list_push_front(), dslib_list_erase()
 */
void dslib_list_pop_front(List const list);

/**
 * \brief Inserts a new element at the end of the list, after its current last
 *        element. The content of val is copied to the inserted element.
 *
 * \param list The list.
 * \param val Value to be copied to the inserted element.
 *
 * \sa dslib_list_push_front(), dslib_list_pop_back(), dslib_list_insert()
 */
void dslib_list_push_back(List const list, const void* const val);

/**
 * \brief Removes the last element in the list list, effectively reducing
 *        its size by one.
 *
 * \param list The list.
 *
 * \sa dslib_list_pop_front(), dslib_list_push_back(), dslib_list_erase()
 */
void dslib_list_pop_back(List const list);

/**
 * \brief Inserts a new element before the element at the specified position.
 *
 * \param list The list.
 * \param position Position in the list where the new element is inserted. It is
 *        an iterator obtained using the iterator functions.
 * \param val Value to be copied to the inserted elements.
 * \return An iterator that points to the inserted element.
 *
 * \sa dslib_list_push_back(), dslib_list_push_front(), dslib_list_erase()
 */
ListIterator dslib_list_insert(List const list, const ListIterator const position, const void* const val);

/**
 * \brief Removes a single element from the list at the specified position.
 *
 * \param list The list.
 * \param position Iterator pointing to the element to be removed.
 * \return An iterator pointing to the element that followed the last element
 *         erased by the function call. This is the list end if the operation
 *         erased the last element in the list.
 *
 * \sa dslib_list_pop_back(), dslib_list_pop_front(), dslib_list_insert()
 */
ListIterator dslib_list_erase(List const list, const ListIterator const position);

/**
 * \brief Removes all elements from the list (which are destroyed), and then
 *        destroys the list itself.
 *
 * \param list The list.
 *
 * \sa dslib_list_erase(), dslib_list_pop_back(), dslib_list_pop_front(),
 *     dslib_list_empty()
 */
void dslib_list_clear(List const list);

/**
 * \brief Returns an iterator pointing to the first element in the list.
 *
 * If the list is empty, the returned iterator value shall not be
 * dereferenced.
 *
 * \param list The list.
 * \return An iterator to the beginning of the list.
 */
ListIterator dslib_list_iterator_begin(const List const list);

/**
 * \brief Returns an iterator referring to the past-the-end element in the
 *        list.
 *
 * The past-the-end element is the theoretical element that would follow the
 * last element in the list. It does not point to any element, and thus
 * shall not be dereferenced.
 *
 * If the list is empty, this function returns the same as
 * dslib_list_iterator_begin().
 *
 * \param list The list.
 * \return An iterator pointing to the past-the-end element of the list.
 */
ListIterator dslib_list_iterator_end(const List const list);

/**
 * \brief Increments the iterator.
 *
 * \param it The iterator.
 */
void dslib_list_iterator_increment(ListIterator* it);

/**
 * \brief Decrements the iterator.
 *
 * \param it The iterator.
 */
void dslib_list_iterator_decrement(ListIterator* it);

/**
 * \brief Returns a reverse iterator pointing to the last element in the
 *        list (i.e. its reverse beginning).
 *
 * Reverse iterators iterate backwards: increasing them moves them towards the
 * beginning of the list.
 *
 * dslib_iterator_rbegin() points to the element right before the one that would
 * be pointed to by member end.
 *
 * If the sequence is empty, the returned value shall not be dereferenced.
 *
 * \param list The list.
 * \return An iterator to the reverse beginning of the list.
 */
ListIterator dslib_list_iterator_rbegin(const List const list);

/**
 * \brief Returns a reverse iterator pointing to the theoretical element
 *        preceding the first element in the list (which is considered its
 *        reverse end).
 *
 * \param list The list.
 * \return An iterator pointing to the before-the-start element of the list.
 */
ListIterator dslib_list_iterator_rend(const List const list);

/**
 * \brief Increments the reverse iterator.
 *
 * \param it The reverse iterator.
 */
void dslib_list_iterator_rincrement(ListIterator* it);

/**
 * \brief Decrements the reverse iterator.
 *
 * \param it The reverse iterator.
 */
void dslib_list_iterator_rdecrement(ListIterator* it);

/**
 * \brief Dereferences the iterator.
 *
 * \param it The iterator.
 */
void* dslib_list_iterator_dereference(ListIterator it);

/**
 * \brief Shortcut to iterate through all elements of a list. Read as "for each
 *        element `it` in the list `list`".
 *
 * \param it A list iterator.
 * \param list The list.
 */

#define dslib_list_foreach(it,list) for ((it) = dslib_list_iterator_begin((list)); (it) != dslib_list_iterator_end((list)); dslib_list_iterator_increment(&(it)))

#endif /* DSLIB_LIST_H_INCLUDED */
