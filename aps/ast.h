// ast.h
#ifndef AST_H
#define AST_H

typedef enum {
    NODE_PROGRAM,
    NODE_BLOCK,
    NODE_LET,
    NODE_ASSIGN,
    NODE_SHOW,
    NODE_LOOP,
    NODE_DECIDE,
    NODE_LITERAL,
    NODE_BINOP
} NodeType;

typedef struct Node {
    NodeType type;
    char* id;
    char* str_val;
    int int_val;

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
Node* create_let_node(char* id, Node* expr);
Node* create_assign_node(char* id, Node* expr);
Node* create_show_node(Node* expr);
Node* create_loop_node(char* id, Node* from, Node* to, Node* body);
Node* create_decide_node(Node* cond, Node* true_expr, Node* false_expr);
Node* create_binop_node(char op, Node* left, Node* right);
Node* append_statement(Node* stmt_list, Node* new_stmt);

void eval(Node* root);
void free_ast(Node* root);

#endif
