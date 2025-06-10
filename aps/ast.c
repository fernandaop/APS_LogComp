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
    n->type = NODE_VAR;
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

        case NODE_VAR:
            if (variable_exists(expr->id)) {
                VarType t = get_variable_type(expr->id);
                if (t == TYPE_TEXT) {
                    const char* val = get_variable_str(expr->id);
                    if (val) {
                        expr->str_val = strdup(val);
                        return 0;
                    }
                } else {
                    return get_variable(expr->id);
                }
            }
            return 0;

            case NODE_BINOP: {
                eval_expr(expr->left);
                eval_expr(expr->right);

                // Verifica se é uma operação de concatenação
                if (expr->int_val == '+') {
                    char lbuf[64] = "", rbuf[64] = "";

                    const char* l = expr->left->str_val;
                    const char* r = expr->right->str_val;

                    if (!l && expr->left->type == NODE_VAR) {
                        VarType lt = get_variable_type(expr->left->id);
                        if (lt == TYPE_INT)
                            sprintf(lbuf, "%d", get_variable(expr->left->id));
                        l = lbuf;
                    } else if (!l) {
                        sprintf(lbuf, "%d", eval_expr(expr->left));
                        l = lbuf;
                    }

                    if (!r && expr->right->type == NODE_VAR) {
                        VarType rt = get_variable_type(expr->right->id);
                        if (rt == TYPE_INT)
                            sprintf(rbuf, "%d", get_variable(expr->right->id));
                        r = rbuf;
                    } else if (!r) {
                        sprintf(rbuf, "%d", eval_expr(expr->right));
                        r = rbuf;
                    }

                    if (expr->str_val) free(expr->str_val);
                    expr->str_val = malloc(strlen(l) + strlen(r) + 1);
                    strcpy(expr->str_val, l);
                    strcat(expr->str_val, r);

                    return 0;
                }

                // Operações matemáticas
                int left = eval_expr(expr->left);
                int right = eval_expr(expr->right);
                switch (expr->int_val) {
                    case '-': return left - right;
                    case '*': return left * right;
                    case '/': return right != 0 ? left / right : 0;
                    default: return left + right;
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
        case NODE_LET: {
            if (root->var_type == TYPE_TEXT) {
                eval_expr(root->left);  // força gerar str_val
                set_variable_str(root->id, root->left->str_val);
            } else {
                int val = eval_expr(root->left);
                set_variable(root->id, val);
            }
            break;
        }
        case NODE_ASSIGN: {
            VarType t = get_variable_type(root->id);
            if (t == TYPE_TEXT) {
                eval_expr(root->left);
                set_variable_str(root->id, root->left->str_val);
            } else {
                int val = eval_expr(root->left);
                set_variable(root->id, val);
            }
            break;
        }
        case NODE_SHOW: {
            eval_expr(root->left);
            if (root->left->str_val)
                printf("%s\n", root->left->str_val);
            else
                printf("%d\n", eval_expr(root->left));
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
