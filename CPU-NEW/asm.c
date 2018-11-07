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
#define CMD_REG(name, reg_name, num) CMD_REG_##name = num,
    

enum asm_commands
{
#include "commands.h"            
};
#undef CMD_REG
#undef CMD
#undef CMD_COMPLEX

struct labels
{
    char label_name[MAX_LABEL_NAME];
    int label_address;
};


int read_code()
{
    FILE * file = fopen("debug.txt", "w");
    FILE * input = fopen("polsk1", "rw");
    const char* name = "polsk1";
    char * buffer =  read_file(name);
    int file_size = size_of_file(input);
    char* code = (char*)calloc(file_size + 1, sizeof(*code));
    int ptr = 0;
    int index = 0;
     int pidr = 0;
    struct labels lab_array[MAX_LABEL_NUM] = {};
     printf("original : %s", buffer);
    
    while(*(buffer + ptr) != '\0')
       {                                            
            #define CMD(name, num) \
            if(strncmp(buffer + (ptr), #name, strlen(#name)) == 0) \
            { \
                printf("dlina" #name "%zd\n", strlen(#name));\
                ptr += strlen(#name) * sizeof(char);\
                code[index++] = num;\
                printf("current ostatok = %s", (buffer + ptr));\
            }  
 
           #define CMD_REG(name, reg_name, num)  \
            if(strncmp(buffer + (ptr), #name, strlen(#name)) == 0) \
            { \
                printf("\nchto v nachale commandy %c\n", *(buffer + ptr));\
                printf("dlina "#name"  %zd\n", strlen(#name));\
                ptr += strlen(#name) * sizeof(char);\
                printf("ptr == %zd\n",strlen(#name));\
                printf("na chato sdvinulos %d\n", *(buffer + ptr));\
               code[index++] = num;\
               while (isspace(*(buffer + ptr)))\
                {\
                    ptr++;\
                }\
                printf("na chato sdvinulos conec %c\n", *(buffer + ptr));\
                if (strncmp(buffer + (ptr), "RAX", strlen("RAX")) == 0) \
                    {\
                        printf("compare with rax %d\n", strncmp(buffer + (ptr), "RAX", strlen("RAX")));\
                        code[index++] = 1;\
                        printf("rax = %d\n", code[index - 1]);\
                    }\
                if (strncmp(buffer + (ptr), "RBX", strlen("RBX")) == 0) \
                    {\
                        code[index++] = 2;\
                    }\
                if (strncmp(buffer + (ptr), "RCX", strlen("RCX")) == 0) \
                    {\
                        code[index++] = 3;\
                    }\
                if (strncmp(buffer + (ptr), "RDX", strlen("RDX")) == 0) \
                    {\
                        code[index++] = 4;\
                    }\
                ptr += strlen(#reg_name) * sizeof(char);\
                printf("posle push pop reg %s\n", buffer + ptr);\
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
                double value = 0;                                       \
                int counter = 0;                                        \
                sscanf(buffer + (ptr), " %lg %n", &value, &counter);    \
                printf("value == %lg\n", value);\
                memcpy(code + (index), &value, sizeof(double));         \
                index += sizeof(double);                                \
                ptr += counter;                                         \
            }

           
                
           #include "commands.h"    
             #undef CMD
            #undef CMD_COMPLEX    
            #undef CMD_REG
            while (isspace(*(buffer + ptr)))
                {
                    sleep(2);
                    printf("perehod\n");
                    ptr++;
                } 
            
        }  
    
    printf("sovsem ostatok %s", buffer + ptr);
    printf("%s", code);
    fwrite(code, sizeof(char), file_size, file);
    fclose(file);
    fclose(input);
    C_FREE(buffer);
    C_FREE(code);
       return 0;
    
}







