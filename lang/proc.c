#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "stack.c"
#include "work_file_strings.h"
#define RAM_SIZE 1024
#include <errno.h>



enum asm_commands
{
#define CMD(name, num, act) CMD_##name = num,
#define CMD_COMPLEX(name, num, act) CMD_COMPLEX_##name = num,
#define CMD_REG(name, reg_name, num, act) CMD_REG_##name = num,
#define CMD_JMP(name, num, act) CMD_JMP_##name = num,
#define CMD_RAM(name, place, num, act) CMD_JMP_##name = num,

#include "commands.h"

#undef CMD_REG
#undef CMD
#undef CMD_COMPLEX
#undef CMD_JMP
#undef CMD_RAM
};



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
    stack_t returns;
    double RAM[RAM_SIZE];

}   CPU_t;

int CPU_Ctor(CPU_t* s);

int Compiler(char* code, const int size, CPU_t* s)
{
    int index = 0;
    int command = 0;
    double value = 0;

    while(code[index] != CMD_END)
    {
        value = 0;
        command = 0;
        memcpy(&command, (code + index), sizeof(char));


        switch (command)
            {
              #define CMD(name, num, act)                      \
              case num: act;
              #define CMD_REG(name, reg_name, num, act)        \
              case num: act;
              #define CMD_COMPLEX(name, num, act)              \
              case num: act;
              #define CMD_JMP(name, num, act)                  \
              case num: act;
              #define CMD_RAM(name, place, num, act)           \
              case num: act;
                                  #include "commands.h"
              #undef CMD_REG
              #undef CMD
              #undef CMD_COMPLEX
              #undef CMD_JMP
              #undef CMD_RAM
                     default: {
                            perror("Unknown command\n");
                            printf("%c%c%C\n", code[index], code[index + 1], code[index + 2]);
                            exit(0);
                            break;
                              }

            }


    }
}

int main(int argc, char* argv[])
{
    CPU_t CPU = {0};
    CPU_Ctor(&CPU);

    FILE* machine_code = fopen("debug.txt", "r + b");
    assert(machine_code);

    int file_size = size_of_file(machine_code);

    char* code = (char*)calloc(file_size + 1, sizeof(*code));
    fread(code, sizeof(char), file_size, machine_code);

    Compiler(code, file_size, &CPU);

}

int CPU_Ctor(CPU_t* s)
{
    dump(stackCtor(&(s -> stack)), (&(s -> stack)));
    dump(stackCtor(&(s -> returns)), (&(s -> returns)));
    double RAM[RAM_SIZE] = {};

    s -> regs.rax = 0;
    s -> regs.rbx = 0;
    s -> regs.rcx = 0;
    s -> regs.rdx = 0;

    return 1;
}
