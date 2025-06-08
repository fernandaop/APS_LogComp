all: lumina

lumina: parser.tab.o lex.yy.o main.o
	gcc -o lumina parser.tab.o lex.yy.o main.o

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o *.tab.* lex.yy.c lumina
