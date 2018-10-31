#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "work_file_strings.h"
#include <ctype.h>
#include <assert.h>
#include "asm.h"

char* skip_spaces(char** buffer)
{
    while(isspace(**buffer)) (*buffer)++;
    return (*buffer);
}



int detect_begin(char* buffer, int* ptr, char* mem, int* index)
{   
    buffer = skip_spaces(&buffer);
    if(strncmp(buffer + (*ptr), "begin", strlen("begin")) == 0)
        {
            *(mem + (*index)) = (unsigned char) CMD_BEGIN;
            (*index)++;
            (*ptr) += sizeof("begin");
            
            return 1;
        }
     return 0;
}

int detect_end(char* buffer, int* ptr, char* mem, int* index)
{   
    buffer = skip_spaces(&buffer);
    if(strncmp(buffer + (*ptr), "end", strlen("end")) == 0)
        {
            *(mem + (*index)) = (unsigned char) CMD_END;
            (*index)++;
            printf("%s", buffer);
            //(*ptr) += sizeof("end");
            (*ptr) ++;
            
            return 1;
        }
     return 0;
}

int detect_out(char* buffer, int* ptr, char* mem, int* index)
{   
    buffer = skip_spaces(&buffer);
    if(strncmp(buffer + (*ptr), "out", strlen("out")) == 0)
        {
            *(mem + (*index)) = (unsigned char) CMD_OUT;
            (*index)++;
            (*ptr) += sizeof("out");
       
            return 1;
        }
     return 0;
}

int detect_push(char* buffer, int* ptr, char* mem, int* index)
{   
    if(strncmp(buffer + (*ptr), "push", strlen("push")) == 0)
        {
            *(mem + (*index)) = (unsigned char) CMD_PUSH;
            (*index)++;
            (*ptr) += sizeof("push"
);

            double value = 0;
            int counter = 0;
            sscanf(buffer + (*ptr), " %lg %n", &value, &counter);
            sprintf(mem + (*index), "%lg", value);
            *index += sizeof(double);

            printf("%d\n", counter);
            (*ptr) += counter; 
            printf("value == %lg\n", value);  
            return 1;
   
        }
     return 0;
}

int detect_in(char* buffer, int* ptr, char* mem, int* index)
{   
    if(strncmp(buffer + (*ptr), "in", strlen("in")) == 0)
        {
            *(mem + (*index)) = (unsigned char) CMD_IN;
            (*index)++;
            (*ptr) += sizeof("in");

            double value = 0;
            int counter = 0;
            counter = scanf(" %lg", &value);
            sprintf(mem + (*index), "%lg", value);
            *index += sizeof(double);

            //printf("%d\n", counter);
            (*ptr) += counter; 
            printf("value == %lg\n", value);  
            return 1;
   
        }
     return 0;
}



int detect_pop(char* buffer, int* ptr, char* mem, int* index)
{   
    if(strncmp(buffer + (*ptr), "pop", strlen("pop")) == 0)
        {
            *(mem + (*index)) = (unsigned char) CMD_POP;
            (*index)++;
            (*ptr) += sizeof("pop");
            
            return 1;
        }
     return 0;
}

int detect_add(char* buffer, int* ptr, char* mem, int* index)
{   
    if(strncmp(buffer + (*ptr), "add", strlen("add")) == 0)
        {
                
            *(mem + (*index)) = (unsigned char) CMD_ADD;
            (*index)++;
            (*ptr) += sizeof("add");
            
            return 1;
        }
     return 0;
}

int detect_sub (char* buffer, int* ptr, char* mem, int* index)
{   
    printf("lol %d\n loool\n", strncmp(buffer + (*ptr), "sub", strlen ("sub"))); 
    if(strncmp(buffer + (*ptr), "sub", strlen("sub")) == 0)
        {
               
            *(mem + (*index)) = (unsigned char) CMD_SUB;
            (*index)++;
            (*ptr) += sizeof("sub");
            
            return 1;
        }
     return 0;
}

int detect_mul (char* buffer, int* ptr, char* mem, int* index)
{   
    if(strncmp(buffer + (*ptr), "mul", strlen("mul")) == 0)
        {
            printf ("%d\n", 0);    
            *(mem + (*index)) = (unsigned char) CMD_MUL;
            (*index)++;
            (*ptr) += sizeof("mul");
            
            return 1;
        }
     return 0;
}

int detect_div (char* buffer, int* ptr, char* mem, int* index)
{   
    if(strncmp(buffer + (*ptr), "div", strlen("div")) == 0)
        {
               
            *(mem + (*index)) = (unsigned char) CMD_DIV;
            (*index)++;
            (*ptr) += sizeof("div");
            
            return 1;
        }
     return 0;
}

/*int detect_ja (char* buffer, int* ptr, char* mem, int* index)
{   
    if(strncmp(buffer + (*ptr), "ja", strlen("ja")) == 0)
        {
            printf ("%d\n", 0);    
            *(mem + (*index)) = (unsigned char) CMD_JA;
            (*index)++;
            (*ptr) += sizeof("ja");
            
            return 1;
        }
     return 0;
}*/

/*int detect_jmp (char* buffer, int* ptr, char* mem, int* index)
{   
    if(strncmp(buffer + (*ptr), "jmp", strlen("jmp")) == 0)
        {
            printf ("%d\n", 0);    
            *(mem + (*index)) = (unsigned char) CMD_JMP;
            (*index)++;
            (*ptr) += sizeof("div");
            
            return 1;
        }
     return 0;
}*/

