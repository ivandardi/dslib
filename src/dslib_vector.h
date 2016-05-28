#ifndef DSLIB_VECTOR_H
#define DSLIB_VECTOR_H

/**
 * \file
 *
 * \brief A vector.
 *
 * The dslib vector is a dinamically sized array. It automatically resizes
 * itself.
 *
 */

#include "helper/dslib_typedefs.h"

/**
 * \brief Initializes a vector.
 *
 * \param size Size of the elements of the vector in bytes. Use sizeof(type) as
 *        the argument.
 * \param free Pointer to a function that takes a void* parameter and returns
 *        void. It's used in case the vector contains malloc'd pointers so that
 *        it doesn't leak memory. If the types used don't contain malloc'd
 *        pointers, this can be passed as NULL.
 * \return An initialized vector.
 * \sa dslib_vector_clear(), dslib_vector_destroy()
 *
 */
Vector dslib_vector_init(size_t size, userFunction free);

/**
 * \brief Destroys the vector. It invalidates the whole vector and any iterators.
 *
 * \param vector The vector.
 *
 * \sa dslib_vector_clear(), dslib_vector_init()
 */
void dslib_vector_destroy(Vector const vector);

size_t dslib_vector_reserve(Vector const vector, size_t new_cap);

size_t dslib_vector_capacity(const Vector const vector);

void* dslib_vector_at(const Vector const vector, size_t pos);

/**
 * \brief Returns whether the vector is empty (whether its size is 0).
 *
 * \param vector The vector.
 * \return 1 if the vector is empty, 0 otherwise.
 *
 * \sa dslib_vector_clear(), dslib_vector_erase(), dslib_vector_size()
 */
int dslib_vector_empty(const Vector const vector);

/**
 * \brief Returns the number of elements in the vector.
 *
 * \param vector The vector.
 * \return The number of elements in the vector.
 *
 * \sa dslib_vector_empty()
 */
size_t dslib_vector_size(const Vector const vector);

/**
 * \brief Returns a pointer to the first element in the vector.
 *
 * Unlike dslib_vector_iterator_begin(), which returns an iterator to this same
 * element, this function returns a direct pointer to the element info.
 * Calling this function on an empty vector returns a NULL pointer.
 *
 * \param vector The vector.
 * \return A void pointer to the info of the first element in the vector.
 *
 * \sa dslib_vector_back(), dslib_vector_iterator_begin(), dslib_vector_push_front(),
 *     dslib_vector_pop_front()
 */
void* dslib_vector_front(const Vector const vector);

/**
 * \brief Returns a pointer to the last element in the vector.
 *
 * Unlike dslib_vector_iterator_end(), which returns an iterator just past this
 * element, this function returns a direct pointer to the element info.
 * Calling this function on an empty vector returns a NULL pointer.
 *
 * \param vector The vector.
 * \return A void pointer to the info of the last element in the vector.
 *
 * \sa dslib_vector_front(), dslib_vector_iterator_end(), dslib_vector_push_back(),
 *     dslib_vector_pop_back()
 */
void* dslib_vector_back(const Vector const vector);

/**
 * \brief Inserts a new element at the end of the vector, after its current last
 *        element. The content of val is copied to the inserted element.
 *
 * \param vector The vector.
 * \param val Value to be copied to the inserted element.
 *
 * \return An iterator to the inserted element.
 *
 * \sa dslib_vector_push_front(), dslib_vector_pop_back(), dslib_vector_insert()
 */
VectorIterator dslib_vector_push_back(Vector const vector, const void* const val);

/**
 * \brief Removes the last element in the vector vector, effectively reducing
 *        its size by one.
 *
 * \param vector The vector.
 *
 * \sa dslib_vector_pop_front(), dslib_vector_push_back(), dslib_vector_erase()
 */
void dslib_vector_pop_back(Vector const vector);

/**
 * \brief Inserts a new element before the element at the specified position.
 *
 * \param vector The vector.
 * \param position Position in the vector where the new element is inserted. It is
 *        an iterator obtained using the iterator functions.
 * \param val Value to be copied to the inserted elements.
 * \return An iterator that points to the inserted element.
 *
 * \sa dslib_vector_push_back(), dslib_vector_push_front(), dslib_vector_erase()
 */
