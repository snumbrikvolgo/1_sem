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
    while(code[index] != CMD_END)
    {   
        value = 0;
        command = 0;
        memcpy(&command, (code + index), sizeof(char));
        printf("cur code %c\n", code[index]);
        printf("cur index %d\n", index);
        switch (command)
            {
                
                case CMD_COMPLEX_PUSH: {
                                        index++;
                                        memcpy(&value, (code + index), sizeof(double));
                                        printf("value == %lg", value);
                                        stackPush(&(s -> stack), value);
                                        index += sizeof(double);
                                        
                                        break;
                                        
                                       }
                case CMD_IN:            {   
                                            index++;
                                            printf("Enter the number\n");
                                            double value = 0;
                                            scanf("%lg", &value);
                                            stackPush(&(s -> stack), value);
                                            break;
                                        }
                case CMD_BEGIN: {                                                           
                                    index++;
                                    break; 
                                }
                 case CMD_END: {                                                   
                                  
                                    abort();
                                    break; 
                                }
                
                case CMD_POP: {
                                index++;
                                printf("popped = %lg", stackPop(&(s -> stack)));
                                break;
                              }
                case CMD_ADD:
                              {
                                    index++;
                                    stackPush(&(s -> stack), stackPop(&(s -> stack)) + stackPop(&(s -> stack)));
                                    break;
                               }
                case CMD_MUL:
                              {
                                    index++;
                                    stackPush(&(s -> stack), stackPop(&(s -> stack)) * stackPop(&(s -> stack)));
                                    break;
                               }
                case CMD_DIV:
                              {
                                    index++;
                                    double  a = stackPop(&(s -> stack));
                                    double  b = stackPop(&(s -> stack));
                        
                                    stackPush(&(s -> stack), b / a
);
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
                                   break;
                                }
                case CMD_REG_R_PUSH:
                                {
                                   
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
                                          
                                            break;
                                         }
                                    }
                                    break;
                                }

                case CMD_REG_R_POP:
                                {
                                   index++;
                                   
                                   switch(code[index])
                                   {
                                   case '1':
                                        {
                                            printf("stack top = %lg\n", stackTop(&(s -> stack)));
                                            s -> regs.rax = stackPop(&(s -> stack));
                                            printf("teper v rax = %lg", s -> regs.rax);
                                            index++;
                                            break;
                                         }
                                    case '2':
                                        {
                                            printf("stack top = %lg\n", stackTop(&(s -> stack)));
                                            s -> regs.rbx = stackPop(&(s -> stack));
                                            printf("teper v rbx = %lg", s -> regs.rbx);
                                            index++;
                                            break;
                                         }
                                    case '3':
                                        {
                                             printf("stack top = %lg\n", stackTop(&(s -> stack)));
                                            s -> regs.rcx = stackPop(&(s -> stack));
                                            printf("teper v rcx = %lg", s -> regs.rcx);
                                            index++;
                                            break;
                                         }
                                   case '4':
                                        {
                                            printf("stack top = %lg\n", stackTop(&(s -> stack)));
                                            s -> regs.rdx = stackPop(&(s -> stack));
                                            printf("teper v rdx = %lg", s -> regs.rdx);
                                            index++;
                                            break;
                                         }
                                    default: {
                                                printf("Sosi hui\n");
                                                break;
                                            }
                                    }
                                    
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
                                    double a = stackPop(&(s -> stack));
                                    
                                    double b = stackPop(&(s -> stack));
                                    printf(" a = %lf b = %lg\n", a, b);
                                    if (a > b)
                                    {
                                        index = code[index];
                                        index++;
                                    }
                                    printf("%s\n", code + index);
                                    
                                    break;
                               }
                      case CMD_JMP_JB: 
                                {
                                    index++;
                                    double a = stackPop(&(s -> stack));
                                    double b = stackPop(&(s -> stack));
                                    printf(" a = %lf b = %lg\n", a, b);
                                    printf("%s\n", code + index);
                                    if (a < b)
                                    {
                                        index = code[index];
                                        index++;
                                    }
                                    else index++;
                                     
                                    
                                    break;
                               }
                       case CMD_JMP_JE: 
                                {
                                    index++;
                                    double a = stackPop(&(s -> stack));
                                    double b = stackPop(&(s -> stack));
                                    if (a == b)
                                    {
                                        index = code[index];
                                        index++;
                                    }
                                    else index = index + 2;
                                    
                                    break;
                               }
                    case CMD_JMP_JAE: 
                                {
                                    index++;
                                    double a = stackPop(&(s -> stack));
                                    double b = stackPop(&(s -> stack));
                                    if (a >= b)
                                    {
                                        index = code[index];
                                        index++;
                                    }
                                    else index++;
                                    
                                    break;
                               }
                case CMD_JMP_JBE: 
                                {
                                    index++;
                                    double a = stackPop(&(s -> stack));
                                    double b = stackPop(&(s -> stack));
                                    if (a <= b)
                                    {
                                        index = code[index];
                                        index++;
                                    }
                                    else index++;
                                    
                                    break;
                               }
                  case CMD_JMP_JNE: 
                                {
                                    index++;
                                    double a = stackPop(&(s -> stack));
                                    double b = stackPop(&(s -> stack));
                                    if (a != b)
                                    {
                                        index = code[index];
                                        index++;
                                    }
                                    else index++;
                                    
                                    break;
                               }
                   case CMD_CUR:{
                                     index++;
                                       double a = stackPop(&(s -> stack));
                                printf("current number ======================== %lg\n", a);
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
