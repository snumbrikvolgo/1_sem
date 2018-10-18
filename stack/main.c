#include "stack.h"

int main()
{
    stack_t stack;
    int size = 0;

    dump(stackCtor(&stack), (&stack));
    dump(stackPush(&stack, 43), (&stack));
    printf("%lg\n", stackTop(&stack));
    printf("%d\n", stackSize(&stack));
    dump(stackPush(&stack, 50), (&stack));
    printf("%d\n", stackSize(&stack));
printf("%lg\n", stackTop(&stack));
    dump(stackPush(&stack, 88), (&stack));
    printf("%d\n", stackSize(&stack));
printf("%lg\n", stackTop(&stack));

    unittest(stackOK(&stack), ==, 1, d);
    unittest(stackPush(&stack, 43), =, 1, d);
printf("%lg\n", stackTop(&stack));
    printf("%d\n", stackSize(&stack));
    unittest(stackOK(&stack), ==, 1, d);
    unittest(stackPop(&stack), ==, 43.0, lg);
printf("%lg\n", stackTop(&stack));
    printf("%d\n", stackSize(&stack));
    unittest(stackPop(&stack), ==, 88.0, lg);
printf("%lg\n", stackTop(&stack));
    unittest(stackPop(&stack), ==, 50.0, lg);
printf("%lg\n", stackTop(&stack));
    printf("%d\n", stackSize(&stack));
    unittest(stackPop(&stack), ==, 43.0, lg);
    printf("%d\n", stackSize(&stack));
    unittest(stackOK(&stack), ==, 1, d);
    unittest(stackOK(&stack), ==, 1, d);
    unittest(stackDtor(&stack), ==, 1, d);



    return 0;
}
