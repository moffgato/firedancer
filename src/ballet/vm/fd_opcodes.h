#ifndef HEADER_fd_src_ballet_runtime_vm_fd_opcodes_h
#define HEADER_fd_src_ballet_runtime_vm_fd_opcodes_h

struct fd_vm_sbpf_opcode_any {
  uchar op_class  : 3;
  uchar _unknown  : 5;
};
typedef struct fd_vm_sbpf_opcode_any fd_vm_sbpf_opcode_any_t;

struct fd_vm_sbpf_opcode_normal {
  uchar op_class  : 3;
  uchar op_src    : 1;
  uchar op_mode   : 4;
};
typedef struct fd_vm_sbpf_opcode_normal fd_vm_sbpf_opcode_normal_t;

struct fd_vm_sbpf_opcode_mem {
  uchar op_class       : 3;
  uchar op_size        : 2;
  uchar op_addr_mode   : 3;
};
typedef struct fd_vm_sbpf_opcode_mem fd_vm_sbpf_opcode_mem_t;

union fd_vm_sbpf_opcode {
  uchar raw;
  fd_vm_sbpf_opcode_any_t any;
  fd_vm_sbpf_opcode_normal_t normal;
  fd_vm_sbpf_opcode_mem_t mem;
};
typedef union fd_vm_sbpf_opcode fd_vm_sbpf_opcode_t;

struct fd_vm_sbpf_instr {
  fd_vm_sbpf_opcode_t opcode;
  uchar dst_reg : 4;
  uchar src_reg : 4;
  short offset;
  uint imm;
};
typedef struct fd_vm_sbpf_instr fd_vm_sbpf_instr_t;

/* Classes */
#define FD_BPF_OPCODE_CLASS_LD    (0b000)
#define FD_BPF_OPCODE_CLASS_LDX   (0b001)
#define FD_BPF_OPCODE_CLASS_ST    (0b010)
#define FD_BPF_OPCODE_CLASS_STX   (0b011)
#define FD_BPF_OPCODE_CLASS_ALU   (0b100)
#define FD_BPF_OPCODE_CLASS_JMP   (0b101)
#define FD_BPF_OPCODE_CLASS_JMP32 (0b110) /* eBPF only, in classic BPF this is RET */
#define FD_BPF_OPCODE_CLASS_ALU64 (0b111) /* eBPF only, in classic BPF this is MISC */

/* Source modes (only ALU, JMP, and ALU64 opcodes) */
#define FD_BPF_OPCODE_SOURCE_MODE_NO_SOURCE (0b0)
#define FD_BPF_OPCODE_SOURCE_MODE_UNARY_IMM (0b0)
#define FD_BPF_OPCODE_SOURCE_MODE_UNARY_REG (0b0)
#define FD_BPF_OPCODE_SOURCE_MODE_IMM       (0b0)
#define FD_BPF_OPCODE_SOURCE_MODE_REG       (0b1)

#define FD_BPF_OPCODE_END_MODE_HOST_TO_LE (0b0)
#define FD_BPF_OPCODE_END_MODE_HOST_TO_BE (0b1)

/* Size modes (only LD, LDX, ST, and STX opcodes) */
#define FD_BPF_OPCODE_SIZE_MODE_WORD (0b00)
#define FD_BPF_OPCODE_SIZE_MODE_HALF (0b01)
#define FD_BPF_OPCODE_SIZE_MODE_BYTE (0b10)
#define FD_BPF_OPCODE_SIZE_MODE_QUAD (0b11) /* eBPF only */

