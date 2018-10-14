#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#define CAPACITY 10
#define POISON 0


typedef  struct stack
        {
            void* data;
            int size;
            int max_size;
            int elem_size;
        } stack_t;

void stackCtor(stack_t* s, int elem_size);
void  stackDtor(stack_t* s);
int  stackPush(stack_t *s, const void* value);
void stackPop (stack_t* s, void* dest);
int   stackOK(const stack_t* s);
void  stackChangeSize(stack_t* s);
void stackTop(stack_t* s, void* dest);
int stackSize(stack_t* s);


void stackCtor(stack_t* s, int elem_size)
{
    assert(s != NULL);
    s -> elem_size = elem_size;
    s -> data = calloc(CAPACITY, s -> elem_size);
    s -> max_size = CAPACITY;
    s -> size = 0;
    assert(stackOK(s));
}

void stackDtor(stack_t *s)
{
    assert(stackOK(s));
    memset(s -> data, POISON, (s -> size) * (s -> elem_size));
    free (s -> data);
    s -> data = NULL;
    s -> max_size = -1;
    s -> size = -1;
}

int stackOK(const stack_t *s)
{
    //printf("%d %p %d\n", s, s -> data, ((s -> max_size) >= 0 ) );
    return s && s -> data && ((s -> max_size) >= 0) && ((s -> elem_size) > 0);
}

int  stackPush(stack_t *s, const void* value)
{
     assert(stackOK(s));
     if (s -> size < s -> max_size)
     {
        //(s -> data)[(s -> size)++] = a;
        memcpy(s -> data + ((s -> size)++) * (s -> elem_size), value, s -> elem_size);
        assert(stackOK(s));
        return 1;
     }

     else
     {
        //printf("WARNING: STACK OVERFLOW\n");
        stackChangeSize(s);
        return stackPush(s, value);
     }
}

void stackPop (stack_t* s, void* dest)
{

    assert(stackOK(s));
    if (s -> size == 0)
    {
        printf("Stack is empty\n");
        stackChangeSize(s);
        return;
    }
    if (s -> size > 0)
    {
        //output = s -> data[(s -> size) - 1];
        memcpy(dest, s -> data + (--(s -> size)) * (s -> elem_size), s -> elem_size);
        //s -> data[--(s -> size)] = 0;
        assert(stackOK(s));
        return;
    }
    else
    {
        printf("Stack is broken\n");
        assert(stackOK(s));
        return;
    }
}

void stackChangeSize(stack_t* s)
{
    assert(stackOK(s));
    if ((2 * (s -> size)) <= (s -> max_size))
    {
        (s -> max_size) = (s -> size);
        s -> data = realloc (s -> data, (s -> max_size) * (s -> elem_size) +1);
         assert(stackOK(s));
    }

    if ((s -> size)+1 >= s -> max_size)
    {
        s -> data = realloc (s -> data, 2 * (s -> max_size) * (s -> elem_size)+1);
        assert(stackOK(s));
    }

}

void stackTop(stack_t *s, void* dest)
{
    assert(stackOK(s));
    if((s -> size) <= 0)
    {
        printf("Stack is empty");
        return;
    }
    memcpy(dest, (s -> data)+ (s -> size - 1) * (s -> elem_size), s -> elem_size);
    return;
}

int stackSize(stack_t* s)
{
    assert(stackOK(s));
    return (s -> size);
}

int main()
{
    struct stack stack;
    int size = 0;
    stackCtor(&stack, sizeof(double));
    double tmp = 42;
    assert(stackPush(&stack, &tmp));
    tmp = 5;
    assert(stackPush(&stack, &tmp));
    tmp = 6;
    assert(stackPush(&stack, &tmp));

    int lo = stackSize(&stack);
    printf("%d\n", lo);
    tmp = 0;
    stackPop(&stack, &tmp);
    stackPop(&stack, &tmp);


    printf("Lovi\n");
    printf ("%f\n", tmp);
    stackDtor(&stack);

    return 0;
}
