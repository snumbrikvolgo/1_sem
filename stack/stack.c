#include <stdio.h>
#define CAPACITY 512

int main()
{
    struct stack s
        {
            double* data;
            int size;
            int CAPACITY;
        };
    stackCtor(&s, CAPACITY);
    assert(StackOK(&s));
    assert(StackPush(&s, 42));

}

void  stackCtor(stack *s)
{
    assert(s);
    s -> *data = (double*)calloc(size, sizeof(*data));
    int a = scanf("%d", &a);
    s -> size = a;
    return s;
}

void stackDtor(stack *s)
{
    
