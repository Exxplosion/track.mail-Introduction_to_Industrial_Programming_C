#ifndef CALC_H
#define CALC_H

#include "tree_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define SINN if (*s == 's' && *( s + 1) == 'i' && *(s + 2) == 'n')
#define DO_SIN                                                   \
      s = s + 3;                                                 \
      val = get_node(FUNC, SIN, getP(), NULL);                   \
    return val;                                                  \

#define COSS if (*s == 'c' && *( s + 1) == 'o' && *(s + 2) == 's')
#define DO_COS                                                   \
      s = s + 3;                                                 \
      val = get_node(FUNC, COS, getP(), NULL);                   \
    return val;                         \

#define EXPP if (*s == 'e' && *( s + 1) == 'x' && *(s + 2) == 'p')
#define DO_EXP                                                   \
      s = s + 3;                                                 \
      val = get_node(FUNC, EXP, getP(), NULL);                   \
    return val;                                                  \

#define COTT if (*s == 'c' && *( s + 1) == 'o' && *(s + 2) == 't')
#define DO_COT                                                   \
      s = s + 3;                                                 \
      val = get_node(FUNC, COT, getP(), NULL);                   \
    return val;                                                  \

#define TANN if (*s == 't' && *( s + 1) == 'a' && *(s + 2) == 'n')
#define DO_TAN                                                   \
      s = s + 3;                                                 \
      val = get_node(FUNC, TAN, getP(), NULL);                   \
    return val;                                                  \

#define LOGG if (*s == 'l' && *( s + 1) == 'o' && *(s + 2) == 'g')
#define DO_LOG                                                   \
      s = s + 3;                                                 \
      val = get_node(FUNC, LOG, getP(), NULL);                   \
    return val;                                                  \

#define SQRTT if (*s == 's' && *( s + 1) == 'q' && *(s + 2) == 'r' && *(s + 3) == 't')
#define DO_SQRT                                                                    \
      s = s + 4;                                                                   \
      val = get_node(FUNC, SQRT, getP(), NULL);                                    \
    return val;                                                                    \


extern enum types
{
    NUM,
    FUNC,
    VAR
} TYPES_NODES;

extern char * s;

extern enum funcs
{
    SUM = 5,
    SUB,
    MUL,
    DIV,
    SIN,
    COS,
    LOG,
    TAN,
    COT,
    SQRT,
    EXP,
    POW,
    VAR_X,
    VAR_Y
} FUNCTIONS;

struct node_t * getG(char* str);
struct node_t * getN();
struct node_t * getE();
struct node_t * getT();
struct node_t * getC();
struct node_t * getP();
struct node_t * getF();


#endif