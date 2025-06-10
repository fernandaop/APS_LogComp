#ifndef AST_H
#define AST_H

typedef enum {
    NODE_PROGRAM,
    NODE_BLOCK,
    NODE_VAR,
    NODE_LET,
    NODE_ASSIGN,
    NODE_SHOW,
    NODE_LOOP,
    NODE_DECIDE,
    NODE_LITERAL,
    NODE_BINOP,
    NODE_WATCH,
    NODE_YIELD
} NodeType;

typedef struct Node {
    NodeType type;
    char* id;
    int int_val;
    char* str_val;
    int var_type;

    struct Node* left;
    struct Node* right;
    struct Node* cond;
    struct Node* true_expr;
    struct Node* false_expr;
    struct Node* body;
    struct Node* next;
} Node;

Node* create_literal_node(int val);
Node* create_string_node(char* str);
Node* create_variable_node(char* id);
Node* create_let_node(char* id, int var_type, Node* expr);
Node* create_assign_node(char* id, Node* expr);
Node* create_show_node(Node* expr);
Node* create_watch_node(char* id);
Node* create_yield_node(Node* expr);
Node* create_loop_node(char* id, Node* from, Node* to, Node* body);
Node* create_decide_node(Node* cond, Node* true_expr, Node* false_expr);
Node* create_binop_node(char op, Node* left, Node* right);
Node* append_statement(Node* stmt_list, Node* new_stmt);

void eval(Node* root);
void free_ast(Node* root);

#endif
