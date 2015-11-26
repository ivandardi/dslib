#ifndef TEST_LIST_H_INCLUDED
#define TEST_LIST_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include "../src/dslib_list.h"
#include "../src/helper/dslib_error.h"

#define NUM 10

void listPrint(List TEST)
{
	ListIterator it;
	dslib_list_foreach(it, TEST) {
		printf("%d\n", *(int*)dslib_list_iterator_dereference(it));
	}
}

void listStatus(List TEST)
{
	printf("List empty: %s\n", (dslib_list_empty(TEST) ? "true" : "false"));
	printf("List  size: %d\n", (int)dslib_list_size(TEST));
}

void test(char* msg)
{
	if (dslib_error != DSLIB_SUCCESS) {
		dslib_error_print(msg);
	}
}

void test_list()
{
	List TEST = dslib_list_init(sizeof(int), NULL);

	clock_t t1, t2;

	int i;
	ListIterator it;

	t1 = clock();
	for (i = 0; i < NUM; i++) {
		dslib_list_push_back(TEST, &i);
		test("dslib_list_push_back");
	}
	t2 = clock();
	listStatus(TEST);
	printf("dslib_list_push_back: %f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	t1 = clock();
	for (i = 0; i < NUM; i++) {
		dslib_list_pop_back(TEST);
		test("dslib_list_pop_back");
	}
	t2 = clock();
	listStatus(TEST);
	printf("dslib_list_pop_back: %f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	t1 = clock();
	for (i = 0; i < NUM; i++) {
		dslib_list_push_front(TEST, &i);
		test("dslib_list_push_front");
	}
	t2 = clock();
	listStatus(TEST);
	printf("dslib_list_push_front: %f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	t1 = clock();
	for (i = 0; i < NUM; i++) {
		dslib_list_pop_front(TEST);
		test("dslib_list_pop_front");
	}
	t2 = clock();
	listStatus(TEST);
	printf("dslib_list_pop_front: %f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	for (i = 0; i < NUM; i++) {
		dslib_list_push_back(TEST, &i);
	}
	listPrint(TEST);

	t1 = clock();
	dslib_list_foreach(it, TEST) {
		(*(int*)dslib_list_iterator_dereference(it))++;
	}
	listPrint(TEST);
	t2 = clock();
	listStatus(TEST);
	printf("list forward iterating: %f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	t1 = clock();
	for (it = dslib_list_iterator_rbegin(TEST); it != dslib_list_iterator_rend(TEST); dslib_list_iterator_rincrement(&it)) {
		(*(int*)dslib_list_iterator_dereference(it))--;
	}
	listPrint(TEST);
	t2 = clock();
	listStatus(TEST);
	printf("list reverse iterating: %f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	t1 = clock();
	it = dslib_list_iterator_begin(TEST);

	listPrint(TEST);
	t2 = clock();
	listStatus(TEST);
	printf("list reverse iterating: %f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);

	t1 = clock();
	dslib_list_clear(TEST);
	t2 = clock();
	printf("dslib_list_clear: %f\n", (double) (t2 - t1) / CLOCKS_PER_SEC);
	listStatus(TEST);
}

#endif // TEST_LIST_H_INCLUDED