#define FD_BPF_OPCODE_ALU_OP_MODE_ADD   (0b0000)
#define FD_BPF_OPCODE_ALU_OP_MODE_SUB   (0b0001)
#define FD_BPF_OPCODE_ALU_OP_MODE_MUL   (0b0010)
#define FD_BPF_OPCODE_ALU_OP_MODE_DIV   (0b0011)
#define FD_BPF_OPCODE_ALU_OP_MODE_OR    (0b0100)
#define FD_BPF_OPCODE_ALU_OP_MODE_AND   (0b0101)
#define FD_BPF_OPCODE_ALU_OP_MODE_LSH   (0b0110)
#define FD_BPF_OPCODE_ALU_OP_MODE_RSH   (0b0111)
#define FD_BPF_OPCODE_ALU_OP_MODE_NEG   (0b1000)
#define FD_BPF_OPCODE_ALU_OP_MODE_MOD   (0b1001)
#define FD_BPF_OPCODE_ALU_OP_MODE_XOR   (0b1010)
#define FD_BPF_OPCODE_ALU_OP_MODE_MOV   (0b1011) /* eBPF only */
#define FD_BPF_OPCODE_ALU_OP_MODE_ARSH  (0b1100) /* eBPF only */
#define FD_BPF_OPCODE_ALU_OP_MODE_END   (0b1101) /* eBPF only */

#define FD_BPF_OPCODE_JMP_OP_MODE_JA    (0b0000) /* only for FD_BPF_OPCODE_CLASS_JMP */
#define FD_BPF_OPCODE_JMP_OP_MODE_JEQ   (0b0001)
#define FD_BPF_OPCODE_JMP_OP_MODE_JGT   (0b0010)
#define FD_BPF_OPCODE_JMP_OP_MODE_JGE   (0b0011)
#define FD_BPF_OPCODE_JMP_OP_MODE_JSET  (0b0100)
#define FD_BPF_OPCODE_JMP_OP_MODE_JNE   (0b0101) /* eBPF only */
#define FD_BPF_OPCODE_JMP_OP_MODE_JSGT  (0b0110) /* eBPF only */
#define FD_BPF_OPCODE_JMP_OP_MODE_JSGE  (0b0111) /* eBPF only */
#define FD_BPF_OPCODE_JMP_OP_MODE_CALL  (0b1000) /* eBPF only */
#define FD_BPF_OPCODE_JMP_OP_MODE_EXIT  (0b1001) /* eBPF only */
#define FD_BPF_OPCODE_JMP_OP_MODE_JLT   (0b1010) /* eBPF only */
#define FD_BPF_OPCODE_JMP_OP_MODE_JLE   (0b1011) /* eBPF only */
#define FD_BPF_OPCODE_JMP_OP_MODE_JSLT  (0b1100) /* eBPF only */
#define FD_BPF_OPCODE_JMP_OP_MODE_JSLE  (0b1101) /* eBPF only */

#define FD_BPF_OPCODE_ADDR_MODE_IMM   (0b000)
#define FD_BPF_OPCODE_ADDR_MODE_ABS   (0b001) /* kernel mode only */
#define FD_BPF_OPCODE_ADDR_MODE_IND   (0b010) /* kernel mode only */
#define FD_BPF_OPCODE_ADDR_MODE_MEM   (0b011)
#define FD_BPF_OPCODE_ADDR_MODE_LEN   (0b100) /* classic BPF only */
#define FD_BPF_OPCODE_ADDR_MODE_MSH   (0b101) /* classic BPF only */
#define FD_BPF_OPCODE_ADDR_MODE_XADD  (0b110) /* eBPF only */

