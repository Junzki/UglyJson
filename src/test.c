#include <stdio.h>
#include <stdlib.h>

#include "include/test.h"
#include "uglyjson.h"
#include "number.h"

static int test_status = EXIT_SUCCESS;
static int test_count = 0;
static int test_passed = 0;

static void
test_parse_number()
{
	char *values[] = {"1", "-1", "0.1", "1.234", "-1.1234"};
	double expected[] = {1.0, -1.0, 0.1, 1.234, -1.1234};
	int index = 0;
	int tests = 5;

	for (index = 0; index < tests; ++index)
	{
		ugly_value val;
		EXPECT_EQ_INT(UGLY_PARSE_OK, ugly_loads(&val, values[index]));
		EXPECT_EQ_INT(UGLY_NUMBER, val.type);
		EXPECT_EQ_DOUBLE(expected[index], val.value);
	}
}


static void
test_parse()
{
    char* values[] = {"true", "false", "null"};
    ugly_type result_types[] = {UGLY_TRUE, UGLY_FALSE, UGLY_NULL};
    int index = 0;
    int tests = 3;

    for (index=0; index < tests; ++index)
    {
        ugly_value val;
        EXPECT_EQ_INT(UGLY_PARSE_OK, ugly_loads(&val, values[index]));
        EXPECT_EQ_INT(result_types[index], ugly_get_type(&val));
    }

	test_parse_number();
}


int
main(void) {
	test_parse();
	printf("%d/%d (%3.2f%%) passed\n", test_passed, test_count, test_passed * 100.0 / test_count);

	return test_status;
}
	
