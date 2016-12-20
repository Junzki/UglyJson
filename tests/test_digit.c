#include <stdio.h>
#include <stdlib.h>

#ifndef __STDBOOL_H
#include <stdbool.h>
#endif

#include "test.h"
#include "../src/number.h"

static int test_status = EXIT_SUCCESS;
static int test_count = 0;
static int test_passed = 0;

int
to_int(bool val) {
	if (val)
		return 1;
	else
		return 0;
}


static void
test_is_digit(int expect, char *val)
{
	bool result;

	result = is_digit(val);
	
	EXPECT_EQ_INT(expect, to_int(result));
}


static void
test_is_number()
{
	char *value[] = {"1", "-1", "0.1", "1.234", "-1.1234"};
	int expect_number[] = {1, 1, 1, 1, 1};
	int expect_digit[] = {1, 0, 1, 1, 0};
	int index;
	int tests = 5;

	for (index = 0; index < tests; ++index)
	{
		test_is_digit(expect_digit[index], value[index]);
		EXPECT_EQ_INT(expect_number[index], is_number(value[index]));
	}
}



int
main(void)
{
	test_is_number();
	printf("%d/%d (%3.2f%%) passed\n", test_passed, test_count, test_passed * 100.0 / test_count);

	return test_status;
}
