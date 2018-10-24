WLang : y.tab.c y.tab.h lex.yy.c
	cc y.tab.c lex.yy.c -ly -ll -o WLang

y.tab.h : WLang.y
	yacc -d WLang.y

lex.yy.c : WLang.l
	lex WLang.l

