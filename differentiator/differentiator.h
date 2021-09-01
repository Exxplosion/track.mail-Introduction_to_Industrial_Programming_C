#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include "tree_func.h"
#include "calc.h"

#define     NODE_NUM(cur)      get_node(NUM, cur, NULL, NULL)
#define     SUM_N(left, right) get_node (FUNC, SUM, left, right)
#define     SUB_N(left, right) get_node (FUNC, SUB, left, right)
#define     MUL_N(left, right) get_node (FUNC, MUL, left, right)
#define     DIV_N(left, right) get_node (FUNC, DIV, left, right)
#define     POW_N(left, right) get_node (FUNC, POW, left, right)
#define     LOG_N(cur)         get_node (FUNC, LOG, cur, NULL)
#define     SIN_N(cur)         get_node (FUNC, SIN, cur, NULL)
#define     COS_N(cur)         get_node (FUNC, COS, cur, NULL)
#define     TAN_N(cur)         get_node (FUNC, TAN, cur, NULL)
#define     COT_N(cur)         get_node (FUNC, COT, cur, NULL)
#define     EXP_N(cur)         get_node (FUNC, EXP, cur, NULL)


#define dL Diff(cur_node -> left)
#define dR Diff(cur_node -> right)
#define cL copy_node(cur_node -> left)
#define cR copy_node(cur_node -> right)

node* Diff(node* cur_node);
void begin_latex(FILE *tex);
void end_latex(FILE *tex);
void tree_pdf(node* node_cur, FILE *file);
void delete_const(node* node_cur);
void delete_zero(node* node_cur);


#endif