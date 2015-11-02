#include <stdio.h>
#include <string.h>
#include "dslib_error.h"

int dslib_error = DSLIB_SUCCESS;

void dslib_error_print(char* const msg)
{
	char* error = NULL;
	switch (dslib_error) {
		case DSLIB_SUCCESS:
			strcpy(msg, "No error.");
			break;
		case DSLIB_FAILURE:
			strcpy(msg, "Unknown error.");
			break;
		case DSLIB_EMPTY:
			strcpy(msg, "Empty.");
			break;
		case DSLIB_FAILED_TO_ALLOCATE_MEMORY:
			strcpy(msg, "Failed to allocate memory.");
			break;
		case DSLIB_ELEMENT_NOT_FOUND:
			strcpy(msg, "Element not found.");
			break;
		case DSLIB_INVALID_TYPES:
			strcpy(msg, "Tried to interface between two structures of different types.");
			break;
		default:
			strcpy(msg, "This should never happen.");
	}
	fprintf(stderr, "%s: %s\n", msg, error);
}
