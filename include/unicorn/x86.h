/* Unicorn Emulator Engine */
/* By Nguyen Anh Quynh <aquynh@gmail.com>, 2015-2017 */
/* This file is released under LGPL2.
   See COPYING.LGPL2 in root directory for more details
*/

#ifndef UNICORN_X86_H
#define UNICORN_X86_H

#ifdef __cplusplus
extern "C" {
#endif

#include "platform.h"

typedef enum uc_cpu_x86 {
    UC_CPU_X86_QEMU64 = 0,
    UC_CPU_X86_PHENOM,
    UC_CPU_X86_CORE2DUO,
    UC_CPU_X86_KVM64,
    UC_CPU_X86_QEMU32,
    UC_CPU_X86_KVM32,
    UC_CPU_X86_COREDUO,
    UC_CPU_X86_486,
    UC_CPU_X86_PENTIUM,
    UC_CPU_X86_PENTIUM2,
    UC_CPU_X86_PENTIUM3,
    UC_CPU_X86_ATHLON,
    UC_CPU_X86_N270,
    UC_CPU_X86_CONROE,
    UC_CPU_X86_PENRYN,
    UC_CPU_X86_NEHALEM,
    UC_CPU_X86_WESTMERE,
    UC_CPU_X86_SANDYBRIDGE,
    UC_CPU_X86_IVYBRIDGE,
    UC_CPU_X86_HASWELL,
    UC_CPU_X86_BROADWELL,
    UC_CPU_X86_SKYLAKE_CLIENT,
    UC_CPU_X86_SKYLAKE_SERVER,
    UC_CPU_X86_CASCADELAKE_SERVER,
    UC_CPU_X86_COOPERLAKE,
    UC_CPU_X86_ICELAKE_CLIENT,
    UC_CPU_X86_ICELAKE_SERVER,
    UC_CPU_X86_DENVERTON,
    UC_CPU_X86_SNOWRIDGE,
    UC_CPU_X86_KNIGHTSMILL,
    UC_CPU_X86_OPTERON_G1,
    UC_CPU_X86_OPTERON_G2,
    UC_CPU_X86_OPTERON_G3,
    UC_CPU_X86_OPTERON_G4,
    UC_CPU_X86_OPTERON_G5,
    UC_CPU_X86_EPYC,
    UC_CPU_X86_DHYANA,
    UC_CPU_X86_EPYC_ROME
} uc_cpu_x86;

// Memory-Management Register for instructions IDTR, GDTR, LDTR, TR.
// Borrow from SegmentCache in qemu/target-i386/cpu.h
typedef struct uc_x86_mmr {
    uint16_t selector; /* not used by GDTR and IDTR */
    uint64_t base;     /* handle 32 or 64 bit CPUs */
    uint32_t limit;
    uint32_t flags; /* not used by GDTR and IDTR */
} uc_x86_mmr;

// Model-Specific Register structure, use this with UC_X86_REG_MSR (as the
// register ID) in call to uc_reg_write/uc_reg_read() to manipulate MSRs.
typedef struct uc_x86_msr {
    uint32_t rid;   // MSR id
    uint64_t value; // MSR value
} uc_x86_msr;

// Callback function for tracing SYSCALL/SYSENTER (for uc_hook_intr())
// @user_data: user data passed to tracing APIs.
typedef void (*uc_cb_insn_syscall_t)(struct uc_struct *uc, void *user_data);

//> X86 registers
typedef enum uc_x86_reg {
    UC_X86_REG_INVALID = 0,
    UC_X86_REG_AH,
    UC_X86_REG_AL,
    UC_X86_REG_AX,
    UC_X86_REG_BH,
    UC_X86_REG_BL,
    UC_X86_REG_BP,
    UC_X86_REG_BPL,
    UC_X86_REG_BX,
    UC_X86_REG_CH,
    UC_X86_REG_CL,
    UC_X86_REG_CS,
    UC_X86_REG_CX,
    UC_X86_REG_DH,
    UC_X86_REG_DI,
    UC_X86_REG_DIL,
    UC_X86_REG_DL,
    UC_X86_REG_DS,
    UC_X86_REG_DX,
    UC_X86_REG_EAX,
    UC_X86_REG_EBP,
    UC_X86_REG_EBX,
    UC_X86_REG_ECX,
    UC_X86_REG_EDI,
    UC_X86_REG_EDX,
    UC_X86_REG_EFLAGS,
    UC_X86_REG_EIP,
    UC_X86_REG_ES,
    UC_X86_REG_ESI,
    UC_X86_REG_ESP,
    UC_X86_REG_FPSW,
    UC_X86_REG_FS,
    UC_X86_REG_GS,
    UC_X86_REG_IP,
    UC_X86_REG_RAX,
    UC_X86_REG_RBP,
    UC_X86_REG_RBX,
    UC_X86_REG_RCX,
    UC_X86_REG_RDI,
    UC_X86_REG_RDX,
    UC_X86_REG_RIP,
    UC_X86_REG_RSI,
    UC_X86_REG_RSP,
    UC_X86_REG_SI,
    UC_X86_REG_SIL,
    UC_X86_REG_SP,
    UC_X86_REG_SPL,
    UC_X86_REG_SS,
    UC_X86_REG_CR0,
    UC_X86_REG_CR1,
    UC_X86_REG_CR2,
    UC_X86_REG_CR3,
    UC_X86_REG_CR4,
    UC_X86_REG_CR8,
    UC_X86_REG_DR0,
    UC_X86_REG_DR1,
    UC_X86_REG_DR2,
    UC_X86_REG_DR3,
    UC_X86_REG_DR4,
    UC_X86_REG_DR5,
    UC_X86_REG_DR6,
    UC_X86_REG_DR7,
    UC_X86_REG_FP0,
    UC_X86_REG_FP1,
    UC_X86_REG_FP2,
    UC_X86_REG_FP3,
    UC_X86_REG_FP4,
    UC_X86_REG_FP5,
    UC_X86_REG_FP6,
    UC_X86_REG_FP7,
    UC_X86_REG_K0,
    UC_X86_REG_K1,
    UC_X86_REG_K2,
    UC_X86_REG_K3,
    UC_X86_REG_K4,
    UC_X86_REG_K5,
    UC_X86_REG_K6,
    UC_X86_REG_K7,
    UC_X86_REG_MM0,
    UC_X86_REG_MM1,
    UC_X86_REG_MM2,
    UC_X86_REG_MM3,
    UC_X86_REG_MM4,
    UC_X86_REG_MM5,
    UC_X86_REG_MM6,
    UC_X86_REG_MM7,
    UC_X86_REG_R8,
    UC_X86_REG_R9,
    UC_X86_REG_R10,
    UC_X86_REG_R11,
    UC_X86_REG_R12,
    UC_X86_REG_R13,
    UC_X86_REG_R14,
    UC_X86_REG_R15,
    UC_X86_REG_ST0,
    UC_X86_REG_ST1,
    UC_X86_REG_ST2,
    UC_X86_REG_ST3,
    UC_X86_REG_ST4,
    UC_X86_REG_ST5,
    UC_X86_REG_ST6,
    UC_X86_REG_ST7,
    UC_X86_REG_XMM0,
    UC_X86_REG_XMM1,
    UC_X86_REG_XMM2,
    UC_X86_REG_XMM3,
    UC_X86_REG_XMM4,
    UC_X86_REG_XMM5,
    UC_X86_REG_XMM6,
    UC_X86_REG_XMM7,
    UC_X86_REG_XMM8,
    UC_X86_REG_XMM9,
    UC_X86_REG_XMM10,
    UC_X86_REG_XMM11,
    UC_X86_REG_XMM12,
    UC_X86_REG_XMM13,
    UC_X86_REG_XMM14,
    UC_X86_REG_XMM15,
    UC_X86_REG_XMM16,
    UC_X86_REG_XMM17,
    UC_X86_REG_XMM18,
    UC_X86_REG_XMM19,
    UC_X86_REG_XMM20,
    UC_X86_REG_XMM21,
    UC_X86_REG_XMM22,
    UC_X86_REG_XMM23,
    UC_X86_REG_XMM24,
    UC_X86_REG_XMM25,
    UC_X86_REG_XMM26,
    UC_X86_REG_XMM27,
    UC_X86_REG_XMM28,
    UC_X86_REG_XMM29,
    UC_X86_REG_XMM30,
    UC_X86_REG_XMM31,
    UC_X86_REG_YMM0,
    UC_X86_REG_YMM1,
    UC_X86_REG_YMM2,
    UC_X86_REG_YMM3,
    UC_X86_REG_YMM4,
    UC_X86_REG_YMM5,
    UC_X86_REG_YMM6,
    UC_X86_REG_YMM7,
    UC_X86_REG_YMM8,
    UC_X86_REG_YMM9,
    UC_X86_REG_YMM10,
    UC_X86_REG_YMM11,
    UC_X86_REG_YMM12,
    UC_X86_REG_YMM13,
    UC_X86_REG_YMM14,
    UC_X86_REG_YMM15,
    UC_X86_REG_YMM16,
    UC_X86_REG_YMM17,
    UC_X86_REG_YMM18,
    UC_X86_REG_YMM19,
    UC_X86_REG_YMM20,
    UC_X86_REG_YMM21,
    UC_X86_REG_YMM22,
    UC_X86_REG_YMM23,
    UC_X86_REG_YMM24,
    UC_X86_REG_YMM25,
    UC_X86_REG_YMM26,
    UC_X86_REG_YMM27,
    UC_X86_REG_YMM28,
    UC_X86_REG_YMM29,
    UC_X86_REG_YMM30,
    UC_X86_REG_YMM31,
    UC_X86_REG_ZMM0,
    UC_X86_REG_ZMM1,
    UC_X86_REG_ZMM2,
    UC_X86_REG_ZMM3,
    UC_X86_REG_ZMM4,
    UC_X86_REG_ZMM5,
    UC_X86_REG_ZMM6,
    UC_X86_REG_ZMM7,
    UC_X86_REG_ZMM8,
    UC_X86_REG_ZMM9,
    UC_X86_REG_ZMM10,
    UC_X86_REG_ZMM11,
    UC_X86_REG_ZMM12,
    UC_X86_REG_ZMM13,
    UC_X86_REG_ZMM14,
    UC_X86_REG_ZMM15,
    UC_X86_REG_ZMM16,
    UC_X86_REG_ZMM17,
    UC_X86_REG_ZMM18,
    UC_X86_REG_ZMM19,
    UC_X86_REG_ZMM20,
    UC_X86_REG_ZMM21,
    UC_X86_REG_ZMM22,
    UC_X86_REG_ZMM23,
    UC_X86_REG_ZMM24,
    UC_X86_REG_ZMM25,
    UC_X86_REG_ZMM26,
    UC_X86_REG_ZMM27,
    UC_X86_REG_ZMM28,
    UC_X86_REG_ZMM29,
    UC_X86_REG_ZMM30,
    UC_X86_REG_ZMM31,
    UC_X86_REG_R8B,
    UC_X86_REG_R9B,
    UC_X86_REG_R10B,
    UC_X86_REG_R11B,
    UC_X86_REG_R12B,
    UC_X86_REG_R13B,
    UC_X86_REG_R14B,
    UC_X86_REG_R15B,
    UC_X86_REG_R8D,
    UC_X86_REG_R9D,
    UC_X86_REG_R10D,
    UC_X86_REG_R11D,
    UC_X86_REG_R12D,
    UC_X86_REG_R13D,
    UC_X86_REG_R14D,
    UC_X86_REG_R15D,
    UC_X86_REG_R8W,
    UC_X86_REG_R9W,
    UC_X86_REG_R10W,
    UC_X86_REG_R11W,
    UC_X86_REG_R12W,
    UC_X86_REG_R13W,
    UC_X86_REG_R14W,
    UC_X86_REG_R15W,
    UC_X86_REG_IDTR,
    UC_X86_REG_GDTR,
    UC_X86_REG_LDTR,
    UC_X86_REG_TR,
    UC_X86_REG_FPCW,
    UC_X86_REG_FPTAG,
    UC_X86_REG_MSR, // Model-Specific Register
    UC_X86_REG_MXCSR,
    UC_X86_REG_FS_BASE, // Base regs for x86_64
    UC_X86_REG_GS_BASE,
    UC_X86_REG_FLAGS,
    UC_X86_REG_RFLAGS,
    UC_X86_REG_ENDING // <-- mark the end of the list of registers
} uc_x86_reg;

//> X86 instructions
typedef enum uc_x86_insn {
    UC_X86_INS_INVALID = 0,

    UC_X86_INS_AAA,
    UC_X86_INS_AAD,
    UC_X86_INS_AAM,
    UC_X86_INS_AAS,
    UC_X86_INS_FABS,
    UC_X86_INS_ADC,
    UC_X86_INS_ADCX,
    UC_X86_INS_ADD,
    UC_X86_INS_ADDPD,
    UC_X86_INS_ADDPS,
    UC_X86_INS_ADDSD,
    UC_X86_INS_ADDSS,
    UC_X86_INS_ADDSUBPD,
    UC_X86_INS_ADDSUBPS,
    UC_X86_INS_FADD,
    UC_X86_INS_FIADD,
    UC_X86_INS_FADDP,
    UC_X86_INS_ADOX,
    UC_X86_INS_AESDECLAST,
    UC_X86_INS_AESDEC,
    UC_X86_INS_AESENCLAST,
    UC_X86_INS_AESENC,
    UC_X86_INS_AESIMC,
    UC_X86_INS_AESKEYGENASSIST,
    UC_X86_INS_AND,
    UC_X86_INS_ANDN,
    UC_X86_INS_ANDNPD,
    UC_X86_INS_ANDNPS,
    UC_X86_INS_ANDPD,
    UC_X86_INS_ANDPS,
    UC_X86_INS_ARPL,
    UC_X86_INS_BEXTR,
    UC_X86_INS_BLCFILL,
    UC_X86_INS_BLCI,
    UC_X86_INS_BLCIC,
    UC_X86_INS_BLCMSK,
    UC_X86_INS_BLCS,
    UC_X86_INS_BLENDPD,
    UC_X86_INS_BLENDPS,
    UC_X86_INS_BLENDVPD,
    UC_X86_INS_BLENDVPS,
    UC_X86_INS_BLSFILL,
    UC_X86_INS_BLSI,
    UC_X86_INS_BLSIC,
    UC_X86_INS_BLSMSK,
    UC_X86_INS_BLSR,
    UC_X86_INS_BOUND,
    UC_X86_INS_BSF,
    UC_X86_INS_BSR,
    UC_X86_INS_BSWAP,
    UC_X86_INS_BT,
    UC_X86_INS_BTC,
    UC_X86_INS_BTR,
    UC_X86_INS_BTS,
    UC_X86_INS_BZHI,
    UC_X86_INS_CALL,
    UC_X86_INS_CBW,
    UC_X86_INS_CDQ,
    UC_X86_INS_CDQE,
    UC_X86_INS_FCHS,
    UC_X86_INS_CLAC,
    UC_X86_INS_CLC,
    UC_X86_INS_CLD,
    UC_X86_INS_CLFLUSH,
    UC_X86_INS_CLFLUSHOPT,
    UC_X86_INS_CLGI,
    UC_X86_INS_CLI,
    UC_X86_INS_CLTS,
    UC_X86_INS_CLWB,
    UC_X86_INS_CMC,
    UC_X86_INS_CMOVA,
    UC_X86_INS_CMOVAE,
    UC_X86_INS_CMOVB,
    UC_X86_INS_CMOVBE,
    UC_X86_INS_FCMOVBE,
    UC_X86_INS_FCMOVB,
    UC_X86_INS_CMOVE,
    UC_X86_INS_FCMOVE,
    UC_X86_INS_CMOVG,
    UC_X86_INS_CMOVGE,
    UC_X86_INS_CMOVL,
    UC_X86_INS_CMOVLE,
    UC_X86_INS_FCMOVNBE,
    UC_X86_INS_FCMOVNB,
    UC_X86_INS_CMOVNE,
    UC_X86_INS_FCMOVNE,
    UC_X86_INS_CMOVNO,
    UC_X86_INS_CMOVNP,
    UC_X86_INS_FCMOVNU,
    UC_X86_INS_CMOVNS,
    UC_X86_INS_CMOVO,
    UC_X86_INS_CMOVP,
    UC_X86_INS_FCMOVU,
    UC_X86_INS_CMOVS,
    UC_X86_INS_CMP,
    UC_X86_INS_CMPPD,
    UC_X86_INS_CMPPS,
    UC_X86_INS_CMPSB,
    UC_X86_INS_CMPSD,
    UC_X86_INS_CMPSQ,
    UC_X86_INS_CMPSS,
    UC_X86_INS_CMPSW,
    UC_X86_INS_CMPXCHG16B,
    UC_X86_INS_CMPXCHG,
    UC_X86_INS_CMPXCHG8B,
    UC_X86_INS_COMISD,
    UC_X86_INS_COMISS,
    UC_X86_INS_FCOMP,
    UC_X86_INS_FCOMPI,
    UC_X86_INS_FCOMI,
    UC_X86_INS_FCOM,
    UC_X86_INS_FCOS,
    UC_X86_INS_CPUID,
    UC_X86_INS_CQO,
    UC_X86_INS_CRC32,
    UC_X86_INS_CVTDQ2PD,
    UC_X86_INS_CVTDQ2PS,
    UC_X86_INS_CVTPD2DQ,
    UC_X86_INS_CVTPD2PS,
    UC_X86_INS_CVTPS2DQ,
    UC_X86_INS_CVTPS2PD,
    UC_X86_INS_CVTSD2SI,
    UC_X86_INS_CVTSD2SS,
    UC_X86_INS_CVTSI2SD,
    UC_X86_INS_CVTSI2SS,
    UC_X86_INS_CVTSS2SD,
    UC_X86_INS_CVTSS2SI,
    UC_X86_INS_CVTTPD2DQ,
    UC_X86_INS_CVTTPS2DQ,
    UC_X86_INS_CVTTSD2SI,
    UC_X86_INS_CVTTSS2SI,
    UC_X86_INS_CWD,
    UC_X86_INS_CWDE,
    UC_X86_INS_DAA,
    UC_X86_INS_DAS,
    UC_X86_INS_DATA16,
    UC_X86_INS_DEC,
    UC_X86_INS_DIV,
    UC_X86_INS_DIVPD,
    UC_X86_INS_DIVPS,
    UC_X86_INS_FDIVR,
    UC_X86_INS_FIDIVR,
    UC_X86_INS_FDIVRP,
    UC_X86_INS_DIVSD,
    UC_X86_INS_DIVSS,
    UC_X86_INS_FDIV,
    UC_X86_INS_FIDIV,
    UC_X86_INS_FDIVP,
    UC_X86_INS_DPPD,
    UC_X86_INS_DPPS,
    UC_X86_INS_RET,
    UC_X86_INS_ENCLS,
    UC_X86_INS_ENCLU,
    UC_X86_INS_ENTER,
    UC_X86_INS_EXTRACTPS,
    UC_X86_INS_EXTRQ,
    UC_X86_INS_F2XM1,
    UC_X86_INS_LCALL,
    UC_X86_INS_LJMP,
    UC_X86_INS_FBLD,
    UC_X86_INS_FBSTP,
    UC_X86_INS_FCOMPP,
    UC_X86_INS_FDECSTP,
    UC_X86_INS_FEMMS,
    UC_X86_INS_FFREE,
    UC_X86_INS_FICOM,
    UC_X86_INS_FICOMP,
    UC_X86_INS_FINCSTP,
    UC_X86_INS_FLDCW,
    UC_X86_INS_FLDENV,
    UC_X86_INS_FLDL2E,
    UC_X86_INS_FLDL2T,
    UC_X86_INS_FLDLG2,
    UC_X86_INS_FLDLN2,
    UC_X86_INS_FLDPI,
    UC_X86_INS_FNCLEX,
    UC_X86_INS_FNINIT,
    UC_X86_INS_FNOP,
    UC_X86_INS_FNSTCW,
    UC_X86_INS_FNSTSW,
    UC_X86_INS_FPATAN,
    UC_X86_INS_FPREM,
    UC_X86_INS_FPREM1,
    UC_X86_INS_FPTAN,
    UC_X86_INS_FFREEP,
    UC_X86_INS_FRNDINT,
    UC_X86_INS_FRSTOR,
    UC_X86_INS_FNSAVE,
    UC_X86_INS_FSCALE,
    UC_X86_INS_FSETPM,
    UC_X86_INS_FSINCOS,
    UC_X86_INS_FNSTENV,
    UC_X86_INS_FXAM,
    UC_X86_INS_FXRSTOR,
    UC_X86_INS_FXRSTOR64,
    UC_X86_INS_FXSAVE,
    UC_X86_INS_FXSAVE64,
    UC_X86_INS_FXTRACT,
    UC_X86_INS_FYL2X,
    UC_X86_INS_FYL2XP1,
    UC_X86_INS_MOVAPD,
    UC_X86_INS_MOVAPS,
    UC_X86_INS_ORPD,
    UC_X86_INS_ORPS,
    UC_X86_INS_VMOVAPD,
    UC_X86_INS_VMOVAPS,
    UC_X86_INS_XORPD,
    UC_X86_INS_XORPS,
    UC_X86_INS_GETSEC,
    UC_X86_INS_HADDPD,
    UC_X86_INS_HADDPS,
    UC_X86_INS_HLT,
    UC_X86_INS_HSUBPD,
    UC_X86_INS_HSUBPS,
    UC_X86_INS_IDIV,
    UC_X86_INS_FILD,
    UC_X86_INS_IMUL,
    UC_X86_INS_IN,
    UC_X86_INS_INC,
    UC_X86_INS_INSB,
    UC_X86_INS_INSERTPS,
    UC_X86_INS_INSERTQ,
    UC_X86_INS_INSD,
    UC_X86_INS_INSW,
    UC_X86_INS_INT,
    UC_X86_INS_INT1,
    UC_X86_INS_INT3,
    UC_X86_INS_INTO,
    UC_X86_INS_INVD,
    UC_X86_INS_INVEPT,
    UC_X86_INS_INVLPG,
    UC_X86_INS_INVLPGA,
    UC_X86_INS_INVPCID,
    UC_X86_INS_INVVPID,
    UC_X86_INS_IRET,
    UC_X86_INS_IRETD,
    UC_X86_INS_IRETQ,
    UC_X86_INS_FISTTP,
    UC_X86_INS_FIST,
    UC_X86_INS_FISTP,
    UC_X86_INS_UCOMISD,
    UC_X86_INS_UCOMISS,
    UC_X86_INS_VCOMISD,
    UC_X86_INS_VCOMISS,
    UC_X86_INS_VCVTSD2SS,
    UC_X86_INS_VCVTSI2SD,
    UC_X86_INS_VCVTSI2SS,
    UC_X86_INS_VCVTSS2SD,
    UC_X86_INS_VCVTTSD2SI,
    UC_X86_INS_VCVTTSD2USI,
    UC_X86_INS_VCVTTSS2SI,
    UC_X86_INS_VCVTTSS2USI,
    UC_X86_INS_VCVTUSI2SD,
    UC_X86_INS_VCVTUSI2SS,
    UC_X86_INS_VUCOMISD,
    UC_X86_INS_VUCOMISS,
    UC_X86_INS_JAE,
    UC_X86_INS_JA,
    UC_X86_INS_JBE,
    UC_X86_INS_JB,
    UC_X86_INS_JCXZ,
    UC_X86_INS_JECXZ,
    UC_X86_INS_JE,
    UC_X86_INS_JGE,
    UC_X86_INS_JG,
    UC_X86_INS_JLE,
    UC_X86_INS_JL,
    UC_X86_INS_JMP,
    UC_X86_INS_JNE,
    UC_X86_INS_JNO,
    UC_X86_INS_JNP,
    UC_X86_INS_JNS,
    UC_X86_INS_JO,
    UC_X86_INS_JP,
    UC_X86_INS_JRCXZ,
    UC_X86_INS_JS,
    UC_X86_INS_KANDB,
    UC_X86_INS_KANDD,
    UC_X86_INS_KANDNB,
    UC_X86_INS_KANDND,
    UC_X86_INS_KANDNQ,
    UC_X86_INS_KANDNW,
    UC_X86_INS_KANDQ,
    UC_X86_INS_KANDW,
    UC_X86_INS_KMOVB,
    UC_X86_INS_KMOVD,
    UC_X86_INS_KMOVQ,
    UC_X86_INS_KMOVW,
    UC_X86_INS_KNOTB,
    UC_X86_INS_KNOTD,
    UC_X86_INS_KNOTQ,
    UC_X86_INS_KNOTW,
    UC_X86_INS_KORB,
    UC_X86_INS_KORD,
    UC_X86_INS_KORQ,
    UC_X86_INS_KORTESTB,
    UC_X86_INS_KORTESTD,
    UC_X86_INS_KORTESTQ,
    UC_X86_INS_KORTESTW,
    UC_X86_INS_KORW,
    UC_X86_INS_KSHIFTLB,
    UC_X86_INS_KSHIFTLD,
    UC_X86_INS_KSHIFTLQ,
    UC_X86_INS_KSHIFTLW,
    UC_X86_INS_KSHIFTRB,
    UC_X86_INS_KSHIFTRD,
    UC_X86_INS_KSHIFTRQ,
    UC_X86_INS_KSHIFTRW,
    UC_X86_INS_KUNPCKBW,
    UC_X86_INS_KXNORB,
    UC_X86_INS_KXNORD,
    UC_X86_INS_KXNORQ,
    UC_X86_INS_KXNORW,
    UC_X86_INS_KXORB,
    UC_X86_INS_KXORD,
    UC_X86_INS_KXORQ,
    UC_X86_INS_KXORW,
    UC_X86_INS_LAHF,
    UC_X86_INS_LAR,
    UC_X86_INS_LDDQU,
    UC_X86_INS_LDMXCSR,
    UC_X86_INS_LDS,
    UC_X86_INS_FLDZ,
    UC_X86_INS_FLD1,
    UC_X86_INS_FLD,
    UC_X86_INS_LEA,
    UC_X86_INS_LEAVE,
    UC_X86_INS_LES,
    UC_X86_INS_LFENCE,
    UC_X86_INS_LFS,
    UC_X86_INS_LGDT,
    UC_X86_INS_LGS,
    UC_X86_INS_LIDT,
    UC_X86_INS_LLDT,
    UC_X86_INS_LMSW,
    UC_X86_INS_OR,
    UC_X86_INS_SUB,
    UC_X86_INS_XOR,
    UC_X86_INS_LODSB,
    UC_X86_INS_LODSD,
    UC_X86_INS_LODSQ,
    UC_X86_INS_LODSW,
    UC_X86_INS_LOOP,
    UC_X86_INS_LOOPE,
    UC_X86_INS_LOOPNE,
    UC_X86_INS_RETF,
    UC_X86_INS_RETFQ,
    UC_X86_INS_LSL,
    UC_X86_INS_LSS,
    UC_X86_INS_LTR,
    UC_X86_INS_XADD,
    UC_X86_INS_LZCNT,
    UC_X86_INS_MASKMOVDQU,
    UC_X86_INS_MAXPD,
    UC_X86_INS_MAXPS,
    UC_X86_INS_MAXSD,
    UC_X86_INS_MAXSS,
    UC_X86_INS_MFENCE,
    UC_X86_INS_MINPD,
    UC_X86_INS_MINPS,
    UC_X86_INS_MINSD,
    UC_X86_INS_MINSS,
    UC_X86_INS_CVTPD2PI,
    UC_X86_INS_CVTPI2PD,
    UC_X86_INS_CVTPI2PS,
    UC_X86_INS_CVTPS2PI,
    UC_X86_INS_CVTTPD2PI,
    UC_X86_INS_CVTTPS2PI,
    UC_X86_INS_EMMS,
    UC_X86_INS_MASKMOVQ,
    UC_X86_INS_MOVD,
    UC_X86_INS_MOVDQ2Q,
    UC_X86_INS_MOVNTQ,
    UC_X86_INS_MOVQ2DQ,
    UC_X86_INS_MOVQ,
    UC_X86_INS_PABSB,
    UC_X86_INS_PABSD,
    UC_X86_INS_PABSW,
    UC_X86_INS_PACKSSDW,
    UC_X86_INS_PACKSSWB,
    UC_X86_INS_PACKUSWB,
    UC_X86_INS_PADDB,
    UC_X86_INS_PADDD,
    UC_X86_INS_PADDQ,
    UC_X86_INS_PADDSB,
    UC_X86_INS_PADDSW,
    UC_X86_INS_PADDUSB,
    UC_X86_INS_PADDUSW,
    UC_X86_INS_PADDW,
    UC_X86_INS_PALIGNR,
    UC_X86_INS_PANDN,
    UC_X86_INS_PAND,
    UC_X86_INS_PAVGB,
    UC_X86_INS_PAVGW,
    UC_X86_INS_PCMPEQB,
    UC_X86_INS_PCMPEQD,
    UC_X86_INS_PCMPEQW,
    UC_X86_INS_PCMPGTB,
    UC_X86_INS_PCMPGTD,
    UC_X86_INS_PCMPGTW,
    UC_X86_INS_PEXTRW,
    UC_X86_INS_PHADDSW,
    UC_X86_INS_PHADDW,
    UC_X86_INS_PHADDD,
    UC_X86_INS_PHSUBD,
    UC_X86_INS_PHSUBSW,
    UC_X86_INS_PHSUBW,
    UC_X86_INS_PINSRW,
    UC_X86_INS_PMADDUBSW,
    UC_X86_INS_PMADDWD,
    UC_X86_INS_PMAXSW,
    UC_X86_INS_PMAXUB,
    UC_X86_INS_PMINSW,
    UC_X86_INS_PMINUB,
    UC_X86_INS_PMOVMSKB,
    UC_X86_INS_PMULHRSW,
    UC_X86_INS_PMULHUW,
    UC_X86_INS_PMULHW,
    UC_X86_INS_PMULLW,
    UC_X86_INS_PMULUDQ,
    UC_X86_INS_POR,
    UC_X86_INS_PSADBW,
    UC_X86_INS_PSHUFB,
    UC_X86_INS_PSHUFW,
    UC_X86_INS_PSIGNB,
    UC_X86_INS_PSIGND,
    UC_X86_INS_PSIGNW,
    UC_X86_INS_PSLLD,
    UC_X86_INS_PSLLQ,
    UC_X86_INS_PSLLW,
    UC_X86_INS_PSRAD,
    UC_X86_INS_PSRAW,
    UC_X86_INS_PSRLD,
    UC_X86_INS_PSRLQ,
    UC_X86_INS_PSRLW,
    UC_X86_INS_PSUBB,
    UC_X86_INS_PSUBD,
    UC_X86_INS_PSUBQ,
    UC_X86_INS_PSUBSB,
    UC_X86_INS_PSUBSW,
    UC_X86_INS_PSUBUSB,
    UC_X86_INS_PSUBUSW,
    UC_X86_INS_PSUBW,
    UC_X86_INS_PUNPCKHBW,
    UC_X86_INS_PUNPCKHDQ,
    UC_X86_INS_PUNPCKHWD,
    UC_X86_INS_PUNPCKLBW,
    UC_X86_INS_PUNPCKLDQ,
    UC_X86_INS_PUNPCKLWD,
    UC_X86_INS_PXOR,
    UC_X86_INS_MONITOR,
    UC_X86_INS_MONTMUL,
    UC_X86_INS_MOV,
    UC_X86_INS_MOVABS,
    UC_X86_INS_MOVBE,
    UC_X86_INS_MOVDDUP,
    UC_X86_INS_MOVDQA,
    UC_X86_INS_MOVDQU,
    UC_X86_INS_MOVHLPS,
    UC_X86_INS_MOVHPD,
    UC_X86_INS_MOVHPS,
    UC_X86_INS_MOVLHPS,
    UC_X86_INS_MOVLPD,
    UC_X86_INS_MOVLPS,
    UC_X86_INS_MOVMSKPD,
    UC_X86_INS_MOVMSKPS,
    UC_X86_INS_MOVNTDQA,
    UC_X86_INS_MOVNTDQ,
    UC_X86_INS_MOVNTI,
    UC_X86_INS_MOVNTPD,
    UC_X86_INS_MOVNTPS,
    UC_X86_INS_MOVNTSD,
    UC_X86_INS_MOVNTSS,
    UC_X86_INS_MOVSB,
    UC_X86_INS_MOVSD,
    UC_X86_INS_MOVSHDUP,
    UC_X86_INS_MOVSLDUP,
    UC_X86_INS_MOVSQ,
    UC_X86_INS_MOVSS,
    UC_X86_INS_MOVSW,
    UC_X86_INS_MOVSX,
    UC_X86_INS_MOVSXD,
    UC_X86_INS_MOVUPD,
    UC_X86_INS_MOVUPS,
    UC_X86_INS_MOVZX,
    UC_X86_INS_MPSADBW,
    UC_X86_INS_MUL,
    UC_X86_INS_MULPD,
    UC_X86_INS_MULPS,
    UC_X86_INS_MULSD,
    UC_X86_INS_MULSS,
    UC_X86_INS_MULX,
    UC_X86_INS_FMUL,
    UC_X86_INS_FIMUL,
    UC_X86_INS_FMULP,
    UC_X86_INS_MWAIT,
    UC_X86_INS_NEG,
    UC_X86_INS_NOP,
    UC_X86_INS_NOT,
    UC_X86_INS_OUT,
    UC_X86_INS_OUTSB,
    UC_X86_INS_OUTSD,
    UC_X86_INS_OUTSW,
    UC_X86_INS_PACKUSDW,
    UC_X86_INS_PAUSE,
    UC_X86_INS_PAVGUSB,
    UC_X86_INS_PBLENDVB,
    UC_X86_INS_PBLENDW,
    UC_X86_INS_PCLMULQDQ,
    UC_X86_INS_PCMPEQQ,
    UC_X86_INS_PCMPESTRI,
    UC_X86_INS_PCMPESTRM,
    UC_X86_INS_PCMPGTQ,
    UC_X86_INS_PCMPISTRI,
    UC_X86_INS_PCMPISTRM,
    UC_X86_INS_PCOMMIT,
    UC_X86_INS_PDEP,
    UC_X86_INS_PEXT,
    UC_X86_INS_PEXTRB,
    UC_X86_INS_PEXTRD,
    UC_X86_INS_PEXTRQ,
    UC_X86_INS_PF2ID,
    UC_X86_INS_PF2IW,
    UC_X86_INS_PFACC,
    UC_X86_INS_PFADD,
    UC_X86_INS_PFCMPEQ,
    UC_X86_INS_PFCMPGE,
    UC_X86_INS_PFCMPGT,
    UC_X86_INS_PFMAX,
    UC_X86_INS_PFMIN,
    UC_X86_INS_PFMUL,
    UC_X86_INS_PFNACC,
    UC_X86_INS_PFPNACC,
    UC_X86_INS_PFRCPIT1,
    UC_X86_INS_PFRCPIT2,
    UC_X86_INS_PFRCP,
    UC_X86_INS_PFRSQIT1,
    UC_X86_INS_PFRSQRT,
    UC_X86_INS_PFSUBR,
    UC_X86_INS_PFSUB,
    UC_X86_INS_PHMINPOSUW,
    UC_X86_INS_PI2FD,
    UC_X86_INS_PI2FW,
    UC_X86_INS_PINSRB,
    UC_X86_INS_PINSRD,
    UC_X86_INS_PINSRQ,
    UC_X86_INS_PMAXSB,
    UC_X86_INS_PMAXSD,
    UC_X86_INS_PMAXUD,
    UC_X86_INS_PMAXUW,
    UC_X86_INS_PMINSB,
    UC_X86_INS_PMINSD,
    UC_X86_INS_PMINUD,
    UC_X86_INS_PMINUW,
    UC_X86_INS_PMOVSXBD,
    UC_X86_INS_PMOVSXBQ,
    UC_X86_INS_PMOVSXBW,
    UC_X86_INS_PMOVSXDQ,
    UC_X86_INS_PMOVSXWD,
    UC_X86_INS_PMOVSXWQ,
    UC_X86_INS_PMOVZXBD,
    UC_X86_INS_PMOVZXBQ,
    UC_X86_INS_PMOVZXBW,
    UC_X86_INS_PMOVZXDQ,
    UC_X86_INS_PMOVZXWD,
    UC_X86_INS_PMOVZXWQ,
    UC_X86_INS_PMULDQ,
    UC_X86_INS_PMULHRW,
    UC_X86_INS_PMULLD,
    UC_X86_INS_POP,
    UC_X86_INS_POPAW,
    UC_X86_INS_POPAL,
    UC_X86_INS_POPCNT,
    UC_X86_INS_POPF,
    UC_X86_INS_POPFD,
    UC_X86_INS_POPFQ,
    UC_X86_INS_PREFETCH,
    UC_X86_INS_PREFETCHNTA,
    UC_X86_INS_PREFETCHT0,
    UC_X86_INS_PREFETCHT1,
    UC_X86_INS_PREFETCHT2,
    UC_X86_INS_PREFETCHW,
    UC_X86_INS_PSHUFD,
    UC_X86_INS_PSHUFHW,
    UC_X86_INS_PSHUFLW,
    UC_X86_INS_PSLLDQ,
    UC_X86_INS_PSRLDQ,
    UC_X86_INS_PSWAPD,
    UC_X86_INS_PTEST,
    UC_X86_INS_PUNPCKHQDQ,
    UC_X86_INS_PUNPCKLQDQ,
    UC_X86_INS_PUSH,
    UC_X86_INS_PUSHAW,
    UC_X86_INS_PUSHAL,
    UC_X86_INS_PUSHF,
    UC_X86_INS_PUSHFD,
    UC_X86_INS_PUSHFQ,
    UC_X86_INS_RCL,
    UC_X86_INS_RCPPS,
    UC_X86_INS_RCPSS,
    UC_X86_INS_RCR,
    UC_X86_INS_RDFSBASE,
    UC_X86_INS_RDGSBASE,
    UC_X86_INS_RDMSR,
    UC_X86_INS_RDPMC,
    UC_X86_INS_RDRAND,
    UC_X86_INS_RDSEED,
    UC_X86_INS_RDTSC,
    UC_X86_INS_RDTSCP,
    UC_X86_INS_ROL,
    UC_X86_INS_ROR,
    UC_X86_INS_RORX,
    UC_X86_INS_ROUNDPD,
    UC_X86_INS_ROUNDPS,
    UC_X86_INS_ROUNDSD,
    UC_X86_INS_ROUNDSS,
    UC_X86_INS_RSM,
    UC_X86_INS_RSQRTPS,
    UC_X86_INS_RSQRTSS,
    UC_X86_INS_SAHF,
    UC_X86_INS_SAL,
    UC_X86_INS_SALC,
    UC_X86_INS_SAR,
    UC_X86_INS_SARX,
    UC_X86_INS_SBB,
    UC_X86_INS_SCASB,
    UC_X86_INS_SCASD,
    UC_X86_INS_SCASQ,
    UC_X86_INS_SCASW,
    UC_X86_INS_SETAE,
    UC_X86_INS_SETA,
    UC_X86_INS_SETBE,
    UC_X86_INS_SETB,
    UC_X86_INS_SETE,
    UC_X86_INS_SETGE,
    UC_X86_INS_SETG,
    UC_X86_INS_SETLE,
    UC_X86_INS_SETL,
    UC_X86_INS_SETNE,
    UC_X86_INS_SETNO,
    UC_X86_INS_SETNP,
    UC_X86_INS_SETNS,
    UC_X86_INS_SETO,
    UC_X86_INS_SETP,
    UC_X86_INS_SETS,
    UC_X86_INS_SFENCE,
    UC_X86_INS_SGDT,
    UC_X86_INS_SHA1MSG1,
    UC_X86_INS_SHA1MSG2,
    UC_X86_INS_SHA1NEXTE,
    UC_X86_INS_SHA1RNDS4,
    UC_X86_INS_SHA256MSG1,
    UC_X86_INS_SHA256MSG2,
    UC_X86_INS_SHA256RNDS2,
    UC_X86_INS_SHL,
    UC_X86_INS_SHLD,
    UC_X86_INS_SHLX,
    UC_X86_INS_SHR,
    UC_X86_INS_SHRD,
    UC_X86_INS_SHRX,
    UC_X86_INS_SHUFPD,
    UC_X86_INS_SHUFPS,
    UC_X86_INS_SIDT,
    UC_X86_INS_FSIN,
    UC_X86_INS_SKINIT,
    UC_X86_INS_SLDT,
    UC_X86_INS_SMSW,
    UC_X86_INS_SQRTPD,
    UC_X86_INS_SQRTPS,
    UC_X86_INS_SQRTSD,
    UC_X86_INS_SQRTSS,
    UC_X86_INS_FSQRT,
    UC_X86_INS_STAC,
    UC_X86_INS_STC,
    UC_X86_INS_STD,
    UC_X86_INS_STGI,
    UC_X86_INS_STI,
    UC_X86_INS_STMXCSR,
    UC_X86_INS_STOSB,
    UC_X86_INS_STOSD,
    UC_X86_INS_STOSQ,
    UC_X86_INS_STOSW,
    UC_X86_INS_STR,
    UC_X86_INS_FST,
    UC_X86_INS_FSTP,
    UC_X86_INS_FSTPNCE,
    UC_X86_INS_FXCH,
    UC_X86_INS_SUBPD,
    UC_X86_INS_SUBPS,
    UC_X86_INS_FSUBR,
    UC_X86_INS_FISUBR,
    UC_X86_INS_FSUBRP,
    UC_X86_INS_SUBSD,
    UC_X86_INS_SUBSS,
    UC_X86_INS_FSUB,
    UC_X86_INS_FISUB,
    UC_X86_INS_FSUBP,
    UC_X86_INS_SWAPGS,
    UC_X86_INS_SYSCALL,
    UC_X86_INS_SYSENTER,
    UC_X86_INS_SYSEXIT,
    UC_X86_INS_SYSRET,
    UC_X86_INS_T1MSKC,
    UC_X86_INS_TEST,
    UC_X86_INS_UD2,
    UC_X86_INS_FTST,
    UC_X86_INS_TZCNT,
    UC_X86_INS_TZMSK,
    UC_X86_INS_FUCOMPI,
    UC_X86_INS_FUCOMI,
    UC_X86_INS_FUCOMPP,
    UC_X86_INS_FUCOMP,
    UC_X86_INS_FUCOM,
    UC_X86_INS_UD2B,
    UC_X86_INS_UNPCKHPD,
    UC_X86_INS_UNPCKHPS,
    UC_X86_INS_UNPCKLPD,
    UC_X86_INS_UNPCKLPS,
    UC_X86_INS_VADDPD,
    UC_X86_INS_VADDPS,
    UC_X86_INS_VADDSD,
    UC_X86_INS_VADDSS,
    UC_X86_INS_VADDSUBPD,
    UC_X86_INS_VADDSUBPS,
    UC_X86_INS_VAESDECLAST,
    UC_X86_INS_VAESDEC,
    UC_X86_INS_VAESENCLAST,
    UC_X86_INS_VAESENC,
    UC_X86_INS_VAESIMC,
    UC_X86_INS_VAESKEYGENASSIST,
    UC_X86_INS_VALIGND,
    UC_X86_INS_VALIGNQ,
    UC_X86_INS_VANDNPD,
    UC_X86_INS_VANDNPS,
    UC_X86_INS_VANDPD,
    UC_X86_INS_VANDPS,
    UC_X86_INS_VBLENDMPD,
    UC_X86_INS_VBLENDMPS,
    UC_X86_INS_VBLENDPD,
    UC_X86_INS_VBLENDPS,
    UC_X86_INS_VBLENDVPD,
    UC_X86_INS_VBLENDVPS,
    UC_X86_INS_VBROADCASTF128,
    UC_X86_INS_VBROADCASTI32X4,
    UC_X86_INS_VBROADCASTI64X4,
    UC_X86_INS_VBROADCASTSD,
    UC_X86_INS_VBROADCASTSS,
    UC_X86_INS_VCMPPD,
    UC_X86_INS_VCMPPS,
    UC_X86_INS_VCMPSD,
    UC_X86_INS_VCMPSS,
    UC_X86_INS_VCOMPRESSPD,
    UC_X86_INS_VCOMPRESSPS,
    UC_X86_INS_VCVTDQ2PD,
    UC_X86_INS_VCVTDQ2PS,
    UC_X86_INS_VCVTPD2DQX,
    UC_X86_INS_VCVTPD2DQ,
    UC_X86_INS_VCVTPD2PSX,
    UC_X86_INS_VCVTPD2PS,
    UC_X86_INS_VCVTPD2UDQ,
    UC_X86_INS_VCVTPH2PS,
    UC_X86_INS_VCVTPS2DQ,
    UC_X86_INS_VCVTPS2PD,
    UC_X86_INS_VCVTPS2PH,
    UC_X86_INS_VCVTPS2UDQ,
    UC_X86_INS_VCVTSD2SI,
    UC_X86_INS_VCVTSD2USI,
    UC_X86_INS_VCVTSS2SI,
    UC_X86_INS_VCVTSS2USI,
    UC_X86_INS_VCVTTPD2DQX,
    UC_X86_INS_VCVTTPD2DQ,
    UC_X86_INS_VCVTTPD2UDQ,
    UC_X86_INS_VCVTTPS2DQ,
    UC_X86_INS_VCVTTPS2UDQ,
    UC_X86_INS_VCVTUDQ2PD,
    UC_X86_INS_VCVTUDQ2PS,
    UC_X86_INS_VDIVPD,
    UC_X86_INS_VDIVPS,
    UC_X86_INS_VDIVSD,
    UC_X86_INS_VDIVSS,
    UC_X86_INS_VDPPD,
    UC_X86_INS_VDPPS,
    UC_X86_INS_VERR,
    UC_X86_INS_VERW,
    UC_X86_INS_VEXP2PD,
    UC_X86_INS_VEXP2PS,
    UC_X86_INS_VEXPANDPD,
    UC_X86_INS_VEXPANDPS,
    UC_X86_INS_VEXTRACTF128,
    UC_X86_INS_VEXTRACTF32X4,
    UC_X86_INS_VEXTRACTF64X4,
    UC_X86_INS_VEXTRACTI128,
    UC_X86_INS_VEXTRACTI32X4,
    UC_X86_INS_VEXTRACTI64X4,
    UC_X86_INS_VEXTRACTPS,
    UC_X86_INS_VFMADD132PD,
    UC_X86_INS_VFMADD132PS,
    UC_X86_INS_VFMADDPD,
    UC_X86_INS_VFMADD213PD,
    UC_X86_INS_VFMADD231PD,
    UC_X86_INS_VFMADDPS,
    UC_X86_INS_VFMADD213PS,
    UC_X86_INS_VFMADD231PS,
    UC_X86_INS_VFMADDSD,
    UC_X86_INS_VFMADD213SD,
    UC_X86_INS_VFMADD132SD,
    UC_X86_INS_VFMADD231SD,
    UC_X86_INS_VFMADDSS,
    UC_X86_INS_VFMADD213SS,
    UC_X86_INS_VFMADD132SS,
    UC_X86_INS_VFMADD231SS,
    UC_X86_INS_VFMADDSUB132PD,
    UC_X86_INS_VFMADDSUB132PS,
    UC_X86_INS_VFMADDSUBPD,
    UC_X86_INS_VFMADDSUB213PD,
    UC_X86_INS_VFMADDSUB231PD,
    UC_X86_INS_VFMADDSUBPS,
    UC_X86_INS_VFMADDSUB213PS,
    UC_X86_INS_VFMADDSUB231PS,
    UC_X86_INS_VFMSUB132PD,
    UC_X86_INS_VFMSUB132PS,
    UC_X86_INS_VFMSUBADD132PD,
    UC_X86_INS_VFMSUBADD132PS,
    UC_X86_INS_VFMSUBADDPD,
    UC_X86_INS_VFMSUBADD213PD,
    UC_X86_INS_VFMSUBADD231PD,
    UC_X86_INS_VFMSUBADDPS,
    UC_X86_INS_VFMSUBADD213PS,
    UC_X86_INS_VFMSUBADD231PS,
    UC_X86_INS_VFMSUBPD,
    UC_X86_INS_VFMSUB213PD,
    UC_X86_INS_VFMSUB231PD,
    UC_X86_INS_VFMSUBPS,
    UC_X86_INS_VFMSUB213PS,
    UC_X86_INS_VFMSUB231PS,
    UC_X86_INS_VFMSUBSD,
    UC_X86_INS_VFMSUB213SD,
    UC_X86_INS_VFMSUB132SD,
    UC_X86_INS_VFMSUB231SD,
    UC_X86_INS_VFMSUBSS,
    UC_X86_INS_VFMSUB213SS,
    UC_X86_INS_VFMSUB132SS,
    UC_X86_INS_VFMSUB231SS,
    UC_X86_INS_VFNMADD132PD,
    UC_X86_INS_VFNMADD132PS,
    UC_X86_INS_VFNMADDPD,
    UC_X86_INS_VFNMADD213PD,
    UC_X86_INS_VFNMADD231PD,
    UC_X86_INS_VFNMADDPS,
    UC_X86_INS_VFNMADD213PS,
    UC_X86_INS_VFNMADD231PS,
    UC_X86_INS_VFNMADDSD,
    UC_X86_INS_VFNMADD213SD,
    UC_X86_INS_VFNMADD132SD,
    UC_X86_INS_VFNMADD231SD,
    UC_X86_INS_VFNMADDSS,
    UC_X86_INS_VFNMADD213SS,
    UC_X86_INS_VFNMADD132SS,
    UC_X86_INS_VFNMADD231SS,
    UC_X86_INS_VFNMSUB132PD,
    UC_X86_INS_VFNMSUB132PS,
    UC_X86_INS_VFNMSUBPD,
    UC_X86_INS_VFNMSUB213PD,
    UC_X86_INS_VFNMSUB231PD,
    UC_X86_INS_VFNMSUBPS,
    UC_X86_INS_VFNMSUB213PS,
    UC_X86_INS_VFNMSUB231PS,
    UC_X86_INS_VFNMSUBSD,
    UC_X86_INS_VFNMSUB213SD,
    UC_X86_INS_VFNMSUB132SD,
    UC_X86_INS_VFNMSUB231SD,
    UC_X86_INS_VFNMSUBSS,
    UC_X86_INS_VFNMSUB213SS,
    UC_X86_INS_VFNMSUB132SS,
    UC_X86_INS_VFNMSUB231SS,
    UC_X86_INS_VFRCZPD,
    UC_X86_INS_VFRCZPS,
    UC_X86_INS_VFRCZSD,
    UC_X86_INS_VFRCZSS,
    UC_X86_INS_VORPD,
    UC_X86_INS_VORPS,
    UC_X86_INS_VXORPD,
    UC_X86_INS_VXORPS,
    UC_X86_INS_VGATHERDPD,
    UC_X86_INS_VGATHERDPS,
    UC_X86_INS_VGATHERPF0DPD,
    UC_X86_INS_VGATHERPF0DPS,
    UC_X86_INS_VGATHERPF0QPD,
    UC_X86_INS_VGATHERPF0QPS,
    UC_X86_INS_VGATHERPF1DPD,
    UC_X86_INS_VGATHERPF1DPS,
    UC_X86_INS_VGATHERPF1QPD,
    UC_X86_INS_VGATHERPF1QPS,
    UC_X86_INS_VGATHERQPD,
    UC_X86_INS_VGATHERQPS,
    UC_X86_INS_VHADDPD,
    UC_X86_INS_VHADDPS,
    UC_X86_INS_VHSUBPD,
    UC_X86_INS_VHSUBPS,
    UC_X86_INS_VINSERTF128,
    UC_X86_INS_VINSERTF32X4,
    UC_X86_INS_VINSERTF32X8,
    UC_X86_INS_VINSERTF64X2,
    UC_X86_INS_VINSERTF64X4,
    UC_X86_INS_VINSERTI128,
    UC_X86_INS_VINSERTI32X4,
    UC_X86_INS_VINSERTI32X8,
    UC_X86_INS_VINSERTI64X2,
    UC_X86_INS_VINSERTI64X4,
    UC_X86_INS_VINSERTPS,
    UC_X86_INS_VLDDQU,
    UC_X86_INS_VLDMXCSR,
    UC_X86_INS_VMASKMOVDQU,
    UC_X86_INS_VMASKMOVPD,
    UC_X86_INS_VMASKMOVPS,
    UC_X86_INS_VMAXPD,
    UC_X86_INS_VMAXPS,
    UC_X86_INS_VMAXSD,
    UC_X86_INS_VMAXSS,
    UC_X86_INS_VMCALL,
    UC_X86_INS_VMCLEAR,
    UC_X86_INS_VMFUNC,
    UC_X86_INS_VMINPD,
    UC_X86_INS_VMINPS,
    UC_X86_INS_VMINSD,
    UC_X86_INS_VMINSS,
    UC_X86_INS_VMLAUNCH,
    UC_X86_INS_VMLOAD,
    UC_X86_INS_VMMCALL,
    UC_X86_INS_VMOVQ,
    UC_X86_INS_VMOVDDUP,
    UC_X86_INS_VMOVD,
    UC_X86_INS_VMOVDQA32,
    UC_X86_INS_VMOVDQA64,
    UC_X86_INS_VMOVDQA,
    UC_X86_INS_VMOVDQU16,
    UC_X86_INS_VMOVDQU32,
    UC_X86_INS_VMOVDQU64,
    UC_X86_INS_VMOVDQU8,
    UC_X86_INS_VMOVDQU,
    UC_X86_INS_VMOVHLPS,
    UC_X86_INS_VMOVHPD,
    UC_X86_INS_VMOVHPS,
    UC_X86_INS_VMOVLHPS,
    UC_X86_INS_VMOVLPD,
    UC_X86_INS_VMOVLPS,
    UC_X86_INS_VMOVMSKPD,
    UC_X86_INS_VMOVMSKPS,
    UC_X86_INS_VMOVNTDQA,
    UC_X86_INS_VMOVNTDQ,
    UC_X86_INS_VMOVNTPD,
    UC_X86_INS_VMOVNTPS,
    UC_X86_INS_VMOVSD,
    UC_X86_INS_VMOVSHDUP,
    UC_X86_INS_VMOVSLDUP,
    UC_X86_INS_VMOVSS,
    UC_X86_INS_VMOVUPD,
    UC_X86_INS_VMOVUPS,
    UC_X86_INS_VMPSADBW,
    UC_X86_INS_VMPTRLD,
    UC_X86_INS_VMPTRST,
    UC_X86_INS_VMREAD,
    UC_X86_INS_VMRESUME,
    UC_X86_INS_VMRUN,
    UC_X86_INS_VMSAVE,
    UC_X86_INS_VMULPD,
    UC_X86_INS_VMULPS,
    UC_X86_INS_VMULSD,
    UC_X86_INS_VMULSS,
    UC_X86_INS_VMWRITE,
    UC_X86_INS_VMXOFF,
    UC_X86_INS_VMXON,
    UC_X86_INS_VPABSB,
    UC_X86_INS_VPABSD,
    UC_X86_INS_VPABSQ,
    UC_X86_INS_VPABSW,
    UC_X86_INS_VPACKSSDW,
    UC_X86_INS_VPACKSSWB,
    UC_X86_INS_VPACKUSDW,
    UC_X86_INS_VPACKUSWB,
    UC_X86_INS_VPADDB,
    UC_X86_INS_VPADDD,
    UC_X86_INS_VPADDQ,
    UC_X86_INS_VPADDSB,
    UC_X86_INS_VPADDSW,
    UC_X86_INS_VPADDUSB,
    UC_X86_INS_VPADDUSW,
    UC_X86_INS_VPADDW,
    UC_X86_INS_VPALIGNR,
    UC_X86_INS_VPANDD,
    UC_X86_INS_VPANDND,
    UC_X86_INS_VPANDNQ,
    UC_X86_INS_VPANDN,
    UC_X86_INS_VPANDQ,
    UC_X86_INS_VPAND,
    UC_X86_INS_VPAVGB,
    UC_X86_INS_VPAVGW,
    UC_X86_INS_VPBLENDD,
    UC_X86_INS_VPBLENDMB,
    UC_X86_INS_VPBLENDMD,
    UC_X86_INS_VPBLENDMQ,
    UC_X86_INS_VPBLENDMW,
    UC_X86_INS_VPBLENDVB,
    UC_X86_INS_VPBLENDW,
    UC_X86_INS_VPBROADCASTB,
    UC_X86_INS_VPBROADCASTD,
    UC_X86_INS_VPBROADCASTMB2Q,
    UC_X86_INS_VPBROADCASTMW2D,
    UC_X86_INS_VPBROADCASTQ,
    UC_X86_INS_VPBROADCASTW,
    UC_X86_INS_VPCLMULQDQ,
    UC_X86_INS_VPCMOV,
    UC_X86_INS_VPCMPB,
    UC_X86_INS_VPCMPD,
    UC_X86_INS_VPCMPEQB,
    UC_X86_INS_VPCMPEQD,
    UC_X86_INS_VPCMPEQQ,
    UC_X86_INS_VPCMPEQW,
    UC_X86_INS_VPCMPESTRI,
    UC_X86_INS_VPCMPESTRM,
    UC_X86_INS_VPCMPGTB,
    UC_X86_INS_VPCMPGTD,
    UC_X86_INS_VPCMPGTQ,
    UC_X86_INS_VPCMPGTW,
    UC_X86_INS_VPCMPISTRI,
    UC_X86_INS_VPCMPISTRM,
    UC_X86_INS_VPCMPQ,
    UC_X86_INS_VPCMPUB,
    UC_X86_INS_VPCMPUD,
    UC_X86_INS_VPCMPUQ,
    UC_X86_INS_VPCMPUW,
    UC_X86_INS_VPCMPW,
    UC_X86_INS_VPCOMB,
    UC_X86_INS_VPCOMD,
    UC_X86_INS_VPCOMPRESSD,
    UC_X86_INS_VPCOMPRESSQ,
    UC_X86_INS_VPCOMQ,
    UC_X86_INS_VPCOMUB,
    UC_X86_INS_VPCOMUD,
    UC_X86_INS_VPCOMUQ,
    UC_X86_INS_VPCOMUW,
    UC_X86_INS_VPCOMW,
    UC_X86_INS_VPCONFLICTD,
    UC_X86_INS_VPCONFLICTQ,
    UC_X86_INS_VPERM2F128,
    UC_X86_INS_VPERM2I128,
    UC_X86_INS_VPERMD,
    UC_X86_INS_VPERMI2D,
    UC_X86_INS_VPERMI2PD,
    UC_X86_INS_VPERMI2PS,
    UC_X86_INS_VPERMI2Q,
    UC_X86_INS_VPERMIL2PD,
    UC_X86_INS_VPERMIL2PS,
    UC_X86_INS_VPERMILPD,
    UC_X86_INS_VPERMILPS,
    UC_X86_INS_VPERMPD,
    UC_X86_INS_VPERMPS,
    UC_X86_INS_VPERMQ,
    UC_X86_INS_VPERMT2D,
    UC_X86_INS_VPERMT2PD,
    UC_X86_INS_VPERMT2PS,
    UC_X86_INS_VPERMT2Q,
    UC_X86_INS_VPEXPANDD,
    UC_X86_INS_VPEXPANDQ,
    UC_X86_INS_VPEXTRB,
    UC_X86_INS_VPEXTRD,
    UC_X86_INS_VPEXTRQ,
    UC_X86_INS_VPEXTRW,
    UC_X86_INS_VPGATHERDD,
    UC_X86_INS_VPGATHERDQ,
    UC_X86_INS_VPGATHERQD,
    UC_X86_INS_VPGATHERQQ,
    UC_X86_INS_VPHADDBD,
    UC_X86_INS_VPHADDBQ,
    UC_X86_INS_VPHADDBW,
    UC_X86_INS_VPHADDDQ,
    UC_X86_INS_VPHADDD,
    UC_X86_INS_VPHADDSW,
    UC_X86_INS_VPHADDUBD,
    UC_X86_INS_VPHADDUBQ,
    UC_X86_INS_VPHADDUBW,
    UC_X86_INS_VPHADDUDQ,
    UC_X86_INS_VPHADDUWD,
    UC_X86_INS_VPHADDUWQ,
    UC_X86_INS_VPHADDWD,
    UC_X86_INS_VPHADDWQ,
    UC_X86_INS_VPHADDW,
    UC_X86_INS_VPHMINPOSUW,
    UC_X86_INS_VPHSUBBW,
    UC_X86_INS_VPHSUBDQ,
    UC_X86_INS_VPHSUBD,
    UC_X86_INS_VPHSUBSW,
    UC_X86_INS_VPHSUBWD,
    UC_X86_INS_VPHSUBW,
    UC_X86_INS_VPINSRB,
    UC_X86_INS_VPINSRD,
    UC_X86_INS_VPINSRQ,
    UC_X86_INS_VPINSRW,
    UC_X86_INS_VPLZCNTD,
    UC_X86_INS_VPLZCNTQ,
    UC_X86_INS_VPMACSDD,
    UC_X86_INS_VPMACSDQH,
    UC_X86_INS_VPMACSDQL,
    UC_X86_INS_VPMACSSDD,
    UC_X86_INS_VPMACSSDQH,
    UC_X86_INS_VPMACSSDQL,
    UC_X86_INS_VPMACSSWD,
    UC_X86_INS_VPMACSSWW,
    UC_X86_INS_VPMACSWD,
    UC_X86_INS_VPMACSWW,
    UC_X86_INS_VPMADCSSWD,
    UC_X86_INS_VPMADCSWD,
    UC_X86_INS_VPMADDUBSW,
    UC_X86_INS_VPMADDWD,
    UC_X86_INS_VPMASKMOVD,
    UC_X86_INS_VPMASKMOVQ,
    UC_X86_INS_VPMAXSB,
    UC_X86_INS_VPMAXSD,
    UC_X86_INS_VPMAXSQ,
    UC_X86_INS_VPMAXSW,
    UC_X86_INS_VPMAXUB,
    UC_X86_INS_VPMAXUD,
    UC_X86_INS_VPMAXUQ,
    UC_X86_INS_VPMAXUW,
    UC_X86_INS_VPMINSB,
    UC_X86_INS_VPMINSD,
    UC_X86_INS_VPMINSQ,
    UC_X86_INS_VPMINSW,
    UC_X86_INS_VPMINUB,
    UC_X86_INS_VPMINUD,
    UC_X86_INS_VPMINUQ,
    UC_X86_INS_VPMINUW,
    UC_X86_INS_VPMOVDB,
    UC_X86_INS_VPMOVDW,
    UC_X86_INS_VPMOVM2B,
    UC_X86_INS_VPMOVM2D,
    UC_X86_INS_VPMOVM2Q,
    UC_X86_INS_VPMOVM2W,
    UC_X86_INS_VPMOVMSKB,
    UC_X86_INS_VPMOVQB,
    UC_X86_INS_VPMOVQD,
    UC_X86_INS_VPMOVQW,
    UC_X86_INS_VPMOVSDB,
    UC_X86_INS_VPMOVSDW,
    UC_X86_INS_VPMOVSQB,
    UC_X86_INS_VPMOVSQD,
    UC_X86_INS_VPMOVSQW,
    UC_X86_INS_VPMOVSXBD,
    UC_X86_INS_VPMOVSXBQ,
    UC_X86_INS_VPMOVSXBW,
    UC_X86_INS_VPMOVSXDQ,
    UC_X86_INS_VPMOVSXWD,
    UC_X86_INS_VPMOVSXWQ,
    UC_X86_INS_VPMOVUSDB,
    UC_X86_INS_VPMOVUSDW,
    UC_X86_INS_VPMOVUSQB,
    UC_X86_INS_VPMOVUSQD,
    UC_X86_INS_VPMOVUSQW,
    UC_X86_INS_VPMOVZXBD,
    UC_X86_INS_VPMOVZXBQ,
    UC_X86_INS_VPMOVZXBW,
    UC_X86_INS_VPMOVZXDQ,
    UC_X86_INS_VPMOVZXWD,
    UC_X86_INS_VPMOVZXWQ,
    UC_X86_INS_VPMULDQ,
    UC_X86_INS_VPMULHRSW,
    UC_X86_INS_VPMULHUW,
    UC_X86_INS_VPMULHW,
    UC_X86_INS_VPMULLD,
    UC_X86_INS_VPMULLQ,
    UC_X86_INS_VPMULLW,
    UC_X86_INS_VPMULUDQ,
    UC_X86_INS_VPORD,
    UC_X86_INS_VPORQ,
    UC_X86_INS_VPOR,
    UC_X86_INS_VPPERM,
    UC_X86_INS_VPROTB,
    UC_X86_INS_VPROTD,
    UC_X86_INS_VPROTQ,
    UC_X86_INS_VPROTW,
    UC_X86_INS_VPSADBW,
    UC_X86_INS_VPSCATTERDD,
    UC_X86_INS_VPSCATTERDQ,
    UC_X86_INS_VPSCATTERQD,
    UC_X86_INS_VPSCATTERQQ,
    UC_X86_INS_VPSHAB,
    UC_X86_INS_VPSHAD,
    UC_X86_INS_VPSHAQ,
    UC_X86_INS_VPSHAW,
    UC_X86_INS_VPSHLB,
    UC_X86_INS_VPSHLD,
    UC_X86_INS_VPSHLQ,
    UC_X86_INS_VPSHLW,
    UC_X86_INS_VPSHUFB,
    UC_X86_INS_VPSHUFD,
    UC_X86_INS_VPSHUFHW,
    UC_X86_INS_VPSHUFLW,
    UC_X86_INS_VPSIGNB,
    UC_X86_INS_VPSIGND,
    UC_X86_INS_VPSIGNW,
    UC_X86_INS_VPSLLDQ,
    UC_X86_INS_VPSLLD,
    UC_X86_INS_VPSLLQ,
    UC_X86_INS_VPSLLVD,
    UC_X86_INS_VPSLLVQ,
    UC_X86_INS_VPSLLW,
    UC_X86_INS_VPSRAD,
    UC_X86_INS_VPSRAQ,
    UC_X86_INS_VPSRAVD,
    UC_X86_INS_VPSRAVQ,
    UC_X86_INS_VPSRAW,
    UC_X86_INS_VPSRLDQ,
    UC_X86_INS_VPSRLD,
    UC_X86_INS_VPSRLQ,
    UC_X86_INS_VPSRLVD,
    UC_X86_INS_VPSRLVQ,
    UC_X86_INS_VPSRLW,
    UC_X86_INS_VPSUBB,
    UC_X86_INS_VPSUBD,
    UC_X86_INS_VPSUBQ,
    UC_X86_INS_VPSUBSB,
    UC_X86_INS_VPSUBSW,
    UC_X86_INS_VPSUBUSB,
    UC_X86_INS_VPSUBUSW,
    UC_X86_INS_VPSUBW,
    UC_X86_INS_VPTESTMD,
    UC_X86_INS_VPTESTMQ,
    UC_X86_INS_VPTESTNMD,
    UC_X86_INS_VPTESTNMQ,
    UC_X86_INS_VPTEST,
    UC_X86_INS_VPUNPCKHBW,
    UC_X86_INS_VPUNPCKHDQ,
    UC_X86_INS_VPUNPCKHQDQ,
    UC_X86_INS_VPUNPCKHWD,
    UC_X86_INS_VPUNPCKLBW,
    UC_X86_INS_VPUNPCKLDQ,
    UC_X86_INS_VPUNPCKLQDQ,
    UC_X86_INS_VPUNPCKLWD,
    UC_X86_INS_VPXORD,
    UC_X86_INS_VPXORQ,
    UC_X86_INS_VPXOR,
    UC_X86_INS_VRCP14PD,
    UC_X86_INS_VRCP14PS,
    UC_X86_INS_VRCP14SD,
    UC_X86_INS_VRCP14SS,
    UC_X86_INS_VRCP28PD,
    UC_X86_INS_VRCP28PS,
    UC_X86_INS_VRCP28SD,
    UC_X86_INS_VRCP28SS,
    UC_X86_INS_VRCPPS,
    UC_X86_INS_VRCPSS,
    UC_X86_INS_VRNDSCALEPD,
    UC_X86_INS_VRNDSCALEPS,
    UC_X86_INS_VRNDSCALESD,
    UC_X86_INS_VRNDSCALESS,
    UC_X86_INS_VROUNDPD,
    UC_X86_INS_VROUNDPS,
    UC_X86_INS_VROUNDSD,
    UC_X86_INS_VROUNDSS,
    UC_X86_INS_VRSQRT14PD,
    UC_X86_INS_VRSQRT14PS,
    UC_X86_INS_VRSQRT14SD,
    UC_X86_INS_VRSQRT14SS,
    UC_X86_INS_VRSQRT28PD,
    UC_X86_INS_VRSQRT28PS,
    UC_X86_INS_VRSQRT28SD,
    UC_X86_INS_VRSQRT28SS,
    UC_X86_INS_VRSQRTPS,
    UC_X86_INS_VRSQRTSS,
    UC_X86_INS_VSCATTERDPD,
    UC_X86_INS_VSCATTERDPS,
    UC_X86_INS_VSCATTERPF0DPD,
    UC_X86_INS_VSCATTERPF0DPS,
    UC_X86_INS_VSCATTERPF0QPD,
    UC_X86_INS_VSCATTERPF0QPS,
    UC_X86_INS_VSCATTERPF1DPD,
    UC_X86_INS_VSCATTERPF1DPS,
    UC_X86_INS_VSCATTERPF1QPD,
    UC_X86_INS_VSCATTERPF1QPS,
    UC_X86_INS_VSCATTERQPD,
    UC_X86_INS_VSCATTERQPS,
    UC_X86_INS_VSHUFPD,
    UC_X86_INS_VSHUFPS,
    UC_X86_INS_VSQRTPD,
    UC_X86_INS_VSQRTPS,
    UC_X86_INS_VSQRTSD,
    UC_X86_INS_VSQRTSS,
    UC_X86_INS_VSTMXCSR,
    UC_X86_INS_VSUBPD,
    UC_X86_INS_VSUBPS,
    UC_X86_INS_VSUBSD,
    UC_X86_INS_VSUBSS,
    UC_X86_INS_VTESTPD,
    UC_X86_INS_VTESTPS,
    UC_X86_INS_VUNPCKHPD,
    UC_X86_INS_VUNPCKHPS,
    UC_X86_INS_VUNPCKLPD,
    UC_X86_INS_VUNPCKLPS,
    UC_X86_INS_VZEROALL,
    UC_X86_INS_VZEROUPPER,
    UC_X86_INS_WAIT,
    UC_X86_INS_WBINVD,
    UC_X86_INS_WRFSBASE,
    UC_X86_INS_WRGSBASE,
    UC_X86_INS_WRMSR,
    UC_X86_INS_XABORT,
    UC_X86_INS_XACQUIRE,
    UC_X86_INS_XBEGIN,
    UC_X86_INS_XCHG,
    UC_X86_INS_XCRYPTCBC,
    UC_X86_INS_XCRYPTCFB,
    UC_X86_INS_XCRYPTCTR,
    UC_X86_INS_XCRYPTECB,
    UC_X86_INS_XCRYPTOFB,
    UC_X86_INS_XEND,
    UC_X86_INS_XGETBV,
    UC_X86_INS_XLATB,
    UC_X86_INS_XRELEASE,
    UC_X86_INS_XRSTOR,
    UC_X86_INS_XRSTOR64,
    UC_X86_INS_XRSTORS,
    UC_X86_INS_XRSTORS64,
    UC_X86_INS_XSAVE,
    UC_X86_INS_XSAVE64,
    UC_X86_INS_XSAVEC,
    UC_X86_INS_XSAVEC64,
    UC_X86_INS_XSAVEOPT,
    UC_X86_INS_XSAVEOPT64,
    UC_X86_INS_XSAVES,
    UC_X86_INS_XSAVES64,
    UC_X86_INS_XSETBV,
    UC_X86_INS_XSHA1,
    UC_X86_INS_XSHA256,
    UC_X86_INS_XSTORE,
    UC_X86_INS_XTEST,
    UC_X86_INS_FDISI8087_NOP,
    UC_X86_INS_FENI8087_NOP,

    UC_X86_INS_ENDING, // mark the end of the list of insn
} uc_x86_insn;

#ifdef __cplusplus
}
#endif

#endif