#define FD_BPF_DEFINE_NORM_INSTR(cls,mode,src) ((cls) | (mode << 4) | (src << 3))
#define FD_BPF_DEFINE_MEM_INSTR(cls,addr_mode,sz) ((cls) | (addr_mode << 5) | (sz << 3))
/*
#define FD_BPF_OP_ADD_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_ADD,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_ADD_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_ADD,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_SUB_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_SUB,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_SUB_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_SUB,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_MUL_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_MUL,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_MUL_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_MUL,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_DIV_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_DIV_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_OR_IMM    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_OR,     FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_OR_REG    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_OR,     FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_AND_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_AND_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_LSH_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_LSH,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_LSH_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_LSH,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_RSH_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_RSH,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_RSH_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_RSH,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_NEG       FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_NEG,    FD_BPF_OPCODE_SOURCE_MODE_UNARY_REG)
#define FD_BPF_OP_MOD_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_MOD,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_MOD_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_MOD,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_MOD_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_MOD,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_MOD_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_MOD,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_MOV_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_MOV,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_MOV_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_MOV,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_ARSH_IMM  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_ARSH,   FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_ARSH_REG  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_ARSH,   FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_END_LE    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_END,    FD_BPF_OPCODE_END_MODE_HOST_TO_LE)
#define FD_BPF_OP_END_BE    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_END,    FD_BPF_OPCODE_END_MODE_HOST_TO_BE)

#define FD_BPF_OP_ADD64_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_ADD,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_ADD64_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_ADD,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_SUB64_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_SUB,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_SUB64_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_SUB,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_MUL64_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_MUL,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_MUL64_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_MUL,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_DIV64_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_DIV64_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_OR64_IMM    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_OR,     FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_OR64_REG    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_OR,     FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_AND64_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_AND64_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_LSH64_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_LSH,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_LSH64_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_LSH,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_RSH64_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_RSH,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_RSH64_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_RSH,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_NEG64       FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_NEG,    FD_BPF_OPCODE_SOURCE_MODE_UNARY_REG)
#define FD_BPF_OP_MOD64_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_MOD,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_MOD64_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_MOD,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_MOD64_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_MOD,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_MOD64_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_MOD,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_MOV64_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_MOV,    FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_MOV64_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_MOV,    FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_ARSH64_IMM  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_ARSH,   FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_ARSH64_REG  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_ARSH,   FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_END64_LE    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_END,    FD_BPF_OPCODE_END_MODE_HOST_TO_LE)
#define FD_BPF_OP_END64_BE    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_END,    FD_BPF_OPCODE_END_MODE_HOST_TO_BE)

#define FD_BPF_OP_JA        FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JA,   FD_BPF_OPCODE_SOURCE_MODE_UNARY_IMM) 
#define FD_BPF_OP_JEQ_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JEQ,  FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JEQ_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JEQ,  FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JGT_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGT,  FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JGT_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGT,  FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JGE_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGE,  FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JGE_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGE,  FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JSET_IMM  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSET, FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JSET_REG  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSET, FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JNE_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JNE,  FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JNE_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JNE,  FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JSGT_IMM  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGT, FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JSGT_REG  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGT, FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JSGE_IMM  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGE, FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JSGE_REG  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGE, FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_CALL_IMM  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_CALL, FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_EXIT_REG  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_EXIT, FD_BPF_OPCODE_SOURCE_MODE_NO_SOURCE)
#define FD_BPF_OP_JLT_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLT,  FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JLT_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLT,  FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JLE_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLE,  FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JLE_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLE,  FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JSLT_IMM  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLT, FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JSLT_REG  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLT, FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JSLE_IMM  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLE, FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JSLE_REG  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLE, FD_BPF_OPCODE_SOURCE_MODE_REG)

#define FD_BPF_OP_JEQ32_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JEQ,  FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JEQ32_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JEQ,  FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JGT32_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGT,  FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JGT32_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGT,  FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JGE32_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGE,  FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JGE32_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGE,  FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JSET32_IMM  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSET, FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JSET32_REG  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSET, FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JNE32_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JNE,  FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JNE32_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JNE,  FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JSGT32_IMM  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGT, FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JSGT32_REG  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGT, FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JSGE32_IMM  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGE, FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JSGE32_REG  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGE, FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JLT32_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLT,  FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JLT32_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLT,  FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JLE32_IMM   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLE,  FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JLE32_REG   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLE,  FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JSLT32_IMM  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLT, FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JSLT32_REG  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLT, FD_BPF_OPCODE_SOURCE_MODE_REG)
#define FD_BPF_OP_JSLE32_IMM  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLE, FD_BPF_OPCODE_SOURCE_MODE_IMM)
#define FD_BPF_OP_JSLE32_REG  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLE, FD_BPF_OPCODE_SOURCE_MODE_REG)

#define FD_BPF_OP_LDQ   FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_LD,   FD_BPF_OPCODE_ADDR_MODE_IMM,  FD_BPF_OPCODE_SIZE_MODE_QUAD)

#define FD_BPF_OP_LDXW  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_LDX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_WORD)
#define FD_BPF_OP_LDXH  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_LDX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_HALF)
#define FD_BPF_OP_LDXB  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_LDX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_BYTE)
#define FD_BPF_OP_LDXQ  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_LDX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_QUAD)

#define FD_BPF_OP_STW   FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_ST,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_WORD)
#define FD_BPF_OP_STH   FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_ST,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_HALF)
#define FD_BPF_OP_STB   FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_ST,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_BYTE)
#define FD_BPF_OP_STQ   FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_ST,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_QUAD)

#define FD_BPF_OP_STXW  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_STX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_WORD)
#define FD_BPF_OP_STXH  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_STX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_HALF)
#define FD_BPF_OP_STXB  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_STX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_BYTE)
#define FD_BPF_OP_STXQ  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_STX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_QUAD)

#define FD_BPF_OP_ADDL_IMM (0b00000000)
*/

