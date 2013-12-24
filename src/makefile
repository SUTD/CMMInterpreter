#The makefile for interpreter based on Flex and Bison
CC = gcc
FLAG = -w
interpreter: main.o util.o cmm.tab.o cmm.lex.o symtab.o analyze.o
	$(CC) $(FLAG) -o ../bin\&test/interpreter main.o util.o cmm.tab.o cmm.lex.o symtab.o analyze.o
main.o: main.c parse.h analyze.h
	$(CC) $(FLAG) -c main.c
cmm.tab.o:cmm.tab.c parse.h
	$(CC) $(FLAG) -c cmm.tab.c
cmm.tab.c:cmm.y
	bison -d cmm.y
cmm.lex.o:cmm.lex.c cmm.tab.h
	$(CC) $(FLAG) -c cmm.lex.c
cmm.lex.c:cmm.l
	flex -o cmm.lex.c cmm.l
symtab.o:symtab.c symtab.h globals.h
	$(CC) $(FLAG) -c symtab.c
analyze.o:analyze.c globals.h symtab.h analyze.h
	$(CC) $(FLAG) -c analyze.c
util.o:util.c
	$(CC) $(FLAG) -c util.c

clean:
	-rm *.o