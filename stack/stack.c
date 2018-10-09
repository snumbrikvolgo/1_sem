#include <stdio.h>
void  stackCtor(struct *s);
void stackDtor(struct *s);


int main()
{
    struct stack s
        {
            double* data;
            int size;
            int capacity;
        };
    struct stack *ps;
    s = {0, 0, 512};
    stackCtor(&s, CAPACITY);
    assert(stackOK(&s));
    assert(stackPush(&s, 42));

}

void  stackCtor(struct *s)
{
    assert(s);
    s -> *data = (double*)calloc(size, sizeof(*data));
    int a = scanf("%d", &a);
    s -> size = a;
    return s;
}

void stackDtor(struct *s)
{
    assert(s);
    free (s->data);
    s->data = 0;
    s->capacity = -1;
    s->size = -1;
}

bool stackOK(const struct *s) 
{
    return s && s->data && s->size;
}

int stackPush(struct *s,int a)
{
    
