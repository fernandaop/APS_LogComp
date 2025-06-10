#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "ast.h"
#include "symbol_table.h"

Node* create_literal_node(int val) {
    Node* n = calloc(1, sizeof(Node));
    n->type = NODE_LITERAL;
    n->int_val = val;
    return n;
}

Node* create_string_node(char* str) {
    Node* n = calloc(1, sizeof(Node));
    n->type = NODE_LITERAL;
    n->str_val = strdup(str);
    return n;
}

Node* create_variable_node(char* id) {
    Node* n = calloc(1, sizeof(Node));
    n->type = NODE_LITERAL;
    n->id = strdup(id);
    return n;
}

Node* create_let_node(char* id, int var_type, Node* expr) {
    Node* n = calloc(1, sizeof(Node));
    n->type = NODE_LET;
    n->id = strdup(id);
    n->var_type = var_type;
    n->left = expr;
    return n;
}

Node* create_assign_node(char* id, Node* expr) {
    Node* n = calloc(1, sizeof(Node));
    n->type = NODE_ASSIGN;
    n->id = strdup(id);
    n->left = expr;
    return n;
}

Node* create_show_node(Node* expr) {
    Node* n = calloc(1, sizeof(Node));
    n->type = NODE_SHOW;
    n->left = expr;
    return n;
}

Node* create_watch_node(char* id) {
    Node* n = calloc(1, sizeof(Node));
    n->type = NODE_WATCH;
    n->id = strdup(id);
    return n;
}

Node* create_yield_node(Node* expr) {
    Node* n = calloc(1, sizeof(Node));
    n->type = NODE_YIELD;
    n->left = expr;
    return n;
}

Node* create_loop_node(char* id, Node* from, Node* to, Node* body) {
    Node* n = calloc(1, sizeof(Node));
    n->type = NODE_LOOP;
    n->id = strdup(id);
    n->left = from;
    n->right = to;
    n->body = body;
    return n;
}

Node* create_decide_node(Node* cond, Node* true_expr, Node* false_expr) {
    Node* n = calloc(1, sizeof(Node));
    n->type = NODE_DECIDE;
    n->cond = cond;
    n->true_expr = true_expr;
    n->false_expr = false_expr;
    return n;
}

Node* create_binop_node(char op, Node* left, Node* right) {
    Node* n = calloc(1, sizeof(Node));
    n->type = NODE_BINOP;
    n->int_val = op;
    n->left = left;
    n->right = right;
    return n;
}

Node* append_statement(Node* stmt_list, Node* new_stmt) {
    if (!stmt_list) return new_stmt;
    Node* current = stmt_list;
    while (current->next) current = current->next;
    current->next = new_stmt;
    return stmt_list;
}

int eval_expr(Node* expr) {
    if (!expr) return 0;
    switch (expr->type) {
        case NODE_LITERAL:
            if (expr->str_val && strlen(expr->str_val) > 0 && isdigit(expr->str_val[0])) 
                return atoi(expr->str_val);
            if (expr->id) 
                return get_variable(expr->id);
            return expr->int_val;
            case NODE_BINOP: {
                int left = eval_expr(expr->left);
                int right = eval_expr(expr->right);
                switch (expr->int_val) {
                    case '+': return left + right;
                    case '-': return left - right;
                    case '*': return left * right;
                    case '/': return right != 0 ? left / right : 0;
                    case '=': return left == right;
                    case '!': return left != right;
                    case '<': return left < right;
                    case '>': return left > right;
                    case 'l': return left <= right;
                    case 'g': return left >= right;
                    default: return 0;
                }
            }

        case NODE_DECIDE: {
            int cond = eval_expr(expr->cond);
            return cond ? eval_expr(expr->true_expr) : eval_expr(expr->false_expr);
        }
        default:
            return 0;
    }
}

void eval(Node* root) {
    if (!root) return;
    switch (root->type) {
        case NODE_LET:
        case NODE_ASSIGN: {
            int val = eval_expr(root->left);
            set_variable(root->id, val);
            break;
        }
        case NODE_SHOW: {
            if (root->left->str_val)
                printf("%s\n", root->left->str_val);
            else {
                int val = eval_expr(root->left);
                printf("%d\n", val);
            }
            break;
        }
        case NODE_WATCH: {
            if (variable_exists(root->id)) {
                int val = get_variable(root->id);
                printf("[watch] %s = %d\n", root->id, val);
            }
            break;
        }
        case NODE_YIELD: {
            int val = eval_expr(root->left);
            printf("[yield] %d\n", val);
            break;
        }
        case NODE_LOOP: {
            int from = eval_expr(root->left);
            int to = eval_expr(root->right);
            for (int i = from; i < to; i++) {
                set_variable(root->id, i);
                eval(root->body);
            }
            break;
        }
        default:
            break;
    }
    eval(root->next);
}

void free_ast(Node* root) {
    if (!root) return;
    free_ast(root->left);
    free_ast(root->right);
    free_ast(root->cond);
    free_ast(root->true_expr);
    free_ast(root->false_expr);
    free_ast(root->body);
    free_ast(root->next);
    if (root->id) free(root->id);
    if (root->str_val) free(root->str_val);
    free(root);
}
