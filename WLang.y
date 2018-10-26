%{
	#include <stdio.h>
	#include "WLang.h"
	// TODO enable function, history
%}
%union{
	Tag *tag;
}
%token HOW_MANY_LINE
%token <tag>JP
%token INT_LITERAL DOUBLE_LITERAL
%token STR SMCLN END
%token LP RP ADD SUB MUL DIV MOD EQ
%type <tag> list expr term factor string
%%

list
	: /* Empty */
	| list expr SMCLN{print_val($2);}
	| list string SMCLN 
	{
		//print_val($2);
		print_variable($2);
		//fprintf(stderr, "Please input 'quit;' to finish the program.\n");
	}
	| list SMCLN
	| list HOW_MANY_LINE SMCLN
	| list JP SMCLN
	{
		print_val($2);
	}
	| list END SMCLN {exit(0);}
	| list string EQ expr SMCLN
	{
		add_variable($2,$4);
		//$$ = return_expr($4);
	}
	;
string
	: STR
	| string STR
	;
expr
	: term
	| expr ADD expr {$$ = return_calculated_tag(ADD_TYPE, $1 ,$3);}
	| expr SUB term {$$ = return_calculated_tag(SUB_TYPE, $1 ,$3);}
	| expr MOD term {$$ = return_calculated_tag(MOD_TYPE, $1 ,$3);}
	| expr expr {$$ = $2;}
	;
term
	: factor
	| term MUL term {$$ = return_calculated_tag(MUL_TYPE, $1 ,$3);}
	| term DIV term {$$ = return_calculated_tag(DIV_TYPE, $1 ,$3);}
	;
factor
	: INT_LITERAL
	| DOUBLE_LITERAL
	| string
	| LP expr RP {$$ = return_expr($2);}
	;

%%






