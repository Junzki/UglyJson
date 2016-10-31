#include <stdio.h>
#include <stdlib.h>

#include "uglyjson.h"

static int test_status = EXIT_SUCCESS;
static int test_count = 0;
static int test_passed = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format)				\
	do {																\
		++test_count;													\
		if (equality)													\
			++test_passed;												\
		else {															\
			fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual); \
			test_status = EXIT_FAILURE;									\
		}																\
	}																	\
	while (0);															\

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")


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
}


int
main(void) {
	test_parse();
	printf("%d/%d (%3.2f%%) passed\n", test_passed, test_count, test_passed * 100.0 / test_count);

	return test_status;
}
	
