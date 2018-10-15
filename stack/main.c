#include "stack.h"

int main()
{
    stack_t stack;
    int size = 0;
    assert(stackCtor(&stack), (&stack), ttype);
    printf("%d", stackSize(&stack));

    assert(stackPush(&stack, 42), (&stack), ttype);
    assert(stackPush(&stack, 50), (&stack), ttype);
    assert(stackPush(&stack, 88), (&stack), ttype);

    printf("%d", stackSize(&stack));


    int lovlyu = stackPop(&stack);
    lovlyu = stackPop(&stack);
    lovlyu = stackPop(&stack);
    //lovlyu = stackPop(&stack);



    printf("Lovi\n");
    printf ("%d\n", lovlyu);
    assert(stackDtor(&stack), (&stack), ttype);
    unittest(stackCtor(&stack), 1);
    unittest(stackOK(&stack), 1);
    unittest(stackPush(&stack, 42), 1);
  unittest(stackOK(&stack), 1);

  unittest(stackPop(&stack), 42);

//unittest(stackPop(&stack), 43);
 assert (0, (&stack), ttype);

  //unittest(stackOK(&stack), 1);
  //unittest(stackOK(&stack), 1);

  //unittest(stackDtor(&stack), 1);

    return 0;
}