VectorIterator dslib_vector_insert(Vector const vector, const VectorIterator const position, const void* const val);

/**
 * \brief Removes a single element from the vector at the specified position.
 *
 * \param vector The vector.
 * \param position Iterator pointing to the element to be removed.
 * \return An iterator pointing to the element that followed the last element
 *         erased by the function call. This is the vector end if the operation
 *         erased the last element in the vector.
 *
 * \sa dslib_vector_pop_back(), dslib_vector_pop_front(), dslib_vector_insert()
 */
VectorIterator dslib_vector_erase(Vector const vector, const VectorIterator const position);

/**
 * \brief Removes all elements from the vector (which are destroyed), and then
 *        destroys the vector itself.
 *
 * \param vector The vector.
 *
 * \sa dslib_vector_erase(), dslib_vector_pop_back(), dslib_vector_pop_front(),
 *     dslib_vector_empty()
 */
void dslib_vector_clear(Vector const vector);

/**
 * \brief Returns an iterator pointing to the first element in the vector.
 *
 * If the vector is empty, the returned iterator value shall not be
 * dereferenced.
 *
 * \param vector The vector.
 * \return An iterator to the beginning of the vector.
 */
VectorIterator dslib_vector_iterator_begin(const Vector const vector);

/**
 * \brief Returns an iterator referring to the past-the-end element in the
 *        vector.
 *
 * The past-the-end element is the theoretical element that would follow the
 * last element in the vector. It does not point to any element, and thus
 * shall not be dereferenced.
 *
 * If the vector is empty, this function returns the same as
 * dslib_vector_iterator_begin().
 *
 * \param vector The vector.
 * \return An iterator pointing to the past-the-end element of the vector.
 */
VectorIterator dslib_vector_iterator_end(const Vector const vector);

/**
 * \brief Increments the iterator.
 *
 * \param it The iterator.
 */
VectorIterator dslib_vector_iterator_increment(VectorIterator it);

/**
 * \brief Decrements the iterator.
 *
 * \param it The iterator.
 */
VectorIterator dslib_vector_iterator_decrement(VectorIterator it);

/**
 * \brief Returns a reverse iterator pointing to the last element in the
 *        vector (i.e. its reverse beginning).
 *
 * Reverse iterators iterate backwards: increasing them moves them towards the
 * beginning of the vector.
 *
 * dslib_iterator_rbegin() points to the element right before the one that would
 * be pointed to by member end.
 *
 * If the sequence is empty, the returned value shall not be dereferenced.
 *
 * \param vector The vector.
 * \return An iterator to the reverse beginning of the vector.
 */
VectorIterator dslib_vector_iterator_rbegin(const Vector const vector);

/**
 * \brief Returns a reverse iterator pointing to the theoretical element
 *        preceding the first element in the vector (which is considered its
 *        reverse end).
 *
 * \param vector The vector.
 * \return An iterator pointing to the before-the-start element of the vector.
 */
VectorIterator dslib_vector_iterator_rend(const Vector const vector);

/**
 * \brief Increments the reverse iterator.
 *
 * \param it The reverse iterator.
 */
VectorIterator dslib_vector_iterator_rincrement(VectorIterator it);

/**
 * \brief Decrements the reverse iterator.
 *
 * \param it The reverse iterator.
 */
VectorIterator dslib_vector_iterator_rdecrement(VectorIterator it);

/**
 * \brief Dereferences the iterator.
 *
 * \param it The iterator.
 */
void* dslib_vector_iterator_dereference(VectorIterator it);

/**
 * \brief Shortcut to iterate through all elements of a vector. Read as "for each
 *        element `it` in the vector `vector`".
 *
 * \param it A vector iterator.
 * \param vector The vector.
 */

#define dslib_vector_foreach(it,vector) for ((it) = dslib_vector_iterator_begin((vector)); (it) != dslib_vector_iterator_end((vector)); (it) = dslib_vector_iterator_increment((it)))

#endif // DSLIB_VECTOR_H
