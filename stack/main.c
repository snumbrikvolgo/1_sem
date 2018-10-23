#include "stack.h"

int main()
{
    stack_t stack;
    int size = 0;

    dump(stackCtor(&stack), (&stack));
    dump(stackPush(&stack, 43), (&stack));
    dump(stackPush(&stack, 50), (&stack));
    dump(stackPush(&stack, 88), (&stack));
    unittest(stackOK(&stack), ==, 1.0, lg);
    unittest(stackPush(&stack, 43), ==, 1.0, lg); 
    unittest(stackOK(&stack), ==, 1.0, lg);
    unittest(stackPop(&stack), ==, 43.0, lg);
    unittest(stackPop(&stack), ==, 88.0, lg);
    unittest(stackPop(&stack), ==, 50.0, lg);
    unittest(stackPop(&stack), ==, 43.0, lg);
    unittest(stackOK(&stack), ==, 1.0, lg);
    unittest(stackOK(&stack), ==, 1.0, lg);
    unittest(stackDtor(&stack), ==, 1.0, lg);
    return 0;
}
