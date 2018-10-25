WLang : y.tab.c y.tab.h lex.yy.c WLangSubFunctions.o WLang.h
	cc y.tab.c lex.yy.c WLangSubFunctions.o -lreadline -ly -ll -o WLang

y.tab.h : WLang.y
	yacc -d WLang.y

lex.yy.c : WLang.l
	lex WLang.l

WLangSubFunctions.o : WLangSubFunctions.c WLang.h
