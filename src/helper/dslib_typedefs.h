#ifndef DSLIB_TYPEDEFS_H_INCLUDED
#define DSLIB_TYPEDEFS_H_INCLUDED

/**
 * \file
 *
 * \brief Typedef definitions.
 */

/**
 * \brief A pointer to a function that takes void* as a parameter and returns
 *        void.
 *
 * Typedef of the function provided by the user that's used to deallocate
 * memory, in case the user creates a container with elements that * dinamically
 * allocate memory.
 */
typedef void (*userFunction)(void*);

/**
 * \brief A graph type.
 */
typedef struct Graph* Graph;

/**
 * \brief A graph iterator type.
 */
typedef struct Vertex* GraphIterator;

/**
 * \brief A graph edge type.
 */
typedef struct Edge* Edge;

/**
 * \brief A list type.
 */
typedef struct List* List;

/**
 * \brief A list iterator type.
 */
typedef struct ListNode* ListIterator;

/**
 * \brief A slist type.
 */
typedef struct SList* SList;

/**
 * \brief A slist iterator type.
 */
typedef struct SListNode* SListIterator;

/**
 * \brief A queue type.
 */
typedef struct Queue* Queue;

/**
 * \brief A stack type.
 */
typedef struct Stack* Stack;

#endif /* DSLIB_TYPEDEFS_H_INCLUDED */
