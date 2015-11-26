#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/dslib.h"
#include "test_list.h"

#define TEST_LIST

int main(void)
{
	#ifdef TEST_LIST

	test_list();

	#endif // TEST_LIST

	return 0;
}
