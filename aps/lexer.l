%{
#include "ast.h"
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}
%%
"let"           { return LET; }
"loop"          { return LOOP; }
"in"            { return IN; }
"range"         { return RANGE; }
"show"          { return SHOW; }
"watch"         { return WATCH; }
"decide"        { return DECIDE; }
"yield"         { return YIELD; }
"section"       { return SECTION; }
"int"           { return TYPE_INT; }
"bool"          { return TYPE_BOOL; }
"text"          { return TYPE_TEXT; }
"yes"|"no"      { yylval.str = strdup(yytext); return BOOLEAN; }
":="            { return ASSIGN_INIT; }
"<-"            { return ASSIGN; }
"++"            { return CONCAT; }
"=="            { return EQ; }
"!="            { return NEQ; }
"<="            { return LTE; }
">="            { return GTE; }
"<"             { return LT; }
">"             { return GT; }
"//"            { return DIV_INT; }
"*"             { return '*'; }
"/"             { return '/'; }
"+"             { return '+'; }
"-"             { return '-'; }
"("             { return '('; }
")"             { return ')'; }
"{"             { return '{'; }
"}"             { return '}'; }
":"             { return ':'; }
","             { return ','; }
";"             { return ';'; }
\"([^\\\"]|\\.)*\" {
    yylval.str = strdup(yytext);
    return STRING;
}
[0-9]+ {
    yylval.num = atoi(yytext);
    return NUMBER;
}
[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext);
    return ID;
}
[ \t\n\r]+      { /* skip whitespace */ }

.               { return *yytext; }
%%

int yywrap(void) {
    return 1;
}
