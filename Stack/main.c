#include "stack_func.h"
#include "stack_unittests.h"




int main()
{
	for (int i = 1; i < 6; i++)
	{
		Stack* Stack_1 = stack_create(10); 

		switch(i)
		{
			case 1: UNIT_1(Stack_1);
				break;
		//	case 2: UNIT_2(Stack_1);
			//	break;
			case 3: UNIT_3(Stack_1);
				break;
			case 4: UNIT_4(Stack_1);
				break;
			case 5: UNIT_5(Stack_1);
				break;
			default: break;
		}
		stack_destroy(Stack_1);
	}

	Stack* Stack_1 = stack_create(10);
	stack_push(Stack_1, 111);
	stack_push(Stack_1, 888);
	stack_push(Stack_1, 777);
	stack_push(Stack_1, 999);

	unittest(stack_pop(Stack_1), ==, 999, 6);
	unittest(stack_pop(Stack_1), ==, 777, 7);
	stack_OK(Stack_1);
	unittest(errno, ==, Success, 8);
	unittest(stack_pop(Stack_1), ==, 888, 9);
	unittest(stack_pop(Stack_1), ==, 111, 10);
	stack_pop(Stack_1);
	unittest(errno, ==, STACK_UNDERFLOW, 11);
}