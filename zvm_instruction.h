#ifndef __ZVM_INSTRUCTION_H__
#define __ZVM_INSTRUCTION_H__
#include <stdint.h>
#include <stdbool.h>
#define ZVM_INSTRUCTION_MAX_OPCODE 255
#define zvm_is_valid_instruction(opcode) ((opcode) < ZVM_INSTRUCTION_HANDLERS_COUNT)

typedef struct zvm_vm_t zvm_vm_t;
typedef bool (*zfn_instruction_handler_t)(zvm_vm_t* vm, uint8_t, uint8_t, uint8_t);

typedef struct zvm_instruction_operand_t zvm_instruction_operand_t;
typedef struct zvm_instruction_t zvm_instruction_t;

typedef struct zvm_instruction_metadata_t zvm_instruction_metadata_t;
typedef struct zvm_operand_metadata_t zvm_operand_metadata_t;

#define ZVM_INSTRUCTION_HANDLER_FUNCTION_NAME(name)   zfnx_ ## name
#define ZVM_INSTRUCTION_HANDLER_FUNCTION_PARAM \
    zvm_vm_t* vm, uint8_t left, uint8_t right, uint8_t output

#define ZVM_INSTRUCTION_HANDLER_FUNCTION_ARGS \
    vm, left, right, output

#define ZVM_INSTRUCTION_HANDLER_FUNCTION(name)  \
    bool ZVM_INSTRUCTION_HANDLER_FUNCTION_NAME(name) (ZVM_INSTRUCTION_HANDLER_FUNCTION_PARAM)


#define ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(name) \
    ZVM_INSTRUCTION_HANDLER_FUNCTION(name) {

#define ZVM_INSTRUCTION_HANDLER_FUNCTION_END    \
        return true;                            \
    }

#define ZVM_INSTRUCTION_HANDLER_CALL(name) zfnx_ ## name(ZVM_INSTRUCTION_HANDLER_FUNCTION_ARGS)

#define ZVM_OPERAND_TYPE_REG 0
#define ZVM_OPERAND_TYPE_MEM 1
#define ZVM_OPERAND_TYPE_IMM 2

typedef struct zvm_operand_metadata_t {
    uint16_t type:2; /* ZVM_OPERAND_XXX */
}zvm_operand_metadata_t;

typedef struct zvm_instruction_operand_t{
    zvm_operand_metadata_t* metadata;
    uint8_t value;
}zvm_instruction_operand_t;

#define ZVM_INST_0_OP  0
#define ZVM_INST_1_OP  1
#define ZVM_INST_2_OP  2
#define ZVM_INST_3_OP  3

#define ZVM_INST_MAX_OPERANDS  3


/* instructions opcodes */
#define ZVM_OPCODE_ADD        0  /* ADD reg, reg, reg  */
#define ZVM_OPCODE_SUB        1  /* SUB reg, reg, reg  */
#define ZVM_OPCODE_LDI        2  /* LDI reg, imm       */
#define ZVM_OPCODE_STR        3  /* STR reg, mem       */
#define ZVM_OPCODE_LDM        4  /* LDM reg, mem       */
#define ZVM_OPCODE_LDA        5  /* LDA reg, reg       */
#define ZVM_OPCODE_STA        6  /* STA reg, reg       */
#define ZVM_OPCODE_PUSH       7  /* PUSH reg           */
#define ZVM_OPCODE_POP        8  /* POP reg            */
#define ZVM_OPCODE_INC        9  /* INC reg            */
#define ZVM_OPCODE_DEC        10 /* DEC reg            */
#define ZVM_OPCODE_MUL        11 /* MUL reg, reg, reg  */
#define ZVM_OPCODE_DIV        12 /* DIV reg, reg, reg  */
#define ZVM_OPCODE_MOD        13 /* MOD reg, reg, reg  */
#define ZVM_OPCODE_AND        14 /* AND reg, reg, reg  */
#define ZVM_OPCODE_OR         15 /* OR reg, reg, reg   */
#define ZVM_OPCODE_XOR        16 /* XOR reg, reg, reg  */
#define ZVM_OPCODE_NOT        17 /* NOT reg            */
#define ZVM_OPCODE_SHL        18 /* SHL reg, reg, reg  */
#define ZVM_OPCODE_SHR        19 /* SHR reg, reg, reg  */
#define ZVM_OPCODE_CMP        20 /* CMP reg, reg       */
#define ZVM_OPCODE_JMP        21 /* JMP imm            */
#define ZVM_OPCODE_JE         22 /* JE imm             */
#define ZVM_OPCODE_JNE        23 /* JNE imm            */
#define ZVM_OPCODE_JG         24 /* JG imm             */
#define ZVM_OPCODE_JL         25 /* JL imm             */
#define ZVM_OPCODE_JGE        26 /* JGE imm            */
#define ZVM_OPCODE_JLE        27 /* JLE imm            */
#define ZVM_OPCODE_CALL       28 /* CALL imm           */
#define ZVM_OPCODE_RET        29 /* RET                */
#define ZVM_OPCODE_IN         30 /* IN reg, imm (port) */
#define ZVM_OPCODE_OUT        31 /* OUT imm (port), reg*/


