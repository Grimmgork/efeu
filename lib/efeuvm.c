#define WORDDEF_IMMEDIATE  0b00010000;
#define WORDDEF_NAMELENGTH 0b00001111;

typedef struct EfeuVM EfeuVM;
typedef void (*Instruction)(EfeuVM*);

struct EfeuVM {
	char* dictionary_top;

	char* heap_start;
	char* heap_pointer;
	char* heap_end;

	Instruction* stack_start;
	Instruction* stack_pointer;
	Instruction* stack_end;

	char status; // compile mode, interupt flag,
	Instruction* ip;
};

EfeuVM
efeu_init(char* memory_start, int memory_size, int stack_size)
{
	EfeuVM vm;
	vm.stack_start = (Instruction*) memory_start;
	vm.stack_pointer = vm.stack_start;
	vm.stack_end = (Instruction*) (((char*) vm.stack_start) + stack_size);

	vm.heap_start = ((char*) vm.stack_end) + 1;
	vm.heap_pointer = vm.heap_start;
	vm.heap_end = memory_start + memory_size;

	vm.dictionary_top = 0;
    vm.status = 0;
    vm.ip = 0;

	return vm;
}

char*
efeu_find_word(EfeuVM* vm, char* name)
{
	char* check = vm->dictionary_top;
	while(check != 0) {
		char* next = *(char**)check;
		char* ptr = check;
		ptr += sizeof(char*);
		char status = *ptr; // read status byte
		char length = status & WORDDEF_NAMELENGTH; // read length of name
		ptr++; // move to start of name
		if (strncmp(ptr, name, length)) {
			break;
		}
		check = next;
	}
	return check;
}

Instruction*
efeu_word_first_instruction(char* word)
{

}

void
instr_exit(EfeuVM* vm)
{
	// exit word execution started by docol
}

void
instr_docol(EfeuVM* vm)
{
	vm->ip++;
	while(*vm->ip != &instr_exit) {
		(*vm->ip)(vm);
	}
}

int
efeu_run(EfeuVM* vm, Instruction* ptr)
{
	if (*ptr != instr_docol) {
		return -1;
	}
	vm->ip = ptr;
	(*vm->ip)(vm);
	return 0;
}

void
instr_next(EfeuVM* vm)
{
	vm->ip++;
}

void
instr_add(EfeuVM* vm)
{
	int a = (int) *vm->stack_pointer;
	vm->stack_pointer--;
	int b = (int) *vm->stack_pointer;
	vm->stack_pointer--;

	vm->stack_pointer++;
	*vm->stack_pointer = (Instruction) a + b;
	vm->ip++;
}

void
instr_call(EfeuVM* vm)
{
	vm->ip++;
	Instruction* ip = vm->ip;
	vm->ip = (Instruction*)*vm->ip;
	(*vm->ip)(vm);
	vm->ip = ip;
	vm->ip++;
}

void
instr_dereference(EfeuVM* vm)
{
	vm->ip++;
}

void
instr_getdp(EfeuVM* vm)
{
	vm->ip++;
}

void
instr_setdp(EfeuVM* vm)
{
	vm->ip++;
}

void
instr_lit(EfeuVM* vm)
{
	vm->ip++;
	vm->stack_pointer++;
	*vm->stack_pointer = *vm->ip;
	vm->ip++;
}

void
instr_dup(EfeuVM* vm)
{
	vm->ip++;
}

void
instr_swap(EfeuVM* vm)
{
	vm->ip++;
}

void
inst_rot(EfeuVM* vm)
{
	vm->ip++;
}

void
inst_allot(EfeuVM* vm)
{
	vm->ip++;
}

void
inst_branch(EfeuVM* vm)
{
	vm->ip++;
}

void
inst_0branch(EfeuVM* vm)
{
	vm->ip++;
}

void
inst_emit(EfeuVM* vm)
{
	printf("%d\n", (int)vm->stack_pointer[0]);
	vm->stack_pointer--;
	vm->ip++;
}
