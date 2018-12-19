#include "stack.h"

#define TO_ELEM(stack, sizeptr)  (stack -> data + sizeof(data_t) * (sizeptr) + sizeof(int))
/*#define nop(...) do {;} while(0)

#define fprintf(...) nop()*/

#ifndef NDEBUG
#   define D if(1)
#else
#   define D if(0)
#endif

//-------------------------------------------------------------------------------------------------------

int stackCtor(stack_t* s)
{
    D dump(s != NULL, s);

    s -> canary1 = CANARY;
    s -> canary2 = CANARY;
    s -> data = (data_t*) calloc(CAPACITY * sizeof(data_t) + 2 * sizeof(int), 1);
    if ((s -> data) == NULL)
    {
        errno = NOMEMORYLEFT;
        perror("Not enough memory, buy some\n");
        return 0;
    }
    s -> max_size = CAPACITY;
    s -> size = 0;
    ((int*)(s-> data))[0] = CANARY;
    ((int*)TO_ELEM(s, s -> max_size))[0] = CANARY;

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
    s -> hash = 0;

    return 1;
}

//-------------------------------------------------------------------------------------------------------

int stackOK(const stack_t *s)
{
    if(!s)
    {
        errno = NULLPOINTER;
        fprintf(stderr, "Stack is lost in data\n");
        return 0;
    }
    if((s -> max_size) < 0)
    {
        errno = MINUSSIZE;
        fprintf(stderr, "Stack capacity undefined\n");
        return 0;
    }
    if(s -> canary1 != CANARY)
    {
        errno = DEADCANARY;
        fprintf(stderr, "OMG, You killed canary1, you bastards!\n");
        return 0;
    }
    if(s -> canary2 != CANARY)
    {
        errno = DEADCANARY;
        fprintf(stderr, "OMG, You killed canary1, you bastards!\n");
        return 0;
    }
    if(!(s -> data))
    {
        errno = NULLPOINTER;
        fprintf(stderr, "Stack is lost in data\n");
        return 0;
    }
    if(((int*)(s-> data))[0] != CANARY)
    {
        errno = ITGOES;
        fprintf(stderr, "Canary is not on the beginning of the stack\n");
        return 0;
    }
    if(((int*)TO_ELEM(s, s -> max_size))[0] != CANARY)
    {
        errno = ITGOES;
        fprintf(stderr, "Canary is not in the end of stack\n");
        return 0;
    }

    return (s && s -> data && ((s -> max_size) >= 0)
            && (s -> canary1 == CANARY)
            && (s -> canary2 == CANARY)
            && (((int*)(s-> data))[0] == CANARY)
            && (((int*)TO_ELEM(s, s -> max_size))[0] == CANARY));
}

//-------------------------------------------------------------------------------------------------------

int  stackPush(stack_t *s, const data_t value)
{
     dump(stackOK(s), s);
     if (s -> size < s -> max_size)                                                             //check for size, without recursion, is enough for PUSH
     {
        TO_ELEM(s, (s -> size)++)[0] = value;

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
//int    stackPop (stack_t* s, data_t* dst)
data_t stackPop (stack_t* s)
{
    dump(stackOK(s), s);

    if (s == NULL)
	    return POISON;

    data_t output = 0;
    if (s -> size == 0)
    {
        dump(stackChangeSize(s), s);
        errno = EMPTYSTACK;
        fprintf(stderr, "Stack is empty\n");
        //*dst = FLUE;
        return FLUE;
    }
    if (s -> size > 0)
    {
        s -> size--;
        output = TO_ELEM(s, s -> size)[0];

        dump(stackOK(s), s);
        //*dst = output;
        return output;
    }
    else
    {
        errno = MINUSSIZE,
        fprintf(stderr, "Stack is broken\n");
        dump(stackOK(s), s);
        return FLUE;
    }
}

//-------------------------------------------------------------------------------------------------------

data_t stackTop(stack_t *s)
{
    dump(stackOK(s), s);
    if((s -> size) <= 0)
    {
        errno = EMPTYSTACK;
        fprintf(stderr, "Stack is empty\n");
        return FLUE;
    }
    return TO_ELEM(s, s -> size - 1)[0];
}

//-------------------------------------------------------------------------------------------------------

int stackChangeSize(stack_t* s)
{
    dump(stackOK(s), s);
    if ((2 * (s -> size)) <= (s -> max_size))
    {
         (s -> max_size) = (s -> size);
         s -> data = (data_t*)realloc (s -> data, (s -> max_size) * sizeof(data_t) + 2 * sizeof(int));
         ((int*)TO_ELEM(s, s -> max_size))[0] = CANARY;

         dump(stackOK(s), s);
         return 1;
    }

    if ((s -> size) + 1 >= s -> max_size)
    {
        s -> max_size = 2 *(s ->  max_size + 2);
        s -> data = (data_t*)realloc (s -> data,  (s -> max_size) * sizeof(data_t) + 2 * sizeof(int));
        ((int*)TO_ELEM(s, s -> max_size))[0] = CANARY;

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

//-------------------------------------------------------------------------------------------------------

/*double hashsum (stack_t *s)
{
    dump(stackOK(s), s);
    s -> hash = 0;

    for (int i = 0; i < (s -> size); i++)
    	(s -> hash) += (i + 1) * (*((s -> data) + i * sizeof (data_t) + sizeof(int)));

    dump(stackOK(s), s);
    return ( s -> hash);
}*/
