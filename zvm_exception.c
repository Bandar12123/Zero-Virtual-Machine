#include <stdbool.h>
#include "zvm.h"
#include "zvm_exception.h"

bool zxpt_fetch(zvm_vm_t* vm, uint8_t code)              { return false; }
bool zxpt_decode(zvm_vm_t* vm, uint8_t code)             { return false; }
bool zxpt_execute(zvm_vm_t* vm, uint8_t code)            { return false; }
bool zxpt_invalid_register(zvm_vm_t* vm, uint8_t code)   { return false; }
bool zxpt_bad_instruction(zvm_vm_t* vm, uint8_t code)    { return false; }
bool zxpt_bad_memory_address(zvm_vm_t* vm, uint8_t code) { return false; }
bool zxpt_stack_overflow(zvm_vm_t* vm, uint8_t code)     { return false; }
bool zxpt_stack_underflow(zvm_vm_t* vm, uint8_t code)    { return false; }

const zvm_exception_entry_t exception_handlers [8] = {
    ZVM_EXCEPTION_HANDLER_ENTRY(FETCH,   FETCH,   fetch,   "fetch instruction error")
    ZVM_EXCEPTION_HANDLER_ENTRY(DECODE,  DECODE,  decode,  "decode instruction error")
    ZVM_EXCEPTION_HANDLER_ENTRY(EXECUTE, EXECUTE, execute, "execution: bad instruction error")
    ZVM_EXCEPTION_HANDLER_ENTRY(EXECUTE, INVALID_REGISTER, invalid_register, "invalid register")
    ZVM_EXCEPTION_HANDLER_ENTRY(DECODE,  BAD_INSTRUCTION,  bad_instruction,  "decoding: bad instruction error")
    ZVM_EXCEPTION_HANDLER_ENTRY(DECODE,  BAD_MEMORY_ADDRESS, bad_memory_address,  "decoding: bad memory address")
    ZVM_EXCEPTION_HANDLER_ENTRY(DECODE,  STACK_OVERFLOW, stack_overflow,  "stack overflow")
    ZVM_EXCEPTION_HANDLER_ENTRY(DECODE,  STACK_UNDERFLOW, stack_underflow, "stack underflow")
};