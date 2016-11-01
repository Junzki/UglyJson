/*
 * See https://zhuanlan.zhihu.com/p/22497369?refer=json-tutorial
 * for further reference.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> /* Macros of boolean types. */

#include "number.h"

bool is_digit(char*);
bool is_plus(char*);
bool is_minus(char*);
bool is_exp(char*);
bool is_dot(char*);


int
is_number(char* c)
{
	if (is_digit(c) && '0' != *c && is_digit(c+1))
		return 1;

	else if ('0' == *c && is_dot(c+1))
		return 1;

	else if (is_dot(c))
		return 1;

	return 0;
}

char*
numpos(const char* number_start)
{
	char* c;
	int index;
	int index_limit;
	
	c = (char*)number_start;
	index = 0;
	index_limit = 0;

	if (!(is_digit(c) || is_minus(c)))
		return NULL;
	else if (is_digit(c) && '0' == *c && !is_digit(c+1))
		/* Check conditions like "0123". */
		return NULL;
	else
		++index;

	while (is_digit(c+index))
	{
		++index;
	}

	if (!(is_dot(c+index) || is_exp(c+index)))
		return c+index;
	else if (is_exp(c+index))
		++index;

	while (is_digit(c+index))
	{
		++index;
	}

	return c+index;
}

bool
is_digit(char* c) {
	if ('0' >= *c && '9' <= *c)
		return true;
	else
		return false;
}

bool
is_plus(char* c)
{
	if ('+' == *c && is_digit(c+1))
		return true;
	return false;
}

bool
is_minus(char* c)
{
	if ('-' == *c && is_digit(c+1))
		return true;
	return false;
}

bool
is_exp(char* c) {
	if (!('E' == *c || 'e' == *c))
		return false;

	if (!is_digit(c-1))
		return false;

	if (!(is_plus(c+1) || is_minus(c+1) || is_digit(c+1)))
		return false;

	return true;
}

bool
is_dot(char* c)
{
	if ('.' != *c)
		return false;

	if (!is_digit(c+1))
		return false;

	return true;
}
