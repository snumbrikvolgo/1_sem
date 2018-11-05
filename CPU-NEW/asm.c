#include <stdio.h>
#include <math.h>
#include "work_file_strings.h"

#define C_FREE(p)       \
    do                  \
    {                   \
        free(p);        \
        p = NULL;       \
    } while(0)


#define MAX_LABEL_NUM  20
#define MAX_LABEL_NAME 10

#define CMD(name, num) CMD_##name = num,
#define CMD_COMPLEX(name, num) CMD_COMPLEX_##name = num,
    

enum asm_commands
{
#include "commands.h"            
};

#undef CMD
#undef CMD_COMPLEX

struct labels
{
    char label_name[MAX_LABEL_NAME];
    int label_address;
};


int read_code(int argc, char* argv[])
{
    FILE * file = fopen("debug.txt", "w");
    FILE * input = fopen(argv[1], "rw");
    char * buffer =  read_file(argv[1]);
    int file_size = size_of_file(input);
    char* code = (char*)calloc(file_size + 1, sizeof(*code));
    int ptr = 0;
    int index = 0;
    struct labels lab_array[MAX_LABEL_NUM] = {};
     printf("%s", buffer);
    
    while(*(buffer + ptr) != '\0')
       {                                            
            #define CMD(name, num) \
            if(strncmp(buffer + (ptr), #name, strlen(#name)) == 0) \
            { \
                printf("%zd\n", strlen(#name));\
                ptr += strlen(#name) * sizeof(char);\
                code[index++] = num;\
            }   
           
           #define CMD_COMPLEX(name, num)   \
               if(strncmp(buffer + (ptr), #name, strlen(#name)) == 0) \
            { \
                ptr += strlen(#name)*sizeof(char);\
                code[index++] = num;\
                printf("%zd\n", strlen(#name));\
                  while (isspace(*(buffer + ptr)))\
                {\
                    ptr++;\
                }\
                 /*printf("%zd\n", strlen(#name));*/\
                double value = 0;                                       \
                int counter = 0;                                        \
                sscanf(buffer + (ptr), " %lg %n", &value, &counter);    \
                printf("value == %lg\n", value);\
                memcpy(code + (index), &value, sizeof(double));         \
                printf("%lg\n", *((double*)((code + index))));\
                index += sizeof(double);                                \
                ptr += counter;                                         \
            }
           #include "commands.h"    
             #undef CMD
            #undef CMD_COMPLEX    
            while (isspace(*(buffer + ptr)))
                {
                    ptr++;
                } 
        }  
    
    //printf("%s", buffer + ptr);
    fwrite(code, sizeof(char), file_size, file);
    C_FREE(buffer);
    C_FREE(code);
       return 0;
    
}







