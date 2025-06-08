#include <stdio.h>
#include "ast.h"
#include "symbol_table.h"

int yyparse(void);
extern Node* root;

int main() {
    init_symbol_table();
    printf("Iniciando análise léxica e sintática...\n");
    if (yyparse() == 0 && root != NULL) {
        printf("\nExecutando programa:\n");
        eval(root);
        free_ast(root);
    } else {
        printf("Erro na análise.\n");
    }
    cleanup_symbol_table();
    return 0;
}
