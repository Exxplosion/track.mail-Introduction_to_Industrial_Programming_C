#include "differentiator.h"

node* Diff(node* cur_node)
{
  assert(cur_node != NULL);
  if (cur_node -> type_node == NUM)
    return NODE_NUM(0);
  if (cur_node -> type_node == VAR)
    return NODE_NUM(1);
  switch((int)(cur_node->val))
  {
    case SUM:
        return SUM_N(dL, dR);
    case SUB:
        return SUB_N(dL, dR);
    case MUL:
        return SUM_N(MUL_N(dL, cR), MUL_N(dR, cL));
    case DIV:
        return DIV_N(SUB_N(MUL_N(dL, cR), MUL_N(dR, cL)), POW_N(cR, NODE_NUM(2)));
    case SIN:
        return MUL_N(COS_N(cL), dL);
    case COS:
        return MUL_N(NODE_NUM(-1), MUL_N(SIN_N(cL), dL));
    case LOG:
        return MUL_N(DIV_N(NODE_NUM(1), cL), dL);
    case TAN:
        return MUL_N(DIV_N(NODE_NUM(1), POW_N(COS_N(cL), NODE_NUM(2))), dL);
    case COT:
        return MUL_N(DIV_N(NODE_NUM(-1), POW_N(SIN_N(cL), NODE_NUM(2))), dL);
    case SQRT:
        return MUL_N(NODE_NUM(0.5), MUL_N(DIV_N(NODE_NUM(1), cL), dL));
    case EXP:
        return MUL_N(EXP_N(cL), dL);
    case POW:
        if (cur_node->right->type_node == NUM)
            return MUL_N(MUL_N(NODE_NUM(cur_node->right->val), POW_N(cL, NODE_NUM(cur_node->right->val - 1))), dL);
        if (cur_node->left->type_node == NUM)
            return MUL_N(MUL_N(POW_N(NODE_NUM(cur_node->left->val), cR), LOG_N(NODE_NUM(cur_node->left->val))), dR);
        return MUL_N(copy_node(cur_node), SUM_N(MUL_N(dL, DIV_N(cR, cL)), MUL_N(dR, LOG_N(cL)))); 
    default:
        printf("Unknown cmd");
    return NULL;
        //exit(1);
  }
}


void begin_latex(FILE *tex)
{   fprintf(tex, "\\documentclass[12pt]{article}\n"
            "\\usepackage[utf8]{inputenc}\n"
            "\\usepackage{amsmath, amssymb, mathtools}\n"
            "\\usepackage[left = 20mm, bottom=15mm, top=15mm, right=10mm]{geometry}\n\n"
            "\\begin{document}\n"   
            "\\begin{equation}\n");
}

void end_latex(FILE *tex)
{
    fprintf(tex, "\n\\end{equation}\n");
    fprintf (tex, "\\end{document}\n");
}

