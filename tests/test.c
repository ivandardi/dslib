#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/dslib.h"

void printListStatus(List TEST)
{
	printf("\n\nDSLIB ==========\n");
	printf("List Length: %u\n", (unsigned int)dslib_list_size(TEST));
	printf("List Empty: %s\n\n", dslib_list_empty(TEST) ? "true" : "false");
	size_t i = 0;
	ListIterator it;
	dslib_list_foreach(it, TEST) {
		int* temp = dslib_list_iterator_dereference(it);
		printf("TEST[%d] = %d\n", i++, *temp);
	}
	printf("DSLIB ==========\n\n");
}

void printEdgeListStatus(List TEST)
{
	printf("\n\nDSLIB ==========\n");
	printf("List Length: %u\n", (unsigned int)dslib_list_size(TEST));
	printf("List Empty: %s\n\n", dslib_list_empty(TEST) ? "true" : "false");
	size_t i = 0;
	ListIterator it;
	dslib_list_foreach(it, TEST) {
		Edge temp = dslib_list_iterator_dereference(it);
		printf("TEST[%d] = %d\n", i++, *(int*)dslib_graph_vertex_getInfo(dslib_graph_edge_pointsTo(temp)));
	}
	printf("DSLIB ==========\n\n");
}

int main(void)
{
	int i;
	Graph GRAPH_TEST = dslib_graph_init(sizeof(int), NULL, 0);
	i = 1;
	GraphIterator a = dslib_graph_vertex_add(GRAPH_TEST, &i);
	i = 2;
	GraphIterator b = dslib_graph_vertex_add(GRAPH_TEST, &i);
	dslib_graph_edge_add_undirected(GRAPH_TEST, a, b, 0);
	List tempL = dslib_graph_vertex_getAdjacents(a);
	printEdgeListStatus(tempL);
	return 0;
}

#if 0

