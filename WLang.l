%{
	#undef YY_INPUT
	#define YY_INPUT(buffer, result, max_size) (result = my_yyinput(buffer, max_size))
	#include <stdio.h>
	#include <string.h>
	#include <readline/readline.h>
	#include "WLang.h"
	#include "y.tab.h"
	
	int line=1;

	static int my_yyinput(char *buffer, int max_size);
%}

%start COMMENT
%%
<INITIAL>"quit" return END;
<INITIAL>"how_many_line" {fprintf(stderr, "%d lines are read.\n", line);return HOW_MANY_LINE;};
<INITIAL>";"		return SMCLN;
<INITIAL>"("		return LP;
<INITIAL>")"		return RP;
<INITIAL>"+"		return ADD;
<INITIAL>"-"		return SUB;
<INITIAL>"*"		return MUL;
<INITIAL>"/"		return DIV;
<INITIAL>"%"		return MOD;
<INITIAL>[1-9][0-9]* {
	Tag *tag = malloc(sizeof(Tag)); 
	tag->type = INT_TYPE;
	sscanf(yytext,"%d",&tag->val.i);
	yylval.tag = tag;
	return INT_LITERAL;
}
<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
	Tag *tag = malloc(sizeof(Tag));
	tag->type = STR_TYPE; 
	tag->val.str = yytext;
	yylval.tag = tag;
	return STR;
}
<INITIAL>[0-9]*\.[0-9]* {
	Tag *tag = malloc(sizeof(Tag)); 
	tag->type = DOUBLE_TYPE;
	sscanf(yytext,"%lf",&tag->val.d);
	yylval.tag = tag;
	return DOUBLE_LITERAL;
}
<INITIAL>[ \t] ;
<INITIAL>[\n\r]|\r\n {line++;}
<INITLAL>[あ-ん][あ-ん]* {
	Tag *tag = malloc(sizeof(Tag));
	tag->type = STR_TYPE; 
	tag->val.str = yytext;
	yylval.tag = tag;
	return JP;
}
<INITIAL>^#	BEGIN COMMENT;
<INITIAL>. fprintf(stderr, "Please input 'quit' to finish the program.\n");
<COMMENT>\n|\r|\r\n	BEGIN INITIAL;
<COMMENT>.      ;
%%

static char *str_buf;
static int str_used_length;

void init_str_buffer(){
	if(str_buf){
		free(str_buf);
	}
	str_buf = NULL;
	str_used_length = 0;
}

static int my_yyinput(char *buffer, int max_size){
	int len;
	
	if(str_buf==NULL){
		str_used_length=0;
		str_buf = readline(">>");
		if(str_buf ==NULL){
			return 0;
		}
	}
	len = strlen(str_buf) - str_used_length > max_size ? max_size : strlen(str_buf) - str_used_length;
	strncpy(buffer, &str_buf[str_used_length], len);
	str_used_length += len;
	if(str_buf[str_used_length] == '\0'){
		free(str_buf);
		str_buf = NULL;
	} 
	return len;
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