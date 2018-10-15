//канарейки произвольного размера
#define DEBUG
#ifdef DEBUG
#define assert(check) if (!(check))\
{\
printf("Something goes wrong: %s in %s, %d\n", #check, __FILE__, __LINE__);\
abort();\
}
#else
#define assert(check)
#endif

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define CAPACITY 3
#define POISON 0  ///problem, when data_t is int etc
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

void stackCtor(stack_t* s);
void  stackDtor(stack_t* s);
int  stackPush(stack_t *s, const data_t value);
int   stackOK(const stack_t* s);
void  stackChangeSize(stack_t* s);
data_t stackTop(stack_t* s);
int stackSize(stack_t* s);


void stackCtor(stack_t* s)
{
    assert(s != NULL);
    s -> canary1 = CANARY;
    s -> canary2 = CANARY;
    s -> data = (data_t*) calloc(CAPACITY + 2, sizeof(data_t));
    s -> max_size = CAPACITY;
    s -> size = 0;
    s -> data[0] = CANARY;
    s -> data[s -> max_size+1] = CANARY;
    assert(stackOK(s));
}

void stackDtor(stack_t *s)
{
    assert(stackOK(s));
    memset(s -> data, POISON, (s -> size + 2) * sizeof(data_t));
    free (s -> data);
    s -> data = NULL;
    s -> max_size = -1;
    s -> size = -1;
}

int stackOK(const stack_t *s)
{
    //printf("%d %p %d\n", s, s -> data, ((s -> max_size) >= 0 ) );
    return (s && s -> data && ((s -> max_size) >= 0)
            && (s -> canary1 == CANARY)
            && (s -> canary2 == CANARY)
            && (s -> data[0] == CANARY)
            && (s -> data[s -> max_size + 1] == CANARY));
}

int  stackPush(stack_t *s, const data_t value)
{
     assert(stackOK(s));
     if (s -> size < s -> max_size)
     {
        (s -> data)[++(s -> size)] = value;
        //memcpy(s -> data + ((s -> size)++) * (s -> elem_size), value, s -> elem_size);
        assert(stackOK(s));
        return 1;
     }

     else
     {
        printf("WARNING: STACK OVERFLOW\n");
        stackChangeSize(s);
        return stackPush(s, value);
     }
}

data_t stackPop (stack_t* s)
{
    assert(stackOK(s));
    data_t output = 0;
    if (s -> size == 0)
    {
        printf("Stack is empty\n");
        stackChangeSize(s);
        return -100000;
    }
    if (s -> size > 0)
    {
        output = s -> data[(s -> size)];
        s -> data[(s -> size)--] = 0;
        assert(stackOK(s));
        return output;
    }
    else
    {
        printf("Stack is broken\n");
        assert(stackOK(s));
    return 0;
    }
}

void stackChangeSize(stack_t* s)
{
    assert(stackOK(s));
    if ((2 * (s -> size)) <= (s -> max_size))
    {
        (s -> max_size) = (s -> size);
         s -> data = (data_t*)realloc (s -> data, (s -> max_size) * sizeof(data_t)+1);

         assert(stackOK(s));
    }

    if ((s -> size) + 1 >= s -> max_size)
    {
        s -> data = (data_t*)realloc (s -> data, 2 * (s -> max_size + 2) * sizeof(data_t)+1);  ///WARNINGGGGG!!!!!!!
        assert(stackOK(s));
    }

}

data_t stackTop(stack_t *s)
{
    assert(stackOK(s));
    if((s -> size) <= 0)
    {
        printf("Stack is empty");
        return -100000;
    }
    return s -> data[(s -> size)];
}

int stackSize(stack_t* s)
{
    assert(stackOK(s));
    return (s -> size);
}

int main()
{
    stack_t stack;
    int size = 0;
    stackCtor(&stack);
    assert(stackPush(&stack, 42));
    assert(stackPush(&stack, 50));
    assert(stackPush(&stack, 88));
    int lo = stackSize(&stack);
    printf("%d", lo);


    int lovlyu = stackPop(&stack);
    lovlyu = stackPop(&stack);
    lovlyu = stackPop(&stack);
    lovlyu = stackPop(&stack);


    printf("Lovi\n");
    printf ("%d\n", lovlyu);
    stackDtor(&stack);

    return 0;
}
