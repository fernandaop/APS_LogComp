%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symbol_table.h"

int yylex(void);
void yyerror(const char *s);

Node* root;
%}

%union {
    int num;
    char* str;
    Node* node;
}

%token <str> ID STRING BOOLEAN
%token <num> NUMBER
%token TOKEN_INT TOKEN_BOOL TOKEN_TEXT
%token LET LOOP IN RANGE SHOW WATCH DECIDE YIELD SECTION
%token ASSIGN_INIT ASSIGN CONCAT
%token EQ NEQ LT LTE GT GTE DIV_INT

%type <node> program blocks block statements statement expression term factor decide_expression loop_statement
%type <num> type

%start program

%%

program:
    blocks { root = $1; }
    ;

blocks:
    block              { $$ = $1; }
    | blocks block     { $$ = append_statement($1, $2); }
    ;

block:
    SECTION ID ':' statements { $$ = $4; }
    | statements              { $$ = $1; }
    ;

statements:
    statement               { $$ = $1; }
    | statements statement  { $$ = append_statement($1, $2); }
    ;

statement:
    LET ID ':' type ASSIGN_INIT expression ';' { $$ = create_let_node($2, $4, $6); }
    | ID ASSIGN expression ';'                 { $$ = create_assign_node($1, $3); }
    | SHOW '(' expression ')' ';'              { $$ = create_show_node($3); }
    | WATCH ID ';'                             { $$ = create_watch_node($2); }
    | YIELD expression ';'                     { $$ = create_yield_node($2); }
    | loop_statement                           { $$ = $1; }
    | decide_expression ';'                    { $$ = $1; }
    ;

loop_statement:
    LOOP ID IN RANGE '(' expression ',' expression ')' '{' statements '}' {
        $$ = create_loop_node($2, $6, $8, $11);
    }
    ;

decide_expression:
    DECIDE '(' expression ',' expression ',' expression ')' {
        $$ = create_decide_node($3, $5, $7);
    }
    ;

type:
    TOKEN_INT  { $$ = TYPE_INT; }
  | TOKEN_BOOL { $$ = TYPE_BOOL; }
  | TOKEN_TEXT { $$ = TYPE_TEXT; }
  ;

expression:
    expression EQ term       { $$ = create_binop_node('=', $1, $3); }
    | expression NEQ term    { $$ = create_binop_node('!', $1, $3); }
    | expression LTE term    { $$ = create_binop_node('l', $1, $3); }
    | expression GTE term    { $$ = create_binop_node('g', $1, $3); }
    | expression LT term     { $$ = create_binop_node('<', $1, $3); }
    | expression GT term     { $$ = create_binop_node('>', $1, $3); }
    | expression '+' term    { $$ = create_binop_node('+', $1, $3); }
    | expression '-' term    { $$ = create_binop_node('-', $1, $3); }
    | expression CONCAT term { $$ = create_binop_node('+', $1, $3); }
    | term                   { $$ = $1; }
    ;

term:
    term '*' factor       { $$ = create_binop_node('*', $1, $3); }
    | term '/' factor     { $$ = create_binop_node('/', $1, $3); }
    | term DIV_INT factor { $$ = create_binop_node('/', $1, $3); }
    | factor              { $$ = $1; }
    ;

factor:
    NUMBER      { $$ = create_literal_node($1); }
    | STRING    { $$ = create_string_node($1); }
    | ID        { $$ = create_variable_node($1); }
    | BOOLEAN   {
        int val = (strcmp($1, "yes") == 0) ? 1 : 0;
        $$ = create_literal_node(val);
    }
    | '(' expression ')' { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe: %s\n", s);
}
