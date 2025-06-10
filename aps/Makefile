all: lumina

lumina: parser.tab.o lex.yy.o main.o ast.o symbol_table.o
	gcc -o lumina parser.tab.o lex.yy.o main.o ast.o symbol_table.o

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser.tab.o: parser.tab.c
	gcc -c parser.tab.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

main.o: main.c
	gcc -c main.c

ast.o: ast.c ast.h
	gcc -c ast.c

symbol_table.o: symbol_table.c symbol_table.h
	gcc -c symbol_table.c

clean:
	rm -f *.o *.tab.* lex.yy.c lumina
