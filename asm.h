enum asm_commands
{
#define CMD(name, num)\
    do\
    {\
    if(stncmp(buffer, #name) == 0)\
        code[index++] = CMD_##name;\
    }\
    while(0)\
#include "commands.h"            
}
