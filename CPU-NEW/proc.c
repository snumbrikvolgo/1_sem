#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "stack-s-typedef-canary-izvrashenie.c"

#define CMD(name, num) CMD_##name = num,
#define CMD_COMPLEX(name, num) CMD_COMPLEX_##name = num,
#define CMD_REG(name, reg_name, num) CMD_REG_##name = num,
#define CMD_JMP(name, num) CMD_JMP_##name = num,
    

enum asm_commands
{
#include "commands.h"            
};
#undef CMD_REG
#undef CMD
#undef CMD_COMPLEX
#undef CMD_JMP


typedef struct registers
{
    double rax;
    double rbx;
    double rcx;
    double rdx;
} registers_t;

typedef struct CPU
{
    stack_t stack;
    registers_t regs;    
}   CPU_t;

int CPU_Ctor(CPU_t* s);
int Compiler(char* code, const int size, CPU_t* s)
{
    int index = 0;
    int command = 0;
    double value = 0;
    printf("size == %d\n", size);
    while(index <= size)
    {   
        value = 0;
        command = 0;
        memcpy(&command, (code + index), sizeof(char)); 
        printf("eto == %c\n", command);
        printf("current text\n %s", code + index);
        switch (command)
            {
                
                case CMD_COMPLEX_PUSH: {
                                        index++;
                                        memcpy(&value, (code + index), sizeof(double));
                                        printf("value == %lg", value);
                                        stackPush(&(s -> stack), value);
                                        index += sizeof(double);
                                        printf("COMMAND %d\n", command);
                                        
                                        break;
                                        
                                       }
                case CMD_IN:            {   
                                            printf("COMMAND %d\n", command);
                                            index++;
                                            printf("Enter the number\n");
                                            double value = 0;
                                            scanf("%lg", &value);
                                            printf("inned %lg\n", value); 
                                            stackPush(&(s -> stack), value);
                                            break;
                                        }
                case CMD_BEGIN: {                                                           
                                    index++;
                                    printf("COMMAND %d\n", command);
                                    break; 
                                }
                 case CMD_END: {                                                           
                                    index++;
                                    printf("COMMAND %d\n", command);
                                    return 1;
                                    break; 
                                }
                
                case CMD_POP: {
                                index++;
                                printf("popped = %lg", stackPop(&(s -> stack)));
                                printf("COMMAND %d\n", command);
                                break;
                              }
                case CMD_ADD:
                              {
                                    index++;
                                    stackPush(&(s -> stack), stackPop(&(s -> stack)) + stackPop(&(s -> stack)));
                                    printf("COMMAND %d\n", command);
                                    break;
                               }
                case CMD_MUL:
                              {
                                    index++;
                                    stackPush(&(s -> stack), stackPop(&(s -> stack)) * stackPop(&(s -> stack)));
                                    printf("COMMAND %d\n", command);
                                    break;
                               }
                case CMD_DIV:
                              {
                                    index++;
                                    double  a = stackPop(&(s -> stack));
                                    double  b = stackPop(&(s -> stack));
                        
                                    stackPush(&(s -> stack), a / b);
                                    printf("COMMAND %d\n", command);
                                    break;
                               }
                case CMD_SUB:
                              {
                                    index++;
                                    double  a = stackPop(&(s -> stack));
                                    double  b = stackPop(&(s -> stack));
                        
                                    stackPush(&(s -> stack), b - a);
                                    break;
                               }
               case CMD_SQRT:
                              {
                                    index++;
                                    double  a = stackPop(&(s -> stack));
                                    a = sqrt(a);
                                    stackPush(&(s -> stack), a);
                                    break;
                               }
                case CMD_SIN:
                              {
                                    index++;
                                    double  a = stackPop(&(s -> stack));
                                    a = sin(a);
                                    stackPush(&(s -> stack), a);
                                    break;
                               }
                 case CMD_COS:
                              {
                                    index++;
                                    double  a = stackPop(&(s -> stack));
                                    a = cos(a);
                                    stackPush(&(s -> stack), a);
                                    break;
                               }
                 case CMD_TAN:
                              {
                                    index++;
                                    double  a = stackPop(&(s -> stack));
                                    a = tan(a);
                                    stackPush(&(s -> stack), a);
                                    break;
                               }
                case CMD_OUT:
                                {
                                   index++;
                                   printf(" out == %lg \n", stackPop(&(s -> stack)));
                                   printf("COMMAND %d\n", command);
                                }
                case CMD_REG_R_PUSH:
                                {
                                   printf("%s\n", code);
                                   index++;
                                   switch(code[index])
                                    {
                                   case '1':
                                        {
                                            //stackPush(&(s -> stack), (s -> regs.rax));
                                            printf("%rax = %lg\n", s->regs.rax);
                                            printf("zapushili %lg\n", stackPush(&(s -> stack), (s -> regs.rax)));
                                            /*printf("topchik 1 %lg\n", stackTop(&( s -> stack)));  
                                            stackPop(&(s -> stack));
                                            printf("topchik 2 %lg\n", stackTop(&( s -> stack)));*/
                                            index++;
                                            printf("%s\n", code + index);
                                            printf("%d\n", index);
                                            break;
                                         }
                                    case '2':
                                        {
                                            //stackPush(&(s -> stack), (s -> regs.rax));
                                            printf("%rbx = %lg\n", s->regs.rbx);
                                            printf("zapushili %lg\n", stackPush(&(s -> stack), (s -> regs.rbx)));
                                            /*printf("topchik 1 %lg\n", stackTop(&( s -> stack)));  
                                            stackPop(&(s -> stack));
                                            printf("topchik 2 %lg\n", stackTop(&( s -> stack)));*/
                                            index++;
                                            printf("%s\n", code + index);
                                            printf("%d\n", index);
                                            break;
                                         }
                                    case '3':
                                        {
                                            //stackPush(&(s -> stack), (s -> regs.rax));
                                            printf("%rcx = %lg\n", s->regs.rcx);
                                            printf("zapushili %lg\n", stackPush(&(s -> stack), (s -> regs.rcx)));
                                            /*printf("topchik 1 %lg\n", stackTop(&( s -> stack)));  
                                            stackPop(&(s -> stack));
                                            printf("topchik 2 %lg\n", stackTop(&( s -> stack)));*/
                                            index++;
                                            printf("%s\n", code + index);
                                            printf("%d\n", index);
                                            break;
                                         }
                                   case '4':
                                        {
                                            //stackPush(&(s -> stack), (s -> regs.rax));
                                            printf("%rdx = %lg\n", s->regs.rdx);
                                            printf("zapushili %lg\n", stackPush(&(s -> stack), (s -> regs.rdx)));
                                            /*printf("topchik 1 %lg\n", stackTop(&( s -> stack)));  
                                            stackPop(&(s -> stack));
                                            printf("topchik 2 %lg\n", stackTop(&( s -> stack)));*/
                                            index++;
                                            printf("%s\n", code + index);
                                            printf("%d\n", index);
                                            break;
                                         }
                                    }
                                    break;
                                }
                case CMD_REG_R_POP:
                                {
                                   index++;
                                   printf("sosi %s\n", code + index); 
                                   switch(code[index])
                                   {
                                   case '1':
                                        {
                                            s -> regs.rax = stackPop(&(s -> stack));
                                            printf("zashli v rpop%d\n", code[index]);
                                            
                                            index++;
                                            printf("%s\n", code + index);
                                            printf("%d\n", index);
                                            break;
                                         }
                                    case '2':
                                        {
                                            s -> regs.rbx = stackPop(&(s -> stack));
                                            index++;
                                            break;
                                         }
                                    case '3':
                                        {
                                            s -> regs.rcx = stackPop(&(s -> stack));
                                            index++;
                                            break;
                                         }
                                   case '4':
                                        {
                                            s -> regs.rdx = stackPop(&(s -> stack));
                                            index++;
                                            break;
                                         }
                                    default: {
                                                printf("Sosi hui\n");
                                                break;
                                            }
                                    }
                                printf("sosih %s\n", code + index); 
                                break;
                                }
                      case CMD_JMP_JMP: 
                                {
                                    index++;
                                    index = code[index];
                                    index++;
                                    break;
                               }
                       case CMD_JMP_JA: 
                                {
                                    index++;
                                    int a = stackPop(&(s -> stack));
                                    int b = stackPop(&(s -> stack));
                                    if (a > b)
                                    {
                                        index = code[index];
                                        index++;
                                    }
                                    
                                    break;
                               }
                      case CMD_JMP_JB: 
                                {
                                    index++;
                                    int a = stackPop(&(s -> stack));
                                    int b = stackPop(&(s -> stack));
                                    if (a < b)
                                    {
                                        index = code[index];
                                        index++;
                                    }
                                    
                                    break;
                               }
                       case CMD_JMP_JE: 
                                {
                                    index++;
                                    int a = stackPop(&(s -> stack));
                                    int b = stackPop(&(s -> stack));
                                    if (a == b)
                                    {
                                        index = code[index];
                                        index++;
                                    }
                                    
                                    break;
                               }
                    case CMD_JMP_JAE: 
                                {
                                    index++;
                                    int a = stackPop(&(s -> stack));
                                    int b = stackPop(&(s -> stack));
                                    if (a >= b)
                                    {
                                        index = code[index];
                                        index++;
                                    }
                                    
                                    break;
                               }
                case CMD_JMP_JBE: 
                                {
                                    index++;
                                    int a = stackPop(&(s -> stack));
                                    int b = stackPop(&(s -> stack));
                                    if (a <= b)
                                    {
                                        index = code[index];
                                        index++;
                                    }
                                    
                                    break;
                               }
                  case CMD_JMP_JNE: 
                                {
                                    index++;
                                    int a = stackPop(&(s -> stack));
                                    int b = stackPop(&(s -> stack));
                                    if (a != b)
                                    {
                                        index = code[index];
                                        index++;
                                    }
                                    
                                    break;
                               }
                   case CMD_CUR:{
                                     index++;
                                       int a = stackPop(&(s -> stack));
                                printf("current number %d\n", a);
                                stackPush(&(s -> stack), a);
                                break;
                                }
                                    
                     default: {
                            printf("keze\n");
                            abort();
                            break;
                                }
                
            }
            
            
    }
}

int main(int argc, char* argv[])
{
    CPU_t CPU = {0};

    //printf ("%d\n", (&(CPU.stack)) -> canary1);
    
    dump(CPU_Ctor(&CPU), (&(CPU.stack)));   //DED NE PRAV!
    read_code();
    FILE* machine_code = fopen("debug.txt", "r + b");
    assert(machine_code);
   
    int file_size = size_of_file(machine_code);
    printf("size == %d", file_size);
    
    char* code = (char*)calloc(file_size + 1, sizeof(*code));
    fread(code, sizeof(char), file_size, machine_code);
    printf("KEK %s", code);
    Compiler(code, file_size, &CPU);
    
  
}

int CPU_Ctor(CPU_t* s)
{
    /*dump((s -> stack) != NULL, (s -> stack));*/
    dump(stackCtor(&(s -> stack)), (&(s -> stack)));
    s -> regs.rax = 0;
    s -> regs.rbx = 0;
    s -> regs.rcx = 0;
    s -> regs.rdx = 0;
    return 1;
}
