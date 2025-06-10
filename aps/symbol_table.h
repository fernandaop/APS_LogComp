#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef enum {
    TYPE_INT = 1,
    TYPE_BOOL = 2,
    TYPE_TEXT = 3
} VarType;

void init_symbol_table();
void cleanup_symbol_table();

void set_variable(const char* name, int value);           // para int
void set_variable_str(const char* name, const char* str); // para texto

int get_variable(const char* name);                       // para int
const char* get_variable_str(const char* name);           // para texto

int variable_exists(const char* name);
VarType get_variable_type(const char* name);

#endif
