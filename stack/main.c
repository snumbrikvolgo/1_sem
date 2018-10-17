#include "stack.h"

int main()
{
    stack_t stack;
    int size = 0;

    assert(stackCtor(&stack), (&stack));
    assert(stackPush(&stack, 42), (&stack));
    assert(stackPush(&stack, 50), (&stack));
    assert(stackPush(&stack, 88), (&stack));

    unittest(stackCtor(&stack), =, 1, d);
    unittest(stackOK(&stack), =, 1, d);
    unittest(stackPush(&stack, 42), =, 1, d);
    unittest(stackOK(&stack), =, 1, d);
    unittest(stackPop(&stack), =, 42.0, lg);
    unittest(stackPop(&stack), =, 43.0, lg);
    unittest(stackOK(&stack), =, 1, d);
    unittest(stackOK(&stack), =, 1, d);
    unittest(stackDtor(&stack), =, 1, d);



    return 0;
}
