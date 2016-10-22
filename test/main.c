#include "test_vector_int.h"
#include "test_stack_int.h"
#include <stdio.h>


int main()
{
	const int SIZE = 5;

	puts("VECTOR BEGIN");
	dslib_vector_int v = dslib_vector_int_init();

	for (int i = 0; i < SIZE; ++i) {
		dslib_vector_int_push_back(&v, i);
	}

	while (!dslib_vector_int_empty(&v)) {
		dslib_vector_iterator_int it;
		DSLIB_FOREACH_VECTOR(it, v, int) {
			printf("%d ", *it.value);
		}
		puts("");
		dslib_vector_int_pop_back(&v);
	}

	dslib_vector_int_destroy(&v);
	puts("VECTOR END");

	puts("STACK BEGIN");
	dslib_stack_int s = dslib_stack_int_init();

	for (int i = 0; i < SIZE; ++i) {
		dslib_stack_int_push(&s, i);
	}

	while (!dslib_stack_int_empty(&s)) {
		printf("%d\n", *dslib_stack_int_top(&s));
		dslib_stack_int_pop(&s);
	}

	dslib_stack_int_destroy(&s);
	puts("STACK END");
	return 0;
}
