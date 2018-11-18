    CMD(BEGIN, 64)    
    CMD(POP, 65)    
    CMD_COMPLEX(PUSH, 66)    
    CMD(MUL, 67)
    CMD(DIV, 68)
    CMD(ADD, 69)
    CMD(SUB, 70)
    CMD(END, 71)

    CMD_REG(R_PUSH, REG_NAME, 72)
    CMD_REG(R_POP, REG_NAME, 73)
   
  
    CMD(SQRT, 74)
    CMD(SIN, 75)
    CMD(COS, 76)
    CMD(TAN, 77)
    CMD(OUT, 78)
    CMD(IN, 79)
    
    CMD_JMP(JMP, 80)
    CMD_JMP(JA, 81)
    CMD_JMP(JB, 82)
    CMD_JMP(JE, 83)
    CMD_JMP(JAE, 84)
    CMD_JMP(JBE, 85)
    CMD_JMP(JNE, 86)
    CMD_JMP(CALL, 87)
    CMD(CUR, 88)

    //CMD_MEM(PUSHMEM, 74)
   //CMD_MEM(POPMEM, 75)
