#include "calc.h"

double getG(char* str)
{

  s = str;
  double answer = getE();

  if (*s != '\0')
  {
    printf("check file!");
    exit(1);
  }

  return answer;
}

double getN()
{
  double val = 0;
  int flag = 0;

  printf("get N cur: %s\n", s);
  while('0' <= *s && *s <= '9')
  {
    flag = 1;
    val = val * 10 + (*s) - '0';
    s++;
  }

  if(flag == 0)
  {
    printf("getN error");
    printf("check file!");
    exit(1);
  }


  return val;
}

double getE()
{
  printf("get E cur: %s\n", s);
  char op = 0;

  double val_1 = getT();
  while (*s == '+' || *s == '-')
  {
    op = *s;
    s++;
    double val_2 = getT();

    if (op == '+')
      val_1 += val_2;
    else
      val_1 -= val_2;
  }

  return val_1;
}

double getT()
{
  printf("get T cur: %s\n", s);
  char op = 0;
  double val_1 = getC();

  while (*s == '*' || *s == '/')
  {
    op = *s;
    s++;

    double val_2 = getC();

    if (op == '*')
      val_1 *= val_2;
    else
      val_1 /= val_2;
  }

  return val_1;
}


double getC()//pow
{
  printf("get С cur: %s\n", s);
  char op = 0;
  double val_1 = getP();
  while (*s == '^')
  {
    op = *s;
    s++;

    double val_2 = getP();

    if (op == '^')
      val_1 = pow(val_1, val_2);
  }
  return val_1;
}

double getP()
{
  if (*s == '(')
  {
    s++;
    printf("\n%s mmm vizof E\n", s);

    double val = getE();
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
    if (*s <= '9' && '0' <= *s)
    {
      return getN();
    }
  }
  return getF();
}


double getF()
{
    printf("get F cur: %s\n", s);
  double val;
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
}