#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "stack-s-typedef-canary-izvrashenie.c"

#define CMD(name, num) CMD_##name = num,
#define CMD_COMPLEX(name, num) CMD_COMPLEX_##name = num,
    

enum commands
{
#include "commands.h"            
};

#undef CMD
#undef CMD_COMPLEX


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
    int value = 0;
    printf("size == %d", size);
    while(index <= size)
    {   
        value = 0;
        command = 0;
        memcpy(&command, (code + index), sizeof(char)); 
        printf("eto == %c", command);
        switch (command)
            {
                case CMD_COMPLEX_PUSH: {
                                        index++;
                                        memcpy(&value, (code + index), sizeof(double));
                                        stackPush(&(s -> stack), value);
                                        index += sizeof(double);
                                        printf("COMMAND %d\n", command);
                                        printf("%lg", value);
                                        break;
                                        
                                       }
                case CMD_IN:            {   
                                            printf("COMMAND %d\n", command);
                                            index++;
                                            printf("Enter the number\n");
                                            double value = 0;
                                            scanf("%lg", &value);
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
                                    break; 
                                }
                
                case CMD_POP: {
                                index++;
                                stackPop(&(s -> stack));
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
                        
                                    stackPush(&(s -> stack), b / a);
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
