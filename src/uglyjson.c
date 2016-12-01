#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "uglyjson.h"
#include "number.h"

#define ugly_str4cmp(m, c0, c1, c2, c3)								\
	*(uint32_t*) m == ((c3 << 24) | (c2 << 16) | (c1 << 8) | c0)

#define ugly_str5cmp(m, c0, c1, c2, c3, c4)							\
	*(uint32_t*) m == ((c3 << 24) | (c2 << 16) | (c1 << 8) | c0)	\
		&& m[4] == c4

static void ugly_parse_ws(ugly_context *);
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
	
	cxt.json = (char *)json;
	val->type = UGLY_NULL;
	ugly_parse_ws(&cxt);
	
	return ugly_parse_value(&cxt, val);
}


static int
ugly_parse_value(ugly_context *cxt,
				 ugly_value *val)
{
    char *c = cxt->json;
    if ('n' == *c && ugly_str4cmp(c, 'n', 'u', 'l', 'l'))
    {
        cxt->json += 4;
        val->type = UGLY_NULL;
    }
    else if ('t' == *c && ugly_str4cmp(c, 't', 'r', 'u', 'e'))
    {
        cxt->json += 4;
        val->type = UGLY_TRUE;
    }
    else if ('f' == *c && ugly_str5cmp(c, 'f', 'a', 'l', 's', 'e'))
    {
        cxt->json += 5;
        val->type = UGLY_FALSE;
    }
	else if (1 == is_number(c))
	{
		char* num_end = numpos(c);
		char* end;
		if (NULL == num_end)
			return UGLY_PARSE_INVALID_VALUE;

		val->value = strtod(c, &end);
		cxt->json = end;
		val->type = UGLY_NUMBER;
	}
    else if ('\0' == *c)
    {
        return UGLY_PARSE_EXPECT_VALUE;
    }
    else
    {
        return UGLY_PARSE_INVALID_VALUE;
    }

    return UGLY_PARSE_OK;
}


static void
ugly_parse_ws(ugly_context *cxt)
{
	const char *p = cxt->json;
	while (' ' == *p || '\t' == *p || '\n' == *p || '\r' == *p)
		++p;
	cxt->json = (char *)p;
}


