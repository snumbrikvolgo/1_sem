#define RESET   "\033[0m"
#define RED     "\a\033[1;31m"
#define GREEN   "\033[1;32m"
#define ttype 1
#define DEBUG

#ifdef DEBUG
#define assert(check, ptr, canary_type)                                                  \
    do                                                                      \
    {                                                                       \
    if(!(check))                                                            \
        {                                                                   \
        printf("Something goes wrong: %s in %s, %d \n                       \
               ====================================\n                       \
               ======= stack ptr =       %p =======\n                       \
               ======= data ptr =        %p========\n                       \
               ======= stack size     = %d ========\n                       \
               ======= stack max_size = %d=========\n                       \
               ======= canary1 =        %d ===\n                       \
               ======= canary2 =        %d ===\n                       \
               ======= data - canary1 = %d ===\n                       \
               ======= data - canary2 = %d ===\n                       \
               ====================================\n",                     \
                #check, __FILE__, __LINE__, ptr, ptr -> data, ptr -> size,  \
                ptr -> max_size, ptr -> canary1, ptr -> canary2,            \
                ((int*)(ptr -> data))[0],((int*)((ptr -> data) + sizeof(data_t)*(ptr -> max_size) + sizeof(int)))[0]);          \
        abort();                                                            \
        }                                                                   \
    } while(0)

#else
#define assert(check)
#endif


#define unittest(what, ref) \
     do                                                                  \
    {                                                                    \
        if(what != ref)                                                  \
            printf("FAILED: %s = %d, expected %d\n", #what, (what), (ref));\
        else                                                             \
            printf("[  "GREEN"%s"RESET"  ]\n", "PASSED");                                    \
    } while(0)

#include <stdio.h>
//#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define CAPACITY 3
#define POISON -10000  ///problem with NAN, when data_t is int etc
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


int stackCtor(stack_t* s)
{
    assert(s != NULL, s, ttype);
    s -> canary1 = CANARY;
    s -> canary2 = CANARY;
    s -> data = (data_t*) calloc(CAPACITY * sizeof(data_t) + 2 * sizeof(int), 1);
    s -> max_size = CAPACITY;
    s -> size = 0;
    ((int*)(s-> data))[0] = CANARY;
    ((int*)((s -> data) + sizeof(data_t)*(s -> max_size) + sizeof(int)))[0] = CANARY;
    assert(stackOK(s), s, ttype);
    return 1;
}

int stackDtor(stack_t *s)
{
    assert(stackOK(s), s, ttype);
    memset(s -> data, POISON, (s -> size) * sizeof(data_t) + 2 * sizeof(int));
    free (s -> data);
    s -> data = NULL;
    s -> max_size = -1;
    s -> size = -1;

    return 1;
}

int stackOK(const stack_t *s)
{
    //printf("%d %p %d\n", s, s -> data, ((s -> max_size) >= 0 ) );
    return (s && s -> data && ((s -> max_size) >= 0)
            && (s -> canary1 == CANARY)
            && (s -> canary2 == CANARY)
            && (((int*)(s-> data))[0] == CANARY)
            && (((int*)((s -> data) + sizeof(data_t)*(s -> max_size) + sizeof(int)))[0] == CANARY));
}

int  stackPush(stack_t *s, const data_t value)
{
     assert(stackOK(s), s, ttype);
     if (s -> size < s -> max_size)
     {
         ((s -> data) + ((s -> size)++) * sizeof(data_t) + sizeof(int))[0] = value;
        //memcpy(s -> data + ((s -> size)++) * (s -> elem_size), value, s -> elem_size);

        assert(stackOK(s), s, ttype);
        return 1;
     }

     else
     {
        //printf("WARNING: STACK OVERFLOW\n");
        stackChangeSize(s);
        return stackPush(s, value);
     }
}

data_t stackPop (stack_t* s)
{
    assert(stackOK(s), s, ttype);
    data_t output = 0;
    if (s -> size == 0)
    {
        printf("Stack is empty\n");
        stackChangeSize(s);
        return POISON;
    }
    if (s -> size > 0)
    {
        output = (s -> data + sizeof(data_t) * (--s -> size) + sizeof(int))[0];
        assert(stackOK(s), s, ttype);
        return output;
    }
    else
    {
        printf("Stack is broken\n");
        assert(stackOK(s), s, ttype);
    return POISON;
    }
}
data_t stackTop(stack_t *s)
{
    assert(stackOK(s), s, ttype);
    if((s -> size) <= 0)
    {
        printf("Stack is empty");
        return POISON;
    }
    return (s -> data + sizeof(data_t) * (s -> size - 1) + sizeof(int))[0];
}

void stackChangeSize(stack_t* s)
{
    assert(stackOK(s), s, ttype);
    if ((2 * (s -> size)) <= (s -> max_size))
    {
        (s -> max_size) = (s -> size);
         s -> data = (data_t*)realloc (s -> data, (s -> max_size) * sizeof(data_t) + 2 * sizeof(int));
         ((int*)((s -> data) + sizeof(data_t)*(s -> max_size) + sizeof(int)))[0] = CANARY;
         assert(stackOK(s), s, ttype);
    }

    if ((s -> size) + 1 >= s -> max_size)
    {
        s -> max_size = 2 *(s ->  max_size + 2);
        s -> data = (data_t*)realloc (s -> data,  (s -> max_size) * sizeof(data_t) + 2 * sizeof(int));  ///WARNINGGGGG!!!!!!!
       ((int*)((s -> data) + sizeof(data_t)*(s -> max_size) + sizeof(int)))[0] = CANARY;
        assert(stackOK(s), s, ttype);
    }

}



int stackSize(stack_t* s)
{
    assert(stackOK(s), s, ttype);
    return (s -> size);
}

int main()
{
    stack_t stack;
    int size = 0;
    assert(stackCtor(&stack), (&stack), ttype);
    //printf ("%d\n", ((int*)((stack.data) + sizeof(data_t)*(stack.max_size) + sizeof(int)))[0]);
    printf("%d\n", stackSize(&stack));
    assert(stackPush(&stack, 42), (&stack), ttype);
   //printf ("%d\n", ((int*)((stack.data) + sizeof(data_t)*(stack.max_size) + sizeof(int)))[0]);
     printf("%d\n", stackSize(&stack));
    assert(stackPush(&stack, 50), (&stack), ttype);
     printf("%d\n", stackSize(&stack));
    assert(stackPush(&stack, 88), (&stack), ttype); ///оверфлоу циклится
     printf("%d\n", stackSize(&stack));
    //assert(stackPush(&stack, 88));
    int lo = stackSize(&stack);
    printf("%d", lo);


    int lovlyu = stackPop(&stack);
    lovlyu = stackPop(&stack);
    lovlyu = stackPop(&stack);
    //lovlyu = stackPop(&stack);
    /// на третьем крашится


    printf("Lovi\n");
    printf ("%d\n", lovlyu);
    assert(stackDtor(&stack), (&stack), ttype);
    /*unittest(stackCtor(&stack), 1);
    unittest(stackOK(&stack), 1);
   unittest(stackPush(&stack, 42), 1);
  //unittest(stackOk(&stack), 1);

  unittest(stackPop(&stack), 42);
  unittest(stackPop(&stack), 43);

  //unittest(stackOK(&stack), 1);
  //unittest(stackOK(&stack), 1);

  unittest(stackDtor(&stack), 1);*/

    return 0;
}
