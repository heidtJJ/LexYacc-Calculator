CC = gcc
FLAGS = -g
YACC = bison
LEX = flex

boo: y.tab.o lex.yy.o tree.o
	$(CC) $(FLAGS) -o boo y.tab.o lex.yy.o tree.o -ll -ly

tree.o: tree.c
	$(CC) $(FLAGS) -c tree.c

y.tab.o: y.tab.c
	$(CC) $(FLAGS) -c y.tab.c

lex.yy.o: lex.yy.c
	$(CC) $(FLAGS) -c lex.yy.c

y.tab.c: calc.y
	$(YACC) -y -dv calc.y

lex.yy.c: calc.l
	$(LEX) -l calc.l

clean:
	rm -f y.tab.* y.output lex.yy.* tree.o boo