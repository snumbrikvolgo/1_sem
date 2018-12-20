#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#define RESET   "\033[0m"
#define RED     "\a\033[1;31m"
#define GREEN   "\033[1;32m"
#define DEBUG
/*#ifdef SECURITY

  #define hashsum(ptr)                                                                          \
    do                                                                                          \
    {                                                                                           \
        ptr -> hash = 0;                                                                        \
        for (int i = 0; i < (ptr -> size); i++)                                                 \
    	    (ptr -> hash) += (i + 1) * (*((ptr -> data) + i * sizeof (data_t) + sizeof(int)));  \
    }while (0)
 
#else 
#define hashsum(ptr)
#endif                                                              
*/

#ifdef DEBUG

#define dump(check, ptr)                                                     \
    do                                                                       \
    {                                                                        \
        if(!(check))                                                         \
        {                                                                    \
		    if (ptr == NULL)					                             \
			    printf ("stack_ptr = NULL\n");		                         \
									                                         \
		    else						                                     \
		    {							                                     \
                    printf("                                               \n\
                            Something goes wrong: %s in %s, %d             \n\
                            ===================================            \n\
                            ======= stack ptr = %p                         \n\
                            ======= data ptr  = %p                         \n\
                            ======= stack size     = %d =====              \n\
                            ======= stack max_size = %d =====              \n\
                            ======= canary1 =        %d ===                \n\
                            ======= canary2 =        %d ===                \n\
                            ======= hash =        %d  ===                \n",\
                            #check, __FILE__, __LINE__,                      \
                            ptr, ptr -> data, ptr -> size,                   \
                            ptr -> max_size, ptr -> canary1, ptr -> canary2, ptr -> hash);\
                    }							                             \
		    if (ptr -> data != NULL)                                         \
                    {                                                        \
                    printf("                                               \n\
                            ======= data - canary1 = %d ===                \n\
                            ======= data - canary2 = %d ===              \n",\
                                                                             \
                            ((int*)(ptr -> data))[0],                        \
                ((int*)((ptr -> data) + sizeof(data_t)*(ptr -> max_size) + sizeof(int)))[0]);\
                    }                                                        \
                    printf("                                                 \
                            ==================================          \n");\
                                                                             \
        }                                                                    \
    } while(0)

#else

#define dump(check)
#endif

/*static int Nunittest = 0;
static int Lunittest = 10;*/

#define unittest(what, op, ref, ftype)                                                                                      \
     do                                                                                                                     \
    {                                                                                                                       \
        (Nunittest)++;                                                                                                      \
        printf("UNITTEST_%d\n", (Nunittest));                                                                               \
        data_t result = (what);                                                                                             \
                                                                                                                            \
        data_t expected = (ref);                                                                                            \
        if ((result) op (expected)) printf("[  "GREEN"PASSED"RESET"  ]\n");                                                 \
                                                                                                                            \
        else                                                                                                                \
            printf("[  "RED"FAILED"RESET": "#what" "#op"  %" #ftype " expected %" #ftype "  ]\n", (double) (result), (ref));\
         printf("[%.*s%.*s]\n\n", (Nunittest), "||||||||||||||||", ((Lunittest) - (Nunittest)) , "...............");        \
    } while(0)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define CAPACITY 64
#define POISON  -10000 // const
#define FLUE     1337 // const
#define CANARY   1234

    

typedef double data_t;

typedef struct stack
        {
            int canary1;
            data_t* data;
            int size;
            int max_size;
            int canary2;
            int hash;
        } stack_t;

int  stackCtor(stack_t* s);
int  stackDtor(stack_t* s);
int  stackPush(stack_t *s, const data_t value);
int  stackOK(const stack_t* s);
int  stackChangeSize(stack_t* s);
data_t stackTop(stack_t* s);
int stackSize(stack_t* s);
data_t stackPop (stack_t* s);
data_t hashsum (stack_t *s);

#endif // STACK_H_INCLUDED
