    CMD(BEGIN, 64, ({
                                    index++;
                                    break;
                                }))
    CMD(POP, 65, ({
                                index++;
                                break;
                              }))
    CMD_COMPLEX(PUSH, 66, ({
                                        index++;
                                        memcpy(&value, (code + index), sizeof(double));
                                        stackPush(&(s -> stack), value);
                                        index += sizeof(double);

                                        break;

                                       }))
    CMD(MUL, 67, ({
                                    index++;
                                    stackPush(&(s -> stack), stackPop(&(s -> stack)) * stackPop(&(s -> stack)));
                                    break;
                               }))
    CMD(DIV, 68, (
                              {
                                    index++;
                                    double  a = stackPop(&(s -> stack));
                                    double  b = stackPop(&(s -> stack));

                                    stackPush(&(s -> stack), b/a);
                                    break;
                               }))
    CMD(ADD, 69, ({
                                    index++;
                                    stackPush(&(s -> stack), stackPop(&(s -> stack)) + stackPop(&(s -> stack)));
                                    break;
                               }))
    CMD(SUB, 70, (
                              {
                                    index++;
                                    double  a = stackPop(&(s -> stack));
                                    double  b = stackPop(&(s -> stack));

                                    stackPush(&(s -> stack), b - a);
                                    break;
                               }))
    CMD(END, 71, ({

                                    exit(0);
                                    break;
                                }))

    CMD_REG(R_PUSH, REG_NAME, 72, ({

                                   index++;
                                   switch(code[index])
                                    {
                                   case '1':
                                        {
                                            stackPush(&(s -> stack), (s -> regs.rax));
                                            index++;
                                            break;
                                         }
                                    case '2':
                                        {

                                            stackPush(&(s -> stack), (s -> regs.rbx));
                                            index++;

                                            break;
                                         }
                                    case '3':
                                        {

                                            stackPush(&(s -> stack), (s -> regs.rcx));
                                            index++;

                                            break;
                                         }
                                   case '4':
                                        {

                                            stackPush(&(s -> stack), (s -> regs.rdx));
                                            index++;

                                            break;
                                         }
                                    }
                                    break;
                                }))
    CMD_REG(R_POP, REG_NAME, 73, ({
                                   index++;

                                   switch(code[index])
                                   {
                                   case '1':
                                        {

                                            s -> regs.rax = stackPop(&(s -> stack));
                                            index++;
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
                                                printf("No index\n");
                                                break;
                                            }
                                    }

                                break;
                                }))


    CMD(SQRT, 74, ({
                                    index++;
                                    double  a = stackPop(&(s -> stack));
                                    a = sqrt(a);
                                    stackPush(&(s -> stack), a);
                                    break;
                               }))
    CMD(SIN, 75, (
                              {
                                    index++;
                                    double  a = stackPop(&(s -> stack));
                                    a = sin(a);
                                    stackPush(&(s -> stack), a);
                                    break;
                               }))
    CMD(COS, 76, (
                              {
                                    index++;
                                    double  a = stackPop(&(s -> stack));
                                    a = cos(a);
                                    stackPush(&(s -> stack), a);
                                    break;
                               }))
    CMD(TAN, 77, ({
                                    index++;
                                    double  a = stackPop(&(s -> stack));
                                    a = tan(a);
                                    stackPush(&(s -> stack), a);
                                    break;
                               }))
    CMD(OUT, 78, ({
                                   index++;
                                   double popret = stackPop(&(s -> stack));
                                   printf("out == %lg \n", popret);
                                   break;
                                }))
    CMD(IN, 79, ( {
                                            index++;
                                            printf("Enter the number\n");
                                            double value = 0;
                                            scanf("%lg", &value);
                                            stackPush(&(s -> stack), value);

                                            break;
                                        }))
    CMD_JMP(JAE, 84, ({
                                    index++;
                                    double a = stackPop(&(s -> stack));
                                    double b = stackPop(&(s -> stack));
                                    if (a >= b)
                                    {
                                       memcpy(&index, code + index, sizeof(int));
                                    }
                                    else index += sizeof(int);

                                    break;
                               }))
    CMD_JMP(JBE, 85, ( {
                                    index++;
                                    double a = stackPop(&(s -> stack));
                                    double b = stackPop(&(s -> stack));
                                    if (a <= b)
                                    {
                                        memcpy(&index, code + index, sizeof(int));
                                    }
                                    else index += sizeof(int);

                                    break;
                               }))
    CMD_JMP(JNE, 86, (  {
                                    index++;
                                    double a = stackPop(&(s -> stack));
                                    double b = stackPop(&(s -> stack));
                                    if (a != b)
                                    {
                                        memcpy(&index, code + index, sizeof(int));
                                    }
                                    else index += sizeof(int);

                                    break;
                               }))
    CMD_JMP(JMP, 80, ({
                                    index++;
                                    memcpy(&index, code + index, sizeof(int));

                                    break;
                               }))
    CMD_JMP(JA, 81, ({
                                    index++;
                                    double a = stackPop(&(s -> stack));

                                    double b = stackPop(&(s -> stack));
                                    printf(" a = %lf b = %lg\n", a, b);
                                    if (a > b)
                                    {
                                        memcpy(&index, code + index, sizeof(int));

                                    }

                                    else index += sizeof(int);



                                    break;
                               }))
    CMD_JMP(JB, 82, ( {
                                    index++;
                                    double a = stackPop(&(s -> stack));
                                    double b = stackPop(&(s -> stack));
                                    printf(" a = %lf b = %lg\n", a, b);

                                    if (a < b)
                                    {
                                        memcpy(&index, code + index, sizeof(int));

                                    }

                                    else index += sizeof(int);


                                    break;
                               }))
    CMD_JMP(JE, 83, ({
                                    index++;
                                    double a = stackPop(&(s -> stack));
                                    double b = stackPop(&(s -> stack));
                                    if (a == b)
                                    {

                                        memcpy(&index, code + index, sizeof(int));

                                    }
                                    else index += sizeof(int);

                                    break;
                               }))
    CMD_JMP(CALL, 87, ( {
                                    double adr = 0;

                                    adr = (double) index;

                                    stackPush(&(s -> returns), (double)adr);

                                    memcpy(&index, code + index + 1, sizeof(int));

                                    break;
                                }))
    CMD(RET, 88, ({

                                    index = (int) (stackPop(&(s -> returns)));
                                    index += 1 + sizeof(int);

                                    break;

                                }
                                    ))
    CMD(CUR, 89, ({
                                     index++;
                                     double a = stackPop(&(s -> stack));
                                    printf("current number == %lg\n", a);
                                    stackPush(&(s -> stack), a);
                                    break;
                                    }))
    CMD_RAM(M_PUSH, place, 90,({
                                    index++;
                                    int ip = *((int*)(code + index));
                                    index += sizeof(int);
                                    stackPush(&(s -> stack), s ->RAM[ip]);
                                    break;
                                    }))
    CMD_RAM(M_POP, place, 91, ({
                                    index++;
                                    int ip = *((int*)(code + index));
                                    index += sizeof(int);
                                    s -> RAM[ip] = stackPop(&(s -> stack));
                                    break;
                                    }))
    CMD(RET, 88, ({


                                }))
