#ifndef UGLY_NUMBER_H__
#define UGLY_NUMBER_H__

int is_number(char*);
char* numpos(const char*);

#ifndef __STDBOOL_H
#include <stdbool.h>  /* Macros of boolean types. */
#endif

bool is_digit(char*);
bool is_plus(char*);
bool is_minus(char*);
bool is_exp(char*);
bool is_dot(char*);

#endif