static const uchar FD_BPF_OP_ADD_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_ADD,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_ADD_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_ADD,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_SUB_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_SUB,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_SUB_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_SUB,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_MUL_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_MUL,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_MUL_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_MUL,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_DIV_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_DIV_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_OR_IMM =    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_OR,     FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_OR_REG =    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_OR,     FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_AND_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_AND_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_LSH_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_LSH,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_LSH_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_LSH,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_RSH_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_RSH,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_RSH_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_RSH,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_NEG =       FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_NEG,    FD_BPF_OPCODE_SOURCE_MODE_UNARY_REG);
static const uchar FD_BPF_OP_MOD_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_MOD,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_MOD_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_MOD,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_XOR_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_XOR,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_XOR_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_XOR,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_MOV_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_MOV,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_MOV_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_MOV,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_ARSH_IMM =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_ARSH,   FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_ARSH_REG =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_ARSH,   FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_END_LE =    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_END,    FD_BPF_OPCODE_END_MODE_HOST_TO_LE);
static const uchar FD_BPF_OP_END_BE =    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU,   FD_BPF_OPCODE_ALU_OP_MODE_END,    FD_BPF_OPCODE_END_MODE_HOST_TO_BE);
;
static const uchar FD_BPF_OP_ADD64_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_ADD,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_ADD64_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_ADD,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_SUB64_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_SUB,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_SUB64_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_SUB,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_MUL64_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_MUL,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_MUL64_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_MUL,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_DIV64_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_DIV64_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_OR64_IMM =    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_OR,     FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_OR64_REG =    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_OR,     FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_AND64_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_AND64_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_DIV,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_LSH64_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_LSH,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_LSH64_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_LSH,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_RSH64_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_RSH,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_RSH64_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_RSH,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_NEG64 =       FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_NEG,    FD_BPF_OPCODE_SOURCE_MODE_UNARY_REG);
static const uchar FD_BPF_OP_MOD64_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_MOD,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_MOD64_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_MOD,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_XOR64_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_XOR,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_XOR64_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_XOR,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_MOV64_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_MOV,    FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_MOV64_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_MOV,    FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_ARSH64_IMM =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_ARSH,   FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_ARSH64_REG =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_ARSH,   FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_END64_LE =    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_END,    FD_BPF_OPCODE_END_MODE_HOST_TO_LE);
static const uchar FD_BPF_OP_END64_BE =    FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_ALU64,   FD_BPF_OPCODE_ALU_OP_MODE_END,    FD_BPF_OPCODE_END_MODE_HOST_TO_BE);
;
static const uchar FD_BPF_OP_JA =        FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JA,   FD_BPF_OPCODE_SOURCE_MODE_UNARY_IMM) ;
static const uchar FD_BPF_OP_JEQ_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JEQ,  FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JEQ_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JEQ,  FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JGT_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGT,  FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JGT_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGT,  FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JGE_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGE,  FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JGE_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGE,  FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JSET_IMM =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSET, FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JSET_REG =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSET, FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JNE_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JNE,  FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JNE_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JNE,  FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JSGT_IMM =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGT, FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JSGT_REG =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGT, FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JSGE_IMM =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGE, FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JSGE_REG =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGE, FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_CALL_IMM =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_CALL, FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_EXIT_REG =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_EXIT, FD_BPF_OPCODE_SOURCE_MODE_NO_SOURCE);
static const uchar FD_BPF_OP_JLT_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLT,  FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JLT_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLT,  FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JLE_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLE,  FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JLE_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLE,  FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JSLT_IMM =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLT, FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JSLT_REG =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLT, FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JSLE_IMM =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLE, FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JSLE_REG =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLE, FD_BPF_OPCODE_SOURCE_MODE_REG);
;
static const uchar FD_BPF_OP_JEQ32_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JEQ,  FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JEQ32_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JEQ,  FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JGT32_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGT,  FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JGT32_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGT,  FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JGE32_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGE,  FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JGE32_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JGE,  FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JSET32_IMM =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSET, FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JSET32_REG =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSET, FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JNE32_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JNE,  FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JNE32_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JNE,  FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JSGT32_IMM =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGT, FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JSGT32_REG =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGT, FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JSGE32_IMM =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGE, FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JSGE32_REG =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSGE, FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JLT32_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLT,  FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JLT32_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLT,  FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JLE32_IMM =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLE,  FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JLE32_REG =   FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JLE,  FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JSLT32_IMM =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLT, FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JSLT32_REG =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLT, FD_BPF_OPCODE_SOURCE_MODE_REG);
static const uchar FD_BPF_OP_JSLE32_IMM =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLE, FD_BPF_OPCODE_SOURCE_MODE_IMM);
static const uchar FD_BPF_OP_JSLE32_REG =  FD_BPF_DEFINE_NORM_INSTR(FD_BPF_OPCODE_CLASS_JMP, FD_BPF_OPCODE_JMP_OP_MODE_JSLE, FD_BPF_OPCODE_SOURCE_MODE_REG);
;
static const uchar FD_BPF_OP_LDQ =   FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_LD,   FD_BPF_OPCODE_ADDR_MODE_IMM,  FD_BPF_OPCODE_SIZE_MODE_QUAD);
;
static const uchar FD_BPF_OP_LDXW =  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_LDX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_WORD);
static const uchar FD_BPF_OP_LDXH =  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_LDX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_HALF);
static const uchar FD_BPF_OP_LDXB =  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_LDX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_BYTE);
static const uchar FD_BPF_OP_LDXQ =  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_LDX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_QUAD);
;
static const uchar FD_BPF_OP_STW =   FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_ST,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_WORD);
static const uchar FD_BPF_OP_STH =   FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_ST,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_HALF);
static const uchar FD_BPF_OP_STB =   FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_ST,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_BYTE);
static const uchar FD_BPF_OP_STQ =   FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_ST,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_QUAD);
;
static const uchar FD_BPF_OP_STXW =  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_STX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_WORD);
static const uchar FD_BPF_OP_STXH =  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_STX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_HALF);
static const uchar FD_BPF_OP_STXB =  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_STX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_BYTE);
static const uchar FD_BPF_OP_STXQ =  FD_BPF_DEFINE_MEM_INSTR(FD_BPF_OPCODE_CLASS_STX,  FD_BPF_OPCODE_ADDR_MODE_MEM,  FD_BPF_OPCODE_SIZE_MODE_QUAD);

static const uchar FD_BPF_OP_ADDL_IMM = (0b00000000);

#endif // HEADER_fd_src_ballet_runtime_vm_fd_opcodes_h
