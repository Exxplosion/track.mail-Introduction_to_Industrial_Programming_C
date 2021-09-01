#include "calc.h"

node* getG(char* str)
{

  s = str;
  node* answer = getE();

  if (*s != '\0')
  {
    printf("check file!");
    exit(1);
  }

  return answer;
}

node* getN()
{
  double val = 0;

  printf("get N cur: %s\n", s);
  printf("%lg\n", val);

  if (*s == 'x' || *s == 'y')
  {
    s++;
    if (*(s - 1) == 'x')
      return get_node(VAR, VAR_X, NULL, NULL);
    else
      return get_node(VAR, VAR_Y, NULL, NULL);
  }

  while('0' <= *s && *s <= '9')
  {
    val = val * 10 + (*s) - '0';
    s++;
  }

  return get_node(NUM, val, NULL, NULL);
}

node* getE()
{
  printf("get E cur: %s\n", s);
  char op = 0;

  node* val_1 = getT();
  while (*s == '+' || *s == '-')
  {
    op = *s;
    s++;
    node* val_2 = getT();

    if (op == '+')
      val_1 = get_node(FUNC, SUM, val_1, val_2);
    else
      val_1 = get_node(FUNC, SUB, val_1, val_2);
  }

  return val_1;
}

node* getT()
{
  printf("get T cur: %s\n", s);
  char op = 0;
  node* val_1 = getC();

  while (*s == '*' || *s == '/')
  {
    op = *s;
    s++;

    node* val_2 = getC();

    if (op == '*')
      val_1 = get_node(FUNC, MUL, val_1, val_2);
    else
      val_1 = get_node(FUNC, DIV, val_1, val_2);
  }

  return val_1;
}


node* getC()//pow
{
  printf("get С cur: %s\n", s);
  char op = 0;
  node* val_1 = getP();
  while (*s == '^')
  {
    op = *s;
    s++;

    node* val_2 = getP();

    if (op == '^')
      val_1 = get_node(FUNC, POW, val_1, val_2);
  }
  return val_1;
}

node* getP()
{
  if (*s == '(')
  {
    s++;
    printf("\n%s mmm vizof E\n", s);

    node* val = getE();
    printf("getaaaaa P cur: %s\n", s);
    if (*s != ')')
    {
      printf("get P cur (error): %s\n", s);
      printf("getP check file!");
      exit(1);
    }

    s++;
    printf("VISHEL\n");
    return val;
  }
  else
  {
      printf("prifol\n");
    if (*s == 'x' || *s == 'y')
    {
      return getN();
    }
    else
    {
      if (*s <= '9' && '0' <= *s)
      {
        printf("%s\n", s);
              printf("prifol\n");

        return getN();
      }
    }
  }
  return getF();
}


node* getF()
{
    printf("get F cur: %s\n", s);
  node* val;
  SINN
  {
    DO_SIN
  }
  COSS
  {
    DO_COS
  }
  COTT
  {
    DO_COT
  }
  TANN
  {
    DO_TAN
  }
  LOGG
  {
    DO_LOG
  }
  EXPP
  {
    DO_EXP
  }
  SQRTT
  {
    DO_SQRT
  }

  printf("fail found func!");
  exit(1);
  return NULL;
}