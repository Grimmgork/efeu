#include <elang.h>

struct InstructionStack {
	int length;
	int chunksize;
	INSTRUCTION* alloc;
	INSTRUCTION* top;
	INSTRUCTION* bottom;
};

struct InstructionStack *
stack_init(int chunksize)
{
	struct InstructionStack *stack = malloc(sizeof(struct InstructionStack));
	if (stack == NULL) {
		return NULL;
	}

	stack->length = 0;
	stack->chunksize = chunksize;
	stack->alloc = NULL;
	stack->top = NULL;
	stack->bottom = NULL;
	return stack;
}

int
stack_push(struct InstructionStack *stack, INSTRUCTION value)
{
	if (stack->alloc == stack->top) {
		void* ptr;
		int new_size = (sizeof(INSTRUCTION) * stack->length) + (sizeof(INSTRUCTION) * stack->chunksize);
		if (stack->bottom == NULL)
		{
			ptr = malloc(new_size);
		}
		else
		{
			ptr = realloc(stack->bottom, new_size);
		}
		if (ptr == NULL) {
			return 1;
		}

		stack->length ++;
		stack->bottom = ptr;
		stack->top = ptr + (sizeof(INSTRUCTION) * stack->length);
		stack->alloc = ptr + new_size;
	}

	stack->top ++;
	stack->top[0] = value;
	return 0;
}

INSTRUCTION
stack_pop(struct InstructionStack *stack)
{
	INSTRUCTION value = stack->top[0];
	stack->length --;
	return value;
}

int 
stack_free(struct InstructionStack *stack)
{
	free(stack->bottom);
	free(stack);
}
