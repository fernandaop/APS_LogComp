#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "symbol_table.h"

#define MAX_VARS 100

typedef struct {
    char* name;
    int value;
} Variable;

static Variable variables[MAX_VARS];
static int var_count = 0;

void init_symbol_table() {
    var_count = 0;
}

void cleanup_symbol_table() {
    for (int i = 0; i < var_count; i++) {
        free(variables[i].name);
    }
    var_count = 0;
}

int variable_exists(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

void set_variable(const char* name, int value) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            variables[i].value = value;
            return;
        }
    }
    if (var_count < MAX_VARS) {
        variables[var_count].name = strdup(name);
        variables[var_count].value = value;
        var_count++;
    } else {
        fprintf(stderr, "Erro: número máximo de variáveis atingido.\n");
    }
}

int get_variable(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }
    fprintf(stderr, "Erro: variável '%s' não definida.\n", name);
    exit(1);
}
