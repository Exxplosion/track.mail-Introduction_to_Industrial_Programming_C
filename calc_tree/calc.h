#ifndef CALC_H
#define CALC_H

//#include "tree_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

extern char *s;

#define SINN if (*s == 's' && *( s + 1) == 'i' && *(s + 2) == 'n')
#define DO_SIN                                                   \
      s = s + 3;                                                 \
      val = sin(getP());                                         \
    return val;                                                  \

#define COSS if (*s == 'c' && *( s + 1) == 'o' && *(s + 2) == 's')
#define DO_COS                                                   \
      s = s + 3;                                                 \
      val = cos(getP());                                         \
    return val;                                                  \

#define EXPP if (*s == 'e' && *( s + 1) == 'x' && *(s + 2) == 'p')
#define DO_EXP                                                   \
      s = s + 3;                                                 \
      val = exp(getP());                                         \
    return val;                                                  \

#define COTT if (*s == 'c' && *( s + 1) == 'o' && *(s + 2) == 't')
#define DO_COT                                                   \
      s = s + 3;                                                 \
      val = 1 / tan(getP());                                     \
    return val;                                                  \

#define TANN if (*s == 't' && *( s + 1) == 'a' && *(s + 2) == 'n')
#define DO_TAN                                                   \
      s = s + 3;                                                 \
      val = tan(getP());                                         \
    return val;                                                  \

#define LOGG if (*s == 'l' && *( s + 1) == 'o' && *(s + 2) == 'g')
#define DO_LOG                                                   \
      s = s + 3;                                                 \
      val = log(getP());                                         \
    return val;                                                  \

#define SQRTT if (*s == 's' && *( s + 1) == 'q' && *(s + 2) == 'r' && *(s + 3) == 't')
#define DO_SQRT                                                                    \
      s = s + 4;                                                                   \
      val = sqrt(getP());                                                               \
    return val;                                                                    \

/*
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
*/

double getG(char* str);
double getN();
double getE();
double getT();
double getC();
double getP();
double getF();


#endif