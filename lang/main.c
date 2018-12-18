#include <stdio.h>
#include <ctype.h>
#include "work_file_strings.h"
#include "tree.h"
#include "reading.h"
#include <stdlib.h>

void SaveTree(FILE* output, node_t* node, const int depth);
const char* PrintOp(const int elem);

#define PRINTOP(what)                                                           \
if (node -> key == OP && node -> elem == what)                                  \
{                                                                               \
  fprintf(input, #what"\n");                                                    \
}

int main()
{
  tree_t* tree = (tree_t*) calloc(1, sizeof(*tree));
  FILE* file = fopen("prog.txt", "r");
  FILE* output = fopen("tree.txt", "w");
  char* buffer = read_file(file);
  fclose(file);
  printf("%s\n", buffer);
  PushFirst(tree, getG(buffer));
  treeShow(tree);
  SaveTree(output, tree -> root, 0);

  fclose(output);

}

void SaveTree(FILE* output, node_t* node, const int depth)
{
  for (int i = 0; i <  depth; i++)
  {
    fprintf(output, "\t");
  }

  switch(node -> key)
  {
    case NUM:
    {
      fprintf(output, "(N'%lg'\n", node -> elem);
      break;
    }
    case VAR:
    {
      fprintf(output, "(V'%g'\n", node -> elem);
      break;
    }
    case FUNC:
    {
      fprintf(output, "(F'%g'\n", node -> elem);
      break;
    }
    case OP:
    {
      fprintf(output, "(OP'%s'\n", PrintOp(node -> elem));
      break;
    }
  }
  if (node -> left) SaveTree(output, node -> left, depth + 1);
  if (node -> right) SaveTree(output, node -> right, depth + 1);

  for (int i = 0; i < depth; i++)
  {
    fprintf(output, "\t");
  }
  fprintf(output, ")\n");

}

const char* PrintOp(const int elem)
{
  switch (elem)
  {
    CHOSEOP(ADD, +)
    CHOSEOP(SUB, -)
    CHOSEOP(MUL, *)
    CHOSEOP(DIV, /)
    CHOSEOP(SIN, sin)
    CHOSEOP(COS, cos)
    CHOSEOP(SQRT, sqrt)
    CHOSEOP(OPER, operator)
    CHOSEOP(JA, >)
    CHOSEOP(JB, <)
    CHOSEOP(JE, ==)
    CHOSEOP(JNE, <>)
    CHOSEOP(JAE, >=)
    CHOSEOP(JBE, <=)
    CHOSEOP(ASG, =)
    CHOSEOP(SI, si)
    CHOSEOP(OTRO, otro)
    CHOSEOP(MIENTRAS, mientras)
    CHOSEOP(SCAN, lee)
    CHOSEOP(PRINT, escribe)
    CHOSEOP(LLAME, llame)
    CHOSEOP(PARAM, param)
    CHOSEOP(DESP, despacito)

    default:
    {
      return 0;
      break;
    }
  }
}


void MakeAsmCode(FILE* input, node_t* node)
{
  if (node -> left)
      MakeAsmCode(input, node -> left);
  if (node -> right)
      MakeAsmCode(input, node -> right);
  if (node -> key == FUNC && node -> elem >= 0)
  {
    fprintf(input, "CALL :%d\n", (int)node -> elem);
  }
  else if (node -> key == FUNC && node -> elem < 0)
  {
    fprintf(input, "BEGIN\n");
  }
  else PRINTOP(SIN)
  else PRINTOP(COS)
  else PRINTOP(SQRT)
  else PRINTOP(ADD)
  else PRINTOP(SUB)
  else PRINTOP(MUL)
  else PRINTOP(DIV)
  else PRINTOP(JA)
  else PRINTOP(JAE)
  else PRINTOP(JBE)
  else PRINTOP(JB)
  else PRINTOP(JE)
  else PRINTOP(JNE)
  else if (node -> key == OP && node -> elem == PRINT)
  {
    fprintf(input, "OUT\n");
  }
  else if (node -> key == OP && node -> elem == SCAN)
  {
    fprintf(input, "IN\n");
  }
  else if(node -> key == OP && (node -> elem == SI || node -> elem == MIENTRAS || node -> elem == DESP))
  {

  }
  else if (node -> key == OP && (node -> elem == OPER || node -> elem == ASG))
  {

  }
  else if (node -> key == NUM)
  {
    fprintf(input, "PUSH %lg", node -> elem);
  }
  else if (node -> key == VAR)
  {
    switch ((int) node -> elem)
    {
      case 0:
      {
        fprintf(input, "R_POP RAX");
        break;
      }
      case 1:
      {
        fprintf(input, "R_POP RBX");
        break;
      }
      case 2:
      {
        fprintf(input, "R_POP RCX");
        break;
      }
      case 3:
      {
        fprintf(input, "R_POP RDX");
        break;
      }
    }
  }


}
