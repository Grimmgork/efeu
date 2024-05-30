#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <efeuvm.c>

Instruction word[] = { &instr_docol, &instr_lit, (Instruction)1, &instr_lit, (Instruction)2, &instr_add, &inst_emit, &instr_exit };
Instruction instructions[] = { &instr_docol, &instr_call, &word, &instr_lit, (Instruction)1, &instr_lit, (Instruction)2, &instr_add, &inst_emit, &instr_exit };

int 
main(int argc, char** argv)
{
	char* memory = malloc(sizeof(Instruction)*512);
	EfeuVM vm = efeu_init(memory, sizeof(Instruction)*512, sizeof(Instruction)*64 + 2);
	efeu_run(&vm, &instructions);
}