void tree_pdf(node* node_cur, FILE *file)
{
  if (node_cur == NULL) 
    return;

    if (node_cur -> type_node == NUM) 
      fprintf(file, "%lg", node_cur -> val);
    else
    {
        if (node_cur -> type_node == VAR)
            fprintf(file, "x");
    }

  if (node_cur -> type_node == FUNC)
  {
    switch ((int) node_cur->val)
    {
        case DIV:
            fprintf(file, "\\frac{");
            tree_pdf(node_cur -> left, file);
            fprintf(file, "}{");
            tree_pdf(node_cur -> right, file);
            fprintf(file, "}");
            return;
        case MUL:   
            fprintf(file, "(");
            tree_pdf(node_cur -> left, file);
            fprintf(file, ")");
            fprintf(file, " \\cdot ");
            fprintf(file, "(");
            tree_pdf(node_cur -> right, file);
            fprintf(file, ")");
            return;
        case SUB:   
            fprintf(file, "(");
            tree_pdf(node_cur -> left, file);
            fprintf(file, ")");
            fprintf(file, " - ");
            fprintf(file, "(");
            tree_pdf(node_cur -> right, file);
            fprintf(file, ")");
            return;
        case SUM:   
            fprintf(file, "(");
            tree_pdf(node_cur -> left, file);
            fprintf(file, ")");
            fprintf(file, " + ");
            fprintf(file, "(");
            tree_pdf(node_cur -> right, file);
            fprintf(file, ")");
            return;
        case POW:
            fprintf(file, "(");
            tree_pdf(node_cur -> left, file);
            fprintf(file, ")");
            fprintf(file, "^{");
            tree_pdf(node_cur -> right, file);
            fprintf(file, "}");
            return;
        case EXP:
            fprintf(file, "e^{");
            tree_pdf(node_cur -> left, file);
            fprintf(file, "}");
            return;
        case SIN:
            fprintf(file, " \\sin");
            fprintf(file, "(");
            tree_pdf(node_cur -> left, file);
            fprintf(file, ")");
            return;
        case COS:
            fprintf(file, " \\cos");
            fprintf(file, "(");
            tree_pdf(node_cur -> left, file);
            fprintf(file, ")");
            return;
        case LOG:
            fprintf(file, " \\ln");
            fprintf(file, "(");
            tree_pdf(node_cur -> left, file);
            fprintf(file, ")");
            return;
        case TAN:
            fprintf(file, " \\tan");
            fprintf(file, "(");
            tree_pdf(node_cur -> left, file);
            fprintf(file, ")");
            return;
        case COT:
            fprintf(file, " \\cos");
            fprintf(file, "(");
            tree_pdf(node_cur -> left, file);
            fprintf(file, ")");
            return;
        case SQRT:
            fprintf(file, " \\sqrt");
            fprintf(file, "(");
            tree_pdf(node_cur -> left, file);
            fprintf(file, ")");
            return;
        default:
            printf("Unknown func\n");
            exit(1);
    }
  }
}

void delete_const(node* node_cur)
{
    assert(node_cur != NULL);
    if (node_cur->left)
        delete_const(node_cur->left);
    if (node_cur->right)
        delete_const(node_cur->right);

    if (node_cur->type_node == FUNC && node_cur->left && node_cur->right && node_cur->left->type_node == NUM && node_cur->right->type_node == NUM)
    {
        double supp = 0;

        switch ((int) node_cur->val)
        {
            case SUM:
                supp = node_cur->left->val + node_cur->right->val;
                break;
            case SUB:
                supp = node_cur->left->val - node_cur->right->val;
                break;
            case MUL:
                supp = node_cur->left->val * node_cur->right->val;
                break;
            case DIV:
                supp = node_cur->left->val / node_cur->right->val;
                break;
            default:
                break;
        }
        free(node_cur->left);
        node_cur->left = NULL;
        free(node_cur->right);
        node_cur->right = NULL;

        node_cur->type_node = NUM;
        node_cur->val = supp;
    }
}


void delete_zero(node* node_cur)
{
    if (node_cur->left)
        delete_zero(node_cur->left);
    if (node_cur->right)
        delete_zero(node_cur->right);

    if (node_cur->type_node == FUNC && (node_cur->val == DIV || node_cur->val == MUL || node_cur->val == POW) && node_cur->left && node_cur->right && (node_cur->left->type_node == NUM || node_cur->right->type_node == NUM) && (node_cur->left->val == 0 || (node_cur->right->val == 0)))
    {
        double res = 0;

        switch ((int) node_cur->val)
        {
            case MUL:
                res = 0;
                break;
            case DIV:
                res = 0;
                break;
            case POW:
                res = 1;
                break;
            default:
                break;
        }
        free(node_cur->left);
        node_cur->left = NULL;
        free(node_cur->right);
        node_cur->right = NULL;

        node_cur->type_node = NUM;
        node_cur->val = res;
    }
}