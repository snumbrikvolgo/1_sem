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

enum asm_commands
{
    #define CMD(name, num, act) CMD_##name = num,
    #define CMD_COMPLEX(name, num, act) CMD_COMPLEX_##name = num,
    #define CMD_REG(name, reg_name, num, act) CMD_REG_##name = num,
    #define CMD_JMP(name, num, act) CMD_JMP_##name = num,
    #define CMD_RAM(name, place, num, act) CMD_RAM_##name = num,

        #include "commands.h"

    #undef CMD_REG
    #undef CMD
    #undef CMD_COMPLEX
    #undef CMD_JMP
    #undef CMD_RAM
};

struct names
{
    char label_name[MAX_LABEL_NAME];
    int label_address;
};

typedef struct labels
{
    struct names names[MAX_LABEL_NUM];
    int size;
} label_t;

int main()
{
    FILE * file = fopen("debug.txt", "wb");
    FILE * input = fopen("tree.txt", "r");
    char * buffer =  read_file(input);
    int file_size = size_of_file(input);

    char* code = (char*)calloc(file_size + 1, sizeof(*code));
    int ptr = 0;
    int index = 0;
    int cycle = 0;
    label_t labels = {0};
    int quantity = 0;


    while(quantity < 2)
    {

        while(*(buffer + ptr) != '\0')
        {
            if (*(buffer + ptr) == ':')
            {

                ptr++;
                int counter = 0;
                if(quantity == 0) {
                    sscanf((buffer + ptr), "%s%n", labels.names[labels.size].label_name, &counter);
                    labels.names[labels.size].label_address = index;
                    labels.size++;
                } else {
                    sscanf((buffer + ptr), "%*s%n", &counter);
                }

                ptr += counter;
            }

            #define CMD(name, num, act)                                                             \
            if(strncmp(buffer + (ptr), #name, strlen(#name)) == 0)                                  \
            {                                                                                       \
                ptr += strlen(#name) * sizeof(char);                                                \
                code[index++] = num;                                                                \
            }

            #define CMD_RAM(name, place, num, act)                                                  \
            if(strncmp(buffer + (ptr), #name, strlen(#name)) == 0)                                  \
            {                                                                                       \
                ptr += strlen(#name) * sizeof(char);                                                \
                code[index++] = num;                                                                \
                while (isspace(*(buffer + ptr)))                                                    \
                {                                                                                   \
                    ptr++;                                                                          \
                }                                                                                   \
                ptr++;                                                                              \
                int ip = 0;                                                                         \
                int counter = 0;                                                                    \
                sscanf(buffer + ptr, "%d%n", &ip, &counter);                                        \
                ptr += counter + 1;                                                                 \
                memcpy(code + index, &ip, sizeof(int));                                             \
                index += sizeof(int);                                                               \
            }
           #define CMD_REG(name, reg_name, num, act)                                                \
            if(strncmp(buffer + (ptr), #name, strlen(#name)) == 0)                                  \
            {                                                                                       \
                ptr += strlen(#name) * sizeof(char);                                                \
                code[index++] = num;                                                                \
                while (isspace(*(buffer + ptr)))                                                    \
                    {                                                                               \
                        ptr++;                                                                      \
                    }                                                                               \
                if (strncmp(buffer + (ptr), "RAX", strlen("RAX")) == 0)                             \
                    {                                                                               \
                        code[index++] = '1';                                                        \
                    }                                                                               \
                if (strncmp(buffer + (ptr), "RBX", strlen("RBX")) == 0)                             \
                    {                                                                               \
                        code[index++] = '2';                                                        \
                    }                                                                               \
                if (strncmp(buffer + (ptr), "RCX", strlen("RCX")) == 0)                             \
                    {                                                                               \
                        code[index++] = '3';                                                        \
                    }                                                                               \
                if (strncmp(buffer + (ptr), "RDX", strlen("RDX")) == 0)                             \
                    {                                                                               \
                        code[index++] = '4';                                                        \
                    }                                                                               \
                ptr += 3 * sizeof(char);                                                            \
            }

           #define CMD_COMPLEX(name, num, act)                                                      \
               if(strncmp(buffer + (ptr), #name, strlen(#name)) == 0)                               \
            {                                                                                       \
                ptr += strlen(#name)*sizeof(char);                                                  \
                code[index++] = num;                                                                \
                while (isspace(*(buffer + ptr)))                                                    \
                    {                                                                               \
                        ptr++;                                                                      \
                    }                                                                               \
                double value = 0;                                                                   \
                int counter = 0;                                                                    \
                sscanf(buffer + (ptr), " %lg %n", &value, &counter);                                \
                memcpy(code + (index), &value, sizeof(double));                                     \
                index += sizeof(double);                                                            \
                ptr += counter;                                                                     \
            }

           #define CMD_JMP(name, num, act)                                                                                      \
               if(strncmp(buffer + (ptr), #name, strlen(#name)) == 0)                                                           \
                {                                                                                                               \
                    ptr += strlen(#name)*sizeof(char);                                                                          \
                    code[index++] = num;                                                                                        \
                    while (isspace(*(buffer + ptr)))                                                                            \
                        {                                                                                                       \
                           ptr++;                                                                                               \
                        }                                                                                                       \
                    int numeros = 0;                                                                                            \
                    char nombre[MAX_LABEL_NAME] = {};                                                                           \
                    sscanf(buffer + ptr, "%s%n", nombre, &numeros);                                                             \
                    char flg = 0;                                                                                               \
                    for (cycle = 0; cycle < labels.size; cycle++)                                                               \
                        {                                                                                                       \
                            if (strncmp(labels.names[cycle].label_name, nombre, numeros) == 0)                                  \
                                {   printf(" cur adr =    %d\n", labels.names[cycle].label_address);                            \
                                    memcpy(code + index, &labels.names[cycle].label_address, sizeof(int));                      \
                                    flg = 1;                                                                                    \
                                    index += sizeof(int);                                                                       \
                                }                                                                                               \
                        }                                                                                                       \
                     if(!flg) {                                                                                                 \
                                    int tmp = -1;                                                                               \
                                    memcpy(code + index, &tmp, sizeof(int));                                                    \
                                    index += sizeof(int);                                                                       \
                                  }                                                                                             \
                    ptr += numeros;                                                                                             \
                }

           #include "commands.h"
           #undef CMD
           #undef CMD_COMPLEX
           #undef CMD_REG
           #undef CMD_JMP


                while (isspace(*(buffer + ptr)))
                {
                    ptr++;
                }
            }

            ptr = 0;
            quantity++;
            index = 0;
            cycle = 0;
    }

    fwrite(code, sizeof(char), file_size, file);
    fclose(file);
    fclose(input);
    C_FREE(buffer);
    C_FREE(code);
    return 1;

}
