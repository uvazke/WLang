#include <stdio.h>
#include <stdlib.h>


typedef enum {
	INT_TYPE,
	DOUBLE_TYPE,
	STR_TYPE,
	ADD_TYPE,
	SUB_TYPE,
	MUL_TYPE,
	DIV_TYPE,
	MOD_TYPE,
	EMPTY_TYPE
}Type;

typedef struct{
	Type type; 
	union {
		int i;
		double d;
		char *str;
	} val;
}Tag;

Tag *return_calculated_tag(Type calc_type, Tag *left ,Tag *right);
Tag *return_expr(Tag *tag);
void print_val(Tag *tag);
Tag *return_empty();