/*int detect_jmp (char* buffer, int* ptr, char* mem, int* index)
{   
    if(strncmp(buffer + (*ptr), "jmp", strlen("jmp")) == 0)
        {
            printf ("%d\n", 0);    
            *(mem + (*index)) = (unsigned char) CMD_JMP;
            (*index)++;
            (*ptr) += sizeof("div");
            
            return 1;
        }
     return 0;
}*/

/*int detect_jmp (char* buffer, int* ptr, char* mem, int* index)
{   
    if(strncmp(buffer + (*ptr), "jmp", strlen("jmp")) == 0)
        {
            printf ("%d\n", 0);    
            *(mem + (*index)) = (unsigned char) CMD_JMP;
            (*index)++;
            (*ptr) += sizeof("div");
            
            return 1;
        }
     return 0;
}*/


int detect_sqrt (char* buffer, int* ptr, char* mem, int* index)
{   
    if(strncmp(buffer + (*ptr), "sqrt", strlen("sqrt")) == 0)
        {
               
            *(mem + (*index)) = (unsigned char) CMD_SQRT;
            (*index)++;
            (*ptr) += sizeof("sqrt");
            
            return 1;
        }
     return 0;
}

int detect_sin (char* buffer, int* ptr, char* mem, int* index)
{   
    if(strncmp(buffer + (*ptr), "sin", strlen("sin")) == 0)
        {
            
            *(mem + (*index)) = (unsigned char) CMD_SIN;
            (*index)++;
            (*ptr) += sizeof("sin");
            
            return 1;
        }
     return 0;
}

int detect_cos(char* buffer, int* ptr, char* mem, int* index)
{   
    if(strncmp(buffer + (*ptr), "cos", strlen("cos")) == 0)
        {
            
            *(mem + (*index)) = (unsigned char) CMD_COS;
            (*index)++;
            (*ptr) += sizeof("cos");
            
            return 1;
        }
     return 0;
}

int detect_tan(char* buffer, int* ptr, char* mem, int* index)
{   
    if(strncmp(buffer + (*ptr), "tan", strlen("tan")) == 0)
        {
             
            *(mem + (*index)) = (unsigned char) CMD_TAN;
            (*index)++;
            (*ptr) += sizeof("tan");
            
            return 1;
        }
     return 0;
}

int main(int argc, char* argv[])
{   
   
    FILE * file = fopen("debug.txt", "w");
    scanf("%s", argv[0]);
    FILE * input = fopen(argv[0], "rw");
    char * buffer =  read_file(argv[0]);
    int file_size = size_of_file(input);
    char* code = (char*)calloc(file_size + 1, sizeof(*code));
    int ptr = 0;
    int index = 0;
    //printf ("%d\n", strncmp(buffer + (ptr), "push", strlen ("push")));
    while (*(buffer ) != '\0')
    {
        if(strncmp(buffer + (ptr), "begin", strlen("begin")) == 0)
             detect_begin(buffer, &ptr, code, &index);
        if(strncmp(buffer + (ptr), "in", strlen("in")) == 0)
             detect_in(buffer, &ptr, code, &index);
        //printf("%s ", code);
        if(strncmp(buffer + (ptr), "push", strlen("push")) == 0)
             detect_push(buffer, &ptr, code, &index);
        //printf("%s ", code);
        if(strncmp(buffer + (ptr), "pop", strlen("pop")) == 0)
             detect_pop(buffer, &ptr, code, &index);
        if(strncmp(buffer + (ptr), "mul", strlen("mul")) == 0)
             detect_mul(buffer, &ptr, code, &index);
        if(strncmp(buffer + (ptr), "div", strlen("div")) == 0)
             detect_div(buffer, &ptr, code, &index);
        if(strncmp(buffer + (ptr), "add", strlen("add")) == 0)
             detect_add(buffer, &ptr, code, &index);
        if(strncmp(buffer + (ptr), "sub", strlen("sub")) == 0)
             detect_sub(buffer, &ptr, code, &index);
        if(strncmp(buffer + (ptr), "end", strlen("end")) == 0)
             detect_end(buffer, &ptr, code, &index);
        if(strncmp(buffer + (ptr), "out", strlen("out")) == 0)
             detect_out(buffer, &ptr, code, &index);
        if(strncmp(buffer + (ptr), "sqrt", strlen("sqrt")) == 0)
             detect_sqrt(buffer, &ptr, code, &index);
        if(strncmp(buffer + (ptr), "sin", strlen("sin")) == 0)
             detect_sin(buffer, &ptr, code, &index);
        if(strncmp(buffer + (ptr), "cos", strlen("cos")) == 0)
             detect_cos(buffer, &ptr, code, &index);
        if(strncmp(buffer + (ptr), "tan", strlen("tan")) == 0)
             detect_tan(buffer, &ptr, code, &index);
        //buffer++;
    }
    /*detect_begin(buffer, &ptr, code, &index);
    printf("%s", buffer + ptr);
    assert(detect_in(buffer, &ptr, code, &index));

    printf ("%s\n", buffer + ptr);
    printf("%s\n", code + index);
     assert(detect_push(buffer, &ptr, code, &index));
    printf ("%s\n", buffer + ptr);
    assert(detect_add(buffer, &ptr, code, &index));
    assert(detect_pop(buffer, &ptr, code, &index));
    assert(detect_out(buffer, &ptr, code, &index));
    assert(detect_end(buffer, &ptr, code, &index));*/
    fwrite(code, sizeof(char), file_size, file);
    printf("%s ", code);
    return 0;
}


