#include <stdio.h>
#include <ctype.h>
#include "work_file_strings.h"
#include "tree.h"
#include "reading.h"
#include <stdlib.h>

void SaveTree(FILE* output, node_t* node, const int depth);
const char* PrintOp(const int elem);
void MakeAsmCode(FILE* input, node_t* node, int* in_jmp);
node_t* PrintEnd(FILE* input, node_t* node);


#define PRINTOP(what)                                                           \
if (node -> key == OP && node -> elem == what)                                  \
  fprintf(input, #what"\n");

#define PRINTJMP(what)                                                           \
if (node -> key == OP && node -> elem == what)                                  \
  {                                    \
  fprintf(input, #what " %d\n", *in_jmp);                                       \
}


int main()
{
  tree_t* tree = (tree_t*) calloc(1, sizeof(*tree));
  FILE* file = fopen("prog.txt", "r");
  FILE* output = fopen("tree.txt", "w");
  FILE* kek = fopen("polsk.txt", "w");
  char* buffer = read_file(file);
  int in_jmp = 0;
  fclose(file);
  printf("%s\n", buffer);
  PushFirst(tree, getG(buffer));
  treeShow(tree);
  SaveTree(output, tree -> root, 0);
  MakeAsmCode(kek, tree -> root, &in_jmp);
  fclose(output);
  fclose(kek);

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


void MakeAsmCode(FILE* input, node_t* node, int* in_jmp)
{
  node_t* end = 0;

  if (node -> left)
      MakeAsmCode(input, node -> left, in_jmp);
  if (node -> right)
      MakeAsmCode(input, node -> right, in_jmp);
  if (node -> key == FUNC && node -> elem >= 0)
    fprintf(input, ":%d\n", (*in_jmp)++);

  else if (node -> key == FUNC && node -> elem < 0)
  {
    fprintf(input, "\n\nBEGIN\n");
    node_t* start = node;
    end = PrintEnd(input, node -> parent);
    printf("%p\n", end);
    node = start;
  }
  else if (node == end)
    fprintf(input, "END\n");
  else PRINTOP(SIN)
  else PRINTOP(COS)
  else PRINTOP(SQRT)
  else PRINTOP(ADD)
  else PRINTOP(SUB)
  else PRINTOP(MUL)
  else PRINTOP(DIV)
  else PRINTJMP(JA)
  else PRINTJMP(JAE)
  else PRINTJMP(JBE)
  else PRINTJMP(JB)
  else PRINTJMP(JE)
  else PRINTJMP(JNE)
  else if (node -> key == OP && node -> elem == PRINT)
    fprintf(input, "OUT\n");

  else if (node -> key == OP && node -> elem == SCAN && node -> left -> key == VAR)
  {
      fprintf(input, "IN\n");
      switch ((int) node -> left -> elem)
      {
        case 0:
        {
          fprintf(input, "R_POP RAX\n");
          break;
        }
        case 1:
        {
          fprintf(input, "R_POP RBX\n");
          break;
        }
        case 2:
        {
          fprintf(input, "R_POP RCX\n");
          break;
        }
        case 3:
        {
          fprintf(input, "R_POP RDX\n");
          break;
        }
      }
  }
  else if(node -> key == OP && (node -> elem == MIENTRAS || node -> elem == DESP))
  {

  }
  else if (node -> key == OP && node -> elem == SI)
  {
    fprintf(input, ":%d\n", (*in_jmp)++);
    //(*in_jmp)++;
    //MakeAsmCode(input, node -> right, in_jmp);

  }
  else if (node -> key == OP && node -> elem == OTRO)
  {
    fprintf(input, ":%d\n", (*in_jmp - 1));
  }

  /*else if(node -> key == OP && node -> parent -> right -> key == OP && node -> parent -> right -> elem == OPER)
  {
    fprintf(input, "RETURN\n")
  }*/
  else if (node -> key == OP && (node -> elem == OPER) /*&& node -> left -> elem == FUNC && node -> left -> elem < 0*/)
  {
    if (node -> left)
      if (node -> left -> elem <0 && node -> left -> key == FUNC)
        fprintf(input, "END\n");
  }
  else if (node -> key == OP /*&& (node -> parent -> left == node)*/ && node -> parent -> elem == SI)
  {
    fprintf(input, "JMP %d\n", (*in_jmp) + 1);
  }
  else if (node -> key == NUM && node -> parent -> elem != SCAN)
    fprintf(input, "PUSH %lg\n", node -> elem);

  else if (node -> key == VAR)
  {
    if (node -> parent ->elem == SCAN)
    {

    }
    else if (node -> parent -> key == OP && node -> parent -> elem == ASG)
    {
      switch ((int) node -> elem)
      {
        case 0:
        {
          fprintf(input, "R_POP RAX\n");
          break;
        }
        case 1:
        {
          fprintf(input, "R_POP RBX\n");
          break;
        }
        case 2:
        {
          fprintf(input, "R_POP RCX\n");
          break;
        }
        case 3:
        {
          fprintf(input, "R_POP RDX\n");
          break;
        }
    }
  }
    else {switch ((int) node -> elem)
    {
      case 0:
      {
        fprintf(input, "R_PUSH RAX\n");
        break;
      }
      case 1:
      {
        fprintf(input, "R_PUSH RBX\n");
        break;
      }
      case 2:
      {
        fprintf(input, "R_PUSH RCX\n");
        break;
      }
      case 3:
      {
        fprintf(input, "R_PUSH RDX\n");
        break;
      }
    }
  }
}
}

node_t* PrintEnd(FILE* input, node_t* node)
{
  if (node -> right) PrintEnd (input, node -> right);
  if (node -> left) PrintEnd(input, node -> left);
  return node;
}
