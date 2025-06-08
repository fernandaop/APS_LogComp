%{
#include "parser.tab.h"
#include <string.h>
%}

digit       [0-9]
letter      [a-zA-Z]
id          {letter}({letter}|{digit}|_)*

%%
"let"           return LET;
"loop"          return LOOP;
"in"            return IN;
"range"         return RANGE;
"show"          return SHOW;
"watch"         return WATCH;
"decide"        return DECIDE;
"yield"         return YIELD;
"section"       return SECTION;
"int"           return TYPE_INT;
"bool"          return TYPE_BOOL;
"text"          return TYPE_TEXT;
"yes"|"no"      return BOOLEAN;

":="            return ASSIGN_INIT;
"<-"            return ASSIGN;
"++"            return CONCAT;

"=="            return EQ;
"!="            return NEQ;
"<="            return LTE;
">="            return GTE;
"<"             return LT;
">"             return GT;

"//"            return DIV_INT;
"*"             return '*';
"/"             return '/';
"+"             return '+';
"-"             return '-';

"("             return '(';
")"             return ')';
"{"             return '{';
"}"             return '}';
":"             return ':';
","             return ',';
";"             return ';';

"\""(\\.|[^\"])*"\"" { yylval.str = strdup(yytext); return STRING; }
{id}             { yylval.str = strdup(yytext); return ID; }
{digit}+         { yylval.num = atoi(yytext); return NUMBER; }

[ \t\n\r]+       ;
.                return *yytext;

%%

int yywrap() { return 1; }