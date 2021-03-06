#define RESET   "\033[0m"
#define RED     "\a\033[1;31m"
#define GREEN   "\033[1;32m"
#define ttype 1
#define DEBUG

#ifdef DEBUG
#define assert(check, ptr, canary_type)                                     \
    do                                                                      \
    {                                                                       \
    if(!(check))                                                            \
        {                                                                   \
        printf("Something goes wrong: %s in %s, %d \n                       \
               ====================================\n                       \
               ======= stack ptr =       %p =======\n                       \
               ======= data ptr =        %p========\n                       \
               ======= stack size     = %d ========\n                       \
               ======= stack max_size = %d=====\n                           \
               ======= canary1 =        %d ===\n                            \
               ======= canary2 =        %d ===\n                            \
               ======= data - canary1 = %d ===\n                            \
               ======= data - canary2 = %d ===\n                            \
               ====================================\n",                     \
                #check, __FILE__, __LINE__, ptr, ptr -> data, ptr -> size,  \
                ptr -> max_size, ptr -> canary1, ptr -> canary2,            \
                ((int*)(ptr -> data))[0],                                      \
                ((int*)((ptr -> data) + sizeof(data_t)*(ptr -> max_size) + sizeof(int)))[0]);          \
        abort();                                                            \
        }                                                                   \
    } while(0)

#else
#define assert(check)
#endif

static int Nunittest = 0;
static int Lunittest = 9;
#define unittest(what, op, ref) 
     do                                                                  
    {    
        (Nunittest)++;
        printf("UNITTEST_%d", (Nunittest));
        data_t result = (what);
        data_t expected = (ref);
        if ((result) op (expected)) printf("[  "GREEN"%s"RESET"  ]\n", "PASSED");  
        else           
            printf("[     "RED"FAILED"RESET": #what #op  %lg, expected %lg\n", (double)(result), (ref));
                                                                                             
    } while(0)

#include <stdio.h>
//#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define CAPACITY 3
#define POISON -10000
#define CANARY 1234

typedef double data_t;

typedef struct stack
        {
            int canary1;
            data_t* data;
            int size;
            int max_size;
            int canary2;
        } stack_t;

int stackCtor(stack_t* s);
int  stackDtor(stack_t* s);
int  stackPush(stack_t *s, const data_t value);
int   stackOK(const stack_t* s);
void  stackChangeSize(stack_t* s);
data_t stackTop(stack_t* s);
int stackSize(stack_t* s);


