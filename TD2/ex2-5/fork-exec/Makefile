LEX 	= flex
YACC 	= yacc -d -v
CC	= gcc -std=c99 -g -D_POSIX_SOURCE 



Shell: Shell.o Affichage.o Evaluation.o y.tab.o lex.yy.o
	$(CC) -o Shell Shell.o Affichage.o Evaluation.o y.tab.o lex.yy.o -lreadline -ly -ll

Shell.o: Shell.c Shell.h

Affichage.o :  Shell.h Affichage.h Affichage.c

Evaluation.o :  Shell.h Evaluation.h Evaluation.c


lex.yy.o: lex.yy.c y.tab.h Shell.h

y.tab.c y.tab.h: Analyse.y
	$(YACC) Analyse.y

lex.yy.c: Analyse.l Shell.h y.tab.h
	$(LEX) Analyse.l

.PHONY: clean
clean:
	rm -f *.o y.tab.* y.output lex.yy.*