/* instructions handlers declarations */
ZVM_INSTRUCTION_HANDLER_FUNCTION(add);
ZVM_INSTRUCTION_HANDLER_FUNCTION(sub);
ZVM_INSTRUCTION_HANDLER_FUNCTION(ldi);
ZVM_INSTRUCTION_HANDLER_FUNCTION(str);
ZVM_INSTRUCTION_HANDLER_FUNCTION(ldm);
ZVM_INSTRUCTION_HANDLER_FUNCTION(lda);
ZVM_INSTRUCTION_HANDLER_FUNCTION(sta);

ZVM_INSTRUCTION_HANDLER_FUNCTION(push);
ZVM_INSTRUCTION_HANDLER_FUNCTION(pop);

ZVM_INSTRUCTION_HANDLER_FUNCTION(inc);
ZVM_INSTRUCTION_HANDLER_FUNCTION(dec);

ZVM_INSTRUCTION_HANDLER_FUNCTION(mul);
ZVM_INSTRUCTION_HANDLER_FUNCTION(div);
ZVM_INSTRUCTION_HANDLER_FUNCTION(mod);
ZVM_INSTRUCTION_HANDLER_FUNCTION(and);
ZVM_INSTRUCTION_HANDLER_FUNCTION(or);
ZVM_INSTRUCTION_HANDLER_FUNCTION(xor);
ZVM_INSTRUCTION_HANDLER_FUNCTION(not);
ZVM_INSTRUCTION_HANDLER_FUNCTION(shl);
ZVM_INSTRUCTION_HANDLER_FUNCTION(shr);
ZVM_INSTRUCTION_HANDLER_FUNCTION(cmp);
ZVM_INSTRUCTION_HANDLER_FUNCTION(jmp);
ZVM_INSTRUCTION_HANDLER_FUNCTION(je);
ZVM_INSTRUCTION_HANDLER_FUNCTION(jne);
ZVM_INSTRUCTION_HANDLER_FUNCTION(jg);
ZVM_INSTRUCTION_HANDLER_FUNCTION(jl);
ZVM_INSTRUCTION_HANDLER_FUNCTION(jge);
ZVM_INSTRUCTION_HANDLER_FUNCTION(jle);
ZVM_INSTRUCTION_HANDLER_FUNCTION(call);
ZVM_INSTRUCTION_HANDLER_FUNCTION(ret);
ZVM_INSTRUCTION_HANDLER_FUNCTION(in);
ZVM_INSTRUCTION_HANDLER_FUNCTION(out);


#define ZVM_INST_HANDLER_TYPE_RRR  0
#define ZVM_INST_HANDLER_TYPE_RI   1
#define ZVM_INST_HANDLER_TYPE_RM   2
#define ZVM_INST_HANDLER_TYPE_RR   3
#define ZVM_INST_HANDLER_TYPE_R    4
#define ZVM_INST_HANDLER_TYPE_I    5 


typedef struct zvm_instruction_handler_t zvm_instruction_handler_t;

struct zvm_instruction_handler_t{
    int8_t type;
    void *action;
};

typedef struct zvm_instruction_metadata_t{
    char *mnemonic;
    uint8_t opcode;
    uint8_t operands_count;
    zvm_operand_metadata_t operands[ZVM_INST_MAX_OPERANDS];
    zvm_instruction_handler_t handler;
}zvm_instruction_metadata_t;


