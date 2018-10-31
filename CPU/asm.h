/*#define BEGIN 1
#define POP 2
#define PUSH 3
#define MUL 4
#define DIV 5
#define ADD 6
#define SUB 7
#define END 0*/

enum commands
{   

    //#define CMD(name, num) CMD_##name = (num),
    //#include "commands.h";
     
    CMD_BEGIN = 64,
    CMD_POP = 65,
    CMD_PUSH = 66,
    CMD_MUL = 67,
    CMD_DIV = 68,
    CMD_ADD = 69,
    CMD_SUB = 70,
    CMD_END = 71,   
    CMD_PUSHREG = 72,
    CMD_POPREG = 73,
    CMD_PUSHMEM = 74,
    CMD_POPMEM = 75,
    CMD_JMP = 76,
    CMD_JA = 77,
    CMD_JB = 78,
    CMD_JE = 79,
    CMD_SQRT = 80,
    CMD_SIN = 81,
    CMD_COS = 82,
    CMD_TAN = 83,
    CMD_OUT = 84,
    CMD_IN = 85,
    
    //#undef CMD
    /*BEGIN = 64,
    POP = 65,
    PUSH = 66,
    MUL = 67,
    DIV = 68,
    ADD = 69,
    SUB = 70,
    END = 71,   
    PUSHREG = 72,
    POPREG = 73,
    PUSHMEM = 74,
    POPMEM = 75,
    JMP = 76,
    JA = 77,
    JB = 78,
    JE = 79,
    SQRT = 80,
    SIN = 81,
    COS = 82,
    TAN = 83,*/
    
};



