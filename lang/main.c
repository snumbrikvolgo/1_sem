#include <stdio.h>
#include <ctype.h>
#include "work_file_strings.h"
#include "tree.h"
#include "reading.h"
#include <stdlib.h>

void SaveTree(FILE* output, node_t* node, const int depth);
const char* PrintOp(const int elem);
void MakeAsmCode(FILE* input, node_t* node, int* in_jmp, int* in_call);
node_t* PrintEnd(FILE* input, node_t* node);


#define PRINTOP(what)                                                           \
if (node -> key == OP && node -> elem == what)                                  \
  fprintf(input, #what"\n");

#define PRINTJMP(what)                                                           \
if (node -> key == OP && node -> elem == what)                                  \
  {                                    \
  fprintf(input, #what " if%d\n", (*in_jmp));                                       \
}


int main()
{
  tree_t* tree = (tree_t*) calloc(1, sizeof(*tree));
  FILE* file = fopen("prog.txt", "r");
  FILE* output = fopen("tree.txt", "w");
  FILE* kek = fopen("polsk..txt", "w");
  char* buffer = read_file(file);
  int in_jmp = 0;
  int in_call = 0;
  fclose(file);
  printf("%s\n", buffer);
  PushFirst(tree, getG(buffer));
  treeShow(tree);
  SaveTree(output, tree -> root, 0);
  fprintf(kek, "JMP start\n\n\n");
  MakeAsmCode(kek, tree -> root, &in_jmp, &in_call);
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


void MakeAsmCode(FILE* input, node_t* node, int* in_jmp,int* in_call)
{
  node_t* end = 0;

  if (node -> left)
      MakeAsmCode(input, node -> left, in_jmp, in_call);
  if (node -> right)
      MakeAsmCode(input, node -> right, in_jmp, in_call);
  if (node -> key == FUNC && node -> elem >= 0 && node -> parent -> elem != LLAME)
    fprintf(input, ":%d\n", (int)node -> elem);

  else if (node -> key == FUNC && node -> elem < 0)
  {
    fprintf(input, "\n\nBEGIN\n:start\n");
    node_t* start = node;
    end = PrintEnd(input, node -> parent);
    printf("%p\n", end);
    node = start;
  }
  else if (node -> key == OP && node -> parent && node -> parent -> left == node && node -> parent -> elem == SI)
     {
       PRINTOP(SIN)
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
       printf("HUI %d\n", (int) node -> elem);

     }
  /*else if (node == end)
    fprintf(input, "END\n");*/
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
  else if (node -> key == OP && node -> elem == LLAME)
  {
    fprintf(input, "CALL %d\n", (int)node -> right -> elem);
  }

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
    fprintf(input, "JMP :jmp%d\n", (*in_call)++);
    fprintf(input, ":if%d\n", (*in_jmp)++);

  }

  else if (node -> key == OP && node -> elem == OTRO)
  {
    fprintf(input, ":jmp%d\n", (*in_call - 1));
  }

  /*else if(node -> key == OP && node -> parent -> right -> key == OP && node -> parent -> right -> elem == OPER)
  {
    fprintf(input, "RETURN\n")
  }*/

  else if (node -> key == OP && (node -> elem == OPER) /*&& node -> left -> elem == FUNC && node -> left -> elem < 0*/)
  {

    if (node -> left)
    {

      if (node -> left -> elem <0 && node -> left -> key == FUNC)
        fprintf(input, "END\n");
      if (node -> left -> elem >= 0 && node -> left -> key == FUNC)
        fprintf(input, "RET\n\n");
    }
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
/*void Make_asm(FILE* input, node_t* node , const int stat)
{
  int jumps = COUNTER;

  if (node -> key == OP && (int) node -> elem == LLAME)
  {
    fprintf(input, ":fun%d\n", int (node -> left -> elem));
  }
  if (node -> left)
  {
    switch (int (node -> elem))
    {
      case OTRO:
        {
          Make_asm(input, node -> left, OTRO);
          break;
        }
      case  SI:
      {
        jumps = COUNTER;
        Make_asm(input, node -> left, SI);
        break;
      }
      case SCAN:
      {
        Make_asm(input, node -> left, SCAN);
        break;
      }
      case OPER:
      {
        if (node -> left -> key == FUNC)
          Make_asm(input, node -> left, OPER);
        else
          Make_asm(input, node -> left, -1);
          break;
      }
      case PARAM:
        Make_asm(input, node -> left, PARAM);
        break;
      default:
          Make_asm(input, node -> left, -1);
          break;

    }
  }
  if (node -> right)
  {
    switch (int (node -> elem))
    {
      case OTRO:
        {
          Make_asm(input, node -> right, OTRO);
          break;
        }
      case  SI:
      {
        jumps = COUNTER++;
        Make_asm(input, node -> right, SI);
        break;
      }
      case ASG:
      {
        Make_asm(input, node -> right, ASG);
        break;
      }
      case PARAM:
        Make_asm(input, node -> right, PARAM);
        break;
      default:
        Make_asm(input, node -> right, -1);
        break;

    }
    if (node -> left -> key == FUNC && (int) node -> right -> elem >= 0)
    {

    }
  }

}*/
