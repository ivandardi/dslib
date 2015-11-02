#ifndef DSLIB_ERROR_INCLUDED
#define DSLIB_ERROR_H_INCLUDED

/**
 * \file
 *
 * \brief Provides a way to detect errors that can occur while using dslib's
 *        functions, along with an error printing function.
 */

/**
 * \brief dslib's error variable.
 *
 * This variable stores dslib_error_code values, which can be used to check
 * whether a function call was successful or not. Think of it as a primitive
 * way to handle exceptions. For example, if `dslib_error != DSLIB_SUCCESS`,
 * then an error has occurred, and that should be dealt with accordingly.
 *
 * \sa dslib_error_print()
 */
extern int dslib_error;

/**
 * \brief dslib's error codes enum.
 *
 * This enum stores possible error codes that are assigned to the dslib_error
 * variable for error checking.
 */
enum dslib_error_code {
	DSLIB_SUCCESS,
	DSLIB_FAILURE,
	DSLIB_EMPTY,
	DSLIB_FAILED_TO_ALLOCATE_MEMORY,
	DSLIB_ELEMENT_NOT_FOUND,
	DSLIB_INVALID_TYPES
};

/**
 * \brief Prints an error message according to dslib_error.
 *
 * How to use:
 *
 * If, for example, `dslib_error` was set to `DSLIB_EMPTY` when trying to pop
 * from a stack, you can do the following:
 * \code{.c}
 * if (dslib_empty != DSLIB_SUCCESS) {
 *     dslib_error_print("Stack failure");
 *    // Handle error here
 * }
 * \endcode
 *
 * Output on stderr:
 * \code{.c}
 * Stack failure: Empty.
 * \endcode
 *
 * \param msg String to describe the error.
 */
void dslib_error_print(char* const msg);

#endif /* DSLIB_ERROR_H_INCLUDED */
