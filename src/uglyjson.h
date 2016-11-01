#ifndef UGLYJSON_H__
#define UGLYJSON_H__

typedef enum {
	UGLY_NULL,
	UGLY_TRUE,
	UGLY_FALSE,

	UGLY_NUMBER,
	UGLY_STRING,
	
	UGLY_LIST,
	UGLY_OBJECT
} ugly_type;

enum {
	UGLY_PARSE_OK = 0,
	UGLY_PARSE_EXPECT_VALUE,
	UGLY_PARSE_INVALID_VALUE,
	UGLY_PARSE_ROOT_NOT_SINGULAR
};

typedef struct {
	ugly_type type;
	double value;
} ugly_value;

typedef struct {
	char* json;
} ugly_context;


ugly_type ugly_get_type(ugly_value *);
int ugly_loads(ugly_value *, const char *);


#endif
