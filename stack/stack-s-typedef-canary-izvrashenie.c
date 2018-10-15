#include "stack.h"

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
    //printf("%d %p %d\n", s, s -> stackPop(&stack)data, ((s -> max_size) >= 0 ) );
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
        // assert (0, s, ttype);
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


