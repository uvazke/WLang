%{
	#include <stdio.h>
	#include "WLang.h"
%}
%union{
	Tag *tag;
}
%token NL
%token HOW_MANY_LINE
%token <tag> A
%token <tag> INT_LITERAL
%token STR
%token LP RP ADD SUB MUL DIV MOD
%type <tag> list expr term factor

%%

list
	: /* Empty */
	| list expr NL {printf("%d\n", $2);}
	| list string NL 
	{
		fprintf(stderr, "Please input 'quit' to finish the program.\n");
	}
	| list NL
	| list HOW_MANY_LINE NL
	| list A NL
	{
		{printf("%s\n", $2);}
	}

	;
string
	: STR
	| string STR
	| ADD
	| SUB
	| MUL
	| DIV
	| MOD
	;
expr
	: term
	| expr ADD expr {$$ = $1 + $3;}
	| expr SUB term {$$ = $1 - $3;}
	| expr MOD term {$$ = $1 % $3;}
	| expr expr {$$ = $2;}
	;
term
	: factor
	| term MUL term {$$ = $1 * $3;}
	| term DIV term {$$ = $1 / $3;}
	;
factor
	: INT_LITERAL
	| LP expr RP {$$ = $2;}
	;

%%






