#include <stdio.h>
#include <stdlib.h>
#include "work_file_strings.h"
#include <math.h>

#define MAX_ID 10

double getG(const char* str);
double getN();
double getE();
double getT();
double getP();
char* getID();
void skipSpaces();

const char* s = NULL;


int recursion()
{
    FILE* file = fopen ("eq", "r");
    char* string = read_file(file);
    printf("%lg", getG(string));

    return 0;
}

double getG(const char* str)
{

  s = str;
  skipSpaces();
  double val = getE();
  skipSpaces();
  assert(*s == '\0');
  assert(s != str);

  s++;
  return val;
}

double getN()
{
  double val = 0;
  double point = 0;
  int rate = 0;
  printf("govno\n");
  skipSpaces();
  while('0' <= *s && *s <= '9')
  {
    val = val * 10 + (*s) - '0';
    s++;
  }
  /*if (*s == '.')
  {
    s++;
    while('0' <= *s && *s <= '9')
    {
      rate++;
      point = point * 10 + (*s) - '0';
      s++;
    }
  }*/

  //val = (val + point)/(pow(10, rate));
  printf(" charN %c\n", *s);

  skipSpaces();
  return val;
}

double getE()
{
  skipSpaces();
  printf("gete %c\n", *s);
  printf("%s\n", s);
  char op = 0;
  double val = getT();
  skipSpaces();
  while (*s == '+' || *s == '-')
  {
    op = *s;
    s++;
    skipSpaces();
    double val2 = getT();
    skipSpaces();
    if (op == '+')
      val += val2;
    if (op == '-')
      val -= val2;
  }
  return val;
}

double getT()
{
  skipSpaces();
  printf("gett %c\n", *s);
  char op = 0;
  double val = getP();
  skipSpaces();
  while (*s == '*' || *s == '/')
  {
    op = *s;
    s++;
    double val2 = getP();
    skipSpaces();
    if (op == '*')
      val *= val2;
    if (op == '/')
      val /= val2;
  }
  return val;
}

double getP()

{
  skipSpaces();
   printf("getp %c\n", *s);
  if (*s == '(')
  {
    s++;
    skipSpaces();
    printf("kek %c\n", *s);
    printf("%s", s);

    double val = getE();
    skipSpaces();
    assert(*s == ')');
    s++;
    printf("heh %d\n", *s);
    skipSpaces();
    return val;
  }

  else
  {
    skipSpaces();
  }return getN();
}

char* getID()
{
  skipSpaces();
  char* id = (char*) calloc (MAX_ID, sizeof(*id));
  char* cur = id;
  if ((*s >= 'A' && *s <= 'Z') ||
  (*s >= 'a' && *s <= 'z') ||
  (*s == '_') ||
  (*s == '$'))
  {
    *cur = *s;
    cur++;
    s++;
  }
  while ((*s >= 'A' && *s <= 'Z') ||
  (*s >= 'a' && *s <= 'z') ||
  (*s == '_') ||
  (*s == '$'))
  {
    if (cur - id < MAX_ID)
    {
      *id = *cur;
      cur++;
      s++;
    }
  }
  *id = '\0';
  skipSpaces();
  return cur;

}

void skipSpaces()
{
  while(*s == ' ' || *s == '\n')
    s++;
  return;
}
