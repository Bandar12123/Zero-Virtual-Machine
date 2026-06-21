#include <stdio.h>
#include "zvm_instruction.h"
#include "zvm.h"

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(add)
    vm->cpu.R[output] = vm->cpu.R[left] + vm->cpu.R[right];
    printf("R=%u\n", vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(sub)
    vm->cpu.R[output] = vm->cpu.R[left] - vm->cpu.R[right];
    printf("R=%u\n", vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(ldi)
    vm->cpu.R[left] = right;
    printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(str)
    /* STR reg, mem */
    vm->program.data[right] = vm->cpu.R[left];
    printf("MEM=%u\n", vm->program.data[right]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(ldm)
    /* LDM reg, mem */
    vm->cpu.R[left] = vm->program.data[right];
    printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(lda)
    uint8_t address = vm->cpu.R[left];
    if(!zvm_is_address(address)){
        zvm_raise(vm, EXECUTE, BAD_MEMORY_ADDRESS)
        return false;
    }
    vm->cpu.R[right] = vm->program.data[address];
    printf("R=%u\n", vm->cpu.R[right]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(sta)
    /* STA reg, reg */
    uint8_t address = vm->cpu.R[left];
    if(!zvm_is_address(address)){
        zvm_raise(vm, EXECUTE, BAD_MEMORY_ADDRESS)
        return false;
    }
    vm->program.data[address] = vm->cpu.R[right];
    printf("address=%u\n", vm->program.data[address]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(push)
    uint8_t value;
    if(vm->cpu.SP >= ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE){
        zvm_raise(vm, EXECUTE, STACK_OVERFLOW)
        return false;
    }

    vm->cpu.SP++;
    value = vm->cpu.R[left];
    vm->program.stack[(ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1) - vm->cpu.SP] = value;
    printf("stack=%u\n", value);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(pop)
    uint8_t value;
    if(vm->cpu.SP < 0){
        zvm_raise(vm, EXECUTE, STACK_UNDERFLOW)
        return false;
    }

    value = vm->program.stack[(ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1) - vm->cpu.SP];
    vm->cpu.SP--;
    
    vm->cpu.R[left] = value;
    printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(inc)
    /* INC reg*/
    vm->cpu.R[left]++;
    printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(dec)
    /* DEC reg*/
    vm->cpu.R[left]--;
    printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(mul)
    vm->cpu.R[output] = vm->cpu.R[left] * vm->cpu.R[right];
    printf("MUL: R%u = %u\n", output, vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(div)
    if(vm->cpu.R[right] == 0) {
        zvm_raise(vm, EXECUTE, BAD_INSTRUCTION); 
        return false;
    }
    vm->cpu.R[output] = vm->cpu.R[left] / vm->cpu.R[right];
    printf("DIV: R%u = %u\n", output, vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(mod)
    if(vm->cpu.R[right] == 0) {
        zvm_raise(vm, EXECUTE, BAD_INSTRUCTION);
        return false;
    }
    vm->cpu.R[output] = vm->cpu.R[left] % vm->cpu.R[right];
    printf("MOD: R%u = %u\n", output, vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(and)
    vm->cpu.R[output] = vm->cpu.R[left] & vm->cpu.R[right];
    printf("AND: R%u = %u\n", output, vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(or)
    vm->cpu.R[output] = vm->cpu.R[left] | vm->cpu.R[right];
    printf("OR: R%u = %u\n", output, vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(xor)
    vm->cpu.R[output] = vm->cpu.R[left] ^ vm->cpu.R[right];
    printf("XOR: R%u = %u\n", output, vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(not)
    vm->cpu.R[left] = ~vm->cpu.R[left];
    printf("NOT: R%u = %u\n", left, vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(shl)
    vm->cpu.R[output] = vm->cpu.R[left] << vm->cpu.R[right];
    printf("SHL: R%u = %u\n", output, vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(shr)
    vm->cpu.R[output] = vm->cpu.R[left] >> vm->cpu.R[right];
    printf("SHR: R%u = %u\n", output, vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(cmp)
    if(vm->cpu.R[left] == vm->cpu.R[right]) vm->cpu.FLAGS = 1;      // Equal
    else if(vm->cpu.R[left] > vm->cpu.R[right]) vm->cpu.FLAGS = 2; // Greater
    else vm->cpu.FLAGS = 3;                                        // Less
    printf("CMP: FLAGS updated to %u\n", vm->cpu.FLAGS);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(jmp)
    vm->cpu.IP = left; 
    printf("JMP: Jumped to IP %u\n", vm->cpu.IP);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(je)
    if(vm->cpu.FLAGS == 1) {
        vm->cpu.IP = left;
        printf("JE: Jumped to IP %u\n", vm->cpu.IP);
    }
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(jne)
    if(vm->cpu.FLAGS != 1) {
        vm->cpu.IP = left;
        printf("JNE: Jumped to IP %u\n", vm->cpu.IP);
    }
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(jg)
    if(vm->cpu.FLAGS == 2) {
        vm->cpu.IP = left;
        printf("JG: Jumped to IP %u\n", vm->cpu.IP);
    }
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(jl)
    if(vm->cpu.FLAGS == 3) {
        vm->cpu.IP = left;
        printf("JL: Jumped to IP %u\n", vm->cpu.IP);
    }
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(jge)
    if(vm->cpu.FLAGS == 1 || vm->cpu.FLAGS == 2) {
        vm->cpu.IP = left;
        printf("JGE: Jumped to IP %u\n", vm->cpu.IP);
    }
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(jle)
    if(vm->cpu.FLAGS == 1 || vm->cpu.FLAGS == 3) {
        vm->cpu.IP = left;
        printf("JLE: Jumped to IP %u\n", vm->cpu.IP);
    }
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(call)
    if(vm->cpu.SP >= ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1) {
        zvm_raise(vm, EXECUTE, STACK_OVERFLOW);
        return false;
    }
    vm->cpu.SP++;
    vm->program.stack[(ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1) - vm->cpu.SP] = vm->cpu.IP;
    vm->cpu.IP = left;
    printf("CALL: Saved return address, jumped to IP %u\n", vm->cpu.IP);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(ret)
    if(vm->cpu.SP < 0) {
        zvm_raise(vm, EXECUTE, STACK_UNDERFLOW);
        return false;
    }
    uint8_t return_address = vm->program.stack[(ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1) - vm->cpu.SP];
    vm->cpu.SP--;
    vm->cpu.IP = return_address;
    printf("RET: Returned to IP %u\n", vm->cpu.IP);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(in)
    printf("IN: Enter an integer value for R%u from port %u: ", left, right);
    int input_val;
    if(scanf("%d", &input_val) == 1) {
        vm->cpu.R[left] = (uint8_t)input_val;
    } else {
        vm->cpu.R[left] = 0;
    }
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(out)
    printf("OUT: Port %u Output Data -> %u\n", left, vm->cpu.R[right]);
    vm->cpu.OUTPUT = vm->cpu.R[right];
ZVM_INSTRUCTION_HANDLER_FUNCTION_END