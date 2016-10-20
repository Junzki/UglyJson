#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "uglyjson.h"

#define ugly_str4cmp(m, c0, c1, c2, c3)								\
	*(uint32_t*) m == ((c3 << 24) | (c2 << 16) | (c1 << 8) | c0)

#define ugly_str5cmp(m, c0, c1, c2, c3, c4)							\
	*(uint32_t*) m == ((c3 << 24) | (c2 << 16) | (c1 << 8) | c0)	\
		&& m[4] == c4

static void ugly_parse_ws(ugly_context *);
static int ugly_parse_null(ugly_context *, ugly_value *);
static int ugly_parse_value(ugly_context *, ugly_value *);


ugly_type
ugly_get_type(ugly_value *val)
{
	return val->type;
}


int
ugly_loads(ugly_value *val,
		   const char* json)
{
	ugly_context cxt;
	assert(val != NULL);
	
	cxt.json = json;
	val->type = UGLY_NULL;
	ugly_parse_ws(&cxt);
	
	return ugly_parse_value(&cxt, val);
}


static int
ugly_parse_value(ugly_context *cxt,
				 ugly_value *val)
{
	switch(*cxt->json)
	{
	case 'n':
		return ugly_parse_null(cxt, val);
	case '\0':
		return UGLY_PARSE_EXPECT_VALUE;
	default:
		return UGLY_PARSE_INVALID_VALUE;
	}
}


static void
ugly_parse_ws(ugly_context *cxt)
{
	const char *p = cxt->json;
	while (' ' == *p || '\t' == *p || '\n' == *p || '\r' == *p)
		++p;
	cxt->json = p;
}


static int
ugly_parse_null(ugly_context *cxt,
				ugly_value *val)
{
	if (!ugly_str4cmp(cxt->json, 'n', 'u', 'l', 'l'))
		 return UGLY_PARSE_INVALID_VALUE;

	cxt->json += 4;
	val->type = UGLY_NULL;
	return UGLY_PARSE_OK;
}
