#include "stack.h"

//-------------------------------------------------------------------------------------------------------

int stackCtor(stack_t* s)
{
    dump(s != NULL, s);
    s -> canary1 = CANARY;
    s -> canary2 = CANARY;
    s -> data = (data_t*) calloc(CAPACITY * sizeof(data_t) + 2 * sizeof(int), 1);
    if ((s -> data) == NULL) printf("Not enough memory, buy some\n");
    s -> max_size = CAPACITY;
    s -> size = 0;
    ((int*)(s-> data))[0] = CANARY;
    ((int*)((s -> data) + sizeof(data_t)*(s -> max_size) + sizeof(int)))[0] = CANARY;
    dump(stackOK(s), s);
    return 1;
}

//-------------------------------------------------------------------------------------------------------

int stackDtor(stack_t *s)
{
    dump(stackOK(s), s);
    memset(s -> data, POISON, (s -> size) * sizeof(data_t) + 2 * sizeof(int));
    free (s -> data);
    s -> data = NULL;
    s -> max_size = -1;
    s -> size = -1;


    return 1;
}

//-------------------------------------------------------------------------------------------------------

int stackOK(const stack_t *s)
{
    if(!s) printf("Stack is lost in data\n");
    if(!(s -> data)) printf("Data is NULL ptr\n");
    if((s -> max_size) < 0) printf("Stack capacity undefined\n");
    if(s -> canary1 != CANARY) printf("OMG, You killed canary, you bastards!\n");
    if(s -> canary2 != CANARY) printf("OMG, You killed canary, you bastards!\n");
    if(((int*)(s-> data))[0] != CANARY) printf("Canary is not on the beginning of the stack\n");
    if(((int*)((s -> data) + sizeof(data_t)*(s -> max_size) + sizeof(int)))[0] != CANARY) printf("Canary is not in the end of stack\n");
    return (s && s -> data && ((s -> max_size) >= 0)
            && (s -> canary1 == CANARY)
            && (s -> canary2 == CANARY)
            && (((int*)(s-> data))[0] == CANARY)
            && (((int*)((s -> data) + sizeof(data_t)*(s -> max_size) + sizeof(int)))[0] == CANARY));
}

//-------------------------------------------------------------------------------------------------------

int  stackPush(stack_t *s, const data_t value)
{
     dump(stackOK(s), s);
     if (s -> size < s -> max_size)
     {
         ((s -> data) + ((s -> size)++) * sizeof(data_t) + sizeof(int))[0] = value;
        dump(stackOK(s), s);
        return 1;
     }

     else
     {
        dump(stackChangeSize(s), s);
        return stackPush(s, value);
     }
}

//-------------------------------------------------------------------------------------------------------

data_t stackPop (stack_t* s)
{
    dump(stackOK(s), s);
    data_t output = 0;
    if (s -> size == 0)
    {
        dump(stackChangeSize(s), s);
        printf("Stack is empty");
        return POISON;
    }
    if (s -> size > 0)
    {
        output = (s -> data + sizeof(data_t) * (--s -> size) + sizeof(int))[0];
        dump(stackOK(s), s);
        return output;
    }
    else
    {
        printf("Stack is broken\n");
        dump(stackOK(s), s);
    return POISON;
    }
}

//-------------------------------------------------------------------------------------------------------

data_t stackTop(stack_t *s)
{
    dump(stackOK(s), s);
    if((s -> size) <= 0)
    {
        printf("Stack is empty\n");
        return POISON;
    }
    return (s -> data + sizeof(data_t) * (s -> size - 1) + sizeof(int))[0];
}

//-------------------------------------------------------------------------------------------------------

int stackChangeSize(stack_t* s)
{
    dump(stackOK(s), s);
    if ((2 * (s -> size)) <= (s -> max_size))
    {
         (s -> max_size) = (s -> size);
         s -> data = (data_t*)realloc (s -> data, (s -> max_size) * sizeof(data_t) + 2 * sizeof(int));
         ((int*)((s -> data) + sizeof(data_t)*(s -> max_size) + sizeof(int)))[0] = CANARY;
         dump(stackOK(s), s);
         return 1;
    }

    if ((s -> size) + 1 >= s -> max_size)
    {
        s -> max_size = 2 *(s ->  max_size + 2);
        s -> data = (data_t*)realloc (s -> data,  (s -> max_size) * sizeof(data_t) + 2 * sizeof(int));
        ((int*)((s -> data) + sizeof(data_t)*(s -> max_size) + sizeof(int)))[0] = CANARY;
        dump(stackOK(s), s);
        return 1;
    }

}

//-------------------------------------------------------------------------------------------------------

int stackSize(stack_t* s)
{
    dump(stackOK(s), s);
    return (s -> size);
}
