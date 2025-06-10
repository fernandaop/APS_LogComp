#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "symbol_table.h"

#define MAX_VARS 100

typedef struct {
    char* name;
    VarType type;
    int int_val;
    char* str_val;
} Variable;

static Variable variables[MAX_VARS];
static int var_count = 0;

void init_symbol_table() {
    var_count = 0;
}

void cleanup_symbol_table() {
    for (int i = 0; i < var_count; i++) {
        free(variables[i].name);
        if (variables[i].str_val) free(variables[i].str_val);
    }
    var_count = 0;
}

int variable_exists(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) return 1;
    }
    return 0;
}

VarType get_variable_type(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].type;
        }
    }
    fprintf(stderr, "Erro: tipo da variável '%s' não encontrado.\n", name);
    exit(1);
}

void set_variable(const char* name, int value) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            variables[i].type = TYPE_INT;
            variables[i].int_val = value;
            return;
        }
    }

    if (var_count < MAX_VARS) {
        variables[var_count].name = strdup(name);
        variables[var_count].type = TYPE_INT;
        variables[var_count].int_val = value;
        variables[var_count].str_val = NULL;
        var_count++;
    } else {
        fprintf(stderr, "Erro: número máximo de variáveis atingido.\n");
    }
}

void set_variable_str(const char* name, const char* str) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            variables[i].type = TYPE_TEXT;
            if (variables[i].str_val) free(variables[i].str_val);
            variables[i].str_val = strdup(str);
            return;
        }
    }

    if (var_count < MAX_VARS) {
        variables[var_count].name = strdup(name);
        variables[var_count].type = TYPE_TEXT;
        variables[var_count].int_val = 0;
        variables[var_count].str_val = strdup(str);
        var_count++;
    } else {
        fprintf(stderr, "Erro: número máximo de variáveis atingido.\n");
    }
}

int get_variable(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0 && variables[i].type == TYPE_INT) {
            return variables[i].int_val;
        }
    }
    fprintf(stderr, "Erro: variável int '%s' não definida ou de tipo incorreto.\n", name);
    exit(1);
}

const char* get_variable_str(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0 && variables[i].type == TYPE_TEXT) {
            return variables[i].str_val;
        }
    }
    return NULL;
}
