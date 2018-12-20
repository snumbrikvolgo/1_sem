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
    s -> hash = hashsum(s);
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
    if(!s) {fprintf(stderr, "Stack is lost in data\n"); return 0;}
    if((s -> max_size) < 0) printf("Stack capacity undefined\n");
    if(s -> canary1 != CANARY) printf("OMG, You killed canary1, you bastards!\n");
    if(s -> canary2 != CANARY) printf("OMG, You killed canary2, you bastards!\n");
    if(!(s -> data)) {printf("Data is NULL ptr\n"); return 0;}
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
     if (s -> size < s -> max_size)                                                             //check for size, without recursion, is enough for PUSH
     {
         ((s -> data) + ((s -> size)++) * sizeof(data_t) + sizeof(int))[0] = value;
        (s -> hash) = hashsum(s);
        dump(stackOK(s), s);
        return 1;
     }

     else
     {
        dump(stackChangeSize(s), s);
        (s -> hash) = hashsum(s);
        return stackPush(s, value);
     }
}

//-------------------------------------------------------------------------------------------------------

data_t stackPop (stack_t* s)
{
    dump(stackOK(s), s);
    
    if (s == NULL)
	    return POISON;

    data_t output = 0;
    if (s -> size == 0)
    {
        dump(stackChangeSize(s), s);
        printf("Stack is empty\n");
        return FLUE;
    }
    if (s -> size > 0)
    {
        output = (s -> data + sizeof(data_t) * (--s -> size) + sizeof(int))[0];   //put to DEFINE
        (s -> hash) = hashsum(s);
        dump(stackOK(s), s);
        return output;
    }
    else
    {
        printf("Stack is broken\n");
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
        printf("Stack is empty\n");
        return FLUE;
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
         (s -> hash) = hashsum(s);
         dump(stackOK(s), s);
         return 1;
    }

    if ((s -> size) + 1 >= s -> max_size)
    {
        s -> max_size = 2 *(s ->  max_size + 2);
        s -> data = (data_t*)realloc (s -> data,  (s -> max_size) * sizeof(data_t) + 2 * sizeof(int));
        ((int*)((s -> data) + sizeof(data_t)*(s -> max_size) + sizeof(int)))[0] = CANARY;
       (s -> hash) = hashsum(s);
        dump(stackOK(s), s);
        return 1;
    }
    return 1;
}

//-------------------------------------------------------------------------------------------------------

int stackSize(stack_t* s)
{
    dump(stackOK(s), s);
    return (s -> size);
}

//-------------------------------------------------------------------------------------------------------

double hashsum (stack_t *s)
{
    dump(stackOK(s), s);
    s -> hash = 0; 

    for (int i = 0; i < (s -> size); i++) 
    	(s -> hash) += (i + 1) * (*((s -> data) + i * sizeof (data_t) + sizeof(int)));
    
    dump(stackOK(s), s);
    return ( s -> hash);
}