int main(int argc, char** argv)
{
	unsigned long X = strtoul(argv[1], NULL, 0);
	int temp;
	size_t i;
	double stackTime, queueTime, slistTime, listTime;
	clock_t c1, c2;

	if (argc == 1) {
		return -1;
	}

	/**************************
	* STACK
	**************************/

	c1 = clock();

	Stack STACK_TEST = stack_init(sizeof(int), NULL);

	printf("Test: stack_push\n");
	for (i = 0; i < X; i++) {
		temp = i * 10;
		stack_push(STACK_TEST, &temp);
	}
	/* printStackStatus(STACK_TEST); */

	printf("Test: stack_foreach\n");
	stack_foreach(STACK_TEST, addOne);
	/* printStackStatus(STACK_TEST); */

	printf("Test: stack_pop\n");
	for (i = 0; i < X; i++) {
		stack_pop(STACK_TEST, &temp);
	}
	/* printStackStatus(STACK_TEST); */

	stack_destroy(STACK_TEST);

	c2 = clock();
	stackTime = (double)(c2 - c1)/CLOCKS_PER_SEC;
	printf("Stack: %f\n", stackTime);
	fflush(stdout);

	/**************************
	* QUEUE
	**************************/

	c1 = clock();

	Queue QUEUE_TEST = queue_init(sizeof(int), NULL);

	printf("Test: queue_push\n");
	for (i = 0; i < X; i++) {
		temp = i * 10;
		queue_push(QUEUE_TEST, &temp);
	}
	/* printQueueStatus(QUEUE_TEST); */

	printf("Test: queue_foreach\n");
	queue_foreach(QUEUE_TEST, addOne);
	/* printQueueStatus(QUEUE_TEST); */

	printf("Test: queue_pop\n");
	for (i = 0; i < X; i++) {
		queue_pop(QUEUE_TEST, &temp);
	}
	/* printQueueStatus(QUEUE_TEST); */

	queue_destroy(QUEUE_TEST);

	c2 = clock();
	queueTime = (double)(c2 - c1)/CLOCKS_PER_SEC;
	printf("Queue: %f\n", queueTime);
	fflush(stdout);

	/**************************
	* SDSLIB
	**************************/

	c1 = clock();

	SList SDSLIB_TEST = slist_init(sizeof(int), NULL);

	printf("Test: slist_push_head, slist_push_tail\n");
	for (i = 0; i < X/2; i++) {
		temp = i * 10;
		slist_push_head(SDSLIB_TEST, &temp);
		slist_push_tail(SDSLIB_TEST, &temp);
	}
	/* printSListStatus(SDSLIB_TEST); */

	printf("Test: slist_push, slist_pop\n");
	temp = 12345;

	slist_push(SDSLIB_TEST, 0, &temp);
	/* printSListStatus(SDSLIB_TEST); */

	slist_pop(SDSLIB_TEST, 0, &temp);
	/* printSListStatus(SDSLIB_TEST); */

	slist_push(SDSLIB_TEST, X/2, &temp);
	/* printSListStatus(SDSLIB_TEST); */

	slist_pop(SDSLIB_TEST, X/2, &temp);
	/* printSListStatus(SDSLIB_TEST); */

	slist_push(SDSLIB_TEST, X, &temp);
	/* printSListStatus(SDSLIB_TEST); */

	slist_pop(SDSLIB_TEST, X, &temp);
	/* printSListStatus(SDSLIB_TEST); */

	printf("Test: slist_foreach\n");
	slist_foreach(SDSLIB_TEST, addOne);
	/* printSListStatus(SDSLIB_TEST); */

	printf("Test: slist_pop_head, slist_pop_tail\n");
	for (i = 0; i < X/2; i++) {
		slist_pop_head(SDSLIB_TEST, &temp);
		slist_pop_tail(SDSLIB_TEST, &temp);
	}
	/* printSListStatus(SDSLIB_TEST); */

	slist_destroy(SDSLIB_TEST);

	c2 = clock();
	slistTime = (double)(c2 - c1)/CLOCKS_PER_SEC;
	printf("SList: %f\n", slistTime);
	fflush(stdout);

	/**************************
	* DSLIB
	**************************/

	c1 = clock();

	List DSLIB_TEST = list_init(sizeof(int), NULL);

	printf("Test: list_push_head, list_push_tail\n");
	for (i = 0; i < X/2; i++) {
		temp = i * 10;
		list_push_head(DSLIB_TEST, &temp);
		list_push_tail(DSLIB_TEST, &temp);
	}
	/* printListStatus(DSLIB_TEST); */

	printf("Test: list_push, list_pop\n");
	temp = 12345;

	list_push(DSLIB_TEST, 0, &temp);
	/* printListStatus(DSLIB_TEST); */

	list_pop(DSLIB_TEST, 0, &temp);
	/* printListStatus(DSLIB_TEST); */

	list_push(DSLIB_TEST, X/2, &temp);
	/* printListStatus(DSLIB_TEST); */

	list_pop(DSLIB_TEST, X/2, &temp);
	/* printListStatus(DSLIB_TEST); */

	list_push(DSLIB_TEST, X, &temp);
	/* printListStatus(DSLIB_TEST); */

	list_pop(DSLIB_TEST, X, &temp);
	/* printListStatus(DSLIB_TEST); */

	printf("Test: list_foreach\n");
	list_foreach(DSLIB_TEST, addOne);
	/* printListStatus(DSLIB_TEST); */

	printf("Test: list_pop_head, list_pop_tail\n");
	for (i = 0; i < X/2; i++) {
		list_pop_head(DSLIB_TEST, &temp);
		list_pop_tail(DSLIB_TEST, &temp);
	}
	/* printListStatus(DSLIB_TEST); */

	c2 = clock();
	listTime = (double)(c2 - c1)/CLOCKS_PER_SEC;
	printf("List: %f\n", listTime);
	fflush(stdout);

	return 0;
}

#endif