#define ZVM_INSTRUCTION_HANDLER_ENTRY_BEGIN(name, argc) \
    [ZVM_OPCODE_ ## name] = {#name, ZVM_OPCODE_ ## name, ZVM_INST_ ## argc ## _OP, {

#define ZVM_INSTRUCTION_HANDLER_ENTRY_END(fn, type) \
    },{ZVM_INST_HANDLER_TYPE_ ## type, ZVM_INSTRUCTION_HANDLER_FUNCTION_NAME(fn)}},

#define ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(type) \
    {ZVM_OPERAND_TYPE_ ## type},

#define ZVM_INSTRUCTION_HANDLER_ENTRY_RRR(name, fn) \
     ZVM_INSTRUCTION_HANDLER_ENTRY_BEGIN(name, 3) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(REG) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(REG) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(REG) \
    ZVM_INSTRUCTION_HANDLER_ENTRY_END(fn, RRR)

#define ZVM_INSTRUCTION_HANDLER_ENTRY_RI(name, fn) \
     ZVM_INSTRUCTION_HANDLER_ENTRY_BEGIN(name, 2) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(REG) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(IMM) \
    ZVM_INSTRUCTION_HANDLER_ENTRY_END(fn, RI)

#define ZVM_INSTRUCTION_HANDLER_ENTRY_RM(name, fn) \
     ZVM_INSTRUCTION_HANDLER_ENTRY_BEGIN(name, 2) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(REG) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(MEM) \
    ZVM_INSTRUCTION_HANDLER_ENTRY_END(fn, RM)

#define ZVM_INSTRUCTION_HANDLER_ENTRY_RR(name, fn) \
     ZVM_INSTRUCTION_HANDLER_ENTRY_BEGIN(name, 2) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(REG) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(REG) \
    ZVM_INSTRUCTION_HANDLER_ENTRY_END(fn, RR)

#define ZVM_INSTRUCTION_HANDLER_ENTRY_R(name, fn) \
     ZVM_INSTRUCTION_HANDLER_ENTRY_BEGIN(name, 1) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(REG) \
    ZVM_INSTRUCTION_HANDLER_ENTRY_END(fn, R)

#define ZVM_INSTRUCTION_HANDLER_ENTRY_I(name, fn) \
     ZVM_INSTRUCTION_HANDLER_ENTRY_BEGIN(name, 1) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(IMM) \
    ZVM_INSTRUCTION_HANDLER_ENTRY_END(fn, I)


static const zvm_instruction_metadata_t instruction_handlers [ZVM_INSTRUCTION_MAX_OPCODE + 1] = {
    ZVM_INSTRUCTION_HANDLER_ENTRY_RRR(ADD, add)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RRR(SUB, sub)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RI(LDI, ldi)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RM(STR, str)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RM(LDM, ldm)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RR(LDA, lda)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RR(STA, sta)
    ZVM_INSTRUCTION_HANDLER_ENTRY_R(PUSH, push)
    ZVM_INSTRUCTION_HANDLER_ENTRY_R(POP, pop)
    ZVM_INSTRUCTION_HANDLER_ENTRY_R(INC, inc)
    ZVM_INSTRUCTION_HANDLER_ENTRY_R(DEC, dec)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RRR(MUL, mul)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RRR(DIV, div)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RRR(MOD, mod)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RRR(AND, and)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RRR(OR, or)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RRR(XOR, xor)
    ZVM_INSTRUCTION_HANDLER_ENTRY_R(NOT, not)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RRR(SHL, shl)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RRR(SHR, shr)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RR(CMP, cmp)
    ZVM_INSTRUCTION_HANDLER_ENTRY_I(JMP, jmp) 
    ZVM_INSTRUCTION_HANDLER_ENTRY_I(JE, je)
    ZVM_INSTRUCTION_HANDLER_ENTRY_I(JNE, jne)
    ZVM_INSTRUCTION_HANDLER_ENTRY_I(JG, jg)
    ZVM_INSTRUCTION_HANDLER_ENTRY_I(JL, jl)
    ZVM_INSTRUCTION_HANDLER_ENTRY_I(JGE, jge)
    ZVM_INSTRUCTION_HANDLER_ENTRY_I(JLE, jle)
    ZVM_INSTRUCTION_HANDLER_ENTRY_I(CALL, call)
    ZVM_INSTRUCTION_HANDLER_ENTRY_I(RET, ret)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RI(IN, in)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RI(OUT, out)
};

#define ZVM_INSTRUCTION_HANDLERS_COUNT (sizeof(instruction_handlers) / sizeof(zvm_instruction_metadata_t))

struct zvm_instruction_t {
    zvm_instruction_metadata_t *metadata;
    zvm_instruction_operand_t operands[ZVM_INST_MAX_OPERANDS];
};


#define zvm_has_next_instruction(vm) \
  ((vm)->cpu.IP < (vm)->program.instructions_count)

#define zvm_set_instruction(p, i, opcode, v1, v2, v3)\
    (p).instructions[(i)].metadata = (zvm_instruction_metadata_t*)&instruction_handlers[ZVM_OPCODE_ ## opcode];\
    (p).instructions[(i)].operands[0].metadata = (zvm_operand_metadata_t*)&instruction_handlers[ZVM_OPCODE_ ## opcode].operands[0];\
    (p).instructions[(i)].operands[1].metadata = (zvm_operand_metadata_t*)&instruction_handlers[ZVM_OPCODE_ ## opcode].operands[1];\
    (p).instructions[(i)].operands[2].metadata = (zvm_operand_metadata_t*)&instruction_handlers[ZVM_OPCODE_ ## opcode].operands[2];\
    (p).instructions[(i)].operands[0].value = (v1); \
    (p).instructions[(i)].operands[1].value = (v2); \
    (p).instructions[(i)].operands[2].value = (v3);

#define R0  0
#define R1  1
#define R2  2
#define R3  3

#define INST(p, opcode, v1, v2, v3) \
    zvm_set_instruction(p, ((p).instructions_count), opcode, v1, v2, v3) \
    (p).instructions_count++;


#define ADD(p, v1, v2, v3) INST(p, ADD, v1, v2, v3)
#define SUB(p, v1, v2, v3) INST(p, SUB, v1, v2, v3)
#define LDI(p, v1, v2) INST(p, LDI, v1, v2, 0)

#define LDM(p, v1, v2) INST(p, LDM, v1, v2, 0)
#define STR(p, v1, v2) INST(p, STR, v1, v2, 0)

#define LDA(p, v1, v2) INST(p, LDA, v1, v2, 0)
#define STA(p, v1, v2) INST(p, STA, v1, v2, 0)

#define PUSH(p, v1) INST(p, PUSH, v1, 0, 0)
#define POP(p, v1) INST(p, POP, v1, 0, 0)

#define INC(p, v1) INST(p, INC, v1, 0, 0)
#define DEC(p, v1) INST(p, DEC, v1, 0, 0)

#define MUL(p, v1, v2, v3) INST(p, MUL, v1, v2, v3)
#define DIV(p, v1, v2, v3) INST(p, DIV, v1, v2, v3)
#define MOD(p, v1, v2, v3) INST(p, MOD, v1, v2, v3)
#define AND(p, v1, v2, v3) INST(p, AND, v1, v2, v3)
#define OR(p, v1, v2, v3)  INST(p, OR, v1, v2, v3)
#define XOR(p, v1, v2, v3) INST(p, XOR, v1, v2, v3)
#define NOT(p, v1)         INST(p, NOT, v1, 0, 0)
#define SHL(p, v1, v2, v3) INST(p, SHL, v1, v2, v3)
#define SHR(p, v1, v2, v3) INST(p, SHR, v1, v2, v3)
#define CMP(p, v1, v2)     INST(p, CMP, v1, v2, 0)
#define JMP(p, v1)         INST(p, JMP, v1, 0, 0)
#define JE(p, v1)          INST(p, JE, v1, 0, 0)
#define JNE(p, v1)         INST(p, JNE, v1, 0, 0)
#define JG(p, v1)          INST(p, JG, v1, 0, 0)
#define JL(p, v1)          INST(p, JL, v1, 0, 0)
#define JGE(p, v1)         INST(p, JGE, v1, 0, 0)
#define JLE(p, v1)         INST(p, JLE, v1, 0, 0)
#define CALL(p, v1)        INST(p, CALL, v1, 0, 0)
#define RET(p)             INST(p, RET, 0, 0, 0)
#define IN_DEV(p, v1, v2)  INST(p, IN, v1, v2, 0)
#define OUT_DEV(p, v1, v2) INST(p, OUT, v1, v2, 0)

#endif