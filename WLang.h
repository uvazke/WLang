#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Types
*/

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

/*
 global variables
*/

char VARIABLE_BUFFER[100][100];
int VARIABLE_BUFFER_USED_LENGTH;
int VARIABLE_VALUES_I[100];
double VARIABLE_VALUES_D[100];
Type VARIABLE_TYPE[100];
char FUNCTION_NAME_BUFFER[100][100];
int FUNCTION_BUFFER_USED_LENGTH;
char FUNCTION_BUFFER[100][1000];

/*
WLangSubFunctions
*/

Tag *return_calculated_tag(Type calc_type, Tag *left ,Tag *right);
Tag *return_expr(Tag *tag);
void print_val(Tag *tag);
void add_variable(Tag *left,Tag *right);
Tag *call_variable(Tag *tag);
void print_variable(Tag *tag);
Tag *return_empty();
char *TrimSMCLNandOperators(Tag* tag);
char *TrimVARIABLE(Tag* tag);
int search_variable(char *str);
