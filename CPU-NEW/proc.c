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
    while(index <= size)
    {   
        value = 0;
        command = 0;
        memcpy(&command, (code + index), sizeof(char)); 
        switch (command)
            {
                case CMD_COMPLEX_PUSH: {
                                        index++;
                                        memcpy(&value, (code + index), sizeof(double));
                                        stackPush(&(s -> stack), value);
                                        index += sizeof(double);
                                        break;
                                       }
                case CMD_BEGIN: {                                                           \\END
                                    index++;
                                    break; 
                                }
                
                case CMD_POP: {
                                index++;
                                stackPop(&(s -> stack));
                                break;
                              }
                case CMD_
                
            }
            
            
    }
}

int main()
{
    CPU_t CPU = {0};

    //printf ("%d\n", (&(CPU.stack)) -> canary1);
    
    dump(CPU_Ctor(&CPU), (&(CPU.stack)));   //DED NE PRAV!
    FILE* machine_code = fopen("debug.txt", "rw");
    assert(machine_code);
    int file_size = size_of_file(machine_code);
    
    char* code = (char*)calloc(file_size + 1, sizeof(*code));
    //fread(code, sizeof(char), file_size, machine_code);
    //printf("%s", code);
    //switch(*(code + index))
  
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
