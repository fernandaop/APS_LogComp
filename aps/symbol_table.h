#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

void init_symbol_table();
void cleanup_symbol_table();
void set_variable(const char* name, int value);
int get_variable(const char* name);
int variable_exists(const char* name);

#endif