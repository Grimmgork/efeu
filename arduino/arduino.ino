#define NULL 0
#include "efeuvm.c"

// Instruction worddef[] = { &instr_docol, &instr_lit, (Instruction)1, &instr_lit, (Instruction)2, &instr_add, &inst_emit, &instr_exit };
Instruction instructions[] = { &instr_docol, &instr_lit, (Instruction)1, &instr_lit, (Instruction)2, &instr_add, &instr_exit };

void 
setup()
{
	// setup pins
	pinMode(LED_BUILTIN, OUTPUT);
	char* memory = malloc(sizeof(Instruction)*512);
	EfeuVM vm = efeu_init(memory, sizeof(Instruction)*512, sizeof(Instruction)*64 + 2);
	int result = efeu_run(&vm, &instructions[0]);
	if(*vm.stack_pointer == (Instruction) 3) {
		digitalWrite(LED_BUILTIN, 1);
	}
}

void
loop()
{
	
}