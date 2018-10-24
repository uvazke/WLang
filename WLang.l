%{
	#undef YY_INPUT
	#define YY_INPUT(buffer, result, max_size) (result = my_yyinput(buffer, max_size))
	#include <stdio.h>
	#include <string.h>
	#include <readline/readline.h>
	#include "y.tab.h"
	#include "WLang.h"
	int line=1;

	static int my_yyinput(char *buffer, int max_size);
%}

%start COMMENT
%%
<INITIAL>"quit" exit(0);
<INITIAL>"how_many_line" {fprintf(stderr, "%d lines are read.\n", line);return HOW_MANY_LINE;};
<INITIAL>"("		return LP;
<INITIAL>")"		return RP;
<INITIAL>"+"		return ADD;
<INITIAL>"-"		return SUB;
<INITIAL>"*"		return MUL;
<INITIAL>"/"		return DIV;
<INITIAL>"%"		return MOD;
<INITIAL>[1-9][0-9]* {sscanf(yytext,"%d",&yylval->tag.i);return INT_LITERAL;};
<INITIAL>[A-Za-z_][A-Za-z_0-9]* {return STR;};
<INITIAL>[0-9]*\.[0-9]* ;
<INITIAL>[ \t] ;
<INITIAL>[\n\r]|\r\n {line++;return NL;};
<INITLAL>"あ" {strcpy(yylval.tag.str, yytext);return A;};
<INITIAL>^#	BEGIN COMMENT;
<INITIAL>. fprintf(stderr, "Please input 'quit' to finish the program.\n");
<COMMENT>\n|\r|\r\n	BEGIN INITIAL;
<COMMENT>.      ;
%%

static int my_yyinput(char *buffer, int max_size){
	int result,len;
	char *str = readline("input");
	if(str){
		len = strlen(str) > max_size ? max_size : strlen(str);
		strncpy(buffer, *str, len);
	}
	if(*str == '\0'){
		free(str);
	} 
	free(str);
	result = len;
	return result;
}
/*
int main(int argc, char ** argv){
	++argv,--argc;
	if(argc > 0){
		yyin = fopen(argv[0], "r");
		printf("File open.\n");
	}else{
		yyin = stdin;
	}
	if(yyin == NULL){
		fprintf(stderr, "File open is failed.\n");exit(0);
	}
	yylex();	
	printf("%d lines are read\n",line);
	
	return(0);
}
*/