#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"
#include "work_file_strings"

int main()
{

}

Node_t* MakeNode(tree_t* s, const int key, const elem_t value, node_t* left, node_t* right)
{
  node_t* node = (node_t*) calloc (1, sizeof(node));

  node -> key = key;
  node -> elem = value;

  node -> left = left;
  node -> right = right;
  return node;

}

node_t* getG(const char* str)
{

  s = str;
  skipSpaces();
  node_t* val = getE();
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
  if (*s == '.')
  {
    s++;
    while('0' <= *s && *s <= '9')
    {
      rate++;
      point = point * 10 + (*s) - '0';
      s++;
    }
  }

  val = (val + point)/(pow(10, rate));
  printf(" charN %c\n", *s);

  skipSpaces();
  return val;
}

node_t* getE()
{
  skipSpaces();
  printf("gete %c\n", *s);
  printf("%s\n", s);
  char op = 0;
  node_t* val = getT();
  skipSpaces();
  while (*s == '+' || *s == '-')
  {
    op = *s;
    s++;
    skipSpaces();
    node_t* val2 = getT();
    skipSpaces();
    if (op == '+')
      val =  MakeNode(tree,OP, ADD, value, val2)
    if (op == '-')
    val =  MakeNode(tree,OP, SUB, value, val2)
  }
  return val;
}

double getT()
{
  skipSpaces();
  printf("gett %c\n", *s);
  char op = 0;
  node_t* val = getP();
  skipSpaces();
  while (*s == '*' || *s == '/')
  {
    op = *s;
    s++;
    node_t* val2 = getP();
    skipSpaces();
    if (op == '*')
    val =  MakeNode(tree, OP, MUL, value, val2)
    if (op == '/')
    val =  MakeNode(tree, OP, DIV, value, val2)
  }
  return val;
}

double getP()

{
  node_t* val = 0, val2 = 0;
  skipSpaces();
   printf("getp %c\n", *s);
  if (*s == '(')
  {
    s++;
    skipSpaces();
    printf("kek %c\n", *s);
    printf("%s", s);

    val = getE();
    skipSpaces();
    assert(*s == ')');
    s++;
    if (*s == '^')
    {
    s++;
    val2 = getP();
    val =  MakeNode(tree, OP, POW, val, val2);
   }
   else if (*s == 's' && *( s + 1) == 'i' && *(s + 2) == 'n')
   {
     s = s + 3;
     if (*s == '^')
     {
       s++;
       val2 = getP();
     }
     val =  MakeNode(tree, OP, SIN, getP(), NULL);
     if (val2)
     val =  MakeNode(tree, OP, POW, val, val2);

   }
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
