#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define CAPACITY 50

typedef  struct stack /// объ€вл€ем стек
        {
            double* data;
            int size;
            int max_size;
        } stack;

void  stackCtor(struct stack* s);
void  stackDtor(struct stack* s);
int   stackPush(struct stack* s, double a);
int stackOK(const struct stack *s);

void stackCtor(struct stack* s)
{
    assert(s != NULL);
    s -> data = (double*)calloc(CAPACITY, sizeof(*(s -> data)));
    s -> max_size = CAPACITY;
    s -> size = 0;
    assert(stackOK(s));
}

void stackDtor(struct stack *s)
{
    assert(stackOK(s));
    free (s->data);
    s -> data = 0;
    s -> max_size = -1;
    s -> size = -1;
}

int stackOK(const struct stack *s)
{
    return s && s -> data && (s -> max_size == CAPACITY);
}

int  stackPush(struct stack *s, double a)
{
     assert(stackOK(s));
     if (s -> size < s -> max_size)
     {
        s -> data[s -> size ++] = a;
        assert(stackOK(s));
        return 1;
     }
     else
     {
        printf("STACK OVERFLOW");
        assert(stackOK(s));
        return 0;
     }
}

double stackPop (stack* s)
{
    assert(stackOK(s));
    if s ->
}


int main()
{
    int size = 0;
    size = scanf("%d", &size);

   // double lovlyu = stackPop(&s);

    printf ("%d", stackPop(&s));

}
