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
test_parse_null()
{
	ugly_value val;

	val.type = UGLY_TRUE;
	EXPECT_EQ_INT(UGLY_PARSE_OK, ugly_loads(&val, "null"));
	EXPECT_EQ_INT(UGLY_NULL, ugly_get_type(&val));
}

static void
test_parse_true()
{
	ugly_value val;

	val.type = UGLY_TRUE;
	EXPECT_EQ_INT(UGLY_PARSE_OK, ugly_loads(&val, "true"));
	EXPECT_EQ_INT(UGLY_TRUE, ugly_get_type(&val));
}

static void
test_parse_false()
{
	ugly_value val;

	val.type = UGLY_TRUE;
	EXPECT_EQ_INT(UGLY_PARSE_OK, ugly_loads(&val, "false"));
	EXPECT_EQ_INT(UGLY_FALSE, ugly_get_type(&val));
}


static void
test_parse()
{
	test_parse_null();
	test_parse_true();
	test_parse_false();
}


int
main(void) {
	test_parse();
	printf("%d/%d (%3.2f%%) passed\n", test_passed, test_count, test_passed * 100.0 / test_count);

	return test_status;
}
	
